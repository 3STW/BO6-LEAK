#include"includes.h"
#include "GameFunction.h"
#include"../shared/lua/lua.h"
#include "offsets.h"
bool  GameFunction::CG::GetWorldBonePos(unsigned int index, unsigned int boneid, math::vec3_t* bonepos)
{
	auto function = Settings::mem.gamefunction.targetassist.cast<void**>();
	VariadicCall<void>((uintptr_t)function[3], (uintptr_t)0, index, boneid, bonepos);

	if (!bonepos->is_Zero())
		return true;
	return false;

}

uintptr_t GameFunction::CG::GetTeam(int index)
{
	return VariadicCall<uintptr_t>((uintptr_t)Settings::mem.gamefunction.targetassist.cast<void**>()[9], (uintptr_t)0, index);

}

game_struct::clientinfo_t* GameFunction::CG::GetClientInfo(int index)
{
	auto fn = mem::get_vfunc(Settings::mem.gamefunction.targetassist, 0xE8).cast< void (*)(uintptr_t, int)  >();

	return VariadicCall<game_struct::clientinfo_t*>((uintptr_t)fn, Settings::mem.gamefunction.targetassist, index);

}

void GameFunction::CG::TagPair(uint32_t* tagpair, uint32_t tagname, uint32_t fallback_tagname)
{
	//return VariadicCall<void>(Settings::mem.gamefunction.TagPair_TagPair, tagpair, tagname,fallback_tagname);

}

char GameFunction::CG::GetTagNameAndBoneIndex(uint32_t* tagpair, uintptr_t dobj, uint32_t* outtag, BYTE* outindex)
{
	return 0;// VariadicCall<char>(Settings::mem.gamefunction.TagPair_GetTagNameAndBoneIndex, tagpair, dobj, outtag, outindex);

}

int GameFunction::CG::CG_DObjGetWorldBoneMatrix(uintptr_t pose, uintptr_t dobj, int boneindex, float* axisshit, math::vec3_t* outorigin)
{
	return 0;//VariadicCall<int>(Settings::mem.gamefunction.CG_DObjGetWorldBoneMatrix, pose, dobj, boneindex, axisshit,outorigin);

}

uintptr_t GameFunction::CG::CG_EntityMP_GetDObj_General(int a1, entity_t* cent, BYTE* createdNew_optionalOut)
{
	return 0;// VariadicCall<uintptr_t>(Settings::mem.gamefunction.CG_EntityMP_GetDObj_General, a1, cent, createdNew_optionalOut);
}

uintptr_t GameFunction::CG::CG_GetPoseExtended(int a1, int handle, int returnNullOnInvalid)
{
	return 0;// VariadicCall<uintptr_t>(Settings::mem.gamefunction.CG_GetPoseExtended, a1, handle, returnNullOnInvalid);

}

uintptr_t GameFunction::CG::GetLinkedVehicle(uintptr_t handler, unsigned int entNumber)
{
	return 0;// VariadicCall<uintptr_t>(Settings::mem.gamefunction.GetLinkedVehicle, handler, entNumber);
}

void GameFunction::CG::CgHandler_GetScriptableDimensions(uintptr_t handler, unsigned int scriptableIndex, math::angle_t* outInitialAngle, math::vec3_t* outOrigin, game_struct::Bounds* outBounds)
{
	VariadicCall<void>(Settings::mem.gamefunction.CgHandler_GetScriptableDimensions.cast(), handler, scriptableIndex, outInitialAngle, outOrigin, outBounds);
}

game_struct::XModel* GameFunction::CG::CG_ClientModel_GetModel(int clientnum, int clientmodelidx, int clientsubmodelidx)
{
	return VariadicCall<game_struct::XModel*>(Settings::mem.gamefunction.CG_ClientModel_GetModel.cast(), clientnum, clientmodelidx, clientsubmodelidx);
}

void GameFunction::CG::AimTargetMP_GetTargetBounds(int localClientNum, entity_t* targetEnt, game_struct::Bounds* box)
{
	VariadicCall<void>(Settings::mem.gamefunction.AimTargetMP_GetTargetBounds.cast(), localClientNum, targetEnt, box);

}

uintptr_t GameFunction::CG::CgVehicleSystem_GetClient(uintptr_t vehiclesystem, entity_t* cent)
{
	return 0;// 	VariadicCall<uintptr_t>(Settings::mem.gamefunction.CgVehicleSystem__GetClient.cast(), vehiclesystem, cent);

}

const game_struct::VehicleDef* GameFunction::CG::CgVehicleSystem_GetClientDef(uintptr_t veh)
{
	return 0;// 	VariadicCall<game_struct::VehicleDef*>(Settings::mem.gamefunction.CgVehicleSystem__GetClientDef.cast(), veh);

}

bool GameFunction::CG::CG_Weapons_BulletTrace(int localclientnum, game_struct::BulletFireParams* bp, int* skipqueueEntitys, __int64 ignoreEntityCount, game_struct::Weapon_t* wp, bool isalternate, entity_t* inflictorEnt, game_struct::BulletTraceResults* br, int lastSurfaceType, entity_t** outHitEnt, bool allowHitSelf)
{
	return 0;// 	VariadicCall<bool>(Settings::mem.gamefunction.CG_Weapons_BulletTrace.cast(), localclientnum, bp, skipqueueEntitys, ignoreEntityCount, wp, isalternate, inflictorEnt, br, lastSurfaceType, outHitEnt, allowHitSelf);

}

__int64 GameFunction::CG::GetignoreEntityCount(game_struct::BulletFireParams* bp)
{
	return 0;// 	VariadicCall<__int64>(Settings::mem.gamefunction.GetignoreEntityCount.cast(), bp);
}

game_struct::score_t* GameFunction::CG::CG_ScoreboardMP_GetClientScore(int index)
{
	return 	VariadicCall<game_struct::score_t*>(Settings::mem.gamefunction.CG_ScoreboardMP_GetClientScore.cast(), 0, index);

}
game_struct::Score_T* GameFunction::CG::niggername(int i) {
	return VariadicCall<game_struct::Score_T*>(Settings::mem.gamefunction.CG_ScoreboardMP_GetClientScore.cast(), 0, i);
}

game_struct::entityState_t* GameFunction::CG::GetEntityState(unsigned int index)
{

	return VariadicCall<game_struct::entityState_t*>((uintptr_t)Settings::mem.gamefunction.missile.cast<void**>()[16], (uintptr_t)0, index);
}

const char* GameFunction::UI::UI_SafeTranslateString(const char* reference)
{
	auto addr = Settings::mem.gamefunction.UI_SafeTranslateString.cast<const char* (*)(const char*)>();
	return spoof_call<const char*>(Settings::mem.trampoline.cast<void*>(), addr, reference);

}

void GameFunction::BG::BG_GetPlayerEyePosition(uintptr_t weaponmap, game_struct::playerState_t* ps, math::vec3_t* outvieworigin, uintptr_t CgHandler)
{
	VariadicCall<void>(Settings::mem.gamefunction.BG_GetPlayerEyePosition.cast(), weaponmap, ps, outvieworigin, CgHandler);

}

float GameFunction::CG::CG_View_GetFovDvarValue()
{
	/*auto addr = Settings::mem.gamefunction.CG_View_GetFovDvarValue.cast<float(*)()>();
	return spoof_call<float>(Settings::mem.trampoline.cast<void*>(), addr);*/
}

float GameFunction::CG::CG_View_GetFovDvarDefaultValue()
{
	/*auto addr = Settings::mem.gamefunction.CG_View_GetFovDvarDefaultValue.cast<float(*)()>();
	return spoof_call<float>(Settings::mem.trampoline.cast<void*>(), addr);*/
}

uintptr_t GameFunction::CG::Get_CgHandler(game_struct::LocalClientNum_t LocalClientNum)
{
	auto addr = Settings::mem.gamefunction.CG_Handler.cast<uintptr_t(*)(game_struct::LocalClientNum_t)>();
	return spoof_call<uintptr_t>(Settings::mem.trampoline.cast<void*>(), addr, LocalClientNum);
}

game_struct::Weapon_t* GameFunction::CG::CG_GetEntWeapon(entity_t* ent)
{
	auto addr = Settings::mem.gamefunction.CG_GetEntWeapon.cast<game_struct::Weapon_t * (*)(int, entity_t*)>();
	return  VariadicCall<game_struct::Weapon_t*>((uintptr_t)addr, 0, ent);
}

std::string_view GameFunction::CG::CG_GetWeaponDisplayName(game_struct::Weapon_t* weapon)
{
	char outputBuffer[512];
	auto addr = Settings::mem.gamefunction.CG_GetWeaponDisplayName.cast<char* (*)(game_struct::Weapon_t*, int, bool, char*, int, bool)>();
	VariadicCall<char*>((uintptr_t)addr, weapon, 0, false, outputBuffer, sizeof(outputBuffer), false);
	return std::string_view(outputBuffer);

}

math::vec3_t GameFunction::CG::CG_GetPoseOrigin(int index)
{

	math::vec3_t Position = math::vec3_t(0, 0, 0);
	auto addr = Settings::mem.gamefunction.CG_GetPoseOrigin.cast<>();
	float matrix[64]{};
	VariadicCall<uintptr_t>(addr, (int)0, index, matrix, &Position);

	return Position;

}

game_struct::snapshot_t* GameFunction::CG::CG_SnapshotMP_GetNextSnap(int localclientnum)
{
	return 	VariadicCall<game_struct::snapshot_t*>(Settings::mem.gamefunction.CG_SnapshotMP_GetNextSnap, localclientnum);
}

game_struct::snapshot_t* GameFunction::CG::CG_SnapshotMP_GetPrevSnap(int localclientnum)
{
	return 	VariadicCall<game_struct::snapshot_t*>(Settings::mem.gamefunction.CG_SnapshotMP_GetPrevSnap, localclientnum);
}

int GameFunction::BG::BG_UsrCmdPackAngle(float angle)
{
	auto MSG_PackSignedFloat = Settings::mem.gamefunction.MSG_PackSignedFloat.cast<int(*)(float, float, unsigned int)>();
	__m128 v26 = { 0ui64, 0ui64 }, v27 = { 0ui64, 0ui64 }, nullm128 = { 0ui64, 0ui64 };
	v26.m128_f32[0] = angle * 0.0027777778;
	v27 = v26;
	v27.m128_f32[0] = v26.m128_f32[0] + 0.5;
	return MSG_PackSignedFloat((float)(v26.m128_f32[0] - _mm_round_ss(nullm128, v27, 1).m128_f32[0]) * 360.0, 180.0, 20);
}

float GameFunction::BG::BG_UsrCmdUnpackAngle(__int64 angle)
{
	double v1;
	__m128 v2;

	auto MSG_UnpackSignedFloat = Settings::mem.gamefunction.MSG_UnPackSignedFloat.cast<float(*)(int, float, unsigned int)>();
	v1 = MSG_UnpackSignedFloat(angle, 180.0, 20);
	v1 *= 0.0027777778;
	v2 = _mm_set_ss(v1 + 0.5);
	v2 = _mm_round_ss(v2, v2, 1);
	v1 -= v2.m128_f32[0];
	return v1 * 360.0;
}

game_struct::BallisticInfo_t* GameFunction::BG::BG_GetBallisticInfo(uintptr_t handler, game_struct::Weapon_t* weapon, bool is_Alternate)
{
	return  VariadicCall<game_struct::BallisticInfo_t*>(Settings::mem.gamefunction.BG_GetBallisticInfo, handler, weapon, is_Alternate);;

}

float GameFunction::BG::BG_Ballistics_TravelTimeForDistance(uintptr_t handler, game_struct::Weapon_t* weapon, bool is_Alternate, float distance)
{
	return  VariadicCall<float>(Settings::mem.gamefunction.BG_Ballistics_TravelTimeForDistance, handler, weapon, is_Alternate, distance);

}

float GameFunction::BG::BG_GetThirdPersonCrosshairOffset(uintptr_t weaponMap, const game_struct::playerState_t* ps)
{
	return VariadicCall<float>(Settings::mem.gamefunction.BG_GetThirdPersonCrosshairOffset.cast(), weaponMap, ps);
}

float GameFunction::BG::BG_CalculateFinalSpreadForWeapon(__int64 a1, game_struct::playerState_t* a2, game_struct::Weapon_t* a3, float a4)
{
	//return VariadicCall<float>(Settings::mem.gamefunction.BG_CalculateFinalSpreadForWeapon.cast(), a1, a2, a3,a4);
}

__int64 GameFunction::BG::BG_srand_timeangles(int seed, math::angle_t* angle)
{
	return 0;// VariadicCall<__int64>(Settings::mem.gamefunction.BG_srand_timeangles.cast(), seed, angle);
}

bool GameFunction::BG::BG_IsRiotShield(const game_struct::Weapon_t* r_weapon, bool isAlternate)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.BG_IsRiotShield.cast(), r_weapon, isAlternate);

}

void GameFunction::BG::BgTrajectory_LegacyEvaluateTrajectory(const game_struct::trajectory_t_secure* tr, int time, math::vec3_t* result)
{
	VariadicCall<void>(Settings::mem.gamefunction.BgTrajectory_LegacyEvaluateTrajectory.cast(), tr, time, result);

}

void GameFunction::BG::BG_GetSpreadForWeapon(game_struct::playerState_t* ps, game_struct::Weapon_t* r_weapon, float* minSpread, float* maxSpread)
{
	//VariadicCall<void>(Settings::mem.gamefunction.BG_GetSpreadForWeapon.cast(), ps, r_weapon, minSpread, maxSpread);

}

void  GameFunction::BG::CG_Weapons_SimulateBulletFire_EndPos(unsigned int* randSeed, float* spreadInner, float* spreadOuter, math::vec3_t* start, math::vec3_t* end, math::vec3_t* dir, float* angleMin, float* angleMax, math::vec3_t* forwardDir, math::vec3_t* rightDir, math::vec3_t* upDir, float maxRange)
{
	//VariadicCall<void>(Settings::mem.gamefunction.CG_Weapons_SimulateBulletFire_EndPos.cast(), randSeed, spreadInner, spreadOuter, start, end, dir, angleMin, angleMax, forwardDir, rightDir, upDir, maxRange);

}

char GameFunction::CG::CG_GetViewDirection(int localClientNum, unsigned int entityNum, math::vec3_t* outForward, math::vec3_t* outRight, math::vec3_t* outUp)
{
	return 0;// VariadicCall<char>(Settings::mem.gamefunction.CG_GetViewDirection.cast(), localClientNum, entityNum,outForward,outRight,outUp);

}

__int64 GameFunction::CG::CG_EntityMP_CalcLerpPositions(int localClientNum, entity_t* cent)
{
	return VariadicCall<__int64>(Settings::mem.gamefunction.CG_EntityMP_CalcLerpPositions.cast(), localClientNum, cent);
}

void GameFunction::CG::CgTrajectory_CgTrajectory(game_struct::BGTrajectory* thisptr, int localClientNum, const entity_t* cent, const game_struct::LerpEntityState* es)
{
	VariadicCall<void>(Settings::mem.gamefunction.CgTrajectory_CgTrajectory.cast(), thisptr, localClientNum, cent, es);
}

void GameFunction::CG::BgTrajectory_EvaluatePosTrajectory(game_struct::BGTrajectory* thisptr, int atTime, math::vec3_t* outPos)
{
	VariadicCall<void>(Settings::mem.gamefunction.BgTrajectory_EvaluatePosTrajectory.cast(), thisptr, atTime, outPos);
}

DWORD* GameFunction::BG::BG_GetWeaponFlashTagname(DWORD* TagOut, game_struct::Weapon_t* weapon, bool isAlternate, unsigned int chamberIndex)
{
	return VariadicCall<DWORD*>(Settings::mem.gamefunction.BG_GetWeaponFlashTagname.cast(), TagOut, weapon, isAlternate, chamberIndex);
}

void GameFunction::BG::CalcMuzzlePoint(uintptr_t weaponsystem, int entnum, uintptr_t TagIndex, bool exactPoint, math::vec3_t* outPoint)
{
	VariadicCall<void>(Settings::mem.gamefunction.CalcMuzzlePoint.cast(), weaponsystem, entnum, TagIndex, exactPoint, outPoint);

}

__int64 GameFunction::BG::BG_GetPenetrateType(game_struct::Weapon_t* r_weapon, bool isAlternate)
{
	return 0;
}

__int64 GameFunction::BG::BG_GetWeaponType(game_struct::Weapon_t* r_weapon, bool isAlternate)
{
	return 0;// VariadicCall<__int64>(Settings::mem.gamefunction.BG_GetWeaponType.cast(), r_weapon, isAlternate);

}

bool GameFunction::BG::BG_IsRifleBullet(game_struct::Weapon_t* r_weapon, bool isAlternate)
{
	return false;
}

float GameFunction::BG::BG_GetSurfacePenetrationDepth(game_struct::Weapon_t* r_weapon, bool isAlternate, unsigned int surfaceType)
{
	return 0;// VariadicCall<float>(Settings::mem.gamefunction.BG_GetSurfacePenetrationDepth.cast(), r_weapon, isAlternate, surfaceType);

}

__int64 GameFunction::BG::BG_GetPerkNetworkPriorityIndex(unsigned int a1)
{
	return 0;
}

bool GameFunction::BG::BG_AdvanceTrace(game_struct::BulletFireParams* bp, game_struct::trace_t* trace, math::vec3_t* hitPos, float dist)
{
	return 0;// VariadicCall<bool>(Settings::mem.gamefunction.BG_AdvanceTrace.cast(), bp, trace, hitPos, dist);

}



math::angle_t game_struct::usercmd_t::GetAngle()
{
	math::angle_t ret;

	ret.x = GameFunction::BG::BG_UsrCmdUnpackAngle(angle[0]);
	ret.y = GameFunction::BG::BG_UsrCmdUnpackAngle(angle[1]);
	ret.z = GameFunction::BG::BG_UsrCmdUnpackAngle(angle[2]);


	return ret;

}



void* GameFunction::OnlineLoot::OnlineLoot_GetInstance()
{
	// auto addr = Settings::mem.gamefunction.OnlineLoot_GetInstance.cast<void* (*)()>();
	//return spoof_call<void*>(Settings::mem.trampoline.cast<void*>(), addr);
	return 0;
}

void GameFunction::OnlineLoot::OnlineLoot_UpdateItemInInventory(__int64 Online_Loot, int controllerIndex, unsigned int itemID, int quantity, char set)
{
	/*	  auto addr = Settings::mem.gamefunction.OnlineLoot_UpdateItemInInventory.cast<void (*)(__int64,int,unsigned int,int,char)>();
		 return spoof_call<void>(Settings::mem.trampoline.cast<void*>(), addr, Online_Loot,controllerIndex,itemID,quantity,set);*/
}

__int64 GameFunction::OnlineLoot::OnlineLoot_GetItemQuantity(__int64 Online_Loot, unsigned int controllerIndex, unsigned int id)
{
	/*	  auto addr = Settings::mem.gamefunction.OnlineLoot_GetItemQuantity.cast<__int64 (*)(__int64, unsigned int, unsigned int)>();
		 return spoof_call<__int64>(Settings::mem.trampoline.cast<void*>(), addr, Online_Loot, controllerIndex, id);*/
	return 0;

}

void GameFunction::StringTable::StringTable_GetAsset(const char* filename, game_struct::StringTable** tableptr)
{
	/*  auto addr = Settings::mem.gamefunction.StringTable_GetAsset.cast<void (*)(const char*, game_struct::StringTable**)>();
	 return spoof_call<void>(Settings::mem.trampoline.cast<void*>(), addr, filename, tableptr);*/
}

const char* GameFunction::StringTable::StringTable_GetColumnValueForRow(game_struct::StringTable* table, const int row, const int column)
{
	/* auto addr = Settings::mem.gamefunction.StringTable_GetColumnValueForRow.cast< const char* (*)( game_struct::StringTable*, const int, const int)>();
	return spoof_call< const char*>(Settings::mem.trampoline.cast<void*>(), addr, table, row, column);*/
	return 0;
}

bool GameFunction::Trace::LegacyTrace(math::vec3_t& start, math::vec3_t& end, int index)
{
	typedef int vec3_t[3];
	vec3_t bounds[2] = { 0.f,0.f ,0.f };
	game_struct::trace_t trace;
	auto addr = Settings::mem.gamefunction.LegacyTrace.cast<void (*)(game_struct::Physics_WorldId, game_struct::trace_t*, math::vec3_t*, math::vec3_t*, float*, unsigned int, int, int, int, int)>();
	VariadicCall<void>((uintptr_t)addr, game_struct::Physics_WorldId::PHYSICS_WORLD_ID_CLIENT0_FIRST, &trace, &start, &end, bounds, Settings::client.local_entity->nextstate().number, 0, 0x280EC93, 0); //0x806130 0x2805823;0x800310;0x806190 0x800410 0x806590;  0x806520  0x814100,0x80E100, 0x8000030;

	return(trace.hitId == index || trace.fraction >= 1.0f);

}

uintptr_t GameFunction::Dvar::Dvar_FindMalleableVar(uintptr_t hash)
{
	return 0;// VariadicCall<uintptr_t>(Settings::mem.gamefunction.Dvar_FindMalleableVar.cast(), hash);

}

typedef void(__fastcall* Gscr_EndLobby)(void* a1);
Gscr_EndLobby EndLobby;
void GameFunction::Dvar::Cbuf_AddText(std::string_view cmd)
{
	char buf[512];
	auto txt = Settings::mem.aXpartydisbanda.cast<char*>();

	memcpy(buf, txt, sizeof(buf));

	DWORD oldProtect;
	VirtualProtect(txt, 512, PAGE_READWRITE, &oldProtect);

	strcpy(txt, cmd.data());

	EndLobby = (Gscr_EndLobby)Settings::mem.Gscr_endlobby.cast();
	EndLobby(nullptr);

	memcpy(txt, buf, sizeof(buf));

	VirtualProtect(txt, cmd.size(), oldProtect, NULL);

	/*auto lua_vm = *Settings::mem.lua.luaVM.cast<lua_State**>();
	if (!lua_vm)
		return;

	GameFunction::Lua::lua_pushstring(lua_vm, cmd.data());
	VariadicCall<int>(Settings::mem.gamefunction.LUI_CoD_LuaCall_Exec_now.cast(), lua_vm);
	GameFunction::Lua::j_lua_pop(lua_vm, GameFunction::Lua::j_lua_gettop(lua_vm));*/
}

float GameFunction::Dvar::Dvar_GetFloatSafe(uintptr_t dvarName)
{
	//return VariadicCall<float>(Settings::mem.gamefunction.Dvar_GetFloatSafe.cast(), dvarName);
}

char* GameFunction::Dvar::Dvar_GetStringSafe(uintptr_t hash)
{
	return 0;// VariadicCall<  char*>(Settings::mem.gamefunction.Dvar_GetStringSafe.cast(), hash);
}

float GameFunction::Gpad::GPad_GetButton(int Buttonid)
{
	return VariadicCall<float>(Settings::mem.gamefunction.GPad_GetButton.cast(), 0, Buttonid);

}

bool GameFunction::Gpad::GPad_isActive()
{
	return VariadicCall<bool>(Settings::mem.gamefunction.GPad_isActive.cast(), 0);
}

void GameFunction::Lua::lua_getfield(lua_State* L, int idx, const char* k)
{

}

void GameFunction::Lua::lua_pushstring(lua_State* L, const char* str)
{

}

void GameFunction::Lua::lua_pushinteger(lua_State* L, uintptr_t str)
{

}

void GameFunction::Lua::lua_pushboolean(lua_State* L, uintptr_t str)
{

}

__int64 GameFunction::Lua::j_lua_gettop(lua_State* L)
{

}

void GameFunction::Lua::j_lua_settop(lua_State* L, int n)
{

}

void GameFunction::Lua::j_lua_pop(lua_State* L, int val)
{
}

int GameFunction::Lua::LuaShared_PCall(lua_State* luaVM, int nargs, int nresults)
{

}

void GameFunction::Lua::j_lua_remove(lua_State* L, int idx)
{

}

void GameFunction::Lua::LUI_CoD_LuaCall_ExecNow(lua_State* luaVM, std::string_view  str)
{

}

void GameFunction::Lua::LUI_CoD_LuaCall_GiveLoot(lua_State* luaVM, int itemid)
{

}

int GameFunction::Lua::LUI_CoD_LuaCall_IsDemoBuild_CustomFunction(lua_State* luaVM)
{

}

void GameFunction::Lua::RegisterCustomCoDEngineFunction()
{

}

void GameFunction::Lua::lua_registerFunction(lua_State* luaVM, __int64 lua_hash, __int64 lua_func)
{
}

uint32_t GameFunction::SL::SL_FindString(const char* string)
{
	uint32_t value{};
	//VariadicCall<void>(Settings::mem.gamefunction.SL_FindString.cast(),&value, string);
	return value;
}

char* GameFunction::SL::SL_ConvertToString(uint32_t stringValue)
{
	//return VariadicCall<char*>(Settings::mem.gamefunction.SL_ConvertToString.cast(), stringValue);

}

int GameFunction::Sys::Sys_Milliseconds()
{
	//return VariadicCall<int>(Settings::mem.gamefunction.sys_milliseconds.cast());
}

void GameFunction::G::G_Bullet_Endpos(unsigned int* randSeed, float spreadMin, float spreadMax, math::vec3_t* end, math::vec3_t* dir, float angleMin, float angleMax, const game_struct::BgWeaponParms* wp, float maxRange)
{
	// VariadicCall<void>(Settings::mem.gamefunction.G_Bullet_Endpos.cast(), randSeed, spreadMin, spreadMax, end, dir, angleMin, angleMax, wp, maxRange);
}

void GameFunction::EngineMath::Vec3Normalize(math::vec3_t* v)
{
	//VariadicCall<void>(Settings::mem.gamefunction.Vec3Normalize.cast(), v);

}

const char* GameFunction::DDL::DDL_GetString(__int64 state, __int64 ddlContext)
{
	return nullptr;
}

const int GameFunction::DDL::DDL_GetInt(__int64 state, __int64 ddlContext)
{
	return 0;
}

__int64 GameFunction::DDL::Com_DDL_LoadAsset(const char* file)
{
	return VariadicCall<__int64>(Settings::mem.gamefunction.Com_DDL_LoadAsset.cast(), file);
}

bool GameFunction::DDL::Com_DDL_CreateContext(uintptr_t buffer, int len, uintptr_t def, uintptr_t ddlContext, uintptr_t accessdb, uintptr_t userData)
{
	return false;
}

bool GameFunction::DDL::NavigateBlueprintDDL(__int64 state, const char* path)
{
	return false;
}

int GameFunction::DDL::DDL_GetType(__int64 state)
{
	return VariadicCall<int>(Settings::mem.gamefunction.DDL_GetType.cast(), state);

}

bool GameFunction::DDL::DDL_SetFloat(__int64 state, __int64 ddlContext, float val)
{
	return false;
}

bool GameFunction::DDL::DDL_SetEnum(__int64 state, __int64 ddlContext, const char* val)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.DDL_SetEnum.cast(), state, ddlContext, val);

}

__int64 GameFunction::DDL::DDL_GetRootState(__int64 result, uintptr_t ddlDef)
{
	return VariadicCall<__int64>(Settings::mem.gamefunction.DDL_GetRootState.cast(), result, ddlDef);
}

bool GameFunction::DDL::CL_PlayerData_GetDDLBuffer(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.CL_PlayerData_GetDDLBuffer.cast(), context, controllerindex, stats_source, statsgroup);
}

__int64 GameFunction::DDL::DDL_MoveToName(__int64 fstate, __int64 tstate, __int64 path)
{
	return 0;
}

bool GameFunction::DDL::DDL_SetInt(__int64 fstate, __int64 tstate, int value)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.DDL_SetInt.cast(), fstate, tstate, value);

}

bool GameFunction::DDL::DDL_SetString(__int64 fstate, __int64 state, const char* val)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.DDL_SetString.cast(), fstate, state, val);

}

bool GameFunction::DDL::DDL_MoveToPath(__int64* fromState, __int64* toState, int depth, const char** path)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.DDL_MoveToPath.cast(), fromState, toState, depth, path);

}

bool GameFunction::DDL::Com_ParseNavStrings(const char* pStr, const char** navStrings, const int navStringMax, int* navStringCount)
{
	return VariadicCall<bool>(Settings::mem.gamefunction.Com_ParseNavStrings.cast(), pStr, navStrings, navStringMax, navStringCount);

}
