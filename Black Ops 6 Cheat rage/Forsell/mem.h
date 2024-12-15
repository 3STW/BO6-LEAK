#pragma once
#include <string>

#define ADD_ADDRESS( name, mod_name, sig ) address_t name =  mem::find_ida_sig( mod_name, sig )
#define ADD_ADDRESS_FUNCTION( name, func ) address_t name =  func( );

#include <string>

inline bool is_bnet()
{
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);

	// Check if the subfolder name is "_retail_"
	size_t pos = std::wstring(path).find_last_of(L"\\/");
	std::wstring subfolder = std::wstring(path).substr(0, pos);
	return (subfolder.find(L"_retail_") != std::wstring::npos);
}

namespace Settings
{
	struct mem_t
	{
		struct centity_t
		{

			address_t nextState = {};
			/*ADD_ADDRESS_FUNCTION(nextState, []() -> address_t {

				auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 44 0F B7 83 ? ? ? ? 4C 8D 4C 24 ? 0F BF 93 ? ? ? ? B8 ? ? ? ? "));
				if (address == nullptr)
					address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 44 0F B7 83 ? ? ? ? 4C 8D 4C 24 ? 0F BF 93 ? ? ? ? B8 ? ? ? ? "));
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
				});*/



			address_t flags;
			/*	ADD_ADDRESS_FUNCTION(flags, []() -> address_t {

					auto address = mem::find_ida_sig(NULL, XOR("48 69 D1 ? ? ? ? 48 03 D0 48 8B C2 74 1B")).self_offset(0x17);
				if (address == nullptr)
					address = mem::find_ida_sig(NULL, XOR("40 53 48 83 EC 20 4C 8B 0D ? ? ? ? 41 0F B7 D8 4D 85 C9   ")).self_offset(0xC3);
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_TEST && instruction.operands[0].mem.base == ZYDIS_REGISTER_RCX && instruction.operands[0].mem.disp.has_displacement)
					return address_t(instruction.operands[0].mem.disp.value);

				return {};
					});*/

			address_t pose;
			//ADD_ADDRESS_FUNCTION(pose, []() -> address_t {

			//	auto address = address_t(0x1323413453);//mem::find_ida_sig(NULL, XOR("4C 8D 83 ? ? ? ? 49 F7 D0 48 8D 8B ? ? ? ? 4C 33 83 ? ? ? ? 48 "));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA &&  instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});
			address_t prevState;

			/*ADD_ADDRESS_FUNCTION(prevState, []() -> address_t {

				auto address = mem::find_ida_sig(NULL, XOR("4D 8D 48 74 41 8B D7 48 8D 4D E7 E8 ? ? ? ? 8B 56 0C 4C 8D 45 C7 48 8D 4D E7 E8 ? ? ? ?  "));
				if (address == nullptr)
					address = mem::find_ida_sig(NULL, XOR("4D 8D 48 74 41 8B D7 48 8D 4D E7 E8 ? ? ? ? 8B 56 0C 4C 8D 45 C7 48 8D 4D E7 E8 ? ? ? ? "));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA  && instruction.operands[1].mem.disp.has_displacement)
					return address_t(instruction.operands[1].mem.disp.value);

				return {};
				});
*/

			address_t size;

			//ADD_ADDRESS_FUNCTION(size, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("48 69 D1 ? ? ? ? 48 03 D0 48 8B C2 74 1B "));
			//if (address == nullptr)
			//	address = mem::find_ida_sig(NULL, XOR("40 53 48 83 EC 20 4C 8B 0D ? ? ? ? 41 0F B7 D8 4D 85 C9   ")).self_offset(0xA9);
			//if (address == nullptr)
			//	return {};

			//auto instruction = zydis::decode(address);
			//if (instruction.mnemonic == ZYDIS_MNEMONIC_IMUL)
			//	return address_t(instruction.operands[2].imm.is_signed ? instruction.operands[2].imm.value.s : instruction.operands[2].imm.value.u);

			//return {};
			//	});

		}centity;

		struct CgGlobalsMP_t
		{



			/*ADD_ADDRESS_FUNCTION(m_frontEndScene, []() -> address_t {

				auto address = mem::find_ida_sig(NULL, "74 20 49 6B D4 1C ");
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_CMP && instruction.operands[1].mem.disp.has_displacement)
					return address_t(instruction.operands[1].mem.disp.value);

				return {};
				});*/

			address_t PerksArray;

			/*	ADD_ADDRESS_FUNCTION(PerksArray, []() -> address_t {

					auto address = mem::find_ida_sig(NULL, "E8 ? ? ? ? 85 C0 78 2F 8B C8 BA ? ? ? ? ");
					if (address == nullptr)
						return {};

					auto instruction = zydis::decode(address.self_offset(0x1b));
					if (instruction.mnemonic == ZYDIS_MNEMONIC_TEST && instruction.operands[0].mem.disp.has_displacement)
						return address_t(instruction.operands[0].mem.disp.value);

					return {};
					});*/

			address_t frameTime;

			/*		ADD_ADDRESS_FUNCTION(frameTime, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, "C5 FA 2A 87 ? ? ? ? C5 7A 59 15 ? ? ? ?");
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_VCVTSI2SS && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/

			address_t baseGunAngles;

			/*		ADD_ADDRESS_FUNCTION(baseGunAngles, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, "C5 FA 10 8F ? ? ? ? 8B CE E8 ? ? ? ? 8B CE E8 ? ? ? ? ");
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_VMOVSS && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/
			address_t sightedEnemyFools;

			//ADD_ADDRESS_FUNCTION(sightedEnemyFools, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 84 c0 74 ? 09 b4 9f"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address.offset(0x9));
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_OR && instruction.operands[0].mem.disp.has_displacement)
			//		return address_t(instruction.operands[0].mem.disp.value); //cod.exe + 2079F1B - 41 21 94 87 30E90C00 - and [r15 + rax * 4 + 000CE930], edx

			//	return {};
			//	});

			address_t FOV;

			//ADD_ADDRESS_FUNCTION(FOV, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("C5 FA 11 ? ? ? ? ? E8 ? ? ? ? C5 FA 58 54 24 ? C5 FA 11 54 24"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_VMOVSS && instruction.operands[0].mem.disp.has_displacement)
			//		return address_t(instruction.operands[0].mem.disp.value);

			//	return {};
			//	});

			address_t RefDef;

			/*		ADD_ADDRESS_FUNCTION(RefDef, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("48 8D 93 ? ? ? ? 48 C7 83 ? ? ? ? ? ? ? ? 44 8B C6 8B CF 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 30 5F E9 ? ? ? ? "));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/

			address_t equippedOffHand;

			//ADD_ADDRESS_FUNCTION(equippedOffHand, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("4c 8d 83 ? ? ? ? 8b ce e8 ? ? ? ? 8b ce"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);
			//	
			//	return {};
			//	});


			address_t weaponSelect;

			/*	ADD_ADDRESS_FUNCTION(weaponSelect, []() -> address_t {

					auto address = mem::find_ida_sig(NULL, XOR("48 8d 93 ? ? ? ? 4c 8d 83 ? ? ? ? 8b ce"));
					if (address == nullptr)
						return {};

					auto instruction = zydis::decode(address);
					if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
						return address_t(instruction.operands[1].mem.disp.value);

					return {};
					});*/


			address_t zoomSensitivity;

			/*		ADD_ADDRESS_FUNCTION(zoomSensitivity, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("c5 fa 10 8f ? ? ? ? 8b ce e8 ? ? ? ? 44 0f b6 8f"));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_VMOVSS && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/


			address_t offsetAngles;

			/*		ADD_ADDRESS_FUNCTION(offsetAngles, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("4c 8d 8b ? ? ? ? 48 8d 54 24 ? e8"));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value + 0xA0);

						return {};
						});*/

			address_t extrabuttons;

			/*		ADD_ADDRESS_FUNCTION(extrabuttons, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("48 c7 87 ? ? ? ? ? ? ? ? 48 8d 97 ? ? ? ? 44 8b c5"));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/


			address_t playerTeleported;

			//ADD_ADDRESS_FUNCTION(playerTeleported, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("0A 99 ? ? ? ? 48 81 C1 ? ? ? ? E8 ? ? ? ? 84 C0 75 33 8B 86 ? ? ? ? 83 F8 01 74 28"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_OR && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});

			address_t predictedPlayerState;

			/*ADD_ADDRESS_FUNCTION(predictedPlayerState, []() -> address_t {

				auto address = mem::find_ida_sig(NULL, XOR("48 8d 8a ? ? ? ? e8 ? ? ? ? c5 f0 57 c9 c5"));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address);
				if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
					return address_t(instruction.operands[1].mem.disp.value);

				return {};
				});*/

			address_t predictedPlayerEntity;

			/*		ADD_ADDRESS_FUNCTION(predictedPlayerEntity, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("C5 FA 11 7C 24 ? E8 ? ? ? ? C5 AA 58 8D ? ? ? ? "));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address.self_offset(0x63));
						if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/

			address_t Time;

			/*		ADD_ADDRESS_FUNCTION(Time, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("8B 83 ? ? ? ? 48 8B CE 2B 83 ? ? ? ? 2B"));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/


			address_t kickAVel;

			/*	ADD_ADDRESS_FUNCTION(kickAVel, []() -> address_t {

					auto address = mem::find_ida_sig(NULL,XOR("E8 ? ? ? ? 48 8B C8 48 8B D7 E8 ? ? ? ? C5 F8 57 C0 C5 F8 2E"));
					if (address == nullptr)
						return {};

					auto instruction = zydis::decode(address.self_offset(0x2C));
					if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
						return address_t(instruction.operands[1].mem.disp.value);

					return {};
					});*/

			address_t rawKickAngles;

			//ADD_ADDRESS_FUNCTION(rawKickAngles, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 41 8B 7F 0C 4C 8D A6 ? ? ? ? 4C 8B F0"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address.self_offset(0x9));
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});

			address_t kickAngles;

			//ADD_ADDRESS_FUNCTION(kickAngles, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 41 8B 7F 0C 4C 8D A6 ? ? ? ? 4C 8B F0"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address.self_offset(0x43));
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});

			address_t shellshock;

			//ADD_ADDRESS_FUNCTION(shellshock, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("85 C0 7E 10 ? ? ? ? ? ? ? ? ? 08 01 41 0F 45 C1 C3"));
			//	if (address == nullptr)
			//		address =  mem::find_ida_sig(NULL, XOR("85 C0 7E 10 ? ? ? ? ? ? 08 01 41 0F 45 C1 C3"));

			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address.offset(0x4));
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});

			address_t characterinfo_ptr;

			//ADD_ADDRESS_FUNCTION(characterinfo_ptr, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("4D 8D 84 24 ? ? ? ? F3 AA 48 8B CE 49 8D 97 ? ? ? ? E8 ? ? ? ? 8B 05 ? ? ? ? 48 8D 4D C0 ")); // need fix
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});

		} CgGlobalsMP;

		struct BG_t
		{
			address_t BG_GetEntityWorldTagPosition;
			address_t v11_Offsets;
			/*	ADD_ADDRESS_FUNCTION(BG_GetEntityWorldTagPosition, [&]() -> address_t {
					auto address = mem::find_ida_sig(NULL, XOR("4c 89 4c 24 ? 44 89 44 24 ? 55 53 56 57 41 54 41 56 41 57 48 8b ec"));
					if (address == nullptr)
						return {};


					return address;
					});*/
		} BG;

		struct refdef_t
		{
			address_t playerTeleport;

			/*		ADD_ADDRESS_FUNCTION(playerTeleport, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("41 0f b6 80 ? ? ? ? 88 42 ? 49 8d 80"));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_MOVZX && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/
		} ref_def;

		struct CharacterInfo_t
		{


			address_t subtract;

			//ADD_ADDRESS_FUNCTION(subtract, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("49 8d 97 ? ? ? ? e8 ? ? ? ? 8b 05 ? ? ? ? 48 8d 4d"));// need fix
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return {};
			//	});
			address_t team;


			/*		ADD_ADDRESS_FUNCTION(team, []() -> address_t {

						auto address = mem::find_ida_sig(NULL, XOR("3A 88 ? ? ? ? 0F 84 ? ? ? ?"));
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address);
						if (instruction.mnemonic == ZYDIS_MNEMONIC_CMP && instruction.operands[1].mem.disp.has_displacement)
							return address_t(instruction.operands[1].mem.disp.value);

						return {};
						});*/

			address_t size;

			//ADD_ADDRESS_FUNCTION(size, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("48 69 d3 ? ? ? ? 48 03 96"));// need fix
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_IMUL )
			//		return address_t(instruction.operands[2].imm.is_signed ? instruction.operands[2].imm.value.s : instruction.operands[2].imm.value.u);

			//	return {};
			//	});


			//ADD_ADDRESS_FUNCTION(viewangle, []() -> address_t {

				//auto address = mem::find_ida_sig(NULL, "c4 c1 7a ? ? 84 61 ? 00 c4");
				//if (address == nullptr)
				//	return {};

				//auto instruction = zydis::decode(address);
				//if (instruction.mnemonic == ZydisMnemonic::ZYDIS_MNEMONIC_VMOVSS && instruction.operands[1].mem.disp.has_displacement)
				//	return address_t(instruction.operands[1].mem.disp.value);

				//return {};
				//});


		}CG_CharacterInfo;

		struct playerstate_Pointer
		{

			address_t aimSpreadScale;

			//ADD_ADDRESS_FUNCTION(aimSpreadScale, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, "C5 FA 11 97 ? ? ? ? 49 8B D7 48 8B CE E8 ? ? ? ? 41 0F B6 C6 ");
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_VMOVSS && instruction.operands[0].mem.disp.has_displacement)
			//		return address_t(instruction.operands[0].mem.disp.value);

			//	return {};
			//	});
			address_t ps_ptr;

			//ADD_ADDRESS_FUNCTION(ps_ptr, []() -> address_t {

			//	auto address = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 48 8d 05 ? ? ? ? 8b d7 4a 8b 0c f0"));
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic != ZydisMnemonic::ZYDIS_MNEMONIC_CALL)
			//		return {};

			//	address = address.self_jmp(0x1);
			//	address = address.self_offset(0xA);
			//	instruction = zydis::decode(address);

			//	if (instruction.mnemonic == ZydisMnemonic::ZYDIS_MNEMONIC_LEA)
			//		 return (address_t(address.self_jmp(0x3) - 0x28));

			//	return {};
			//	});
		}playerstate_P;

		struct ClStatic_t
		{

		}ClStatic;

		struct CLActiveClient_t
		{

			address_t cmdNumber;

			/*	ADD_ADDRESS_FUNCTION(cmdNumber, []() -> address_t {
					auto address = mem::find_ida_sig(NULL, XOR("8D 87 ? ? ? ? 33 87 ? ? ? ? 8D 58 02 0F AF D8 33 9F ? ? ? ? 3B F3 7E 17 41 B8 ? ? ? ? "));
					if (address == nullptr)
						return {};

					auto instruction = zydis::decode(address);
					if (instruction.operands[1].mem.disp.has_displacement)
						return address_t(instruction.operands[1].mem.disp.value);

					return {};
					});*/
			address_t cmd_number_aab;

			/*ADD_ADDRESS_FUNCTION(cmd_number_aab, []() -> address_t {
				auto address = mem::find_ida_sig(NULL, XOR("8D 87 ? ? ? ? 33 87 ? ? ? ? 8D 58 02 0F AF D8 33 9F ? ? ? ? 3B F3 7E 17 41 B8 ? ? ? ?"));
				if (address == nullptr)
					return {};

				auto instruction = zydis::decode(address.offset(0x6));
				if (instruction.operands[1].mem.disp.has_displacement)
					return address_t(instruction.operands[1].mem.disp.value);

				return {};
				});*/

				//ADD_ADDRESS_FUNCTION(usercmd, [&]() -> address_t {
				//	auto address = mem::find_ida_sig(NULL, { XOR("48 8D 47 60 48 03 C6 90 48 8D 80 ? ? ? ? C5 F8 10 01 48 8D 89 ? ? ? ?  ") });
				//	if (address == nullptr)
				//		/*		 address = mem::find_ida_sig(NULL, { XOR("48 8D 87 ? ? ? ? 48 03 C6 48 8D 80 ? ? ? ? C5 F8 10 01 ") });
				//			if (address == nullptr)*/
				//		return {};

				//		auto instruction = zydis::decode(address);
				//		if (instruction.operands[1].mem.disp.has_displacement)
				//			return address_t(instruction.operands[1].mem.disp.value);

				//	return address;
				//	});


			address_t usercmd;

			/*	ADD_ADDRESS_FUNCTION(usercmd, [&]() -> address_t {
					auto address = mem::find_ida_sig(NULL, { XOR("E8 ? ? ? ? 8D 43 80 3B F0 0F 8E ? ? ? ? 85 F6 0F 8E ? ? ? ? 48 81 C7 ? ? ? ? 83 E6 7F 41 B8") });
					if (address == nullptr)
						return {};

					auto instruction = zydis::decode(address.self_offset(0x18));



					if (instruction.mnemonic == ZYDIS_MNEMONIC_ADD)
					{
						address = address.offset(0x3);
						if(!is_bnet())
						return address_t(*address.cast<uint32_t*>());
						else
						return address_t(*address.cast<uint32_t*>());


					}

					return address;
					});*/

			address_t seed;

			/*		ADD_ADDRESS_FUNCTION(seed, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, { XOR("8B 8B ? ? ? ? 8D 83 ? ? ? ? 03 8B ? ? ? ? 41 B8 ? ? ? ? C5 E2 59 25 ? ? ? ?") });
						if (address == nullptr)
							return {};

						auto instruction = zydis::decode(address.offset(0xC));
						if (instruction.mnemonic == ZYDIS_MNEMONIC_ADD)
						{

							return address_t(instruction.operands[1].mem.disp.value);

						}

						return address;
						});*/

			address_t angle;

			//ADD_ADDRESS_FUNCTION(angle, [&]() -> address_t {
			//	//auto address = mem::find_ida_sig(NULL, { XOR("8B 8B ? ? ? ? 8D 83 ? ? ? ? 03 8B ? ? ? ? 41 B8 ? ? ? ? C5 E2 59 25 ? ? ? ?") });
			//	//if (address == nullptr)
			//	//	return {};

			//	//auto instruction = zydis::decode(address.offset(0x6));
			//	//if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA)
			//	//	return address_t(instruction.operands[1].mem.disp.value);

			//	//return address;
			//	//});



		}CLActiveClient;

		struct Scriptable_t
		{

			address_t CG_ClientModel_RuntimeData;

			//ADD_ADDRESS_FUNCTION(CG_ClientModel_RuntimeData, [&]() -> address_t { 
			//	auto address = mem::find_ida_sig(NULL, { XOR("49 8d 8f ? ? ? ? 42 c6 84 3e") });
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_LEA && instruction.operands[1].mem.disp.has_displacement)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return address;
			//	});
			address_t LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex;

			//ADD_ADDRESS_FUNCTION(LUI_DataBinding_Interactions_GetLootItemFromScriptableIndex, [&]() -> address_t {
			//	auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? 48 85 C0 74 20 48 8B 10 48 8B CE E8 ? ? ? ? B8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 48 83 C4 20 5F C3 "));
			//	if (address == nullptr)
			//		return {};


			//	return address.self_jmp(1);
			//	});

			address_t scriptable_id;


			//ADD_ADDRESS_FUNCTION(scriptable_id, [&]() -> address_t { //0CB33E10
			//	auto address = mem::find_ida_sig(NULL, { XOR("41 C7 84 84") });
			//	if (address == nullptr)
			//		return {};

			//	auto instruction = zydis::decode(address);
			//	if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV)
			//		return address_t(instruction.operands[1].mem.disp.value);

			//	return address;
			//	});


			address_t ClientContext;

			//ADD_ADDRESS_FUNCTION(ClientContext, [&]() -> address_t { 
				//auto address = mem::find_ida_sig(NULL, { XOR("49 8b 84 f0 ? ? ? ? 48 69 ca") });
				//if (address == nullptr)
				//	return {};

				//auto instruction = zydis::decode(address);
				//if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV && instruction.operands[1].mem.disp.has_displacement)
				//	return address_t(instruction.operands[1].mem.disp.value );

				//return address;
				//});


		}scriptable;

		/*struct GScr_t
		{
			ADD_ADDRESS_FUNCTION(GScr_EndLobby, [&]() -> address_t {
				auto address = mem::find_ida_sig(NULL, XOR("B9 AD 0C 00 00 E8"));
				if (address == nullptr)
					return {};

				while (address.get<uint8_t>() != static_cast<uint8_t>(0xCC))
					address.self_offset(0x1);

				while (address.get<uint8_t>() == static_cast<uint8_t>(0xCC))
					address.self_offset(0x1);

				return address;
				});
		} GScr;*/

		struct Lua_t
		{

			address_t luaVM;

			/*		ADD_ADDRESS_FUNCTION(luaVM, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("48 8b 0d ? ? ? ? ba ? ? ? ? 44 8b c2 e8 ? ? ? ? 85 c0 74 ? 48 8b 15 ? ? ? ? 48 8d 0d ? ? ? ? e8 ? ? ? ? 48 8b 0d"));
						if (address == nullptr)
							return {};

						return address.self_jmp(0x3);
						});*/
			address_t j_lua_remove;

			//ADD_ADDRESS_FUNCTION(j_lua_remove, [&]() -> address_t {
			//	auto address = mem::find_ida_sig(NULL, XOR("E8 ? ? ? ? EB 11 41 B8 ? ? ? ? 48 8B D3 48 8B CE E8 ? ? ? ? "));
			//	if (address == nullptr)
			//		return {};

			//	return address.self_jmp(1);
			//	});
			address_t lua_pushstring;

			//ADD_ADDRESS_FUNCTION(lua_pushstring, [&]() -> address_t {
			//	auto address = mem::find_ida_sig(NULL, XOR("48 89 5C 24 ? 57 48 83 EC 20 48 8B FA 48 8B D9 48 85 D2 75 10 48 8B 41 28 49 C7 C0 ? ? ? ? 4C 89 00 EB 54 48 8B 49 10 48 8B 81 ? ? ? ? 48 39 81 ? ? ? ? 72 08 48 8B CB E8 ? ? ? ? 49 C7 C0 ? ? ? ? "));
			//	if (address == nullptr)
			//		return {};

			//	return address;
			//	});
			address_t LuaShared_PCall;

			/*		ADD_ADDRESS_FUNCTION(LuaShared_PCall, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("e8 ? ? ? ? 85 c0 74 ? 48 8b 15 ? ? ? ? 48 8d 0d ? ? ? ? e8 ? ? ? ? 48 8b 0d"));
						if (address == nullptr)
							return {};

						return address.self_jmp(1);
						});*/
			address_t lua_getfield;

			/*		ADD_ADDRESS_FUNCTION(lua_getfield, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("48 89 5c 24 ? 48 89 74 24 ? 57 48 83 ec ? 49 8b d8 48 8b f9 e8"));
						if (address == nullptr)
							return {};

						return address;
						});*/
			address_t lua_pushinteger;

			/*		ADD_ADDRESS_FUNCTION(lua_pushinteger, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("48 8b 41 ? c5 f8 57 c0 c4 ? fb"));
						if (address == nullptr)
							return {};

						return address;
						});*/
			address_t lua_pushboolean;

			//ADD_ADDRESS_FUNCTION(lua_pushboolean, [&]() -> address_t {
			//	auto address = mem::find_ida_sig(NULL, XOR("48 8B 41 28 45 33 C0 85 D2 41 0F 95 C0 49 FF C0 49 C1 E0 2F 49 F7 D0 4C 89 00 48 83 41 ? ? 48 8B 41 28 48 3B 41 30 0F 83 ? ? ? ? C3 "));
			//	if (address == nullptr)
			//		return {};

			//	return address;
			//	});

			ADD_ADDRESS(CG_ViewMP_DrawActiveFrame, NULL, { XOR("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 C5 F8 29 BC 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85") });

			address_t lua_registerFunction;

			//ADD_ADDRESS_FUNCTION(lua_registerFunction, [&]() -> address_t {
			//	auto address = mem::find_ida_sig(NULL, XOR("48 89 5C 24 ? 57 48 83 EC 20 49 8B D8 48 8B F9 45 33 C0 E8 ? ? ? ? 45 33 C0 48 8B D3 48 8B CF E8 ? ? ? ? BA ? ? ? ? 48 8B CF "));
			//	if (address == nullptr)
			//		return {};

			//	return address;
			//	});

			address_t lua_gettop;

			/*		ADD_ADDRESS_FUNCTION(lua_gettop, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("48 8B 41 28 48 2B 41 20 48 C1 F8 03 C3 "));
						if (address == nullptr)
							return {};

						return address;
						});*/
			address_t lua_settop;

			/*		ADD_ADDRESS_FUNCTION(lua_settop, [&]() -> address_t {
						auto address = mem::find_ida_sig(NULL, XOR("48 89 5C 24 ? 57 48 83 EC 20 48 63 FA 48 8B D9 85 D2 78 64 4C 8B 41 20 48 8B 49 28 49 8D 04 F8 48 3B C1 76 44 "));
						if (address == nullptr)
							return {};

						return address;
						});*/


		} lua;

		struct GameFunction
		{
			uintptr_t playerstat2e;
			address_t UI_SafeTranslateString;
			address_t BG_GetPlayerEyePosition;
			address_t CG_Handler;
			address_t CG_GetEntWeapon;
			address_t CG_GetWeaponDisplayName;
			address_t MSG_PackSignedFloat;
			address_t MSG_UnPackSignedFloat;
			address_t ClActiveClient;
			address_t LegacyTrace;
			address_t CG_GetPoseOrigin;
			address_t CL_SetViewAngle;
			address_t CG_View_GetFovDvarDefaultValue;
			address_t CG_View_GetFovDvarValue;
			address_t CG_SnapshotMP_GetNextSnap;
			address_t CG_SnapshotMP_GetPrevSnap;
			address_t BG_GetBallisticInfo;
			address_t BG_Ballistics_TravelTimeForDistance;
			address_t Dvar_GetFloatSafe;
			address_t missile;
			address_t targetassist;
			address_t GPad_GetButton;
			address_t GPad_isActive;
			address_t BG_GetThirdPersonCrosshairOffset;
			address_t BG_IsThirdPersonMode;
			address_t R_AddDObjToScene;
			address_t CG_GetViewFovBySpace;
			address_t CG_PredictMP_PredictPlayerState;
			address_t BG_WeaponFireRecoil;
			address_t CL_GetAgentName;
			address_t BG_CalculateFinalSpreadForWeapon;
			address_t BG_GetSpreadForWeapon;
			address_t SL_ConvertToString;
			address_t BulletHitEvent_Internal;
			address_t sys_milliseconds;
			address_t LUI_CoD_LuaCall_Exec;
			address_t LUI_CoD_LuaCall_Exec_now;
			address_t unknown_macaddress;
			address_t Plat_GetMacAddressAsUint64;
			address_t CgHandler_GetScriptableDimensions;
			address_t CG_ClientModel_GetModel;
			address_t BG_IsRiotShield;
			address_t AimTargetMP_GetTargetBounds;
			address_t BG_GetWeaponFlashTagname;
			address_t AimTargetCalcMuzzlePointMP_GetTargetBounds;
			address_t Slide_EndCheck;
			address_t CG_ViewMP_DrawActiveFrame;
			address_t CgTrajectory_CgTrajectory;
			address_t BgTrajectory_EvaluatePosTrajectory;
			address_t BgTrajectory_LegacyEvaluateTrajectory;
			address_t CL_PlayerData_SetCustomClanTag;
			address_t unknow_func;
			address_t CG_EntityMP_CalcLerpPositions;
			address_t CG_ScoreboardMP_GetClientScore;
			address_t Live_GetMACAddressAsUint64;
			address_t CalcMuzzlePoint;



			address_t bdAntiCheat_reportExtendedAuthInfo;
			address_t Plat_GetMachineID;
			address_t hwidprofileshit;
			address_t Live_GetXuid;
			address_t DWServicesAccess_GetInstance;
			address_t DWServicesAccess_GetLogin;



			address_t Com_DDL_CreateContext;
			address_t Com_DDL_LoadAsset;
			address_t CL_PlayerData_GetDDLBuffer;
			address_t DDL_GetRootState;
			address_t DDL_MoveToPath;
			address_t DDL_GetType;
			address_t DDL_SetInt;
			address_t DDL_SetEnum;
			address_t DDL_SetString;
			address_t Com_ParseNavStrings;



			address_t packet_test;
			address_t bdEventLog;
			address_t bdEventInfo;
			address_t bdEventLog_recordEventsMixed;
			address_t somerandomfunclol;



		}gamefunction;

		address_t CgWeaponSystem__ms_weaponSystemArray;
		address_t CgVehicleSystem__ms_vehicleSystemArray;

		address_t networkadapterMacptr;
		address_t swapchain;
		address_t commandqueue;
		address_t Weaponmap;
		address_t clientinfo;
		address_t DVARBOOL_cl_packetdup;
		address_t trampoline;
		address_t refdef;
		address_t FrontendCheck;
		address_t s_trbase_aab;
		address_t aXpartydisbanda;
		address_t Gscr_endlobby;




		//ADD_ADDRESS_FUNCTION(v11_Offsets, []() -> address_t {
		//	auto addr = mem::find_ida_sig(NULL, XOR("44 8B 83 ? ? ? ? 8D 8B ? ? ? ? 41 33 c8 48 89 44 24 58"));
		//	if (addr == nullptr)
		//		return {};

		//	auto instruction = zydis::decode(addr);
		//	if (instruction.mnemonic == ZYDIS_MNEMONIC_MOV)
		//		return address_t(instruction.operands[1].mem.disp.value);

		//	return {};
		//	});


	//	if (log == 1
	};

	extern mem_t mem;

}


