#pragma once


struct ClActiveClient_t
{
	OFFSET(unsigned int, cmd_number_aab, Settings::mem.CLActiveClient.cmd_number_aab);
	OFFSET(int, cmdNumber, Settings::mem.CLActiveClient.cmdNumber);
	OFFSET(uint32_t, Angle, Settings::mem.CLActiveClient.angle);

	int GetCmdNumber();
	void SetCmdNumber(int cmdNumber_new);

	void SetViewAngles(math::angle_t newAngles);

	math::angle_t Get_Angle();
	void SetAngle(math::angle_t* angles);

	game_struct::usercmd_t* CL_GetUserCmd(int sequence_number);
	uintptr_t* CL_GetUserCmdTest(int sequence_number);

};
inline ClActiveClient_t* hooked_ptr = nullptr;