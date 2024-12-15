#pragma once
#include"includes.h"
#define ADD_INTERFACE( type, var_name, address ) type* var_name = address.cast< type* >();

#define ADD_INTERFACE_CUSTOM( type, var_name, function ) type* var_name = function();

inline int aim_target = 0;
namespace Settings
{
	
	struct ModernWarfare3_t
	{
		//ADD_INTERFACE(void*, missile, mem::find_ida_sig(0, XOR("48 8D 05 ? ? ? ? C7 43 ? ? ? ? ? 48 89 03 48 8B C3 C6 43 0B 01 C6 43 1D 01 C7 43 ? ? ? ? ? 48 83 C4 20 5B C3")).self_jmp(0x3));

		//maybe move refdef to here. makes more sense
		/*ADD_INTERFACE(IDXGISwapChain3, swapchain, mem::find_ida_sig(0, XOR("48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 C7 05 ? ? ? ? 00 00 00 00 48 83 C4 ? C3")).self_jmp(0x3));
		ADD_INTERFACE(address_t, commandqueue, mem::find_ida_sig(0, XOR("48 03 3D ? ? ? ? 48 8B CF E8 ? ? ? ? 48 8D")).self_jmp(0x5));*/
		ADD_INTERFACE(game_struct::CgWeaponMap*, CgWeaponMap__ms_instance, mem::find_ida_sig(NULL, XOR("48 8B 0D ? ? ? ? 48 8B D0 E8 ? ? ? ? 45 33 C0 48 8B D3 48 8B CE")).self_jmp(0x3));
		ADD_INTERFACE(uintptr_t*, ms_cgameStaticsArray, mem::find_ida_sig(NULL, XOR("4c 8d 0d ? ? ? ? 8b d7 4d 8b 0c c9")).self_jmp(0x3));
		ADD_INTERFACE(game_struct::ClStatic, clStatic, mem::find_ida_sig(NULL, XOR("48 8D 0D ? ? ? ? 48 89 5C 24 ? 48 8B 58 28 E8 ? ? ? ? 3C 01 74 22 48 8B CB E8 ? ? ? ?")).self_jmp(0x3));

	};

	extern ModernWarfare3_t mw3;
}
