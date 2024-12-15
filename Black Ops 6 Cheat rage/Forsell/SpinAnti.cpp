#include "includes.h"

namespace aimbot
{
	//void MovementFix(game_struct::usercmd_t* usercmd, float yaw);
}

namespace antiaim
{
	//void AntiAimPitch(game_struct::usercmd_t* newCmd)
	//{
	//	if (!newCmd)
	//		return;

	//	if (!game_sdk::in_game())
	//		return;

	//	if (!game_sdk::GetRefDef())
	//		return;


	//	math::angle_t local_angles{};
	//	game_sdk::VecToAngle(game_sdk::GetRefDef()->view.axis[0], local_angles);

	//	math::angle_t delta_angles;
	//	delta_angles.x = ctx::client.ps->deltaAngle.x;/* -aimbot::Angle_Normalize(ctx::client.angle.x - local_angles.x);*/


	//	math::angle_t AntiAimAngles{};
	//	if (Settings::Aimbot::Anti_aim_pitch_selection == 0)
	//	{
	//		AntiAimAngles.x = 0.0f - delta_angles.x;
	//	}

	//	else if (Settings::Aimbot::Anti_aim_pitch_selection == 1)
	//	{
	//		AntiAimAngles.x = -85.0f - delta_angles.x;
	//	}

	//	else if (Settings::Aimbot::Anti_aim_pitch_selection == 2)
	//	{
	//		AntiAimAngles.x = 85.0f - delta_angles.x;
	//	}

	//	else if (Settings::Aimbot::Anti_aim_pitch_selection == 3)
	//	{
	//		static bool bMode = false;

	//		switch (bMode)
	//		{
	//		case false:
	//			AntiAimAngles.x = -80.f - delta_angles.x;
	//			bMode = true;
	//			break;

	//		case true:
	//			AntiAimAngles.x = 80.f - delta_angles.x;
	//			bMode = false;
	//			break;
	//		}
	//	}

	//	else if (Settings::Aimbot::Anti_aim_pitch_selection == 4)
	//	{
	//		std::random_device Device;
	//		std::uniform_real_distribution<float> RandomPitch(-85.0f, 85.0f);

	//		AntiAimAngles.x = RandomPitch(Device) - delta_angles.x;
	//	}

	//	else if (Settings::Aimbot::Anti_aim_pitch_selection == 5)
	//	{
	//		AntiAimAngles.x = 45.f - local_angles.x;

	//		if (AntiAimAngles.x > 85.0f) AntiAimAngles.x = 85.0f;
	//		if (AntiAimAngles.x < -85.0f) AntiAimAngles.x = -85.0f;

	//		AntiAimAngles.x -= delta_angles.x;

	//	}
	//	if (Settings::Aimbot::AntiAim_pitch)
	//	{
	//		newCmd->angle[0] = GameFunction::BG::BG_UsrCmdPackAngle(AntiAimAngles.x);
	//		aimbot::MovementFix(newCmd, delta_angles.x - ctx::client.ps->deltaAngle.x);
	//	}
	//}
	//void AntiAimYaw(game_struct::usercmd_t* newCmd)
	//{

	//	if (!newCmd)
	//		return;

	//	if (!game_sdk::in_game())
	//		return;

	//	if (!game_sdk::GetRefDef())
	//		return;



	//	math::angle_t local_angles{};
	//	game_sdk::VecToAngle(game_sdk::GetRefDef()->view.axis[0], local_angles);

	//	math::angle_t delta_angles{};
	//	delta_angles.y = ctx::client.ps->deltaAngle.y; //-aimbot::Angle_Normalize(ctx::client.angle.y - local_angles.y);

	//	math::angle_t AntiAimAngles{};

	//	if (Settings::Aimbot::Anti_aim_yaw_selection == 0)
	//	{
	//		AntiAimAngles.x = 0.0f - delta_angles.x;

	//	}

	//	else if (Settings::Aimbot::Anti_aim_yaw_selection == 1)
	//	{
	//		static float flAngle = 0.0f;

	//		if (flAngle > 180.0f)
	//			flAngle -= 360.0f;

	//		AntiAimAngles.y = flAngle - delta_angles.y;

	//		flAngle += 10.0f;
	//	}

	//	else if (Settings::Aimbot::Anti_aim_yaw_selection == 2)
	//	{
	//		/*static int iMode = 1;

	//		switch (iMode)
	//		{
	//		case 1:
	//			AntiAimAngles.y = 0.0f - delta_angles.y;
	//			iMode = 2;
	//			break;

	//		case 2:
	//			AntiAimAngles.y = 90.0f - delta_angles.y;
	//			iMode = 3;
	//			break;

	//		case 3:
	//			AntiAimAngles.y = 180.0f - delta_angles.y;
	//			iMode = 4;
	//			break;

	//		case 4:
	//			AntiAimAngles.y = -90.0f - delta_angles.y;
	//			iMode = 1;
	//			break;
	//		}*/

	//		switch (newCmd->commandTime % 4)
	//		{
	//		case 0:
	//			AntiAimAngles.y = 0.0f - delta_angles.y;
	//			break;

	//		case 1:
	//			AntiAimAngles.y = 90.0f - delta_angles.y;
	//			break;

	//		case 2:
	//			AntiAimAngles.y = 180.0f - delta_angles.y;
	//			break;

	//		case 3:
	//			AntiAimAngles.y = 269.0f - delta_angles.y;
	//			break;
	//		}

	//	}

	//	else if (Settings::Aimbot::Anti_aim_yaw_selection == 3)
	//	{
	//		std::random_device Device;
	//		std::uniform_real_distribution<float> RandomYaw(-179.0f, 179.0f);

	//		AntiAimAngles.y = RandomYaw(Device) - delta_angles.y;
	//	}

	//	else if (Settings::Aimbot::Anti_aim_yaw_selection == 4)
	//	{

	//		AntiAimAngles.y = local_angles.y - 180.0f;

	//		while (AntiAimAngles.y > 180.0f) AntiAimAngles.y -= 360.0f;
	//		while (AntiAimAngles.y < -180.0f) AntiAimAngles.y += 360.0f;

	//		AntiAimAngles.y -= delta_angles.y;
	//	}

	//	if (GetAsyncKeyState(anti_aim_yaw_key))
	//	{
	//		Settings::Aimbot::AntiAim_yaw = !Settings::Aimbot::AntiAim_yaw;

	//	}

	//	if (Settings::Aimbot::AntiAim_yaw)
	//	{
	//		newCmd->angle[1] = GameFunction::BG::BG_UsrCmdPackAngle(AntiAimAngles.y);
	//		aimbot::MovementFix(newCmd, delta_angles.y - ctx::client.ps->deltaAngle.y);

	//	}
	//}
}