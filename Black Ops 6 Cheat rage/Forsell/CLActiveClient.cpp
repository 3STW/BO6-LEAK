#include"includes.h"


ClActiveClient_t* GameFunction::CL::GetClActiveClient(game_struct::LocalClientNum_t LocalClientNum)
{
	return VariadicCall<ClActiveClient_t*>(Settings::mem.gamefunction.ClActiveClient.cast(), LocalClientNum);
}

void GameFunction::CL::CL_SetFOVSensitivityScale(game_struct::LocalClientNum_t localClientNum, double scale)
{
	//VariadicCall<void>(Settings::mem.gamefunction.CL_SetFOVSensitivityScale.cast(), localClientNum, scale);
}

void GameFunction::CL::CL_CGameMP_SetUserCmdAimValues(game_struct::LocalClientNum_t localClientNum, const math::vec3_t* kickAngles)
{
	//VariadicCall<void>(Settings::mem.gamefunction.CL_CGameMP_SetUserCmdAimValues.cast(), localClientNum, kickAngles);

}

void GameFunction::CL::CL_SetUserCmdWeapons(int a1, game_struct::Weapon_t*  a2, game_struct::Weapon_t*  a3, bool a4)
{
	//VariadicCall<void>(Settings::mem.gamefunction.CL_SetUserCmdWeapons.cast(), a1, a2, a3, a4);

}

void GameFunction::CL::CL_SetExtraButtons(game_struct::LocalClientNum_t localClientNum, unsigned __int64 buttons)
{
	//VariadicCall<void>(Settings::mem.gamefunction.CL_SetExtraButtons.cast(), localClientNum, buttons);

}

const char* GameFunction::CL::CL_GetAgentName(int index, int ownerIndex)
{
	char buff[0x60i64];
	//VariadicCall<__int64>(Settings::mem.gamefunction.CL_GetAgentName.cast(), 0, index, ownerIndex, buff, 0x60i64);

	return std::string(buff).c_str();
}

void GameFunction::CL::CL_SetCustomClanTag(int localClientNum, const char* clantag)
{
	VariadicCall<void>(Settings::mem.gamefunction.CL_PlayerData_SetCustomClanTag.cast(), localClientNum, clantag);

}


int ClActiveClient_t::GetCmdNumber()
{
	auto a1 = (uintptr_t)this;
	return cmdNumber() ^ (((a1 + Settings::mem.CLActiveClient.cmdNumber.cast()) ^ cmd_number_aab()) * (((a1 + Settings::mem.CLActiveClient.cmdNumber.cast()) ^ cmd_number_aab()) + 2));
}
void ClActiveClient_t::SetCmdNumber(int cmdNumber_new)
{
	auto a1 = (uintptr_t)this;
	*(int*)(a1 + Settings::mem.CLActiveClient.cmdNumber.cast()) = (((__int64)a1+ Settings::mem.CLActiveClient.cmdNumber.cast()) ^ *(int*)(a1 + Settings::mem.CLActiveClient.cmd_number_aab.cast())) *
		(((__int64(a1 + Settings::mem.CLActiveClient.cmdNumber.cast()) ^ *(int*)(a1 + Settings::mem.CLActiveClient.cmdNumber.cast())) + 2)) ^ cmdNumber_new; // this is ud chat
}

void ClActiveClient_t::SetViewAngles(math::angle_t newAngles)
{
	auto addr = Settings::mem.gamefunction.CL_SetViewAngle.cast<void(*)(CgGlobalsMP*, math::angle_t) >();
	spoof_call<void>(Settings::mem.trampoline.cast<void*>(), addr, Settings::client.cg, newAngles);
}

game_struct::usercmd_t* ClActiveClient_t::CL_GetUserCmd(int sequence_number)
{
	return reinterpret_cast<game_struct::usercmd_t*>((uintptr_t)this + Settings::mem.CLActiveClient.usercmd.cast() + ((sequence_number & 0x7F) * 0x240));
	//return reinterpret_cast<game_struct::usercmd_t*>((uintptr_t)this + Settings::mem.CLActiveClient.usercmd.cast() + ((9 * (sequence_number & 0x7F) ) << 6));

}

uintptr_t* ClActiveClient_t::CL_GetUserCmdTest(int sequence_number)
{
	return reinterpret_cast<uintptr_t*>((uintptr_t)this + Settings::mem.CLActiveClient.usercmd.cast() + ((sequence_number & 0x7F) * 0x240));

}


math::angle_t ClActiveClient_t::Get_Angle()
{
	
	const auto input = (uintptr_t)this;
	const auto key = *reinterpret_cast<uint32_t*>(input + Settings::mem.CLActiveClient.seed);

	const auto low_x = static_cast<uint32_t>(input + Settings::mem.CLActiveClient.angle);
	const auto low_y = static_cast<uint32_t>(input + Settings::mem.CLActiveClient.angle + 4);

	const auto x = *reinterpret_cast<uint32_t*>(input + Settings::mem.CLActiveClient.angle ) ^ ((low_x ^ key) * ((low_x ^ key) + 2));
	const auto y = *reinterpret_cast<uint32_t*>(input + Settings::mem.CLActiveClient.angle + 4) ^ ((low_y ^ key) * ((low_y ^ key) + 2));

	return { *(float*)&x ,*(float*)&y,0 };


}


void ClActiveClient_t::SetAngle(math::angle_t* angles)
{
	const auto input = (uintptr_t)this;
	const auto key = *reinterpret_cast<uint32_t*>(input + Settings::mem.CLActiveClient.seed);

	const auto low_x = static_cast<uint32_t>(input + Settings::mem.CLActiveClient.angle);
	const auto low_y = static_cast<uint32_t>(input + Settings::mem.CLActiveClient.angle + 4);

	const auto x = *(uint32_t*)(&angles->x) ^ ((key ^ low_x) * ((key ^ low_x) + 2));
	const auto y = *(uint32_t*)(&angles->y) ^ ((low_y ^ key) * ((low_y ^ key) + 2));

	*reinterpret_cast<uint32_t*>(input + Settings::mem.CLActiveClient.angle) = x;
	*reinterpret_cast<uint32_t*>(input + Settings::mem.CLActiveClient.angle + 4) = y;
}