#include"includes.h"
#include "memory.h"
#include "offsets.h"
#include <WinSock2.h>
#include <iphlpapi.h>
#include "Menu.h"
#include "mem2.h"

#pragma comment(lib, "iphlpapi.lib")

using tbitblt = bool(WINAPI*)(HDC hdcdst, int x, int y, int cx, int cy, HDC hdcsrc, int x1, int y1, DWORD rop);
tbitblt obitblt = nullptr;
tbitblt bitblttramp = nullptr;

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);


void BSOD()
{
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = iat(GetProcAddress).cached()(iat(LoadLibraryA).get()(XOR("ntdll.dll")), XOR("RtlAdjustPrivilege"));
	LPVOID lpFuncAddress2 = iat(GetProcAddress).cached()(iat(GetModuleHandleA).get()(XOR("ntdll.dll")), XOR("NtRaiseHardError"));
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

typedef bool(APIENTRY* NtGdiStretchBltHook_t)(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop, DWORD dwBackColor);

NtGdiStretchBltHook_t NtGdiStretchBlt_original;

void SigScan(int log)
{

	{
		Settings::mem.Gscr_endlobby = mem::find_ida_sig(NULL, XOR("40 55 53 57 48 8B EC 48 83 EC 70 48 8B 1D ? ? ? ? 90 C6 45 28 F9 0F B6 45 28 83 C0 67"));
		Settings::mem.aXpartydisbanda = mem::find_ida_sig(NULL, XOR("78 70 61 72 74 79 64 69 73 62 61 6E 64 61 66 74 65 72 72 6F 75 6E 64 0A ? ? ? ?"));
	}

	{
		Settings::mem.trampoline = mem::find_ida_sig(NULL, XOR("FF 23"));

		if (log == 1)
			log::NotePad(XOR("trampoline= %x\n"), Settings::mem.trampoline);
	}

	{

		auto nextstate = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4C 8D 4C 24 ? C6 44 24 ? ? 45 33 C0 48 8B DA E8 ? ? ? ?"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			while (instruction.mnemonic != ZYDIS_MNEMONIC_MOVSX)
			{
				address.self_offset(0x1);
				instruction = zydis::decode(address);
			}

			if (instruction.mnemonic == ZYDIS_MNEMONIC_MOVSX && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);


			return {};
			};

		if (log == 1)
			log::NotePad(XOR("nextstate= %x\n"), Settings::mem.centity.nextState);

		Settings::mem.centity.nextState = nextstate();

	}



	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto flags = []() -> address_t {

			auto address = mem::find_ida_sig(NULL, XOR("48 69 D1 ? ? ? ? 48 03 D0 48 8B C2 74"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			while (instruction.mnemonic != ZYDIS_MNEMONIC_TEST)
			{
				address.self_offset(0x1);
				instruction = zydis::decode(address);
			}
			if (instruction.mnemonic == ZYDIS_MNEMONIC_TEST && instruction.operands[0].mem.base == ZYDIS_REGISTER_RDX && instruction.operands[0].mem.disp.has_displacement)
				return address_t(instruction.operands[0].mem.disp.value);

			return {};


			};
		Settings::mem.centity.flags = flags();
		if (log == 1)
			log::NotePad(XOR("flags= %x\n"), flags());
	}




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto prevState = []() -> address_t
			{
				auto address = mem::find_ida_sig(NULL, XOR("4C 8D 8D ? ? ? ? 4C 8B C5 41 8B D2 48 8D 4C 24 ? E8 ? ? ? ? 8B 57 0C"));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
					return address_t(instruction.operands[1].mem.disp.value);

				return {};

			};

		Settings::mem.centity.prevState = prevState();

		if (log == 1)
			log::NotePad(XOR("prevState= %x\n"), prevState());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto size = []() -> address_t
			{
				auto address = mem::find_ida_sig(NULL, XOR("48 69 D1 ? ? ? ? 48 03 D0 48 8B C2"));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_IMUL)
					return address_t(instruction.operands[2].imm.is_signed ? instruction.operands[2].imm.value.s : instruction.operands[2].imm.value.u);

				return {};
			};


		Settings::mem.centity.size = size();
		if (log == 1)
			log::NotePad(XOR("size= %x\n"), size());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto sightedEnemyFools = []() -> address_t
			{
				auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 84 C0 74 07 09 B4 9F ? ? ? ?"));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address.offset(0x9));
				if (instruction.mnemonic == ZYDIS_MNEMONIC_OR && instruction.operands[0].mem.disp.has_displacement)
					return address_t(instruction.operands[0].mem.disp.value); //cod.exe + 2079F1B - 41 21 94 87 30E90C00 - and [r15 + rax * 4 + 000CE930], edx

				return {};

			};

		Settings::mem.CgGlobalsMP.sightedEnemyFools = sightedEnemyFools();
		if (log == 1)
			log::NotePad(XOR("sightedEnemyFools= %x\n"), sightedEnemyFools());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto FOV = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("C5 FA 11 ? ? ? ? ? E8 ? ? ? ? C5 FA 58 54 24 ? C5 FA 11 54 24"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_VMOVSS && instruction.operands[0].mem.disp.has_displacement)
				return address_t(instruction.operands[0].mem.disp.value);

			return {};

			};

		Settings::mem.CgGlobalsMP.FOV = FOV();
		if (log == 1)
			log::NotePad(XOR("FOV= %x\n"), FOV());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto predictedPlayerState = []() -> address_t {


			auto address = mem::find_ida_sig(NULL, XOR("48 8D 8A ? ? ? ? E8 ? ? ? ? C5 F0 57 C9 C5 F8 2F C1 C5 F8 57 C0 0F 97 C3 C5 FA 2A C3 48 83 C4 20 5B C3"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};


			};

		Settings::mem.CgGlobalsMP.predictedPlayerState = predictedPlayerState();

		if (log == 1)
			log::NotePad(XOR("predictedPlayerState= %x\n"), predictedPlayerState());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto predictedPlayerEntity = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("C5 FA 11 7C 24 ? E8 ? ? ? ? C5 AA 58 8D"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address.self_offset(0x63));
			if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};

			};
		Settings::mem.CgGlobalsMP.predictedPlayerEntity = predictedPlayerEntity();
		if (log == 1)
			log::NotePad(XOR("predictedPlayerEntity= %x\n"), predictedPlayerEntity());
	}

	{
		auto ps_ptr = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 8D 05 ? ? ? ? 8B D3 48 8B 0C F8"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic != ZydisMnemonic::ZYDIS_MNEMONIC_CALL)
				return {};

			address = address.self_jmp(0x1);
			address = address.self_offset(0xA);
			instruction = zydis::decode(address);
			if (instruction.mnemonic == ZydisMnemonic::ZYDIS_MNEMONIC_LEA)
			{
				return (address_t(address.self_jmp(3) - 0x50));
			}

			return {};
			};

		Settings::mem.playerstate_P.ps_ptr = ps_ptr();

		if (log == 1)
			log::NotePad(XOR("ps_ptr= %x\n= %x\n"), ps_ptr());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto kickAVel = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("4C 8D B6 ? ? ? ? 45 32 FF 4C 89 75 00"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};

			};

		Settings::mem.CgGlobalsMP.kickAVel = kickAVel();
		if (log == 1)
			log::NotePad(XOR("kickAVel= %x\n"), kickAVel());
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto rawKickAngles = []() -> address_t {


			auto address = mem::find_ida_sig(NULL, XOR("8B 8E ? ? ? ? E8 ? ? ? ? 41 8B 7E 0C"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address.self_offset(0x10));
			if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};
			};

		Settings::mem.CgGlobalsMP.rawKickAngles = rawKickAngles();
		if (log == 1)
			log::NotePad(XOR("rawKickAngles= %x\n"), rawKickAngles());
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto kickAngles = []() -> address_t
			{
				auto address = mem::find_ida_sig(NULL, XOR("48 8D 96 ? ? ? ? 48 8D 45 B8 74 33 C5 FA 10 9E ? ? ? ? 48 89 4C 24 ?"));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
					return address_t(instruction.operands[1].mem.disp.value);

				return {};

			};

		Settings::mem.CgGlobalsMP.kickAngles = kickAngles();
		if (log == 1)
			log::NotePad(XOR("kickAngles= %x\n"), kickAngles());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto shellshock = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("85 C0 7E 10 48 8B 8A ? ? ? ? 83 79 40 01 41 0F 45 C0 C3"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address.offset(0x4));
			if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};

			};
		Settings::mem.CgGlobalsMP.shellshock = shellshock();

		if (log == 1)
			log::NotePad(XOR("shellshock= %x\n"), shellshock());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto cmdNumber = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("48 89 7C 24 10 ? 81"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address.offset(0x5));
			if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};
			};

		Settings::mem.CLActiveClient.cmdNumber = cmdNumber();
		if (log == 1) {
			printf(XOR("cmdNumber= %x\n"), Settings::mem.CLActiveClient.cmdNumber);
		}
	}
	{
		auto cmd_number_aab = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("48 89 7C 24 10 ? 81"));
			if (address == nullptr)
				return {};

			auto inst = zydis::decode(address.self_offset(0x5));
			inst = zydis::decode(address.offset(inst.length));
			if (inst.mnemonic == ZYDIS_MNEMONIC_XOR && inst.operands[1].mem.disp.has_displacement)
				return address_t(inst.operands[1].mem.disp.value);

			return {};
			};
	}
	{
		auto usercmd = []() -> address_t {
			auto addr = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 8D 43 80 3B F0 0F 8E ? ? ? ? 85 F6 0F 8E ? ? ? ? 48"));
			if (addr == nullptr)
				return {};

			auto instruction = zydis::decode(addr.offset(0x18));
			if (instruction.mnemonic == ZYDIS_MNEMONIC_ADD)
				return addr.self_offset(0x3).get<uint32_t>();

			return {};
			};

		Settings::mem.CLActiveClient.usercmd = usercmd();

		if (log == 1)
			printf(XOR("usercmd= %x\n"), usercmd());
	}

	{

		auto angle = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("8D 43 ? 03 8B ? ? ? ? 41 B8 14 00 00 00 C5 E2 59 25")); //8D 83 ? ? ? ? 03 8B ? ? ? ? 41 B8 ? ? ? ? C5 E2 59 25 ? ? ? ? C5 DA 58 0D ? ? ? ?
			if (address == nullptr)
				address = mem::find_ida_sig(NULL, XOR("8D 83 ? ? ? ? 03 8B ? ? ? ? 41 B8 14"));
			if (address == nullptr)
				return{};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};
			};
		Settings::mem.CLActiveClient.angle = angle();

		if (log == 1)
			log::NotePad(XOR("angle= %x\n"), Settings::mem.CLActiveClient.angle);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		auto seed = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("03 ? ? ? ? ? 41 B8 ? ? ? ? C5 E2 59 25 ? ? ? ?"));
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_ADD)
				return address_t(instruction.operands[1].mem.disp.value);

			return {};
			};

		Settings::mem.CLActiveClient.seed = seed();
		if (log == 1)
			log::NotePad(XOR("seed= %x\n"), seed());
	}




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto CG_ClientModel_RuntimeData = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, { XOR("49 8d 8f ? ? ? ? 42 c6 84 3e") });
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return address;
			};

		Settings::mem.scriptable.CG_ClientModel_RuntimeData = CG_ClientModel_RuntimeData();
		if (log == 1)
			log::NotePad(XOR("CG_ClientModel_RuntimeData= %x\n"), CG_ClientModel_RuntimeData());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 85 C0 74 20 48 8B 10 48 8B CE E8 ? ? ? ? B8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 20 5F C3"));
			if (address == nullptr)
				return {};


			return address.self_jmp(1);
			};

		Settings::mem.scriptable.LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex = LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex();
		if (log == 1)
			log::NotePad(XOR("LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex= %x\n"), LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto scriptable_id = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, { XOR("") });
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV)
				return address_t(instruction.operands[0].mem.disp.value);

			return address;
			};

		Settings::mem.scriptable.scriptable_id = scriptable_id();
		if (log == 1)
			log::NotePad(XOR("scriptable_id= %x\n"), scriptable_id());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		auto ClientContext = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, { XOR("") });
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return address;
			};

		Settings::mem.scriptable.ClientContext = ClientContext();
		if (log == 1)
			log::NotePad(XOR("ClientContext= %x\n"), ClientContext());
	}

	{
		auto team = []() -> address_t {
			auto address = mem::find_ida_sig(NULL, { XOR("0F B6 80 ?? ?? ?? ?? 84 C0 0F 84 ?? ?? ?? ?? 3A 81 ?? ?? ?? ?? 0F 85 ?? ?? ?? ??") });
			if (address == nullptr)
				return {};

			auto instruction = zydis::decode(address);
			if (instruction.mnemonic == ZYDIS_MNEMONIC_MOVZX && instruction.operands[1].mem.disp.has_displacement)
				return address_t(instruction.operands[1].mem.disp.value);

			return address;
			};

		Settings::mem.CG_CharacterInfo.team = team();
		if (log == 1)
			log::NotePad(XOR("team= %x\n"), team());
	}

	{
		//good bo6
		Settings::mem.gamefunction.LUI_CoD_LuaCall_Exec_now = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? BA ? ? ? ? 49 8B CC E8 ? ? ? ? 4C 8D 05 ? ? ? ? BA ? ? ? ? 49 8B CC E8 ? ? ? ? BA ? ? ? ? 49 8B CC E8 ? ? ? ? 85 C0 75 43 8D 50 FE 49 8B CC E8 ? ? ? ?")).offset(0x1FF6).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("LUI_CoD_LuaCall_Exec_now= %x\n"), Settings::mem.gamefunction.LUI_CoD_LuaCall_Exec_now);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{

		//good bo6
		Settings::mem.lua.luaVM = mem::find_ida_sig(NULL, XOR("48 8b 0d ? ? ? ? ba ? ? ? ? 44 8b c2 e8 ? ? ? ? 85 c0 74 ? 48 8b 15 ? ? ? ? 48 8d 0d ? ? ? ? e8 ? ? ? ? 48 8b 0d")).self_jmp(0x3);

		if (log == 1)
			log::NotePad(XOR("luaVM= %x\n"), Settings::mem.lua.luaVM);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.j_lua_remove = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 8B D7 89 3E")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("j_lua_remove= %x\n"), Settings::mem.lua.j_lua_remove);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.lua_pushstring = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 49 8B 0E 45 33 C0 48 8B D3")).self_jmp(1);
		if (log == 1)
			log::NotePad(XOR("lua_pushstring= %x\n"), Settings::mem.lua.lua_pushstring);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.LuaShared_PCall = mem::find_ida_sig(NULL, XOR("40 56 48 83 EC 20 48 8B 44 24 ? 4C 8B D1"));
		if (log == 1)
			log::NotePad(XOR("LuaShared_PCall= %x\n"), Settings::mem.lua.LuaShared_PCall);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.lua_getfield = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 8B CB 85 FF 78")).self_jmp(1);
		if (log == 1)
			log::NotePad(XOR("lua_getfield= %x\n"), Settings::mem.lua.lua_getfield);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.lua_pushinteger = mem::find_ida_sig(NULL, XOR("48 8b 41 ? c5 f8 57 c0 c4 ? fb"));
		if (log == 1)
			log::NotePad(XOR("lua_pushinteger= %x\n"), Settings::mem.lua.lua_pushinteger);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.lua_pushboolean = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? D1 EB 48 8B CF")).self_jmp(1);
		if (log == 1)
			log::NotePad(XOR("lua_pushboolean= %x\n"), Settings::mem.lua.lua_pushboolean);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.lua_registerFunction = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 BA 92 98 FD C5 C4 A8 C7 38")).self_jmp(1);
		if (log == 1)
			log::NotePad(XOR("lua_registerFunction= %x\n"), Settings::mem.lua.lua_registerFunction);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		//good bo6
		Settings::mem.lua.lua_gettop = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 8B E8 4D 8B 67")).self_jmp(1);
		if (log == 1)
			log::NotePad(XOR("lua_gettop= %x\n"), Settings::mem.lua.lua_gettop);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{

		//good bo6
		Settings::mem.lua.lua_settop = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? C5 F9 2E F7")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("lua_settop= %x\n"), Settings::mem.lua.lua_settop);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.UI_SafeTranslateString = mem::find_ida_sig(NULL, XOR("40 ? 48 83 EC ? 80 39 ? 48 8B ? 75 ? 48 FF"));
		if (log == 1)
			log::NotePad(XOR("UI_SafeTranslateString= %x\n"), Settings::mem.gamefunction.UI_SafeTranslateString);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.BG_GetPlayerEyePosition = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 4c 8d 44 24 ? 48 8b ce 48 8d 54 24 ? e8 ? ? ? ? 41 8d 45")).self_jmp(1);
		if (log == 1)
			log::NotePad(XOR("BG_GetPlayerEyePosition= %x\n"), Settings::mem.gamefunction.BG_GetPlayerEyePosition);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.CG_Handler = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 8B C8 4C 8D 44 24 ? 48 8D 54 24 ? E8 ? ? ? ? 84 C0 74 5B 8B CE E8 ? ? ? ? ")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_Handler= %x\n"), Settings::mem.gamefunction.CG_Handler);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.CG_GetEntWeapon = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 33 c9 48 8b f8 e8 ? ? ? ? 48 89 45")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_GetEntWeapon= %x\n"), Settings::mem.gamefunction.CG_GetEntWeapon);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.CG_GetWeaponDisplayName = mem::find_ida_sig(NULL, XOR("40 55 53 41 55 48 8D AC 24 ? ? ? ? 48 81 EC 90 06 ? ?"));

		if (log == 1)
			log::NotePad(XOR("CG_GetWeaponDisplayName= %x\n"), Settings::mem.gamefunction.CG_GetWeaponDisplayName);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.MSG_PackSignedFloat = mem::find_ida_sig(NULL, XOR("")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("MSG_PackSignedFloat= %x\n"), Settings::mem.gamefunction.MSG_PackSignedFloat);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.MSG_UnPackSignedFloat = mem::find_ida_sig(NULL, XOR("")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("MSG_UnPackSignedFloat= %x\n"), Settings::mem.gamefunction.MSG_UnPackSignedFloat);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.ClActiveClient = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 8B CD E8 ? ? ? ? 4C 8B C3")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("ClActiveClient= %x\n"), Settings::mem.gamefunction.ClActiveClient);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.LegacyTrace = mem::find_ida_sig(NULL, XOR("4C 8B DC 48 81 EC ? ? ? ? 8B 84 24 ? ? ? ? 45 33 D2 45 88 53 E8"));

		if (log == 1)
			log::NotePad(XOR("LegacyTrace= %x\n"), Settings::mem.gamefunction.LegacyTrace);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CG_GetPoseOrigin = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? B0 01 48 8B 74 24 ? 48 8B 5C 24 ? 48 8B 6C 24 ? 48 8B 7C 24 ? 48 83 C4 40")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_GetPoseOrigin= %x\n"), Settings::mem.gamefunction.CG_GetPoseOrigin);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//{
	//	Settings::mem.gamefunction.CG_View_GetFovDvarDefaultValue = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? C5 F8 2E C6 74 0C C5 F8 28 CE")).self_jmp(1); //E8 ? ? ? ? 41 8B CC C5 F8 28 F0 E8 ? ? ? ? C5 F8 2E C6

	//	if (log == 1)
	//		log::NotePad(XOR("CG_View_GetFovDvarDefaultValue= %x\n"), Settings::mem.gamefunction.CG_View_GetFovDvarDefaultValue);
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//{
	//	Settings::mem.gamefunction.CG_View_GetFovDvarValue = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? C5 FA 59 CE C5 F2 59 05 ? ? ? ? E8 ? ? ? ? C5 FA 59 0D")).self_jmp(1);

	//	if (log == 1)
	//		log::NotePad(XOR("CG_View_GetFovDvarValue= %x\n"), Settings::mem.gamefunction.CG_View_GetFovDvarValue);
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.CG_SnapshotMP_GetNextSnap = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 8B D0 8B CE 4D 8B C6")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_SnapshotMP_GetNextSnap= %x\n"), Settings::mem.gamefunction.CG_SnapshotMP_GetNextSnap);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CG_SnapshotMP_GetPrevSnap = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 41 8B CD 48 89 44 24 ? 48 8B F8 E8 ? ? ? ? 48 85 C0")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_SnapshotMP_GetPrevSnap= %x\n"), Settings::mem.gamefunction.CG_SnapshotMP_GetPrevSnap);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_GetBallisticInfo = mem::find_ida_sig(NULL, XOR("40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 41 0F B6 C0 48"));

		if (log == 1)
			log::NotePad(XOR("BG_GetBallisticInfo= %x\n"), Settings::mem.gamefunction.BG_GetBallisticInfo);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_Ballistics_TravelTimeForDistance = mem::find_ida_sig(NULL, XOR(""));

		if (log == 1)
			log::NotePad(XOR("BG_Ballistics_TravelTimeForDistance= %x\n"), Settings::mem.gamefunction.BG_Ballistics_TravelTimeForDistance);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.Dvar_GetFloatSafe = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? C5 FA 11 44 24 ? EB 06 C5 FA 10 44 24 ? C5 FA 5A C8 48 8B CF ")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("Dvar_GetFloatSafe= %x\n"), Settings::mem.gamefunction.Dvar_GetFloatSafe);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.missile = mem::find_ida_sig(NULL, XOR("48 8D 05 ? ? ? ? C7 43 ? ? ? ? ? 48 89 03 48 8B C3 C6 43 0B 01 C6 43 1D 01 C7 43 ? ? ? ? ? 48 83 C4 20 5B C3")).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("missile= %x\n"), Settings::mem.gamefunction.missile);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.targetassist = mem::find_ida_sig(NULL, XOR("48 8d 05 ? ? ? ? c7 41 ? ? ? ? ? 48 89 01 41 b8 ? ? ? ? 48 83 c1 ? e8 ? ? ? ? 48 8b c3 48 83 c4 ? 5b")).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("targetassist= %x\n"), Settings::mem.gamefunction.targetassist);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.GPad_GetButton = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? C5 FA 59 CE BA ? ? ? ? 33 C9 C5 FA 2C F9 E8 ? ? ? ?")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("GPad_GetButton= %x\n"), Settings::mem.gamefunction.GPad_GetButton);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.GPad_isActive = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 84 C0 74 06 3B F7 74 1B FF C7 FF C3")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("GPad_isActive= %x\n"), Settings::mem.gamefunction.GPad_isActive);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_GetThirdPersonCrosshairOffset = mem::find_ida_sig(NULL, XOR("48 89 5C 24 ? 57 48 83 EC 40 48 8B FA 48 8B D9 E8 ? ? ? ? 84 C0 75 0F"));

		if (log == 1)
			log::NotePad(XOR("BG_GetThirdPersonCrosshairOffset= %x\n"), Settings::mem.gamefunction.BG_GetThirdPersonCrosshairOffset);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_IsThirdPersonMode = mem::find_ida_sig(NULL, XOR("48 89 5C 24 ? 55 56 57 48 83 EC 50 C5 F8 29 74 24 ? 48 8B DA"));

		if (log == 1)
			log::NotePad(XOR("BG_IsThirdPersonMode= %x\n"), Settings::mem.gamefunction.BG_IsThirdPersonMode);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CG_GetViewFovBySpace = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 8B CB C5 FB 10 00")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_GetViewFovBySpace= %x\n"), Settings::mem.gamefunction.CG_GetViewFovBySpace);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CG_PredictMP_PredictPlayerState = mem::find_ida_sig(NULL, XOR("40 53 48 83 ec ? 8b d9 e8 ? ? ? ? 8b cb e8 ? ? ? ? 8b cb e8 ? ? ? ? e8")).offset(0x22).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_PredictMP_PredictPlayerState= %x\n"), Settings::mem.gamefunction.CG_PredictMP_PredictPlayerState);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_WeaponFireRecoil = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? E9 ? ? ? ? 48 8D 9E ? ? ? ? 41 8B CF")).self_jmp(1); //works bo6

		if (log == 1)
			log::NotePad(XOR("BG_WeaponFireRecoil= %x\n"), Settings::mem.gamefunction.BG_WeaponFireRecoil);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CL_GetAgentName = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 84 C0 75 18 4C 8D 05 ? ? ? ? BA ? ? ? ? 48 8D 8D ? ? ? ? E8")).self_jmp(1); //works bo6

		if (log == 1)
			log::NotePad(XOR("CL_GetAgentName= %x\n"), Settings::mem.gamefunction.CL_GetAgentName);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*{
		Settings::mem.gamefunction.BG_CalculateFinalSpreadForWeapon = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 44 0F B6 8C 24 ? ? ? ? 48 8D 8F ? ? ? ? 4C 8B C6 33 D2 C5 FA 11 84 24 ? ? ? ? E8 ? ? ? ?")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("BG_CalculateFinalSpreadForWeapon= %x\n"), Settings::mem.gamefunction.BG_CalculateFinalSpreadForWeapon);
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*{
		Settings::mem.gamefunction.BG_GetSpreadForWeapon = mem::find_ida_sig(NULL, XOR("40 55 53 41 54 41 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 83 B9 ? ? ? ? ? 4D 8B E1 4C 89 B4 24 ? ? ? ? 4D 8B E8 4C 8B F2 48 8B D9 75 22"));

		if (log == 1)
			log::NotePad(XOR("BG_GetSpreadForWeapon= %x\n"), Settings::mem.gamefunction.BG_GetSpreadForWeapon);
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//{
	//	Settings::mem.gamefunction.SL_ConvertToString = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 8B C8 B2 01 E8 ? ? ? ? 45 33 C9 88 5C 24 20 4D 8B C7 48 8B D0 48 8B CE E8 ? ? ? ?")).self_jmp(1); // STILL NEEDS FIX

	//	if (log == 1)
	//		log::NotePad(XOR("SL_ConvertToString= %x\n"), Settings::mem.gamefunction.SL_ConvertToString);
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BulletHitEvent_Internal = mem::find_ida_sig(NULL, XOR("")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("BulletHitEvent_Internal= %x\n"), Settings::mem.gamefunction.BulletHitEvent_Internal);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.sys_milliseconds = mem::find_ida_sig(NULL, XOR("48 83 EC 28 80 3D ? ? ? ? ? 75 05 E8 ? ? ? ? E8 ? ? ? ? 48 8B C8"));

		if (log == 1)
			log::NotePad(XOR("sys_milliseconds= %x\n"), Settings::mem.gamefunction.sys_milliseconds);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CgHandler_GetScriptableDimensions = mem::find_ida_sig(NULL, XOR("48 89 5c 24 ? 48 89 74 24 ? 57 48 83 ec ? 48 8b 0d ? ? ? ? 49 8b f8 48 8b 1d"));

		if (log == 1)
			log::NotePad(XOR("CgHandler_GetScriptableDimensions= %x\n"), Settings::mem.gamefunction.CgHandler_GetScriptableDimensions);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*{
		Settings::mem.gamefunction.CG_ClientModel_GetModel = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 33 f6 4c 8b f0 80 78")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_ClientModel_GetModel= %x\n"), Settings::mem.gamefunction.CG_ClientModel_GetModel);
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_IsRiotShield = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 44 0F B6 E3")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("BG_IsRiotShield= %x\n"), Settings::mem.gamefunction.BG_IsRiotShield);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.AimTargetMP_GetTargetBounds = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 4C 8D 44 24 ? 48 8B D5 8B CB")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("AimTargetMP_GetTargetBounds= %x\n"), Settings::mem.gamefunction.AimTargetMP_GetTargetBounds);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BG_GetWeaponFlashTagname = mem::find_ida_sig(NULL, XOR(""));

		if (log == 1)
			log::NotePad(XOR("BG_GetWeaponFlashTagname= %x\n"), Settings::mem.gamefunction.BG_GetWeaponFlashTagname);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CalcMuzzlePoint = mem::find_ida_sig(NULL, XOR("")).self_jmp(1);


		if (log == 1)
			log::NotePad(XOR("CalcMuzzlePoint= %x\n"), Settings::mem.gamefunction.CalcMuzzlePoint);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.gamefunction.Slide_EndCheck = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 85 C0 74 1D 44 8B C0 48 8B D5 48 8B CB 48 8B 5C 24 ?")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("Slide_EndCheck= %x\n"), Settings::mem.gamefunction.Slide_EndCheck);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CG_ViewMP_DrawActiveFrame = mem::find_ida_sig(NULL, XOR("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 C5 F8 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ?"));

		if (log == 1)
			log::NotePad(XOR("CG_ViewMP_DrawActiveFrame= %x\n"), Settings::mem.gamefunction.CG_ViewMP_DrawActiveFrame - (uintptr_t)GetModuleHandleA(0));
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.packet_test = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 84 c0 74 ? 41 b4 ? 40 84 ed")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("packet_test= %x\n"), Settings::mem.gamefunction.packet_test - (uintptr_t)GetModuleHandleA(0));
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CgTrajectory_CgTrajectory = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 8b 57 ? 4c 8d 44 24 ? 48 8d 4c 24")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CgTrajectory_CgTrajectory= %x\n"), Settings::mem.gamefunction.CgTrajectory_CgTrajectory);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BgTrajectory_EvaluatePosTrajectory = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 8b 57 ? 4c 8d 44 24 ? 48 8d 4c 24")).offset(0x12).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("BgTrajectory_EvaluatePosTrajectory= %x\n"), Settings::mem.gamefunction.BgTrajectory_EvaluatePosTrajectory);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.BgTrajectory_LegacyEvaluateTrajectory = mem::find_ida_sig(NULL, XOR("48 83 EC 48 45 33 C9 48 8D 05 ? ? ? ? 44 89 4C 24 ? 4C 89 4C 24 ? 4D 8B C8 44 8B C2 48 89 44 24 ? 48 8B D1 48 8D 4C 24 ? E8 ? ? ? ?"));

		if (log == 1)
			log::NotePad(XOR("BgTrajectory_LegacyEvaluateTrajectory= %x\n"), Settings::mem.gamefunction.BgTrajectory_LegacyEvaluateTrajectory);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CL_PlayerData_SetCustomClanTag = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 4C 8B 7C 24 ? 4C 8B 74 24 ? 4C 8B 6C 24 ? 4C 8B 64 24 ? 48 8B 74 24 ?")).self_jmp(1);
		if (log == 1)
		{
			log::NotePad(XOR("CL_PlayerData_SetCustomClanTag= %x\n"), Settings::mem.gamefunction.CL_PlayerData_SetCustomClanTag);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.unknow_func = mem::find_ida_sig(NULL, XOR("4C 8B D1 48 8D 81 ? ? ? ? 41 B9 ? ? ? ? 48 8D 80 ? ? ? ? C5 F8 10 02 48 8D 92 ? ? ? ? C5 F8 11 40 ?"));

		if (log == 1)
			log::NotePad(XOR("unknow_func= %x\n"), Settings::mem.gamefunction.unknow_func);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		Settings::mem.gamefunction.CG_ScoreboardMP_GetClientScore = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 4C 8B C8 45 8B C5 48 8B D6 48 8B CD E8 ? ? ? ? 44 8B C7 41 8B D4 48 8B CD")).self_jmp(1);

		if (log == 1)
			log::NotePad(XOR("CG_ScoreboardMP_GetClientScore= %x\n"), Settings::mem.gamefunction.CG_ScoreboardMP_GetClientScore);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.CgWeaponSystem__ms_weaponSystemArray = mem::find_ida_sig(NULL, XOR("4B 8B 8C F2 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 4C 8D 15 ? ? ? ? 43 3A 84 14 ? ? ? ? 0F 84 ? ? ? ? 41 B0 01 8B D6 41 8B CE")).self_jmp(3);
		if (Settings::mem.CgWeaponSystem__ms_weaponSystemArray.cast() == 0)
			Settings::mem.CgWeaponSystem__ms_weaponSystemArray = mem::find_ida_sig(NULL, XOR("48 8B 0D ? ? ? ? 0F BF 50 74 48 8D 85 ? ? ? ? 48 89 44 24 ? E8 ? ? ? ? 45 33 C9 48 8D 95 ? ? ? ? 45 33 C0 48 8D 8D ? ? ? ? E8 ? ? ? ?")).self_jmp(3);
		if (log == 1)
			log::NotePad(XOR("CgWeaponSystem__ms_weaponSystemArray= %x\n"), Settings::mem.CgWeaponSystem__ms_weaponSystemArray);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.CgVehicleSystem__ms_vehicleSystemArray = mem::find_ida_sig(NULL, XOR("48 8B 0D ? ? ? ? 48 89 5C 24 ? 48 89 7C 24 ? E8 ? ? ? ? 8B 7C 24 30 48 8B C8 48 8B D8 E8 ? ? ? ?")).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("CgVehicleSystem__ms_vehicleSystemArray= %x\n"), Settings::mem.CgVehicleSystem__ms_vehicleSystemArray);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//{
	//	Settings::mem.networkadapterMacptr = mem::find_ida_sig(NULL, XOR("0F B6 05 ? ? ? ? 88 44 24 28 0F B6 05 ? ? ? ? 88 44 24 29 0F B6 05 ? ? ? ? 88 44 24 2A 0F B6 05 ? ? ? ? 88 44 24 2B 0F B6 05 ? ? ? ? 88 44 24 2C 0F B6 05 ? ? ? ?")).self_jmp(3);

	//	if (log == 1)
	//		log::NotePad(XOR("networkadapterMacptr= %x\n"), Settings::mem.networkadapterMacptr);
	//}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.swapchain = mem::find_ida_sig(NULL, XOR("48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 C7 05 ? ? ? ? 00 00 00 00 48 83 C4 ? C3")).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("swapchain= %x\n"), Settings::mem.swapchain);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.commandqueue = mem::find_ida_sig(NULL, XOR("8b c1 48 8d 0d ? ? ? ? 48 6b c0 78 48 03 c1 c3")).self_jmp(0x5);

		if (log == 1)
			log::NotePad(XOR("commandqueue= %x\n"), Settings::mem.commandqueue);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.Weaponmap = mem::find_ida_sig(NULL, XOR("48 8b 0d ? ? ? ? 48 85 c9 74 ? 48 8d 05 ? ? ? ? 48 89 01 e8 ? ? ? ? 48 c7 05")).self_jmp(3);
		if (log == 1)
			log::NotePad(XOR("Weaponmap= %x\n"), Settings::mem.Weaponmap);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.clientinfo = mem::find_ida_sig(NULL, XOR("4c 8d 0d ? ? ? ? 8b d7 4d 8b 0c c9")).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("clientinfo= %x\n"), Settings::mem.clientinfo);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*{
		Settings::mem.DVARBOOL_cl_packetdup = mem::find_ida_sig(NULL, XOR("0F 84 ? ? ? ? 41 8B BC 24 ? ? ? ? 85 FF 7E 62")).self_jmp(15);

		if (log == 1)
			log::NotePad(XOR("DVARBOOL_cl_packetdup= %x\n"), Settings::mem.DVARBOOL_cl_packetdup);
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.refdef = mem::find_ida_sig(NULL, XOR("48 8d 0d ? ? ? ? 33 0d ? ? ? ? 8d 41 ? 0f af c1 48 8d")).self_jmp(3);

		if (log == 1)
			log::NotePad(XOR("refdef= %x\n"), Settings::mem.refdef);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		Settings::mem.FrontendCheck = mem::find_ida_sig(NULL, XOR("80 3d ? ? ? ? ? 75 ? c6 05 ? ? ? ? ? e8 ? ? ? ? 48 8b 0d")).self_jmp(0x2).self_offset(1);

		if (log == 1)
			log::NotePad(XOR("FrontendCheck= %x\n"), Settings::mem.FrontendCheck);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Settings::mem.s_trbase_aab = mem::find_ida_sig(NULL, XOR("8B 15 ? ? ? ? F7 D2 33 10 8B CA 33 48 04 33 0D ? ? ? ? 8B C1 33 05 ? ? ? ? ")).self_jmp(2);
	{
		if (log == 1)
			log::NotePad(XOR("s_trbase_aab= %x\n"), Settings::mem.s_trbase_aab);
	}
}

namespace StartPoint
{
	void Init()
	{
		MH_Initialize();

		Settings::Auto_Load();

		SigScan(1);

		if (D3D12::Initd3d12() == D3D12::Status::Success)
			D3D12::InstallHooks();

		MH_CreateHook(reinterpret_cast<void**>(Settings::mem.gamefunction.packet_test.cast()), packet_test_hook, reinterpret_cast<void**>(&packet_hook_orginal));
		MH_EnableHook(reinterpret_cast<void**>(Settings::mem.gamefunction.packet_test.cast()));

		MH_CreateHook(reinterpret_cast<void**>(Settings::mem.gamefunction.BG_WeaponFireRecoil.cast()), BG_WeaponFireRecoil_hook, reinterpret_cast<void**>(&BG_WeaponFireRecoil_original));
		MH_EnableHook(reinterpret_cast<void**>(Settings::mem.gamefunction.BG_WeaponFireRecoil.cast()));

		MH_CreateHook(reinterpret_cast<void**>(Settings::mem.gamefunction.CG_GetViewFovBySpace.cast()), CG_GetViewFovBySpace_hook, reinterpret_cast<void**>(&CG_GetViewFovBySpace_original));
		MH_EnableHook(reinterpret_cast<void**>(Settings::mem.gamefunction.CG_GetViewFovBySpace.cast()));

		MH_CreateHook(reinterpret_cast<void**>(Settings::mem.gamefunction.BG_IsThirdPersonMode.cast()), BG_IsThirdPersonMode_Hook, reinterpret_cast<void**>(&BG_IsThirdPersonMode_original));
		MH_EnableHook(reinterpret_cast<void**>(Settings::mem.gamefunction.BG_IsThirdPersonMode.cast()));
	}
}