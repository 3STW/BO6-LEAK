#pragma once
struct CharacterInfo_t;
struct entity_t;
struct CgGlobalsMP;


CgGlobalsMP* CG_GetLocalClientGlobals();
entity_t* CG_GetEntity(int index);

struct entity_t
{
	void CgTrajectory_CgTrajectory2(game_struct::BGTrajectory* thisptr);
	__int64 CG_EntityMP_CalcLerpPositions();
	math::vec3_t get_velocity();
	bool get_bbox(math::vec4_t& box);
	CharacterInfo_t* Get_CharacterInfo();
	math::angle_t GetAngle();
	bool is_alive();
	bool hasriotShield();
	bool stowedriotShield();
	bool GetViewDirection(math::vec3_t* forward, math::vec3_t* right, math::vec3_t* up);
	bool is_team();
	bool Get_Bone(int bone_index, math::vec3_t* pos);
	math::angle_t GetLocalAngle();
	math::vec3_t get_pos();
	math::vec3_t set_pos(math::vec3_t* position);
	int isInVehicle();
	game_struct::clientinfo_t* Get_ClientInfo();
	std::string_view  GetWeaponName();
	game_struct::Weapon_t* GetWeapon();
	OFFSET(game_struct::LerpEntityState, PrevState, Settings::mem.centity.prevState);
	OFFSET(game_struct::entityState_t, nextstate, Settings::mem.centity.nextState);
	OFFSET(char, flag, Settings::mem.centity.flags);

};

struct CharacterInfo_t
{
	OFFSET(int, Team, Settings::mem.CG_CharacterInfo.team); 

};

struct CgGlobalsMP
{
	OFFSET(game_struct::UserClientBits_t, ClientBits, Settings::mem.CgGlobalsMP.sightedEnemyFools); // visible check
	OFFSET(entity_t*, predictedPlayerEntity, Settings::mem.CgGlobalsMP.predictedPlayerEntity); // pointer to centity_t. used to bypass the pointer encryption
	OFFSET(game_struct::playerState_t, predictedPlayerState, Settings::mem.CgGlobalsMP.predictedPlayerState);   // pointer to playerstate_t. used to bypass the pointer encryption of GetLocalClientGlobals(aka cg_t)
	OFFSET(game_struct::shellshock_t, shellShock, Settings::mem.CgGlobalsMP.shellshock); // stun nade effects
	OFFSET(game_struct::secured_vec3_t, kickAVel, Settings::mem.CgGlobalsMP.kickAVel); //recoil
	OFFSET(game_struct::secured_vec3_t, rawKickAngles, Settings::mem.CgGlobalsMP.rawKickAngles); //recoil
	OFFSET(game_struct::refdef_t, RefDef, Settings::mem.CgGlobalsMP.RefDef); 
	OFFSET(game_struct::Weapon_t, equippedOffHand, Settings::mem.CgGlobalsMP.equippedOffHand);
	OFFSET(game_struct::Weapon_t, weaponSelect, Settings::mem.CgGlobalsMP.weaponSelect);
	OFFSET(uintptr_t, extrabuttons, Settings::mem.CgGlobalsMP.extrabuttons);
	OFFSET(int, Time, Settings::mem.CgGlobalsMP.Time);
	OFFSET(float, FrameTime, Settings::mem.CgGlobalsMP.frameTime);
	//OFFSET(bool, FrontEndScene, Settings::mem.CgGlobalsMP.m_frontEndScene);

	OFFSET(float, zoomSensitivity, Settings::mem.CgGlobalsMP.zoomSensitivity);
	OFFSET(math::vec3_t, offsetAngles, Settings::mem.CgGlobalsMP.offsetAngles);
	OFFSET(math::angle_t, gunAngle, Settings::mem.CgGlobalsMP.baseGunAngles);


	OFFSET(game_struct::secured_vec3_t, kickAngles, Settings::mem.CgGlobalsMP.kickAngles); 
	OFFSET(CharacterInfo_t*, character_ptr, Settings::mem.CgGlobalsMP.characterinfo_ptr); // pointer to characterinfo. used to bypass the pointer encryption 
	OFFSET(float, FOV, Settings::mem.CgGlobalsMP.FOV); 

};