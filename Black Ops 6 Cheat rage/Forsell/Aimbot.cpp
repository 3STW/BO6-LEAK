#include"includes.h"
namespace aimbot
{
	std::vector< entity_t* > m_targets, m_sorted_targets, aimbot_targets;

	entity_t* m_best_target;
	entity_t* m_previous_target;
	int				m_best_bone;
	math::vec3_t	m_best_pos;
	bool			m_disabled;




	class Result
	{
	public:
		bool hasResult;
		float a;
		float b;
	};

	struct velocityInfo_t
	{
		math::vec3_t lastPos;
		math::vec3_t delta;
	};

	std::map<DWORD, velocityInfo_t> velocityMap;



	//void MovementFix(game_struct::usercmd_t* usercmd, float yaw)
	//{

	//	if (*(int8_t*)((uintptr_t)usercmd + 0xd4) || *(int8_t*)((uintptr_t)usercmd + 0xd5))
	//	{
	//		float flmove = AngleNormalize(RadiansToDegrees(atan2(-*(int8_t*)((uintptr_t)usercmd + 0xd5) / 127.0f, *(int8_t*)((uintptr_t)usercmd + 0xd4) / 127.0f))),
	//			flDelta = AngleNormalize(yaw),
	//			flDestination = AngleNormalize(flmove - flDelta),
	//			flforwardradio = cos(DegreesToRadians(flDestination)),
	//			flrightradio = -sin(DegreesToRadians(flDestination));

	//		if (abs(flforwardradio) < abs(flrightradio))
	//		{
	//			flforwardradio *= 1.0f / abs(flrightradio);
	//			flrightradio = flrightradio > 0.0f ? 1.0f : -1.0f;
	//		}


	//		else if (abs(flforwardradio) > abs(flrightradio)) {
	//			flrightradio *= 1.0f / abs(flforwardradio);
	//			flforwardradio = flforwardradio > 0.0f ? 1.0f : -1.0f;
	//		}

	//		else {
	//			flforwardradio = 1.0f;
	//			flrightradio = 1.0f;
	//		}

	//		*(int8_t*)((uintptr_t)usercmd + 0xd4) = (char)(flforwardradio * 127.0f);
	//		*(int8_t*)((uintptr_t)usercmd + 0xd5) = (char)(flrightradio * 127.0f);

	//	}

	//}

	//void AirStuck()
	//{
	//	if (!usercmd::cmd)
	//		//nlog("!!!! cmd isnt right mane");
	//		return;

	//	if (AirStuckKey.isDown() && !SlideKey.isDown())
	//	{
	//		usercmd::cmd->servertime = 0;
	//	}

	//}

	//void spinbot(game_struct::usercmd_t* usercmd)
	//{
	//	if (!game_sdk::in_game())
	//		return;

	//	if (is_bad_ptr(usercmd))return;



	//	if (!spinbotKey.isDown())
	//		return;

	//	if (usercmd::cmd->buttons.has_flag(1) / keyPressed || ViewAngle::iskey_down / )
	//		return;

	//	static float spinAngle = 0.0f;

	//	if (spinAngle > 180.f)
	//		spinAngle -= -180.f;

	//    usercmd->cmdAngle[0] = GameFunction::BG::BG_UsrCmdPackAngle(80.0f - Settings::client.cg->predictedPlayerState().deltaAngle.x);
	//	usercmd->cmdAngle[1] = GameFunction::BG::BG_UsrCmdPackAngle(spinAngle - Settings::client.cg->predictedPlayerState().deltaAngle.y);
	//	MovementFix(usercmd::cmd, spinAngle - game_sdk::get_local_player().get_viewangle().y);

	//	spinAngle += 15.0f;
	//}

	unsigned long get_bone_opt()
	{
		switch (Settings::Aimbot::bone_priority)
		{
		case 0:
			return j_head;
		case 1:
			return j_neck;
		case 2:
			return j_chest;
		case 3:
			return tag_ik_foot_loc_le; //    tag_ik_foot_loc_le,
		case 4:
			return tag_ik_foot_loc_ri;
		case 5:
			return j_ik_foot_root;
		};
		return j_head;


		switch (Settings::Aimbot::override_priority)
		{
		case 0:
			return j_spineupper;
		case 1:
			return j_spine4;
		case 2:
			return j_head;
		case 3:
			return j_neck;
		case 4:
			return tag_ik_foot_loc_le; //    tag_ik_foot_loc_le,
		case 5:
			return tag_ik_foot_loc_ri;
		case 6:
			return j_ik_foot_root;
		};
		return j_head;


	}


	inline int revert_sorted_bone_loop_id(int id)
	{
		switch (id)
		{
		case 0: return 17;
		case 1: return 18;
		default: return  j_mainroot;
			break;
		}
	}

	inline int sorted_bone_loop_id(int id)
	{
		switch (id)
		{
		case 0: return j_head;
		case 1: return j_neck;
		case 2: return j_spine4;
		case 3: return  j_spineupper;
		case 4: return j_spinelower;
		case 5: return j_mainroot;
		case 6: return  j_clavicle_ri;
		case 7: return j_shoulder_ri;
		case 8: return j_elbow_ri;
		case 9: return  j_wrist_ri;
		case 10: return  j_clavicle_le;
		case 11: return   j_shoulder_le;
		case 12: return  j_elbow_le;
		case 13: return  j_wrist_le;
		case 14: return  j_hip_le;
		case 15: return  j_knee_le;
		case 16: return  j_ankle_le;
		case 17: return  j_ball_le;
		case 18: return j_hip_ri;
		case 19: return j_knee_ri;
		case 20: return j_ankle_ri;
		default: return j_spine4;
			break;
		}
	}

	bool fire_delay(bool should_delay)
	{
		if (Settings::Aimbot::delay < 1)
			return false;

		static std::chrono::milliseconds delta_time = std::chrono::milliseconds(0);

		if (should_delay && !delta_time.count())
			delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()) + std::chrono::milliseconds(Settings::Aimbot::delay);

		if (delta_time >= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()))
			return true;
		else if (delta_time.count())
			delta_time = std::chrono::milliseconds(0);

		return false;
	}

	bool is_visible(math::vec3_t start, math::vec3_t end, int index)
	{
		return GameFunction::Trace::LegacyTrace(start, end, index);
	}


	int SmartBoneSelection(entity_t* ent, math::vec3_t eyepos)
	{


		math::vec3_t camera = eyepos;
		auto preferred_bone_id = get_bone_opt();
		math::vec3_t smart_bone{};


		if ((ent->hasriotShield() || ent->stowedriotShield()) && !Settings::Aimbot::skip_riotshield)
		{

			for (size_t i = 0; i != 1; i++)
			{
				auto bone_id = revert_sorted_bone_loop_id(i); // from top to bottom

				if (ent->Get_Bone(bone_id, &smart_bone))
				{
					if (aimbot::is_visible(camera, smart_bone, ent->nextstate().number))
					{
						return bone_id;
					}

				}

			}

			return j_knee_le;
		}

		if (ent->Get_Bone(preferred_bone_id, &smart_bone))
		{
			if (aimbot::is_visible(camera, smart_bone, ent->nextstate().number))
			{
				return preferred_bone_id;

			}
		}

		for (size_t i = 0; i != 20; i++)
		{
			auto bone_id = sorted_bone_loop_id(i); // from top to bottom

			if (ent->Get_Bone(bone_id, &smart_bone))
			{
				if (aimbot::is_visible(camera, smart_bone, ent->nextstate().number))
				{
					return bone_id;
				}

			}

		}

		return preferred_bone_id;

	}

	float calculate_real_fov(const math::angle_t& local_angles, const math::vec3_t& local_pos, const math::vec3_t& target_pos)
	{
		const auto distance = (target_pos - local_pos).length();
		auto angle_difference = (local_angles - math::calc_angle(local_pos, target_pos));

		angle_difference.x = abs(angle_difference.x);
		angle_difference.y = abs(angle_difference.y);

		auto pitch_difference = sin(math::deg2rad(angle_difference.x)) * distance;
		auto yaw_difference = sin(math::deg2rad(angle_difference.y)) * distance;

		return sqrt(pitch_difference * pitch_difference + yaw_difference * yaw_difference);
	}

	void calculate_delta_angle(game_struct::refdef_t* refdef, math::angle_t& delta_angles)
	{
		math::angle_t local_angles;
		game_sdk::VecToAngle(refdef->view.axis[0], local_angles);
		local_angles.z = 0;

		delta_angles.x = -AngleNormalize(Settings::client.angle.x - local_angles.x);
		delta_angles.y = -AngleNormalize(Settings::client.angle.y - local_angles.y);

	}

	float calculate_by_crosshair(const math::vec3_t& local_pos, const math::vec3_t& target_pos)
	{
		//auto ret = (FLOAT)INT_MAX;
		auto ret = FLT_MAX;
		auto screensize = ImGui::GetIO().DisplaySize;
		FLOAT ScreenX = (FLOAT)screensize.x / 2.0f;
		FLOAT ScreenY = (FLOAT)screensize.y / 2.0f;
		FLOAT PosX = 0.0f;
		FLOAT PosY = 0.0f;

		math::vec2_t vOut{};

		if (game_sdk::world_to_screen(target_pos, vOut))
		{
			PosX = vOut.x > ScreenX ? vOut.x - ScreenX : ScreenX - vOut.x;
			PosY = vOut.y > ScreenY ? vOut.y - ScreenY : ScreenY - vOut.y;
			ret = sqrt(PosX * PosX + PosY * PosY);
		}

		return ret;
	}

	bool isKeyDown(int key) {
		return GetAsyncKeyState(aimbotkey) & 0x8000;
	}

	bool is_key_active()
	{
		return (isKeyDown(aimbotkey) || (GameFunction::Gpad::GPad_GetButton(game_sdk::GamePadkey(Settings::Gamepad::buttonID))) > 0.0f);
	}


	std::vector<int> get_selected_bones(entity_t* pl)
	{
		std::vector<int> selected_bones = {};

		int selected_bone_group = Settings::Aimbot::bone_priority;

		switch (selected_bone_group)
		{
		case 0:
			selected_bones = { j_neck ,j_head };
			break;
		case 1:
			selected_bones = { j_spine4, j_spinelower, j_spineupper, j_mainroot };
			break;
		case 2:
			selected_bones = { j_ball_le, j_knee_le };
			break;
		case 3:
			selected_bones = { j_ball_ri, j_knee_ri };
			break;
		case 4:
			for (int i = j_spinelower; i <= j_ball_ri; i++)
			{
				if (i != j_helmet)
					if (std::find(selected_bones.begin(), selected_bones.end(), i) == selected_bones.end())
						selected_bones.push_back(i);
			}
			break;
		case 5:
			selected_bones = { tag_ik_foot_loc_le, tag_ik_foot_loc_le };
			break;
		case 6:
			selected_bones = { tag_ik_foot_loc_ri, tag_ik_foot_loc_ri };
			break;
		case 7:
			selected_bones = { j_ik_foot_root,  j_ik_foot_root };
			break;
		default:
			selected_bones = { j_spine4 };
			break;
		}

		return selected_bones;
	}



	void draw_fov(const float aimbot_fov)
	{
		auto refdef = game_sdk::GetRefDef();
		if (is_bad_ptr(refdef))return;
		ImVec2 center = ImVec2(refdef->displayViewport.Width / 2, refdef->displayViewport.Height / 2);

		game_sdk::draw::draw_circle(center, aimbot_fov, 0xFFFFFFFF, 100.0f);
	}


	void rect(const math::vec2_t& pos, const math::vec2_t& size, const col_t& col)
	{
		ImGui::GetBackgroundDrawList()->AddRect({ pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, ImColor(col.r(), col.g(), col.b(), col.a()));
	}



	float get_target_in_fov(math::vec2_t target_pos2, math::vec3_t target_pos)
	{
		auto refdef = game_sdk::GetRefDef();
		const float x = target_pos2.x - (refdef->displayViewport.Width / 2);
		const float y = target_pos2.y - (refdef->displayViewport.Height / 2);
		return sqrt(pow(y, 2) + pow(x, 2));
	}


	_declspec(noinline) bool is_visible(entity_t* pl, math::vec3_t start, math::vec3_t end)
	{

	}


	bool is_valid_target(entity_t* ent)
	{

		if (ent->nextstate().eType == game_struct::entityType_s::ET_PLAYER)
		{

			if (ent->is_team() && !Settings::Aimbot::aim_at_team)
				return false;

			if (ent->hasriotShield() && Settings::Aimbot::skip_riotshield)
				return false;

			if (Settings::Aimbot::self_reviving)
			{
				auto knocked = ent->Get_ClientInfo()->game_extrainfo & game_struct::BRDataFlags::Downed;
				auto SelfReviving = ent->Get_ClientInfo()->game_extrainfo & game_struct::BRDataFlags::SelfReviving;

				if (knocked && (!Settings::Aimbot::self_reviving && !SelfReviving))
					return false;

			}

			if (Settings::Aimbot::skip_knocked && (ent->Get_ClientInfo()->game_extrainfo & game_struct::BRDataFlags::Downed))
				return false;


			auto fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(ent->get_pos()));

			if (fdistance > Settings::Aimbot::max_distance)
				return false;

			return true;
		}
		else if (ent->nextstate().eType == game_struct::entityType_s::ET_AGENT && Settings::Aimbot::Aim_at_ai)
		{

			auto fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(ent->get_pos()));

			if (ent->isInVehicle() && Settings::Aimbot::skip_vehicle)
				return false;

			if (fdistance > Settings::Aimbot::max_distance)
				return false;

			return true;
		}




		return false;

	}



	void init()
	{
		if (Settings::Aimbot::Disable_on_Kill && m_best_target)
		{
			if (!m_best_target->is_alive())
				m_disabled = true;
		}

		//start_tick();
		aim_target = -1;
		m_targets.clear();
		m_sorted_targets.clear();
		//clear_vel_map();
		m_best_target = nullptr;
		m_best_bone = -1;
		m_best_pos = math::vec3_t();

		if (!is_key_active())
		{
			m_disabled = false;
		}


	}



	void sort()
	{
		m_sorted_targets = m_targets;
		if (m_sorted_targets.size() == 0)
			return;

		auto refdef = game_sdk::GetRefDef();

		/// Get camera angles
		math::angle_t local_angles;

		game_sdk::VecToAngle(refdef->view.axis[0], local_angles);


		/// Function to determine apprioriate delta
		const auto get_delta = [&](entity_t* ent) -> float {

			switch (Settings::Aimbot::target_mode)
			{
			case 0:
			{
				math::angle_t angle = local_angles - math::calc_angle(Settings::client.cg->predictedPlayerEntity()->get_pos(), ent->get_pos());
				angle = angle.normalize();//math::normalize_angle(angle);
				return angle.length(); //Closest To Crosshair

			}
			case 1:
				return (ent->get_pos() - Settings::client.cg->predictedPlayerEntity()->get_pos()).length(); // closest distance
			default:
				return {};
			}
			};

		/// Sort our targets by the appropriate delta
		std::sort(m_sorted_targets.begin(), m_sorted_targets.end(), [&](auto& a, auto& b) {
			return get_delta(a) < get_delta(b);
			});


	}

	//usercmd->buttons = 0x80000000;
	//usercmd->buttons = 0x20000000;
	// can be used for melee add a distance check to make it P

	//void auto_fire(game_struct::usercmd_t* usercmd)
	//{
	//	static auto last_fire_time = 0u;
	//	if (last_fire_time > usercmd->commandTime)
	//	{
	//		last_fire_time = 0u;
	//	}

	//	if (usercmd->commandTime - last_fire_time)
	//	{
	//		usercmd->buttons = 0x80000000;
	//		usercmd->buttons = 0x20000000;

	//		last_fire_time = usercmd->commandTime;
	//	}
	//}


	void find()
	{

		if (m_sorted_targets.size() == 0)
			return;

		auto refdef = game_sdk::GetRefDef();
		if (!refdef)
			return;


		math::angle_t local_angles;
		game_sdk::VecToAngle(refdef->view.axis[0], local_angles);

		for (auto target : m_sorted_targets)
		{
			if (!target->is_alive())
				continue;

			math::vec3_t bone_pos;
			auto bone = Settings::Aimbot::smart_bone_scan ? SmartBoneSelection(target, refdef->view.GetRefdefViewOrigin()) : get_bone_opt();
			if (!target->Get_Bone(bone, &bone_pos))
				continue;

			if ((Settings::Aimbot::visible_only && !is_visible(refdef->view.GetRefdefViewOrigin(), bone_pos, target->nextstate().number)))
				continue;

			float value{};
			if (Settings::Aimbot::fov_mode == 0)
			{
				value = FLT_MAX;
				math::vec2_t target_pos{};
				if (game_sdk::world_to_screen(bone_pos, target_pos))
				{
					const float x = target_pos.x - (refdef->displayViewport.Width / 2);
					const float y = target_pos.y - (refdef->displayViewport.Height / 2);
					value = sqrt(pow(y, 2) + pow(x, 2));
				}
			}
			else if (Settings::Aimbot::fov_mode == 1)
			{
				value = game_sdk::get_fov(local_angles, math::calc_angle2(refdef->view.GetRefdefViewOrigin(), bone_pos));
			}

			if (value > Settings::Aimbot::fov)
				continue;

			if (Settings::Aimbot::prediction)
			{
				//bone_pos = game_sdk::get_prediction(Settings::client.local_entity, target->nextstate().number, refdef->view.GetRefdefViewOrigin(), bone_pos);
			}


			m_best_target = target;
			m_best_bone = bone;
			m_best_pos = bone_pos;
			return;
		}


	}

	float Angle_Normalize(float angle)
	{
		angle = fmodf(angle, 360.0f);
		if (angle > 180)
		{
			angle -= 360;
		}
		if (angle < -180)
		{
			angle += 360;
		}
		return angle;
	}
	float GetMagnitude(math::vec3_t vec)
	{
		return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	}
	math::vec3_t  NormalizeVec(math::vec3_t  vec)
	{
		float Length = GetMagnitude(vec);
		vec /= Length;
		return vec;
	}

	math::angle_t calculate_angle_old(math::vec3_t src, math::vec3_t dest, math::vec3_t ViewAxis[3])
	{
		math::angle_t angles(0, 0, 0);
		math::vec3_t aimAt = dest - src;
		math::vec3_t normalized = NormalizeVec(aimAt);
		angles = math::angle_t();
		aimAt = normalized * ViewAxis[1];
		float yaw = (float)(asin(aimAt.x + aimAt.y + aimAt.z) * (180 / M_PI));
		aimAt = normalized * ViewAxis[2];
		float pitch = (float)(-asin(aimAt.x + aimAt.y + aimAt.z) * (180 / M_PI));

		angles.x = yaw;
		angles.y = pitch;
		angles.z = 0.0f;

		return angles;
	}


	uint32_t xor_for_viewangle(uint64_t pointer, uint32_t value)
	{
		uint32_t xorvalue1 = *(uint32_t*)((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.seed);//random_seed_viewangle 
		uint32_t xorvalue2 = pointer;
		uint32_t xorvalue = (((xorvalue1 ^ xorvalue2) + 2) * (xorvalue1 ^ xorvalue2)) ^ value;
		return xorvalue;
	}


	//void applyStandard()
	//{

	//	math::vec3_t vieworg{};
	//	auto refdef = game_sdk::GetRefDef();

	//	
	//		GameFunction::BG::BG_GetPlayerEyePosition(Settings::mem.Weaponmap.cast<uintptr_t>(), *Settings::mem.playerstate_P.ps_ptr.cast<game_struct::playerState_t**>(), &vieworg, GameFunction::CG::Get_CgHandler(game_struct::LocalClientNum_t::LOCAL_CLIENT_0));
	//		if (vieworg.is_Zero())
	//			return;
	//	

	//	
	//	if (m_best_target && is_key_active() && !m_disabled)
	//	{

	//		auto smooth_angle = math::calc_angle2(vieworg, m_best_pos);
	//		if (Settings::Aimbot::enabled)
	//		{
	//			
	//				if (Settings::Aimbot::smoothness > 1.0f)
	//				{

	//					auto angle_delta = smooth_angle - (Settings::client.angle + Settings::client.cg->predictedPlayerState().deltaAngle).normalize();
	//					angle_delta = angle_delta.normalize();

	//					smooth_angle = (Settings::client.angle + Settings::client.cg->predictedPlayerState().deltaAngle).normalize() + angle_delta / (Settings::Aimbot::smoothness * Settings::Aimbot::acceleration);
	//					smooth_angle = smooth_angle.normalize();
	//				}
	//			
	//				Settings::client.cl->SetViewAngles(math::angle_t(smooth_angle.x, smooth_angle.y,0));
	//	
	//				if (Settings::Aimbot::autoshoot)
	//				{
	//					intptr_t cmd_ = (uintptr_t)Settings::client.cl->CL_GetUserCmd(Settings::client.cl->GetCmdNumber());
	//					*(char*)(cmd_ + 0x3) |= 0x80;
	//				}

	//				aim_target = m_best_target->nextstate().number;
	//		}
	//	}
	//}


	void applyStandard() {

		if (m_sorted_targets.size() == 0)
			return;

		if (!Settings::client.local_entity->is_alive())
			return;

		auto refdef = game_sdk::GetRefDef();
		if (!refdef)
		{
			return;
		}

		math::vec3_t vieworg = refdef->view.GetRefdefViewOrigin();
		if (vieworg.is_Zero())
		{
			return;
		}

		if (fire_delay(m_previous_target != m_best_target))
			return;

		if (m_best_target && is_key_active() && !m_disabled && m_best_target->is_alive())
		{
			math::angle_t Angle = calculate_angle_old(vieworg, m_best_pos, refdef->view.axis).normalize();


			uint32_t viewangle_y_xor = xor_for_viewangle((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle, *(uint32_t*)((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle));
			uint32_t viewangle_x_xor = xor_for_viewangle((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle + 0x4, *(uint32_t*)((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle + 0x4));

			float viewangle_y = *(float*)&viewangle_y_xor;
			float viewangle_x = *(float*)&viewangle_x_xor;


			if (Settings::Aimbot::smoothness > 0.0f) {

				float viewangle_y_new = viewangle_y + (Angle.y /= Settings::Aimbot::smoothness);
				float viewangle_x_new = viewangle_x + (Angle.x /= Settings::Aimbot::smoothness);

				int32_t viewangle_y_new_xor = *(int32_t*)&viewangle_y_new;
				int32_t viewangle_x_new_xor = *(int32_t*)&viewangle_x_new;

				*(uint32_t*)((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle) = xor_for_viewangle((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle, viewangle_y_new_xor);
				*(uint32_t*)((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle + 0x4) = xor_for_viewangle((uintptr_t)Settings::client.cl + Settings::mem.CLActiveClient.angle + 0x4, viewangle_x_new_xor);
			}


			m_previous_target = m_best_target;
			aim_target = m_best_target->nextstate().number;
		}
	}

	//void applySilent()
	//{
	//	math::vec3_t vieworg{};
	//	auto refdef = game_sdk::GetRefDef();

	//	GameFunction::BG::BG_GetPlayerEyePosition(Settings::mem.Weaponmap.cast<uintptr_t>(), *Settings::mem.playerstate_P.ps_ptr.cast<game_struct::playerState_t**>(), &vieworg, GameFunction::CG::Get_CgHandler(game_struct::LocalClientNum_t::LOCAL_CLIENT_0));

	//	if (vieworg.is_Zero())
	//		return;

	//	if (m_best_target && is_key_active() && !m_disabled)
	//	{
	//		if (Settings::Aimbot::enabled)
	//		{
	//			auto angle = math::calc_angle(vieworg, m_best_pos).normalize();

	//			math::angle_t local_angles;
	//			game_sdk::VecToAngle(refdef->view.axis[0], local_angles);
	//			local_angles.z = 0;

	//			if (Settings::Aimbot::silent)
	//			{
	//				Settings::client.cmd->angle[0] = GameFunction::BG::BG_UsrCmdPackAngle(angle.x - Settings::client.cg->predictedPlayerState().deltaAngle.x);
	//				Settings::client.cmd->angle[1] = GameFunction::BG::BG_UsrCmdPackAngle(angle.y - Settings::client.cg->predictedPlayerState().deltaAngle.y);

	//				// Fix movement when silent aim is used to prevent weird behavior
	//				// MovementFix(Settings::client.cmd, angle.y - Settings::client.cg->predictedPlayerState().deltaAngle.y); 
	//			}
	//			else
	//			{
	//				// Normal aim: adjust local player angles
	//				math::angle_t delta_angles;
	//				delta_angles.x = -Angle_Normalize(Settings::client.angle.x - local_angles.x);
	//				delta_angles.y = -Angle_Normalize(Settings::client.angle.y - local_angles.y);

	//				Settings::client.angle.x = angle.x;
	//				Settings::client.angle.y = angle.y;
	//			}

	//			aim_target = m_best_target->nextstate().number;

	//			// If autoshoot or autowall is enabled, add shooting logic
	//			// if (Settings::Aimbot::autoshoot /*|| (AutoWall::AutoWall( m_best_target, vieworg, m_best_pos) > 0.0f && Settings::Aimbot::autowall)*/)
	//			// {
	//			// 		auto cl = GameFunction::CL::GetClActiveClient(game_struct::LocalClientNum_t::LOCAL_CLIENT_0);
	//			// 		auto cmd = cl ? cl->CL_GetUserCmd(cl->GetCmdNumber()) : nullptr;

	//			// 		*(char*)(cmd + 0x3) |= 0x80;
	//			// }
	//		}
	//	}

	//}

	//void applypSilent(game_struct::usercmd_t* cmd) {

	//	math::vec3_t vieworg{};
	//	auto refdef = game_sdk::GetRefDef();

	//	GameFunction::BG::BG_GetPlayerEyePosition(Settings::mem.Weaponmap.cast<uintptr_t>(), Settings::client.ps, &vieworg, GameFunction::CG::Get_CgHandler(game_struct::LocalClientNum_t::LOCAL_CLIENT_0));
	//	math::angle_t angle = math::calc_angle(vieworg, m_best_pos).normalize();

	//	if (m_best_target && is_key_active() && !m_disabled) {

	//		cmd->angle[0] = GameFunction::BG::BG_UsrCmdPackAngle(angle.x - Settings::client.cg->predictedPlayerState().deltaAngle.x);
	//		cmd->angle[1] = GameFunction::BG::BG_UsrCmdPackAngle(angle.y - Settings::client.cg->predictedPlayerState().deltaAngle.y);
	//		aim_target = m_best_target->nextstate().number;

	//	}
	//}

	void StandardAim()
	{
		init();

		if (!game_sdk::in_game())
			return;


		if (!Settings::Aimbot::enabled)
			return;

		if (!Settings::client.cg)
			return;


		if (is_bad_ptr(Settings::client.cg->predictedPlayerEntity()))
			return;

		if (!Settings::client.cg->predictedPlayerEntity()->is_alive())
			return;



		game_sdk::for_every_player([](entity_t* pl) -> bool
			{
				if (!is_valid_target(pl))
					return false;

				m_targets.push_back(pl);

				return false;
			});


		sort();

		find();

		applyStandard();
	}

	//void SilentAim()
	//{
	//	if (!Settings::Aimbot::enabled)
	//		return;

	//	init();

	//	if (!game_sdk::in_game())
	//		return;

	//	if (is_bad_ptr(Settings::client.cg))
	//		return;

	//	if (is_bad_ptr(Settings::client.local_entity))
	//		return;

	//	/*if (is_bad_ptr(Settings::client.character))
	//		return;*/

	//	if (is_bad_ptr(Settings::client.cmd))
	//		return;

	//	if (is_bad_ptr(Settings::client.ps))
	//		return;

	//	auto refdef = game_sdk::GetRefDef();
	//	if (is_bad_ptr(refdef))
	//		return;

	//	// loop trough all player + AI 
	//	game_sdk::for_every_player([](entity_t* pl) -> bool
	//		{
	//			if (!is_valid_target(pl))
	//				return false;

	//			m_targets.push_back(pl);

	//			return false;
	//		});


	//	// sort the targets
	//	sort();

	//	//find the best target
	//	find();

	//	//// aim at the best target
	//	applySilent();

	//}

	//void perfectSilentAim(game_struct::usercmd_t* cmd)
	//{
	//	if (!Settings::Aimbot::enabled || !Settings::Aimbot::silent)
	//		return;

	//	init();

	//	if (!game_sdk::in_game() || is_bad_ptr(Settings::client.cg) || is_bad_ptr(Settings::client.local_entity) || !Settings::client.local_entity->is_alive() || is_bad_ptr(cmd))
	//		return;

	//	// loop trough all player + AI 
	//	game_sdk::for_every_player([](entity_t* pl) -> bool
	//		{
	//			if (!is_valid_target(pl))
	//				return false;

	//			m_targets.push_back(pl);

	//			return false;
	//		});


	//	// sort the targets
	//	sort();
	//	//find the best target
	//	find();

	//	//// aim at the best target
	//	applypSilent(cmd);
	//}

	//void NoSpread(game_struct::usercmd_t* cmd)
	//{
	//	if (Settings::Misc::nospread && game_sdk::in_game())
	//	{
	//		aimbot::FirstBulletFix();



	//		auto spread = game_sdk::GetSpread();
	//		cmd->angle[0] = GameFunction::BG::BG_UsrCmdPackAngle(spread.x);
	//		cmd->angle[1] = GameFunction::BG::BG_UsrCmdPackAngle(spread.y);
	//	}

	//}
}