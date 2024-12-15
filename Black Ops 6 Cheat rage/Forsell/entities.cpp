#include"includes.h"
#include "entities.h"
#include "velocitymanager.hpp"



CgGlobalsMP* CG_GetLocalClientGlobals()
{
	Settings::client.ps = *Settings::mem.playerstate_P.ps_ptr.cast<game_struct::playerState_t**>();
	if (!Settings::client.ps)
		return nullptr;

	return reinterpret_cast<CgGlobalsMP*>((uintptr_t)Settings::client.ps - Settings::mem.CgGlobalsMP.predictedPlayerState.cast());
}

void entity_t::CgTrajectory_CgTrajectory2(game_struct::BGTrajectory* thisptr)
{
	VariadicCall<void>(Settings::mem.gamefunction.CgTrajectory_CgTrajectory, thisptr, game_struct::LOCAL_CLIENT_0, const_cast<const entity_t*>(this), const_cast<const game_struct::LerpEntityState*>(&this->PrevState()));
}

entity_t* CG_GetEntity(int index)
{
	auto predictedPlayerEntity = Settings::client.cg->predictedPlayerEntity();
	if (!predictedPlayerEntity)
		return nullptr;

	auto cg_entities = reinterpret_cast<uintptr_t>(predictedPlayerEntity) - Settings::client.cg->predictedPlayerEntity()->nextstate().number * Settings::mem.centity.size;
	if (!cg_entities)
		return nullptr;

	return reinterpret_cast<entity_t*>(cg_entities + index * Settings::mem.centity.size);
}

__int64 entity_t::CG_EntityMP_CalcLerpPositions()
{
	return VariadicCall<__int64>(Settings::mem.gamefunction.CG_EntityMP_CalcLerpPositions, game_struct::LocalClientNum_t::LOCAL_CLIENT_0, const_cast<const entity_t*>(this));
}



player_velocity_manager velocity_manager;
math::vec3_t entity_t::get_velocity()
{
	math::vec3_t target_velocity{};

	auto next_snap = GameFunction::CG::CG_SnapshotMP_GetNextSnap(0);
	auto prev_snap = GameFunction::CG::CG_SnapshotMP_GetPrevSnap(0);

	if (is_bad_ptr(next_snap) || is_bad_ptr(prev_snap))
		return velocity_manager.get_speed(this->nextstate().number);

	auto magnitude = (next_snap->serverTime - prev_snap->serverTime) * 0.001f;

	if (magnitude <= 0.0f)
		return velocity_manager.get_speed(this->nextstate().number);

	game_struct::BGTrajectory trajectory{};
	math::vec3_t prev_pos{}, pos{};
	CgTrajectory_CgTrajectory2(&trajectory);
	GameFunction::CG::BgTrajectory_EvaluatePosTrajectory(&trajectory, prev_snap->serverTime, &prev_pos);
	trajectory.m_es = &this->nextstate().lerp;
	GameFunction::CG::BgTrajectory_EvaluatePosTrajectory(&trajectory, next_snap->serverTime, &pos);

	target_velocity = (pos - prev_pos) / magnitude;

	return target_velocity;

}
bool entity_t::get_bbox(math::vec4_t& box)
{

	auto pos = get_pos();

	math::vec2_t screen_pos;
	if (!game_sdk::world_to_screen(pos, screen_pos))
		return false;

	pos.z += 70;

	math::vec2_t screen_pos_2;
	if (!game_sdk::world_to_screen(pos, screen_pos_2))
		return false;

	screen_pos_2.x -= (screen_pos.y - screen_pos_2.y) / 4;
	screen_pos.x += (screen_pos.y - screen_pos_2.y) / 4;

	box.x = screen_pos_2.x;
	box.y = screen_pos_2.y;
	box.w = screen_pos.x - screen_pos_2.x;
	box.z = screen_pos.y - screen_pos_2.y;

	return true;
}

CharacterInfo_t* entity_t::Get_CharacterInfo()
{
		auto pointer = Settings::client.cg->character_ptr();
		if (!pointer)
			return nullptr;
	
		auto local_character = pointer - Settings::mem.CG_CharacterInfo.subtract.cast();
		if (!local_character)
			return nullptr;
	
		auto characterinfo_start = local_character - (Settings::mem.CG_CharacterInfo.size.cast() * Settings::client.cg->predictedPlayerState().clientnum);
		if (!characterinfo_start)
			return nullptr;
	
	
		return (characterinfo_start + Settings::mem.CG_CharacterInfo.size.cast() * nextstate().number);
}

math::angle_t entity_t::GetAngle() 
{
	game_struct::LerpEntityState* currentState = &this->nextstate().lerp;

	auto current_pos = currentState->apos.trBase;
	if (currentState->apos.trType == game_struct::trType_t::TR_LINEAR_STOP_SECURE)
		game_struct::trajectory_t_secure::Trajectory_GetTrBase(Settings::mem.s_trbase_aab.cast(), &currentState->apos, &current_pos);

	return math::angle_t(current_pos.x,normalizeAngle360(current_pos.y), current_pos.z);
}

bool entity_t::is_alive()
{
	return (flag() & 1) != 0;
}

bool entity_t::hasriotShield()
{
	auto weapon = this->GetWeapon();
	if (!weapon)
		return false;

	return GameFunction::BG::BG_IsRiotShield(weapon,this->nextstate().inAltWeaponMode);
}

bool entity_t::stowedriotShield()
{
	auto weapon = game_sdk::GetWeaponByIndex(this->nextstate().staticState.player.stowedWeaponHandle.m_mapEntryId);
	if (!weapon)
		return false;

	return GameFunction::BG::BG_IsRiotShield(weapon, this->nextstate().inAltWeaponMode);
}

bool entity_t::GetViewDirection(math::vec3_t* forward, math::vec3_t* right, math::vec3_t* up)
{
	return GameFunction::CG::CG_GetViewDirection(0,this->nextstate().number,forward,right,up);
}

bool entity_t::is_team()
{
	return GameFunction::CG::CG_ScoreboardMP_GetClientScore(this->nextstate().number)->Team == GameFunction::CG::CG_ScoreboardMP_GetClientScore(Settings::client.cg->predictedPlayerEntity()->nextstate().number)->Team;
}

bool entity_t::Get_Bone(int bone_index, math::vec3_t* pos)
{
	return GameFunction::CG::GetWorldBonePos( static_cast<int>(this->nextstate().number), bone_index, pos);
}

math::angle_t entity_t::GetLocalAngle()
{
	auto refdef = game_sdk::GetRefDef();
	if (!refdef)
		return math::angle_t();
	math::angle_t local_angles;
	game_sdk::VecToAngle(refdef->view.axis[0], local_angles);
	local_angles.z = 0;

	return local_angles;
}

math::vec3_t entity_t::get_pos()
{
	
	return GameFunction::CG::CG_GetPoseOrigin(this->nextstate().number);
}

math::vec3_t entity_t::set_pos(math::vec3_t* position)
{

	/*uintptr_t ent = (uintptr_t)this;

	uintptr_t set_origin_func =  (ent + Settings::mem.centity.pose + 0x8) ^ *(uintptr_t*)(ent + Settings::mem.centity.pose) ^ *Settings::mem.s_aab_get_pointer_origin.cast<uint32_t*>();
	auto setorigin = reinterpret_cast<void(*)(float*, uintptr_t )>(set_origin_func);

	if (setorigin && set_origin_func)
		setorigin((float*)position, ent + Settings::mem.centity.pose + 0x10);*/
}

int entity_t::isInVehicle()
{
	return GameFunction::CG::GetLinkedVehicle(GameFunction::CG::Get_CgHandler(game_struct::LocalClientNum_t::LOCAL_CLIENT_0),this->nextstate().number);
}

game_struct::clientinfo_t* entity_t::Get_ClientInfo()
{
	auto ms_cgameStatics = Settings::mw3.ms_cgameStaticsArray[0];

	game_struct::clientinfo_t* pClientInfo = (game_struct::clientinfo_t*)(*(__int64(__fastcall**)(uintptr_t*, __int64))(*(__int64*)(__int64)ms_cgameStatics + 0x128))(ms_cgameStatics, this->nextstate().number);
	return pClientInfo;
}

std::string_view entity_t::GetWeaponName()
{
	auto weapon = GameFunction::CG::CG_GetEntWeapon(this);// game_sdk::GetWeaponByIndex(this->nextstate().staticState.player.offhandWeaponHandle.m_mapEntryId);
	if (!weapon)
		return std::string_view();

	return GameFunction::UI::UI_SafeTranslateString(GameFunction::CG::CG_GetWeaponDisplayName(weapon).data());
}

game_struct::Weapon_t* entity_t::GetWeapon()
{
	return GameFunction::CG::CG_GetEntWeapon(this);
}

