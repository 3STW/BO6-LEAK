#pragma once


namespace shared::mem
{
    class Scanner
    {
    private:
        bool m_debugflag;
        const char* m_name = nullptr;

    public:
        explicit Scanner(const char* module, const char* pattern, const char* name, std::ptrdiff_t offset = 0, bool debug = false);
        explicit Scanner(const char* pattern, const char* name, std::ptrdiff_t offset = 0x0, bool debug = true);
        explicit Scanner(address_t addr);


        ~Scanner() {};
        address_t addr ;

        void logger(bool log);
        auto getaddr() -> address_t;
        auto validaddr() -> bool;
        auto resolve_call() -> address_t;
        auto resolve_Add() -> address_t;
        auto resolve_lea() -> address_t;
        auto resolve_cmp() -> address_t;
        auto vtable_call() -> address_t;
        auto resolve_mov() -> address_t;
        auto resolve_mov32() -> address_t;
        auto resolve_jmp() -> address_t;
        auto resolve_jmp2() -> address_t;
        template<typename T> T get_offset()
        {
            if (validaddr())
                return  *reinterpret_cast<T*>(addr);

            return 0;
        }
    };
}
