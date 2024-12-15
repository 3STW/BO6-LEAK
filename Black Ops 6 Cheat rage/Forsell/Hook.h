#pragma once
#include"input_controls.h"
#include <WinSock2.h>
#include <iphlpapi.h>
#include <time.h>

#pragma comment(lib, "iphlpapi.lib")
#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))
#define GetSign(a) ((a)?((*(int*)&(a)>>31)|1):0)

inline std::mutex hook_mutex;
inline std::recursive_mutex render_hook;
inline std::recursive_mutex visualhook;

inline uintptr_t orig;

extern  void  hk_wow64_prepare_for_exception(PEXCEPTION_RECORD exception_record, PCONTEXT context);
typedef void(__stdcall* wow64_prepare_for_exception_fn)(PEXCEPTION_RECORD exception_record, PCONTEXT context);
inline wow64_prepare_for_exception_fn o_wow64_prepare_for_exception = nullptr;

inline uintptr_t bdEventLog_recordEventsMixed_ORIGINAL;
inline int64_t __fastcall bdEventLog_recordEventsMixed(int64_t a1, int64_t* result, int64_t* eventInfo, uint32_t count, int64_t eventLogIDs)
{
	return 0;
}

inline void generateMacAddress(uintptr_t xuid, uint8_t macAddress[6]) {

	std::mt19937 rng(static_cast<unsigned int>(xuid));
	std::uniform_int_distribution<int> distByte(0x00, 0xff);

	macAddress[0] = 0x00;

	for (int i = 1; i < 6; ++i)
	{
		macAddress[i] = static_cast<uint8_t>(distByte(rng));
	}
}


inline std::string GenerateRandomGuid() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint32_t> dis(0, 15);

	std::stringstream ss;
	for (int i = 0; i < 8; ++i) {
		ss << std::hex << dis(gen);
	}
	ss << "-";

	for (int i = 0; i < 4; ++i) {
		ss << std::hex << dis(gen);
	}
	ss << "-";

	for (int i = 0; i < 4; ++i) {
		ss << std::hex << dis(gen);
	}
	ss << "-";

	for (int i = 0; i < 4; ++i) {
		ss << std::hex << dis(gen);
	}
	ss << "-";


	// Append the constant last part
	ss << "806e6f6e6963";

	return ss.str();
}


inline float flHue = 0.0f;
inline float rgb_speed = 0.04f;

inline ImColor esp_rgb()
{
	// Get elapsed time since the application started
	static auto startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	auto elapsedTime = currentTime.count() - startTime.count();

	// Update hue based on elapsed time
	flHue = fmod(elapsedTime * rgb_speed, 255.0f);

	// Generate color using the hue value
	ImColor EspColorsrgb = ImColor::HSV(flHue, 1.f, 1.f, 1.f);

	return EspColorsrgb;
}

inline void SetSpeed(float value)
{
	auto MSG_PackSignedFloat = Settings::mem.gamefunction.MSG_PackSignedFloat.cast<int(*)(float, float, unsigned int)>();
	//*(unsigned int*)((uintptr_t)Settings::client.ps + 0x530) = MSG_PackSignedFloat(value, 5, 0xC);
}


//inline uintptr_t CG_PredictMP_PredictPlayerState_original;
////this needed for pSilent
//inline void  CG_PredictMP_PredictPlayerState_hook(game_struct::LocalClientNum_t localClientNum) {
//
//	VariadicCall<void>(CG_PredictMP_PredictPlayerState_original, localClientNum);
//
//	auto cg = Settings::client.cg = Settings::client.cg;
//	auto cl = GameFunction::CL::GetClActiveClient(game_struct::LocalClientNum_t::LOCAL_CLIENT_0);
//	auto currentcmdnumber = cl->GetCmdNumber();
//	Settings::client.local_entity = cg ? cg->predictedPlayerEntity() : nullptr;
//	auto cmd = cl ? cl->CL_GetUserCmd(cl->GetCmdNumber()) : nullptr;
//	auto new_cmd = cl ? cl->CL_GetUserCmd(cl->GetCmdNumber() + 1) : nullptr;
//	Settings::client.ps = *Settings::mem.playerstate_P.ps_ptr.cast<game_struct::playerState_t**>();
//	Settings::client.cmd = cmd;
//	if ((cmd) && (new_cmd)) {
//
//
//		static int prevcmdnum{};
//		if (currentcmdnumber > prevcmdnum) {
//			--cmd->commandTime;
//			*new_cmd = *cmd;
//		}
//		prevcmdnum = cl->GetCmdNumber();
//
//		if (Settings::Aimbot::silent)
//			aimbot::perfectSilentAim(cmd);
//	}
//}
inline uintptr_t BG_IsThirdPersonMode_original;

inline bool  BG_IsThirdPersonMode_Hook(__int64 weaponMap, DWORD* playerstate)
{
	if (Settings::Misc::thirdperson)
	{
		//auto result = VariadicCall<bool>(BG_IsThirdPersonMode2_original, weaponMap, playerstate);
		return true;
	}

	return VariadicCall<bool>(BG_IsThirdPersonMode_original, weaponMap, playerstate);
}

inline uintptr_t AddDObjToScene_original;
inline void R_AddDObjToScene_hook(__int64 a1, game_struct::cpose_t* a2, unsigned int a3, unsigned int entnum, int other, game_struct::GfxSceneEntityMutableShaderData* sceneEntityMutableShaderData, uint32_t* a7, int a8)
{
	if (Settings::Outlines::b_enable_outline) {
		if (a2->eType == game_struct::entityType_s::ET_PLAYER && Settings::Outlines::b_outline_player) {
			sceneEntityMutableShaderData->hudOutlineInfo.drawOccludedPixels = true;// Settings::Outline::drawOccludedPixels;
			sceneEntityMutableShaderData->hudOutlineInfo.drawNonOccludedPixels = true;// Settings::Outline::drawNonOccludedPixels;
			sceneEntityMutableShaderData->hudOutlineInfo.renderMode = 0; // Settings::Outline::RenderMode;
			sceneEntityMutableShaderData->hudOutlineInfo.fill = true;
			sceneEntityMutableShaderData->hudOutlineInfo.lineWidth = 2.f;
			sceneEntityMutableShaderData->hudOutlineInfo.color = Settings::Colors::outline_player;
		}
		else if (a2->eType == game_struct::entityType_s::ET_VEHICLE && Settings::Outlines::b_outline_vehicle) {
			sceneEntityMutableShaderData->hudOutlineInfo.drawOccludedPixels = true;// Settings::Outline::drawOccludedPixels;
			sceneEntityMutableShaderData->hudOutlineInfo.drawNonOccludedPixels = true;// Settings::Outline::drawNonOccludedPixels;
			sceneEntityMutableShaderData->hudOutlineInfo.renderMode = 0; // Settings::Outline::RenderMode;
			sceneEntityMutableShaderData->hudOutlineInfo.fill = true;
			sceneEntityMutableShaderData->hudOutlineInfo.lineWidth = 2.f;
			sceneEntityMutableShaderData->hudOutlineInfo.color = Settings::Colors::outline_vehicle;
		}
		else if (a2->eType == game_struct::entityType_s::ET_ITEM && Settings::Outlines::b_outline_item)	{

			sceneEntityMutableShaderData->hudOutlineInfo.drawOccludedPixels = true;// Settings::Outline::drawOccludedPixels;
			sceneEntityMutableShaderData->hudOutlineInfo.drawNonOccludedPixels = true;// Settings::Outline::drawNonOccludedPixels;
			sceneEntityMutableShaderData->hudOutlineInfo.renderMode = 0; // Settings::Outline::RenderMode;
			sceneEntityMutableShaderData->hudOutlineInfo.fill = true;
			sceneEntityMutableShaderData->hudOutlineInfo.lineWidth = 2.f;
			sceneEntityMutableShaderData->hudOutlineInfo.color = Settings::Colors::outline_vehicle;
		}
	}

	VariadicCall<void>((uintptr_t)AddDObjToScene_original, a1, a2, a3, entnum, other, sceneEntityMutableShaderData, a7, a8);
}


inline uintptr_t CG_GetViewFovBySpace_original;

inline uintptr_t* CG_GetViewFovBySpace_hook(float* a1, int a2, unsigned int a3, char a4)
{

	if (Settings::Misc::fov && game_sdk::in_game()) // remove && game_sdk::In_game if you want it to work in the lobby - Kohy
	{
		auto orig = VariadicCall<uintptr_t*>(CG_GetViewFovBySpace_original, a1, a2, a3, a4);

		a1[0] = game_sdk::get_ingame_fov_value(Settings::Misc::f_fov);

		return orig;
	}

	return VariadicCall<uintptr_t*>(CG_GetViewFovBySpace_original, a1, a2, a3, a4);
}


inline uintptr_t BG_WeaponFireRecoil_original;
inline void  BG_WeaponFireRecoil_hook(__int64* a1, uint32_t* a2, float* a3, __int64 a4, __int64 a5, unsigned __int8 a6, int a7, int a8, __int64 a9, __int64 a10, BYTE* a11, char* a12)
{
	if (!Settings::Misc::norecoil)
		return VariadicCall<void>(BG_WeaponFireRecoil_original, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

	return;
}



inline uintptr_t BG_CalculateWeaponMovement_Sway_original;
inline void  BG_CalculateWeaponMovement_Sway(__int64 a1, __int64 a2)
{
	if (!Settings::Misc::nosway)
		return VariadicCall<void>(BG_CalculateWeaponMovement_Sway_original, a1, a2);

	return;

}

inline uintptr_t BG_CalculateFinalSpreadForWeapon_original;

inline float BG_CalculateFinalSpreadForWeapon(__int64 a1, uint32_t* a2, unsigned __int16* a3)
{
	if (Settings::Misc::norecoil)
		return 0.0f;

	return VariadicCall<float>(BG_CalculateFinalSpreadForWeapon_original, a1, a2, a3);
}

inline uintptr_t BulletHitEvent_Internal_original;

inline void BulletHitEvent_Internal_hook(uintptr_t thisptr, int sourceEntityNum, int targetEntityNum, unsigned int targetScriptableIndex,
	unsigned __int8 boneIndex, const game_struct::Weapon_t* weapon, bool isAlternate, const math::vec3_t* initialPos, const math::vec3_t* startPos, const math::vec3_t* position, const
	math::vec3_t* normal, int surfType, int event, unsigned int impactEffects, int hitContents, const int hitImpactDelayOverride, game_struct::SndHitArmorType hitArmorType, game_struct::SndHitmarkerType hitmarkerType, const  game_struct::CgEventLodData* optionalEventLodData, char unknown)
{

	VariadicCall<void>(BulletHitEvent_Internal_original, thisptr, sourceEntityNum, targetEntityNum, targetScriptableIndex, boneIndex, weapon, isAlternate, initialPos, startPos, position, normal, surfType, event, impactEffects, hitContents, hitImpactDelayOverride, hitArmorType, hitmarkerType, optionalEventLodData, unknown);

	math::vec3_t tracestart{};
	if (/*game_sdk::in_game() &&*/  Settings::client.cg)
	{
		auto cg = Settings::client.cg;
		game_sdk::sTracer Tracer;


		if (cg->predictedPlayerEntity()->nextstate().number == sourceEntityNum && Settings::Visuals::b_bulletTracer/* && (entity->nextstate().eType == game_struct::ET_PLAYER || entity->nextstate().eType == game_struct::ET_AGENT)*/)
		{


			DWORD flashtag{};
			math::vec3_t muzzleflash{};
			GameFunction::BG::BG_GetWeaponFlashTagname(&flashtag, cg->predictedPlayerEntity()->GetWeapon(), cg->predictedPlayerEntity()->nextstate().inAltWeaponMode, 0);
			GameFunction::BG::CalcMuzzlePoint(Settings::mem.CgWeaponSystem__ms_weaponSystemArray.cast(), cg->predictedPlayerState().clientnum, flashtag, true, &muzzleflash);

			Tracer.vStartPos3D = muzzleflash;
			Tracer.vHitPos3D = *position;
			Tracer.iStartTime = GetTickCount64();
			Tracer.cColorShadow = Settings::Visuals::RGB_tracer ? esp_rgb() : Settings::Colors::tracer_shadow;
			Tracer.cColorHitMarker = Settings::Visuals::RGB_tracer ? esp_rgb() : Settings::Colors::tracer_hitmarker;
			Tracer.cColorTracer = Settings::Visuals::RGB_tracer ? esp_rgb() : Settings::Colors::tracer;
			Tracer.flAlphaShadow = 255;
			Tracer.flAlphaHitMarker = 255;
			Tracer.flAlphaTracer = 255;

			game_sdk::vTracers.push_back(Tracer);

		}



	}


}


inline uintptr_t sub_7FF6BC1CE2B0_original;

inline  __int64 sub_7FF6BC1CE2B0_hook(ClActiveClient_t* a1, __int64 _RDX, int a3)
{
	//Settings::logging::counter++;

	if (a1)
		hooked_ptr = a1;

	return VariadicCall<__int64>(sub_7FF6BC1CE2B0_original, a1, _RDX, a3);;
}



inline uintptr_t  sub_7FF643DC3400_original;

inline bool sub_7FF643DC3400()
{
	return 1;
}

inline uintptr_t  LiveAntiCheat_ReportPlayer_original;

inline void  LiveAntiCheat_ReportPlayer(unsigned int a1, int a2, __int64 a3, __int64 a4, __int64 a5)
{


	return;
	//VariadicCall<void>(Live_GetConsoleDetails_original, a1, a2, a3, a4, a5);

}


inline uintptr_t CG_EntityMP_CalcLerpPositions_original;

inline void CG_EntityMP_CalcLerpPositions_hook(int localClientNum, entity_t* cent)
{
	VariadicCall<void>(CG_EntityMP_CalcLerpPositions_original, localClientNum, cent);


	auto next_snap = GameFunction::CG::CG_SnapshotMP_GetNextSnap(0);
	auto prev_snap = GameFunction::CG::CG_SnapshotMP_GetPrevSnap(0);

	game_struct::BGTrajectory trajectory{};
	math::vec3_t prev_pos{}, pos{};
	GameFunction::CG::CgTrajectory_CgTrajectory(&trajectory, 0, cent, &cent->PrevState());
	GameFunction::CG::BgTrajectory_EvaluatePosTrajectory(&trajectory, prev_snap->serverTime, &prev_pos);
	trajectory.m_es = &cent->nextstate().lerp;
	GameFunction::CG::BgTrajectory_EvaluatePosTrajectory(&trajectory, next_snap->serverTime, &pos);

	auto deltapos = pos - prev_pos;

	deltapos.x = (float)GetSign(deltapos.x);
	deltapos.y = (float)GetSign(deltapos.y);
	deltapos.z = (float)GetSign(deltapos.z);

	// need to set to decrypted pos
}


inline uintptr_t bdAntiCheat_reportExtendedAuthInfo_original;
inline __int64  bdAntiCheat_reportExtendedAuthInfo(
	void* a1,
	__int64* result,
	unsigned int a3,
	unsigned int a4,
	unsigned __int64 a5,
	game_struct::bdMACAddr* a6,
	unsigned __int64 a7,
	unsigned __int64 a8,
	unsigned __int64* a9,
	int a10)
{


	static uintptr_t xuid{};
	VariadicCall<uintptr_t*>(Settings::mem.gamefunction.Live_GetXuid.cast(), &xuid, 0);

	if (!xuid)
		return 0;
	Settings::logging::counter;
	//generateMacAddress(xuid, a6->m_data);

	for (size_t i = 0; i < 6; i++)
	{
		Settings::logging::macaddr[i] = a6->m_data[i];
	}

	return VariadicCall<__int64>(bdAntiCheat_reportExtendedAuthInfo_original, a1, result, a3, a4, a5, a6, a7, a8, a9, a10);

}

inline uintptr_t PM_UpdateSwayPrediction_original;

inline  void  PM_UpdateSwayPrediction(__int64 a1, __int64 a2, float* a3, unsigned int* a4, __int64 a5)
{
	return;
}

inline uintptr_t  CG_ViewMP_UpdateKickAngles_original;

inline  void  CG_ViewMP_UpdateKickAngles(__int64 a1)
{

	if (!Settings::Misc::norecoil)
		VariadicCall<void>(CG_ViewMP_UpdateKickAngles_original, a1);

}

inline uintptr_t  BG_CalculateWeaponMovement_Recoil_original;

inline  void  BG_CalculateWeaponMovement_Recoil(uintptr_t* a1, DWORD* a2)
{

	if (!Settings::Misc::norecoil)
		VariadicCall<void>(BG_CalculateWeaponMovement_Recoil_original, a1, a2);

}