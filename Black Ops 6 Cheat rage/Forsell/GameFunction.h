#pragma once

struct entity_t;
struct ClActiveClient_t;
namespace GameFunction
{

	namespace UI
	{
		const char* UI_SafeTranslateString(const char* reference);
	}

	namespace G
	{
		void  G_Bullet_Endpos(unsigned int* randSeed, float spreadMin, float spreadMax, math::vec3_t* end, math::vec3_t* dir, float angleMin, float angleMax, const game_struct::BgWeaponParms* wp, float maxRange);

	}

	namespace BG
	{
		void BG_GetPlayerEyePosition(uintptr_t weaponmap, game_struct::playerState_t* ps, math::vec3_t* outvieworigin, uintptr_t CgHandler);
		int BG_UsrCmdPackAngle(float angle);
		float BG_UsrCmdUnpackAngle(__int64 a1);
		game_struct::BallisticInfo_t* BG_GetBallisticInfo(uintptr_t handler, game_struct::Weapon_t*, bool is_Alternate);
		float BG_Ballistics_TravelTimeForDistance(uintptr_t handler, game_struct::Weapon_t*, bool is_Alternate, float distance);
		float BG_GetThirdPersonCrosshairOffset(uintptr_t weaponMap, const game_struct::playerState_t* ps);
		float BG_CalculateFinalSpreadForWeapon(__int64 a1, game_struct::playerState_t* a2, game_struct::Weapon_t* a3, float a4);
		__int64  BG_srand_timeangles(int seed, math::angle_t* angle);
		bool BG_IsRiotShield(const game_struct::Weapon_t* r_weapon, bool isAlternate);
		void BgTrajectory_LegacyEvaluateTrajectory(const game_struct::trajectory_t_secure* tr, int time, math::vec3_t* result);
		void  BG_GetSpreadForWeapon(game_struct::playerState_t* ps, game_struct::Weapon_t* r_weapon, float* minSpread, float* maxSpread);
		void  CG_Weapons_SimulateBulletFire_EndPos(unsigned int* randSeed, float* spreadInner, float* spreadOuter, math::vec3_t* start, math::vec3_t* end, math::vec3_t* dir, float* angleMin, float* angleMax, math::vec3_t* forwardDir, math::vec3_t* rightDir, math::vec3_t* upDir, float maxRange);
		DWORD* BG_GetWeaponFlashTagname(DWORD* TagOut, game_struct::Weapon_t* weapon, bool isAlternate, unsigned int chamberIndex);
		void CalcMuzzlePoint(uintptr_t weaponsystem, int entnum, uintptr_t TagIndex, bool exactPoint, math::vec3_t* outPoint);
		__int64  BG_GetPenetrateType(game_struct::Weapon_t* r_weapon, bool isAlternate);
		__int64  BG_GetWeaponType(game_struct::Weapon_t* r_weapon, bool isAlternate);
		bool  BG_IsRifleBullet(game_struct::Weapon_t* r_weapon, bool isAlternate);
		float BG_GetSurfacePenetrationDepth(game_struct::Weapon_t* r_weapon, bool isAlternate, unsigned int surfaceType);
		__int64  BG_GetPerkNetworkPriorityIndex(unsigned int a1);
		bool  BG_AdvanceTrace(game_struct::BulletFireParams* bp, game_struct::trace_t* trace, math::vec3_t* hitPos, float dist);
	}

	namespace CG
	{
		char  CG_GetViewDirection(int localClientNum, unsigned int entityNum, math::vec3_t* outForward, math::vec3_t* outRight, math::vec3_t* outUp);
		__int64  CG_EntityMP_CalcLerpPositions(int localClientNum, entity_t* cent);
		void  CgTrajectory_CgTrajectory(game_struct::BGTrajectory* thisptr, int localClientNum, const entity_t* cent, const game_struct::LerpEntityState* es);
		void  BgTrajectory_EvaluatePosTrajectory(game_struct::BGTrajectory* thisptr, int atTime, math::vec3_t* outPos);
		float CG_View_GetFovDvarValue();
		float CG_View_GetFovDvarDefaultValue();
		uintptr_t Get_CgHandler(game_struct::LocalClientNum_t LocalClientNum);
		game_struct::Weapon_t* CG_GetEntWeapon(entity_t* ent);
		std::string_view CG_GetWeaponDisplayName(game_struct::Weapon_t* weapon);
		math::vec3_t CG_GetPoseOrigin(int index);
		game_struct::snapshot_t* CG_SnapshotMP_GetNextSnap(int localclientnum);
		game_struct::snapshot_t* CG_SnapshotMP_GetPrevSnap(int localclientnum);
		game_struct::entityState_t* GetEntityState(unsigned int index);
		bool GetWorldBonePos(unsigned int index, unsigned int boneid, math::vec3_t* bonepos);
		uintptr_t GetTeam(int index);
		game_struct::clientinfo_t* GetClientInfo(int index);
		void TagPair(uint32_t* tagpair, uint32_t tagname, uint32_t fallback_tagname);
		char GetTagNameAndBoneIndex(uint32_t* tagpair, uintptr_t dobj, uint32_t* outtag, BYTE* outindex);
		int CG_DObjGetWorldBoneMatrix(uintptr_t pose, uintptr_t dobj, int boneindex, float* axisshit, math::vec3_t* outorigin);
		uintptr_t  CG_EntityMP_GetDObj_General(int a1, entity_t* cent, BYTE* createdNew_optionalOut);
		uintptr_t  CG_GetPoseExtended(int a1, int handle, int returnNullOnInvalid);
		uintptr_t  GetLinkedVehicle(uintptr_t handler, unsigned int entNumber);
		void  CgHandler_GetScriptableDimensions(uintptr_t handler, unsigned int scriptableIndex, math::angle_t* outInitialAngle, math::vec3_t* outOrigin, game_struct::Bounds* outBounds);
		game_struct::XModel* CG_ClientModel_GetModel(int clientnum, int clientmodelidx, int clientsubmodelidx);
		void  AimTargetMP_GetTargetBounds(int localClientNum, entity_t* targetEnt, game_struct::Bounds* box);
		uintptr_t  CgVehicleSystem_GetClient(uintptr_t vehiclesystem, entity_t* cent);
		const game_struct::VehicleDef* CgVehicleSystem_GetClientDef(uintptr_t veh);
		bool  CG_Weapons_BulletTrace(int localclientnum, game_struct::BulletFireParams* bp, int* skipqueueEntitys, __int64 ignoreEntityCount, game_struct::Weapon_t* wp, bool isalternate, entity_t* inflictorEnt, game_struct::BulletTraceResults* br, int lastSurfaceType, entity_t** outHitEnt, bool allowHitSelf);
		__int64 GetignoreEntityCount(game_struct::BulletFireParams* bp);
		game_struct::score_t* CG_ScoreboardMP_GetClientScore(int index);
		game_struct::Score_T* niggername(int i);

	}

	namespace CL
	{
		ClActiveClient_t* GetClActiveClient(game_struct::LocalClientNum_t LocalClientNum);
		void  CL_SetFOVSensitivityScale(game_struct::LocalClientNum_t localClientNum, double scale);
		void CL_CGameMP_SetUserCmdAimValues(game_struct::LocalClientNum_t localClientNum, const math::vec3_t* kickAngles);
		void  CL_SetUserCmdWeapons(int a1, game_struct::Weapon_t* a2, game_struct::Weapon_t* a3, bool a4);
		void  CL_SetExtraButtons(game_struct::LocalClientNum_t localClientNum, unsigned __int64 buttons);
		const char* CL_GetAgentName(int index, int ownerIndex);
		void  CL_SetCustomClanTag(int localClientNum, const char* clantag);

	}

	namespace SL
	{
		uint32_t SL_FindString(const char* string);
		char* SL_ConvertToString(uint32_t stringValue);

	}

	namespace Lua
	{
		void  lua_getfield(lua_State* L, int idx, const char* k);
		void  j_lua_remove(lua_State* L, int idx);
		void  lua_pushstring(lua_State* L, const char* str);
		void  lua_pushinteger(lua_State* L, uintptr_t str);
		void  lua_pushboolean(lua_State* L, uintptr_t str);
		__int64 j_lua_gettop(lua_State* L);
		void j_lua_settop(lua_State* L, int n);

		void j_lua_pop(lua_State* L, int val);

		int  LuaShared_PCall(lua_State* luaVM, int nargs, int nresults);
		void LUI_CoD_LuaCall_ExecNow(lua_State* luaVM, std::string_view  str);
		void LUI_CoD_LuaCall_GiveLoot(lua_State* luaVM, int itemid);
		int LUI_CoD_LuaCall_IsDemoBuild_CustomFunction(lua_State* luaVM);
		void RegisterCustomCoDEngineFunction();
		void lua_registerFunction(lua_State* luaVM, __int64 lua_hash, __int64 lua_func);
	}


	namespace OnlineLoot
	{
		void* OnlineLoot_GetInstance();
		void OnlineLoot_UpdateItemInInventory(__int64 Online_Loot, int controllerIndex, unsigned int itemID, int quantity, char set);
		__int64  OnlineLoot_GetItemQuantity(__int64 Online_Loot, unsigned int controllerIndex, unsigned int id);
	}

	namespace StringTable
	{
		void StringTable_GetAsset(const char* filename, game_struct::StringTable** tableptr);
		const char* StringTable_GetColumnValueForRow(game_struct::StringTable* table, const int row, const int column);
	}

	namespace DDL
	{
		const char* DDL_GetString(__int64 state, __int64 ddlContext);
		const int DDL_GetInt(__int64 state, __int64 ddlContext);
		__int64 Com_DDL_LoadAsset(const char* file);
		bool Com_DDL_CreateContext(uintptr_t buffer, int len, uintptr_t def, uintptr_t ddlContext, uintptr_t accessdb, uintptr_t userData);
		bool NavigateBlueprintDDL(__int64 state, const char* path);
		int DDL_GetType(__int64 state);
		bool DDL_SetFloat(__int64 state, __int64 ddlContext, float val);
		bool DDL_SetEnum(__int64 state, __int64 ddlContext, const char* val);
		__int64 DDL_GetRootState(__int64 result, uintptr_t ddlDef);
		bool CL_PlayerData_GetDDLBuffer(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup);
		__int64 DDL_MoveToName(__int64 fstate, __int64 tstate, __int64 path);
		bool DDL_SetInt(__int64 fstate, __int64 tstate, int value);
		bool DDL_SetString(__int64 fstate, __int64 state, const char* val);
		bool DDL_MoveToPath(__int64* fromState, __int64* toState, int depth, const char** path);
		bool Com_ParseNavStrings(const char* pStr, const char** navStrings, const int navStringMax, int* navStringCount);
	}

	namespace Scriptable
	{
		game_struct::ScriptableInstanceContextSecure* Scriptable_GetScriptableInstanceContexts(const uint32_t id);
	}

	namespace Sys
	{
		int Sys_Milliseconds();
	}

	namespace Trace
	{
		bool LegacyTrace(math::vec3_t& start, math::vec3_t& end, int index);

	}

	namespace Dvar
	{
		uintptr_t Dvar_FindMalleableVar(uintptr_t hash);
		void Cbuf_AddText(std::string_view cmd);
		float Dvar_GetFloatSafe(uintptr_t dvarName);
		char* Dvar_GetStringSafe(uintptr_t hash);

	}

	namespace Gpad
	{
		float GPad_GetButton(int Buttonid);
		bool GPad_isActive();
	}

	namespace EngineMath
	{
		void Vec3Normalize(math::vec3_t* v);
	}


}



