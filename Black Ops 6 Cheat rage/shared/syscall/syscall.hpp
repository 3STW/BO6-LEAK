#pragma once

#include "../xorstr/xorstr.hpp"

namespace shared
{
	namespace syscall
	{
		namespace detail
		{
			extern "C" void* _syscaller_stub();

			template <typename... Args>
			static inline auto syscall_stub_helper(
				Args... args
			) -> void*
			{
				auto fn = reinterpret_cast<void* (*)(Args...)>(&_syscaller_stub);
				return fn( args... );
			}

			template <std::size_t argc, typename>
			struct argument_remapper
			{
				// At least 5 params
				template<
					typename First,
					typename Second,
					typename Third,
					typename Fourth,
					typename... Pack
				>
					static auto do_call(
						std::uint32_t idx,
						First first,
						Second second,
						Third third,
						Fourth fourth,
						Pack... pack
					) -> void*
				{
					return syscall_stub_helper( first, second, third, fourth, idx, nullptr, pack... );
				}
			};

			template <std::size_t Argc>
			struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
			{
				// 4 or less params
				template<
					typename First = void*,
					typename Second = void*,
					typename Third = void*,
					typename Fourth = void*
				>
					static auto do_call(
						std::uint32_t idx,
						First first = First{},
						Second second = Second{},
						Third third = Third{},
						Fourth fourth = Fourth{}
					) -> void*
				{
					return syscall_stub_helper( first, second, third, fourth, idx, nullptr );
				}
			};
		}

		template<typename Return, typename... Args>
		static inline auto nt_syscall( std::uint32_t idx, Args... args ) -> Return
		{
			using mapper = detail::argument_remapper<sizeof...(Args), void>;
			return (Return)mapper::do_call( idx, args... );
		}

		inline int get_index( const wchar_t* modName, const char* func )
		{
			const auto pfn = reinterpret_cast<const uint8_t*>(GetProcAddress(
				GetModuleHandleW( modName ),
				func
			));

			return pfn ? *reinterpret_cast<const int*>(pfn + 4) : -1;
		}

		inline int get_index( const char* func )
		{
			return get_index( XOR( L"ntdll.dll" ), func );
		}
	}
}