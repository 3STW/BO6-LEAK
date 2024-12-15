#pragma once
#include "mem2.h"
#include "../shared/xorstr/xorstr.hpp"
#include "offsets.h"
void memory::memcopy(BYTE* dst, BYTE* src, size_t size) {
    DWORD oldprotect; //variable to hold protection
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect); //make memory read/writeable and save the old protection
    memcpy(dst, src, size); //typical memcopy
    VirtualProtect(dst, size, oldprotect, &oldprotect); //restore our old protection
}

uintptr_t memory::modinfo(info param) {
    MODULEINFO moduleInfo{};
    if (!GetModuleInformation((HANDLE)-1, GetModuleHandle(NULL), &moduleInfo, sizeof(MODULEINFO)) || !moduleInfo.lpBaseOfDll) {
        std::cout << XOR("Couldnt GetModuleInformation") << std::endl;
        return 0;
    }
    switch (param)
    {
    case 1:
        return (uintptr_t)moduleInfo.lpBaseOfDll; //returns module base
        break;
    case 2:
        return (uintptr_t)moduleInfo.SizeOfImage; //return image size
        break;
    }
}

uintptr_t memory::find_ida_sig(const char* mod, const char* sig)
{
    /// Credits: MarkHC, although slightly modified by me and also documented

    static auto pattern_to_byte = [](const char* pattern)
    {
        /// Prerequisites
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + strlen(pattern);

        /// Convert signature into corresponding bytes
        for (auto current = start; current < end; ++current)
        {
            /// Is current byte a wildcard? Simply ignore that that byte later
            if (*current == '?')
            {
                ++current;

                /// Check if following byte is also a wildcard
                if (*current == '?')
                    ++current;

                /// Dummy byte
                bytes.push_back(-1);
            }
            else
            {
                /// Convert character to byte on hexadecimal base
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    const auto module_handle = GetModuleHandleA(mod);
    if (!module_handle)
        return {};

    /// Get module information to search in the given module
    MODULEINFO module_info;
    GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(module_handle), &module_info, sizeof(MODULEINFO));

    /// The region where we will search for the byte sequence
    const auto image_size = module_info.SizeOfImage;

    /// Check if the image is faulty
    if (!image_size)
        return {};

    /// Convert IDA-Style signature to a byte sequence
    auto pattern_bytes = pattern_to_byte(sig);

    const auto image_bytes = reinterpret_cast<byte*>(module_handle);

    const auto signature_size = pattern_bytes.size();
    const auto signature_bytes = pattern_bytes.data();


    /// Loop through all pages and check the accessable pages
    auto page_information = MEMORY_BASIC_INFORMATION{};
    for (auto current_page = reinterpret_cast<byte*>(module_handle); current_page < reinterpret_cast<byte*>(module_handle + image_size); current_page = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(page_information.BaseAddress) + page_information.RegionSize))
    {
        auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

        if (page_information.Protect != PAGE_EXECUTE_READWRITE)
            continue;

        /// Now loop through all bytes and check if the byte sequence matches
        for (auto i = reinterpret_cast<uintptr_t>(page_information.BaseAddress) - reinterpret_cast<uintptr_t>(module_handle); i < page_information.RegionSize; ++i)
        {
            auto byte_sequence_found = true;

            if (i + signature_size == page_information.RegionSize)
            {
                auto status = VirtualQuery(reinterpret_cast<LPCVOID>(current_page), reinterpret_cast<PMEMORY_BASIC_INFORMATION>(&page_information), sizeof(MEMORY_BASIC_INFORMATION));

                if (page_information.Protect != PAGE_EXECUTE_READ)
                    break;
            }

            /// Go through all bytes from the signature and check if it matches
            for (auto j = 0ul; j < signature_size; ++j)
            {
                if (image_bytes[i + j] != signature_bytes[j] /// Bytes don't match
                    && signature_bytes[j] != -1) /// Byte isn't a wildcard either, WHAT THE HECK
                {
                    byte_sequence_found = false;
                    break;
                }
            }



            /// All good, now return the right address
            if (byte_sequence_found)
                return (uintptr_t(&image_bytes[i]));
        }
    }


    /// Byte sequence wasn't found
    return {};
}

uintptr_t memory::find_pattern(uintptr_t range_start, uintptr_t range_end, const char* pattern)
{
    const char* pat = pattern;
    __int64 firstMatch = NULL;
    __int64 pCur = range_start;
    __int64 region_end{};
    MEMORY_BASIC_INFORMATION mbi{};
    SIZE_T size = VirtualQuery((LPCVOID)pCur, &mbi, sizeof(mbi));

    while (sizeof(mbi) == size) {
        if (pCur >= range_end - strlen(pattern))
        {
            break;
        }
        if (!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
            pCur += mbi.RegionSize;
            continue;
        }
        region_end = pCur + mbi.RegionSize;

        if (mbi.State == MEM_COMMIT && mbi.Protect != PAGE_NOACCESS && !(mbi.Protect & PAGE_GUARD))
        {
            region_end = pCur + mbi.RegionSize;
            while (pCur < region_end)
            {
                if (!*pat)
                    return firstMatch;
                if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
                    if (!firstMatch)
                        firstMatch = pCur;
                    if (!pat[1] || !pat[2])
                        return firstMatch;
                    if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                        pat += 3;
                    else
                        pat += 2;
                }
                else {
                    if (firstMatch)
                        pCur = firstMatch;
                    pat = pattern;
                    firstMatch = 0;
                }
                pCur++;
            }
        }
    }
    return NULL;
}

void nlog(const char* str, ...) {
    va_list ap;
    HWND notepad, edit;
    char buf[256];

    va_start(ap, str);
    vsprintf_s(buf, str, ap);
    va_end(ap);
    strcat_s(buf, "");

    notepad = FindWindow(NULL, ("Untitled - Notepad"));
    if (!notepad)
        notepad = FindWindow(NULL, ("*Untitled - Notepad"));

    edit = FindWindowEx(notepad, NULL, ("EDIT"), NULL);
    SendMessageA(edit, EM_REPLACESEL, 0, (LPARAM)buf);
}

Scanner::Scanner(std::ptrdiff_t startAddr, std::ptrdiff_t endAddr, const char* pattern, const char* name, bool debug, std::ptrdiff_t offset) : name{ name }, debugflag{ debug }
{
    addr = (memory::find_pattern(startAddr, endAddr, pattern) + (offset));
}

Scanner::Scanner(const char* pattern, const char* name, std::ptrdiff_t offset, bool debug) : name{ name }, debugflag{ debug }
{

    addr = (memory::find_ida_sig(0, pattern) + (offset));

}

Scanner::Scanner(__int64 skip, __int64 search_size, const char* pattern) : _skip{ skip }
{
    addr = memory::find_pattern(searchStart, searchStart + search_size, pattern);
}

Scanner::Scanner(std::ptrdiff_t address)
{
    addr = address;
}

auto Scanner::validaddr() -> bool
{
    if (is_bad_ptr(addr))
    {
        if (debugflag)
        {


            nlog("Failed --- %s : 0\n", name);
        }
        return false;
    }
    if (is_valid_ptr(addr))
    {
        if (debugflag)
        {

            nlog("Success --- %s : 0x%x\n", name, addr - sig_offsets::base);

        }
        return true;
    }
};

auto Scanner::getaddr() -> std::ptrdiff_t {
    if (validaddr()) {
        return addr;
    }
    return NULL;
};

auto Scanner::resolve_call() -> std::ptrdiff_t {
    if (validaddr()) {
        return *(int*)(addr + 1) + addr + 5;
    }
    return NULL;
};

auto Scanner::resolve_lea() -> std::ptrdiff_t {
    if (validaddr()) {
        return *(int*)(addr + 3) + addr + 7;
    }
    return NULL;
};

//works with XOR
auto Scanner::resolve_cmp() -> std::ptrdiff_t {
    if (validaddr()) {
        return *(int*)(addr + 2) + addr + 6;
    }
    return NULL;
};

auto Scanner::vtable_call() -> std::ptrdiff_t {
    if (validaddr()) {

        return *(int*)(addr + 2) + addr + 6;
    }
    return NULL;
};

auto Scanner::resolve_mov() -> std::ptrdiff_t {
    if (validaddr()) {

        return *(int*)(addr + 3) + addr + 7;
    }
    return NULL;
}

auto Scanner::resolve_jmp() -> std::ptrdiff_t {
    if (validaddr()) {

        return *(int*)(addr + 2) + addr + 8;
    }
    return NULL;
}
auto Scanner::resolve(Opcodes op) -> std::ptrdiff_t {
    if (validaddr())
        return addr + *reinterpret_cast<int*>(addr + (op >> 8)) + (op & 0xFF);
    return NULL;
}

#include "utility.h"

#define INRANGE(x,a,b)    (x >= a && x <= b)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
#pragma section(".text")
__declspec(allocate(".text"))const unsigned char jmp_rbx_0[] = { 0xFF, 0x23 };

DWORD GetProcId(LPCSTR procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_stricmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

HMODULE GetModuleHandleSafe(LPCSTR pszModuleName)
{
    HMODULE hmModuleHandle = NULL;

    do
    {
        hmModuleHandle = GetModuleHandle(pszModuleName);
        Sleep(1);
    } while (hmModuleHandle == NULL);

    return hmModuleHandle;
}

bool MemCompare(const BYTE* bData, const BYTE* bMask, const char* szMask) {
    for (; *szMask; ++szMask, ++bData, ++bMask) {
        if (*szMask == 'x' && *bData != *bMask) {
            return false;
        }
    }
    return (*szMask == NULL);
}

void Read(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{
    ReadProcessMemory(hProcess, dst, src, size, nullptr);
}

void Write(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{
    DWORD oldprotect;
    VirtualProtectEx(hProcess, dst, size, PAGE_READWRITE, &oldprotect);
    WriteProcessMemory(hProcess, dst, src, size, nullptr);
    VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

uintptr_t PointerChain(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
    uintptr_t addr = ptr;

    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(uint64_t), NULL);
        addr += offsets[i];
    }
    return addr;
}

void Patch(BYTE* dst, BYTE* src, unsigned size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Nop(BYTE* dst, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memset(dst, 0x90, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}
uintptr_t PatternScanExCustom(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask, int index)
{
    BYTE* data = new BYTE[size];
    SIZE_T bytesRead;
    int curRead = 0;
    ReadProcessMemory(hProcess, (LPVOID)start, data, size, &bytesRead);

    for (uintptr_t i = 0; i < size; i++)
    {

        if (MemCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
            if (curRead == index)
            {
                return start + i;
            }
            curRead++;
        }


    }
    delete[] data;
    return NULL;
}
uintptr_t PatternScanEx(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask)
{
    BYTE* data = new BYTE[size];
    SIZE_T bytesRead;

    ReadProcessMemory(hProcess, (LPVOID)start, data, size, &bytesRead);

    for (uintptr_t i = 0; i < size; i++)
    {
        if (MemCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
            return start + i;
        }
    }
    delete[] data;
    return NULL;
}

uintptr_t FindOffset(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask, uintptr_t base_offset, uintptr_t pre_base_offset, uintptr_t rindex, bool addRip)
{
    auto address = PatternScanEx(hProcess, start, size, sig, mask) + rindex;
    if (!address)
        return 0;
    auto ret = pre_base_offset + *reinterpret_cast<int32_t*>(address + base_offset);

    if (addRip)
    {
        ret = ret + address;
        if (ret)
            return (ret - sig_offsets::base);
    }

    return ret;
}

DWORD  FindPattern(uintptr_t start, uintptr_t size, const char* pattern, const char* mask)
{
    DWORD patternLength = (DWORD)strlen(mask);

    for (DWORD i = 0; i < size - patternLength; i++)
    {
        bool found = true;

        for (DWORD j = 0; j < patternLength; j++)
        {
            found &= mask[j] == '?' || pattern[j] == *(char*)(start + i + j);
        }

        if (found)
            return start + i;
    }

    return 0xDEADBEEF;
}

void PatchBytes(BYTE* destination, BYTE* source, size_t size)
{
    DWORD oldProtect;
    VirtualProtect((LPVOID)destination, size, PAGE_EXECUTE_READWRITE, &oldProtect);
    memcpy(destination, source, size);
    VirtualProtect(destination, size, oldProtect, &oldProtect);
}