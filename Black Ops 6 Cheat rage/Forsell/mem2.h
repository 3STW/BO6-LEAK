#pragma once
#include "stdafx.h"
#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))

#define ENCODE(l, r) l << 8 | r
#define SCAN(name, start, size, sig, extension, debase, log) name = Scanner(start, size, sig).extension; if (debase && name > Human_Modz::base) name -= Human_Modz::base;

namespace memory
{
    enum info { modbase = 1, imagesize, };

    extern uintptr_t modinfo(info); //gets module information when needed

    extern void memcopy(BYTE* dst, BYTE* src, size_t size);
    extern uintptr_t find_ida_sig(const char* mod, const char* sig);

    extern uintptr_t find_pattern(uintptr_t range_start, uintptr_t range_end, const char* pattern);

    template<typename T> inline auto readMemory(uintptr_t ptr) noexcept -> T {
        if (is_bad_ptr(ptr)) {
            //DEBUG_INFO("Attempted to read invalid memory at {:#x}", ptr);
            return {};
        }
        return *reinterpret_cast<T*>(ptr);
    }

    template<typename T> inline auto writeMemory(uintptr_t ptr, T value) noexcept -> T {
        if (is_bad_ptr(ptr)) {
            //DEBUG_INFO("Attempted to read invalid memory at {:#x}", ptr);
            return {};
        }
        return *reinterpret_cast<T*>(ptr) = value;
    }
}
class Scanner
{
private:
    std::ptrdiff_t _skip = 0x500000;
    std::ptrdiff_t  searchStart = ((uintptr_t)GetModuleHandle(0)) + _skip;
    std::ptrdiff_t searchEnd = searchStart + (0x1F000 - _skip);
    bool debugflag;
    const char* name = nullptr;

public:
    enum Opcodes {
        GET_ADDRESS = 0,
        OP_LEA = ENCODE(3, 7),
        OP_MOV = ENCODE(3, 7),
        OP_MOVCS = ENCODE(2, 7),
        OP_CALL = ENCODE(1, 5),
        OP_XOR = ENCODE(2, 2),
        OP_CMP = ENCODE(2, 6),
        OP_JZ = ENCODE(2, 6)
    };

    explicit Scanner(std::ptrdiff_t startAddr, std::ptrdiff_t endAddr, const char* pattern, const char* name, bool debug = false, std::ptrdiff_t offset = 0x0);
    explicit Scanner(const char* pattern, const char* name, std::ptrdiff_t offset = 0x0, bool debug = true);
    explicit Scanner(__int64 skip, __int64 search_size, const char* pattern);
    explicit Scanner(std::ptrdiff_t addr);

    ~Scanner() {};
    std::ptrdiff_t addr = 0;

    auto resolve(Opcodes op) -> std::ptrdiff_t;

    void logger(bool log);
    auto getaddr() -> std::ptrdiff_t;
    auto validaddr() -> bool;
    auto resolve_call() -> std::ptrdiff_t;
    auto resolve_lea() -> std::ptrdiff_t;
    auto resolve_cmp() -> std::ptrdiff_t;
    auto vtable_call() -> std::ptrdiff_t;
    auto resolve_mov() -> std::ptrdiff_t;
    auto resolve_jmp() -> std::ptrdiff_t;
    template <typename T>
    Scanner add(T offset)
    {
        if (getaddr())
            addr += offset;
        return Scanner(addr);
    }

    template <typename T>
    Scanner sub(T offset)
    {
        if (getaddr())
            addr -= offset;
        return Scanner(addr);
    }

    template<typename T> T get_offset()
    {
        if (validaddr())
            return *(T*)addr;

        return 0;
    }
};
