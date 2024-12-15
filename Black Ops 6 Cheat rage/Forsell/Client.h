#pragma once
#include"includes.h"

namespace Settings
{
	struct Client_t
	{
		CgGlobalsMP* cg;
		ClActiveClient_t* cl;
		entity_t* local_entity;
		game_struct::usercmd_t* cmd;
		game_struct::usercmd_t* next_cmd;

		game_struct::playerState_t* ps;
		CharacterInfo_t* character;
		math::angle_t angle;
	};
		extern Client_t client;

}

