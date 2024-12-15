#include "includes.h"


namespace shared::mem
{
    Scanner::Scanner(const char* module, const char* pattern, const char* name, std::ptrdiff_t offset, bool debug) : m_name{ name }, m_debugflag{ debug }
    {
        addr = find_ida_sig(module, pattern);
        if (addr)
            addr = addr + (offset);
    }

    Scanner::Scanner(const char* pattern, const char* name, std::ptrdiff_t offset, bool debug) : m_name{ name }, m_debugflag{ debug }
    {
        addr = find_ida_sig(0, pattern);
        if (addr)
            addr = addr + (offset);

    }

    Scanner::Scanner(address_t address)
    {
        addr = address;
    }




    auto Scanner::validaddr() -> bool
    {
        if (is_bad_ptr(addr))
        {
            
        }

        if (is_valid_ptr(addr))
        {
            return true;
        }
    };

    auto Scanner::getaddr() -> address_t {
        if (validaddr()) {
            log::NotePad("Success --- %s : 0x%x\n", m_name, addr - (uintptr_t)GetModuleHandleA(0));

            return addr;

        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    };

    auto Scanner::resolve_call() -> address_t {
        if (validaddr()) {

            auto address =  *(int*)(addr + 1) + addr + 5;

            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    }
    auto Scanner::resolve_Add() -> address_t
    {
        if (validaddr()) {
            auto address = *(int*)(addr + 3) + addr + 7;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    };

    auto Scanner::resolve_lea() -> address_t {
        if (validaddr()) {
            auto address = *(int*)(addr + 3) + addr + 7;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    };

    //works with XOR
    auto Scanner::resolve_cmp() -> address_t {
        if (validaddr()) {
            auto address = *(int*)(addr + 2) + addr + 6;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    };

    auto Scanner::vtable_call() -> address_t {
        if (validaddr()) {

            auto address = *(int*)(addr + 2) + addr + 6;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    };

    auto Scanner::resolve_mov() -> address_t {
        if (validaddr()) {

            auto address = *(int*)(addr + 3) + addr + 7;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    }

    auto Scanner::resolve_mov32() -> address_t {
        if (validaddr()) {

            auto address = *(int*)(addr + 2) + addr + 6;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    }

    auto Scanner::resolve_jmp() -> address_t {
        if (validaddr()) {

            auto address = *(int*)(addr + 2) + addr + 8;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    }

    auto Scanner::resolve_jmp2() -> address_t {
        if (validaddr()) {

            auto address = *(int*)(addr + 1) + addr + 5;
            log::NotePad("Success --- %s : 0x%x\n", m_name, address - (uintptr_t)GetModuleHandleA(0));
            return address;
        }
        else
        {
            log::NotePad("Failed --- %s : 0\n", m_name);

        }
        return address_t();
    }


  
}