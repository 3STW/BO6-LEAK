#include"includes.h"
#include "skCrypter.h"


//#define SET_CURRENT_COLOR(is_friendly, i, visible_color,not_visible_color) \
//    ((Settings::client.cg->ClientBits().isVisible(i)) ? \
//        ((is_friendly) ? Settings::Colors::visible_team : visible_color) : \
//        ((is_friendly) ? Settings::Colors::not_visible_team : not_visible_color))


#define SET_CURRENT_COLOR(is_friendly, i, visible_color,not_visible_color) \
    ((Settings::client.cg->ClientBits().isVisible(i)) ? \
        ((is_friendly) ? Settings::Colors::visible_team : visible_color) : \
        ((is_friendly) ? Settings::Colors::not_visible_team : not_visible_color))


bool overridekeyPressed;


ImColor VisCheckEntity(bool isvis, bool isfriendly, ImColor visible_color, ImColor not_visible_color)
{
	return ((isvis) ? ((isfriendly) ? Settings::Colors::visible_team : visible_color) : ((isfriendly) ? Settings::Colors::not_visible_team : not_visible_color));
}

bool isKeyDown(int key) {
	return GetAsyncKeyState(aimbotkey) & 0x8000;
}
bool is_key_active2()
{

	if (Settings::Aimbot::aim_key == 0)
		keyPressed = (isKeyDown(aimbotkey));
	overridekeyPressed = (isKeyDown(overrideaimbotkey));

	if (Settings::Aimbot::aim_key == 1 && isKeyDown(aimbotkey))
		return keyPressed = !keyPressed;
	return overridekeyPressed = !overridekeyPressed;


	return false;

}

namespace visuals
{
	//Draw Real PLayers
	void DrawPlayer(entity_t* ent)
	{
	}
	// Draw Bots
	void DrawAI(entity_t* ai)
	{
		float display_string{};
		float fdistance{};
		ImColor entColor{};
		math::vec4_t bbox{};


		if (!ai->get_bbox(bbox))
			return;
		//Settings::logging::_localpos = Settings::client.local_entity->get_pos();

		if (game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(ai->get_pos())) > Settings::Visuals::max_ai_distance)
			return;

		fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(ai->get_pos()));

		if (fdistance > Settings::Visuals::max_distance)
			return;




		if (Settings::Visuals::b_showDistance)
		{

			std::string distance_string("[");
			distance_string += std::to_string(fdistance);
			std::string::size_type end = distance_string.find('.');
			if (end != std::string::npos && (end + 2) <= (distance_string.length() - 1))
				distance_string.erase(distance_string.begin() + end + 2, distance_string.end());
			distance_string += "m]";
			game_sdk::draw::DrawString(distance_string, bbox.x + (bbox.z / 2), bbox.y + bbox.w + 5 + display_string, 18.f, true, Settings::Colors::AI_color);

			display_string += 15;
		}



		if (Settings::Visuals::b_showName)
		{
			std::string name = XOR("Bot");
			game_sdk::draw::DrawString(name, bbox.x + (bbox.z / 2), bbox.y + bbox.w + 5 + display_string, 18.f, true, Settings::Colors::AI_color);


			display_string += 15;
		}

		if (Settings::Visuals::b_showBones)
		{
			game_sdk::draw::draw_bones(ai->nextstate().number, Settings::Colors::AI_color);
		}



	}
	//draw Dropped Weapons and items in MP
	void DrawItem(entity_t* Item)
	{
		//float display_string{};
		//float fdistance{};
		//ImColor ItemColor{};
		//math::vec4_t bbox{};
		//if (!Item->get_bbox(bbox))
		//	return;

		//fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(Item->get_pos()));

		//if (fdistance > Settings::Visuals::max_distance)
		//	return;




		//if (Settings::Visuals::b_showItem)
		//{
		//	std::string_view name = Item->GetWeaponName();
		//	game_sdk::draw::DrawString(name.data(), bbox.x + (bbox.z / 2), bbox.y + bbox.w + 5 + display_string, 18.f, true, Settings::Colors::item_color);

		//	display_string += 15;
		//}

	}
	//draw grenades and tactical MP/WZ
	//void DrawMissile()
	//{
	//	float fdistance{};
	//	float display_string{};
	//	ImColor MissileColor{};
	//	math::vec4_t bbox{};
	//	/*if (!Missile->get_bbox(bbox))
	//		return;*/

	//	fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(Missile->get_pos()));

	//	if (fdistance > Settings::Visuals::max_distance)
	//		return;

	//	 ts even work? its buggy in this source look ill show u my other src
	//	if (Settings::Visuals::b_showMissile)
	//	{
	//		std::string_view name = game_struct::entityType_s::ET_MISSILE->GetWeaponName();
	//		game_sdk::draw::DrawString(name.data(), bbox.x + (bbox.z / 2), bbox.y + bbox.w + 5 + display_string, 18.f, true, Settings::Colors::Missile_color);


	//		display_string += 15;
	//	}



	//}
	void draw_l2ine(const ImVec2& from, const ImVec2& to, ImColor color, float thickness)
	{
		auto window = ImGui::GetWindowDrawList();
		//window->AddLine(from, to, color, thickness);
		ImGui::GetBackgroundDrawList()->AddLine(from, to, ImColor(color), thickness);
	}

	//game_struct::Bounds& angle, const math::vec2_t& pos, const math::vec2_t& size, const ImColor& col
	void draw_corned_box(const math::vec2_t& rect, const math::vec2_t& size, const ImColor& color, float thickness)
	{
		size.x - 5;
		const float lineW = (size.x / 5);
		const float lineH = (size.y / 6);
		const float lineT = 1;

		//outline
		draw_l2ine(ImVec2(rect.x - lineT, rect.y - lineT), ImVec2(rect.x + lineW, rect.y - lineT), color, thickness); //top left
		draw_l2ine(ImVec2(rect.x - lineT, rect.y - lineT), ImVec2(rect.x - lineT, rect.y + lineH), color, thickness);
		draw_l2ine(ImVec2(rect.x - lineT, rect.y + size.y - lineH), ImVec2(rect.x - lineT, rect.y + size.y + lineT), color, thickness); //bot left
		draw_l2ine(ImVec2(rect.x - lineT, rect.y + size.y + lineT), ImVec2(rect.x + lineW, rect.y + size.y + lineT), color, thickness);
		draw_l2ine(ImVec2(rect.x + size.x - lineW, rect.y - lineT), ImVec2(rect.x + size.x + lineT, rect.y - lineT), color, thickness); // top right
		draw_l2ine(ImVec2(rect.x + size.x + lineT, rect.y - lineT), ImVec2(rect.x + size.x + lineT, rect.y + lineH), color, thickness);
		draw_l2ine(ImVec2(rect.x + size.x + lineT, rect.y + size.y - lineH), ImVec2(rect.x + size.x + lineT, rect.y + size.y + lineT), color, thickness); // bot right
		draw_l2ine(ImVec2(rect.x + size.x - lineW, rect.y + size.y + lineT), ImVec2(rect.x + size.x + lineT, rect.y + size.y + lineT), color, thickness);

		//inline
		draw_l2ine(ImVec2(rect.x, rect.y), ImVec2(rect.x, rect.y + lineH), color, thickness);//top left
		draw_l2ine(ImVec2(rect.x, rect.y), ImVec2(rect.x + lineW, rect.y), color, thickness);
		draw_l2ine(ImVec2(rect.x + size.x - lineW, rect.y), ImVec2(rect.x + size.x, rect.y), color, thickness); //top right
		draw_l2ine(ImVec2(rect.x + size.x, rect.y), ImVec2(rect.x + size.x, rect.y + lineH), color, thickness);
		draw_l2ine(ImVec2(rect.x, rect.y + size.y - lineH), ImVec2(rect.x, rect.y + size.y), color, thickness); //bot left
		draw_l2ine(ImVec2(rect.x, rect.y + size.y), ImVec2(rect.x + lineW, rect.y + size.y), color, thickness);
		draw_l2ine(ImVec2(rect.x + size.x - lineW, rect.y + size.y), ImVec2(rect.x + size.x, rect.y + size.y), color, thickness);//bot right
		draw_l2ine(ImVec2(rect.x + size.x, rect.y + size.y - lineH), ImVec2(rect.x + size.x, rect.y + size.y), color, thickness);

	}
	void rect(const math::vec2_t& pos, const math::vec2_t& size, const col_t& col)
	{
		ImGui::GetBackgroundDrawList()->AddRect({ pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, ImColor(col.r(), col.g(), col.b(), col.a()));
	}
	void testrectangles(game_struct::Bounds& angle, const math::vec2_t& pos, const math::vec2_t& size, const ImColor& col)
	{
		ImGui::GetBackgroundDrawList()->AddRect({ pos.x, pos.y }, { pos.x + size.x, pos.y + size.y }, col);
	}
	_declspec(noinline) void draw()
	{
		if (!game_sdk::in_game())
			return;

		if (!Settings::client.cg)
			return;

		if (!Settings::client.local_entity)
			return;

		if (!Settings::client.character)
			return;

		if (!Settings::client.cmd)
			return;
		// is "d
		// lampda function which can be used globally(esp ,aimbot ect
		game_sdk::for_every_player(
			[](entity_t* ent) -> bool
			{
				if (ent->nextstate().eType == game_struct::entityType_s::ET_PLAYER)
					DrawPlayer(ent);
				return false;
			});




	}
	int saved = 0;
	bool reset_danger = false;
	math::vec2_t get_screen_size()
	{
		return math::vec2_t(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
	}

	void get_screen_size(math::vec2_t& size)
	{
		size = get_screen_size();
	}

#define debug false
	_declspec(noinline)  void draw2()
	{
		if (!Settings::client.cg)
			return;
#if debug
		log::print("CG Valid.");
#endif
		auto refdef = game_sdk::GetRefDef();
		if (is_bad_ptr(refdef))
			return;
#if debug
		log::print("Refdef Valid");
#endif
		static float rainbow;
		rainbow += 0.0010f; //0.0001f
		if (rainbow > 1.f)
			rainbow = 0.f;
		auto rgb = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);

		if (Settings::Visuals::rgbmode)
		{
			// visible

			Settings::Colors::visible_Bone = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::visible_box = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::visible_name = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::visible_distance = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::visible_Weapon = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::visible_compass = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);

			// misc

			//Settings::Colors::Crosshairnew = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			//Settings::Colors::fovcirclenew = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);

			// non visible

			Settings::Colors::not_visible_Bone = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::not_visible_box = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::not_visible_name = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::not_visible_distance = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::not_visible_Weapon = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
			Settings::Colors::not_visible_compass = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
		}
		if (Settings::Visuals::rgbcircle)
		{
			Settings::Colors::fovcirclenew = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
		}
		if (Settings::Visuals::rgbcrosshair)
		{
			Settings::Colors::Crosshairnew = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
		}
		if (Settings::Misc::rgbmenu)
		{
			main_color = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
		}
		if (!Settings::Colors::MenuColor)
		{
			Settings::Colors::MenuColor = ImColor(140, 140, 140, 255);
		}
		ImVec2 center{};
		if (Settings::Visuals::b_fov && Settings::Aimbot::fov_mode == 1)
		{
			float fov = Settings::client.cg->FOV(); // not calculated
			float realFov = game_sdk::get_actual_fov_value(fov);
			float radius = (tanf(math::deg2rad(Settings::Aimbot::fov) / 2.f) / tanf(math::deg2rad(realFov) / 2.f) * (ImGui::GetIO().DisplaySize.x));
			center = ImVec2(refdef->displayViewport.Width / 2, refdef->displayViewport.Height / 2);

			ImGui::GetBackgroundDrawList()->AddCircle(center, radius, Settings::Colors::fovcirclenew, 100);
		}
		else if (Settings::Visuals::b_fov && Settings::Aimbot::fov_mode == 0)
		{
			center = ImVec2(refdef->displayViewport.Width / 2, refdef->displayViewport.Height / 2);
			ImGui::GetBackgroundDrawList()->AddCircle(center, Settings::Aimbot::fov, Settings::Colors::fovcirclenew, 100);

		}

		if (Settings::Misc::crosshair)
		{
			constexpr auto width = 1, height = 8;

			game_sdk::draw::rect_filled(get_screen_size() / 2 - math::vec2_t{ width + 1, height + 1 }, { (width + 1) * 2, (height + 1) * 2 }, { 0, 0, 0, 255 });
			game_sdk::draw::rect_filled(get_screen_size() / 2 - math::vec2_t{ height + 1, width + 1 }, { (height + 1) * 2, (width + 1) * 2 }, { 0, 0, 0, 255 });

			game_sdk::draw::rect_filled(get_screen_size() / 2 - math::vec2_t{ width, height }, { width * 2, height * 2 }, Settings::Colors::Crosshairnew);
			game_sdk::draw::rect_filled(get_screen_size() / 2 - math::vec2_t{ height, width }, { height * 2, width * 2 }, Settings::Colors::Crosshairnew);
		}

		if (!game_sdk::in_game())
			return;

		for (size_t i = 0; i <= 2046; i++)
		{

			float display_string{};
			float fdistance{};
			ImColor entColor{};
			math::vec4_t bbox{};

			if (Settings::client.cg->predictedPlayerEntity()->nextstate().number == i)
				continue;
#if debug
			log::print("Not local player.");
#endif

			auto ent = CG_GetEntity(i);
			if (!ent)
				continue;
#if debug
			log::print("Grabbed Entity");
#endif
			if (!ent->is_alive())
				continue;
			
			if (ent->nextstate().eType == game_struct::entityType_s::ET_PLAYER)
			{
#if debug
				log::print("Inside player loop");
#endif
				auto team = ent->is_team();

				math::vec3_t eyepos{};
				ent->Get_Bone(tag_eye, &eyepos);
#if debug
				log::print("grabbed eyepos");
#endif
				bool isvisible = aimbot::is_visible(refdef->view.GetRefdefViewOrigin(), eyepos, ent->nextstate().number);

				fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(ent->get_pos()));


				if (Settings::Visuals::b_showCompass)
					game_sdk::DrawCompass(ent, Settings::client.local_entity->get_pos(), ent->get_pos(), VisCheckEntity(isvisible, team, Settings::Colors::visible_compass, Settings::Colors::not_visible_compass));

				if (Settings::Visuals::b_radar)
					game_sdk::DrawRadar(ent, VisCheckEntity(isvisible, team, Settings::Colors::visible_radar, Settings::Colors::not_visible_radar));



				if (fdistance > Settings::Visuals::max_distance)
					continue;



				if (team && !Settings::Visuals::b_showTeam)
					continue;


				auto clientinfo = ent->Get_ClientInfo();
				if (!clientinfo)
					continue;
#if debug
				ImGui::Text("got clientinfo");
#endif
				//if (isvisible && !team)
				//{
				//	auto value = game_sdk::get_entity_fov(ent);

				//	if (fdistance < 100.f && value < 70.f && Settings::Visuals::b_lookingAtYou) // if we are in sight of the enemy in a 80 degree angle they can see us
				//		game_sdk::draw::DrawString(std::string(clientinfo->name) + std::string(XOR(" Is Looking At You!")), game_sdk::GetRefDef()->displayViewport.Width / 2, game_sdk::GetRefDef()->displayViewport.Height / 3, 25.f, true, ImColor(255, 0, 0, 255));
				//	else if (fdistance < 180.f && value < 10.f && Settings::Visuals::b_aimingAtYou) // if the crosshair is on our body the enemy is aiming at us
				//		game_sdk::draw::DrawString(std::string(clientinfo->name) + std::string(XOR(" Is Aiming At You!")), game_sdk::GetRefDef()->displayViewport.Width / 2, game_sdk::GetRefDef()->displayViewport.Height / 7, 25.f, true, ImColor(255, 0, 0, 255));
				//}



				if (!ent->get_bbox(bbox))
					continue;


				if (Settings::Visuals::b_showHealth)
				{
					game_sdk::draw::draw_health(clientinfo->health, bbox);

				}

				if (Settings::Visuals::b_showBones)
				{
					//ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(j_head, j_neck), 300, 1.f);

					static BYTE iBoneArmL[] = { j_neck,  j_clavicle_le, j_shoulder_le, j_elbow_le, j_wrist_le };
					static BYTE iBoneArmR[] = { j_neck, j_clavicle_ri, j_shoulder_ri, j_elbow_ri, j_wrist_ri };

					static BYTE iBoneBody[] = { j_head, j_neck, j_spine4, j_spineupper, j_spinelower, j_mainroot };

					static BYTE iBoneLegL[] = { j_mainroot,  j_hip_le, j_knee_le, j_ankle_le, j_ball_le };
					static BYTE iBoneLegR[] = { j_mainroot, j_hip_ri, j_knee_ri, j_ankle_ri, j_ball_ri };

					//Body
					for (int i = 0; i < 5; i++)
					{
						game_sdk::draw::draw_bone(ent, iBoneBody[i], iBoneBody[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_Bone, Settings::Colors::not_visible_Bone));
					}

					//Arms
					for (int i = 0; i < 4; i++)
					{
						game_sdk::draw::draw_bone(ent, iBoneArmL[i], iBoneArmL[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_Bone, Settings::Colors::not_visible_Bone));
						game_sdk::draw::draw_bone(ent, iBoneArmR[i], iBoneArmR[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_Bone, Settings::Colors::not_visible_Bone));
					}
					//Legs
					for (int i = 0; i < 4; i++)
					{
						game_sdk::draw::draw_bone(ent, iBoneLegL[i], iBoneLegL[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_Bone, Settings::Colors::not_visible_Bone));
						game_sdk::draw::draw_bone(ent, iBoneLegR[i], iBoneLegR[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_Bone, Settings::Colors::not_visible_Bone));
					}
				}


				if (Settings::Visuals::b_showBox)
				{
					game_struct::Bounds bounds{ {}, {} };
					game_sdk::GetPlayerBounds(&ent->nextstate(), bounds);

					switch (Settings::Visuals::box_type)
					{
					case 0:
						rect({ bbox.x - 1, bbox.y - 1 }, { bbox.w + 2, bbox.z + 2 }, { 10, 10, 10, 255 });
						testrectangles(bounds, { bbox.x, bbox.y }, { bbox.w, bbox.z }, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_box, Settings::Colors::not_visible_box));

						break;
					case 1:
					{
						game_sdk::draw::draw_3d_box(bounds, ent->get_pos(), ent->GetAngle(), Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_box, Settings::Colors::not_visible_box));
					}
					break;
					case 2:
					{
						draw_corned_box({ bbox.x, bbox.y }, { bbox.w, bbox.z }, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_box, Settings::Colors::not_visible_box), 0.1f);
					}
					break;
					default:
						break;
					}
				}

				//game_extrainfo

				if (Settings::Visuals::b_showteamid)
				{

					//std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					std::string distance_stringg(XOR("Team: "));
					distance_stringg += std::to_string(clientinfo->squadIndex);
					std::string::size_type end = distance_stringg.find('.');
					if (end != std::string::npos && (end + 2) <= (distance_stringg.length() - 1))
						distance_stringg.erase(distance_stringg.begin() + end + 2, distance_stringg.end());
					distance_stringg += "";

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, distance_stringg, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 45), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					display_string += 15;

				}

				if (Settings::Visuals::ping)
				{

					std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					int Ping = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Ping;
					std::string sigma = (XOR("Ping: ") + std::to_string(Ping)).c_str(); // deaths

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, sigma, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 73), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					display_string += 15;

				}

				if (Settings::Visuals::score)
				{

					std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Score;
					std::string Score = (XOR("Score: ") + std::to_string(name)).c_str(); // deaths

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, Score, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 59), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					display_string += 15;

				}

				if (Settings::Visuals::kills)
				{

					//std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Kills;
					std::string killsnew = (XOR("Kills: ") + std::to_string(name)).c_str(); // deaths

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, killsnew, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 32), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					display_string += 15;

				}

				if (Settings::Visuals::b_showWeapon)
				{
					std::string name = ent->GetWeaponName().data();
					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, name, ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 7 + 1), 14, Settings::Visuals::show_aim_target&& aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_Weapon, Settings::Colors::not_visible_Weapon), true);


					display_string += 15;
				}

				if (Settings::Visuals::b_showDistance)
				{
					std::string distance_string("");
					distance_string += std::to_string(fdistance);
					std::string::size_type end = distance_string.find('.');
					if (end != std::string::npos && (end + 2) <= (distance_string.length() - 1))
						distance_string.erase(distance_string.begin() + end + 2, distance_string.end());
					distance_string += XOR("M");

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, distance_string, ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 21 + 1), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_distance, Settings::Colors::not_visible_distance), true);

					display_string += 15;

				}

				if (Settings::Visuals::testnew)
				{
					int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Deaths;
					std::string skibidi = (XOR("Deaths: ") + std::to_string(name)).c_str(); // deaths

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, skibidi, ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 35 + 1), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_distance, Settings::Colors::not_visible_distance), true);

					display_string += 15;

				}

				if (Settings::Visuals::Damage)
				{
					int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Damage;
					std::string Damage = (XOR("Damage: ") + std::to_string(name)).c_str(); // deaths

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, Damage, ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 49 + 1), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_distance, Settings::Colors::not_visible_distance), true);

					display_string += 15;

				}

				if (Settings::Visuals::assits)
				{
					int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Assists;
					std::string assits = (XOR("Assists: ") + std::to_string(name)).c_str(); // deaths

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, assits, ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 8 + 1), 14, Settings::Visuals::show_aim_target&& aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_distance, Settings::Colors::not_visible_distance), true);

					display_string += 15;

				}

				if (Settings::Visuals::b_showName)
				{

					std::string teamID = std::to_string(clientinfo->squadIndex);
					std::string player = clientinfo->name; //nameWithHash //name

					std::string output;
					std::string test;
					std::string newtest;

					output = player;

					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, output, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 17), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);





				}
            }
			else if (ent->nextstate().eType == game_struct::ET_AGENT && Settings::Visuals::b_showAI)
			{

				auto team = ent->is_team();

				math::vec3_t eyepos{};
				ent->Get_Bone(tag_eye, &eyepos);

				bool isvisible = aimbot::is_visible(eyepos, refdef->view.GetRefdefViewOrigin(), ent->nextstate().number);

				fdistance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(ent->get_pos()));

				if (fdistance <= Settings::Visuals::max_danger_distance && !team)
				{
					saved++;
				}


				auto ZombieColor = ImColor(236, 216, 26, 255);

				if (Settings::Visuals::b_showCompass)
					game_sdk::DrawCompass(ent, Settings::client.local_entity->get_pos(), ent->get_pos(), ZombieColor);

				if (Settings::Visuals::b_radar)
					game_sdk::DrawRadar(ent, ZombieColor);



				if (fdistance > Settings::Visuals::max_ai_distance)
					continue;



				if (team && !Settings::Visuals::b_showTeam)
					continue;

				if (isvisible && !team)
				{
					auto value = game_sdk::get_entity_fov(ent);

					if (fdistance < 100.f && value < 70.f && Settings::Visuals::b_lookingAtYou) // if we are in sight of the enemy in a 80 degree angle they can see us
						game_sdk::draw::DrawString(XOR("Zombie is Looking at You!"), game_sdk::GetRefDef()->displayViewport.Width / 2, game_sdk::GetRefDef()->displayViewport.Height / 3, 25.f, true, ZombieColor);
					else if (fdistance < 180.f && value < 10.f && Settings::Visuals::b_aimingAtYou) // if the crosshair is on our body the enemy is aiming at us
						game_sdk::draw::DrawString(XOR("Zombie is Aiming at You!"), game_sdk::GetRefDef()->displayViewport.Width / 2, game_sdk::GetRefDef()->displayViewport.Height / 7, 25.f, true, ZombieColor);
				}



				if (!ent->get_bbox(bbox))
					continue;

				if (Settings::Visuals::b_showBones)
				{



					//ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(j_head, j_neck), 300, 1.f);

					static BYTE iBoneArmL[] = { j_neck,  j_clavicle_le, j_shoulder_le, j_elbow_le, j_wrist_le };
					static BYTE iBoneArmR[] = { j_neck, j_clavicle_ri, j_shoulder_ri, j_elbow_ri, j_wrist_ri};

					static BYTE iBoneBody[] = { j_head, j_neck, j_spine4, j_spineupper, j_spinelower, j_mainroot };

					static BYTE iBoneLegL[] = { j_mainroot,  j_hip_le, j_knee_le, j_ankle_le, j_ball_le };
					static BYTE iBoneLegR[] = { j_mainroot, j_hip_ri, j_knee_ri, j_ankle_ri, j_ball_ri };

					//Body
					for (int i = 0; i < 5; i++)
					{
						game_sdk::draw::draw_bone(ent, iBoneBody[i], iBoneBody[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);
					}																																												  
																																																	  
					//Arms																																											  
					for (int i = 0; i < 4; i++)																																						  
					{																																												  
						game_sdk::draw::draw_bone(ent, iBoneArmL[i], iBoneArmL[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);
						game_sdk::draw::draw_bone(ent, iBoneArmR[i], iBoneArmR[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);
					}																																												 
					//Legs																																											 
					for (int i = 0; i < 4; i++)																																						 
					{																																												 
						game_sdk::draw::draw_bone(ent, iBoneLegL[i], iBoneLegL[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);
						game_sdk::draw::draw_bone(ent, iBoneLegR[i], iBoneLegR[i + 1], Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);
					}
				}


				if (Settings::Visuals::b_showBox)
				{
					game_struct::Bounds bounds{ {}, {} };
					game_sdk::GetPlayerBounds(&ent->nextstate(), bounds);
					auto angles = ent->GetAngle();
					switch (Settings::Visuals::box_type)
					{
					case 0:
						rect({ bbox.x - 1, bbox.y - 1 }, { bbox.w + 2, bbox.z + 2 }, { 10, 10, 10, 255 });
						//rect({ bbox.x + 1, bbox.y + 1 }, { bbox.w - 2, bbox.z - 2 }, { 10, 10, 10, 255 });
						testrectangles(bounds, { bbox.x, bbox.y }, { bbox.w, bbox.z }, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);

						break;
					case 1:
					{
						game_sdk::draw::draw_3d_box(bounds, ent->get_pos(), angles, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor);
					}
					break;
					case 2:
					{
						draw_corned_box({ bbox.x, bbox.y }, { bbox.w, bbox.z }, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor, 0.1f);
					}
					break;
					default:
						break;
					}
				}

				//game_extrainfo

				//if (Settings::Visuals::b_showteamid)
				//{

				//	//std::string teamIDTest = std::to_string(clientinfo->squadIndex);

				//	std::string distance_stringg("Team: ");
				//	distance_stringg += std::to_string(clientinfo->squadIndex);
				//	std::string::size_type end = distance_stringg.find('.');
				//	if (end != std::string::npos && (end + 2) <= (distance_stringg.length() - 1))
				//		distance_stringg.erase(distance_stringg.begin() + end + 2, distance_stringg.end());
				//	distance_stringg += "";

				//	game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, distance_stringg, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 31), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

				//	display_string += 15;

				//}

				if (Settings::Visuals::ping)
				{

					//std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					//int Ping = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Ping;
					//std::string sigma = (("Ping: " + std::to_string(Ping)).c_str()); // deaths

					//game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, sigma, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 73), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					//display_string += 15;

				}

				if (Settings::Visuals::score)
				{

					//std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					//int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Score;
					//std::string Score = (("Score: " + std::to_string(name)).c_str()); // deaths

					//game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, Score, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 59), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					//display_string += 15;

				}

				if (Settings::Visuals::kills)
				{

					////std::string teamIDTest = std::to_string(clientinfo->squadIndex);

					//int name = GameFunction::CG::CG_ScoreboardMP_GetClientScore(i)->Kills;
					//std::string killsnew = (("Kills: " + std::to_string(name)).c_str()); // deaths

					//game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, killsnew, ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 45), 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : VisCheckEntity(isvisible, team, Settings::Colors::visible_name, Settings::Colors::not_visible_name), true);

					//display_string += 15;

				}

				if (Settings::Visuals::b_showWeapon)
				{
					std::string name = ent->GetWeaponName().data();

					auto pos = ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 7 + 1);
					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, name, pos, 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor, true);


					display_string += 15;
				}

				if (Settings::Visuals::b_showDistance)
				{
					std::string distance_string("");
					distance_string += std::to_string(fdistance);
					std::string::size_type end = distance_string.find('.');
					if (end != std::string::npos && (end + 2) <= (distance_string.length() - 1))
						distance_string.erase(distance_string.begin() + end + 2, distance_string.end());
					distance_string += "M";

					auto pos = ImVec2(bbox.x + bbox.w * 0.5f + 1, bbox.y + bbox.z + 21 + 1);
					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, distance_string, pos, 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor, true);

					display_string += 15;
				}


				if (Settings::Visuals::b_showName)
				{

					//std::string teamID = std::to_string(clientinfo->squadIndex);
					//std::string player = clientinfo->name; //nameWithHash //name

					std::string output = XOR("Zombie/AI");
					//std::string test;
					//std::string newtest;

					auto pos = ImVec2(bbox.x + bbox.w * 0.5f, bbox.y - 17);
					game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, output, pos, 14, Settings::Visuals::show_aim_target && aim_target == ent->nextstate().number ? Settings::Colors::aim_target : ZombieColor, true);





				}
			}
		}

		if (saved > 0 && Settings::Visuals::b_danger)
		{
			if (is_bad_ptr(refdef))return;

			game_sdk::draw::DrawString(XOR("WARNING ") + std::string(std::to_string(saved)) + XOR(" Player Nearby!"), refdef->displayViewport.Width / 2, refdef->displayViewport.Height / 4, 30.f, true, ImColor(255, 0, 0, 255));
			reset_danger = true;
		}

		if (!aimbot::m_best_pos.is_Zero())
		{
			if (math::vec2_t predict_screen; game_sdk::world_to_screen(aimbot::m_best_pos, predict_screen) && Settings::Aimbot::prediction_circle)
			{
				game_sdk::draw::draw_circle(ImVec2(predict_screen.x, predict_screen.y), 6.5f, ImColor(255, 0, 0), 100.0f);
			}
		}
		math::vec2_t bone_screen_pos;
		if (game_sdk::world_to_screen(aimbot::m_best_pos, bone_screen_pos))
		{
			//auto col_hitbone = config::get<t>(Settings::Colors::aimbot_visuals_hitbone_col);
			if (Settings::Aimbot::aimbot_visuals_hitbone)
			{
				ImGui::GetBackgroundDrawList()->AddCircle({ bone_screen_pos.x, bone_screen_pos.y }, 5, ImColor(255, 255, 255), 100);
			}

			if (Settings::Aimbot::aimbot_visuals_snapline)
			{
				ImGui::GetBackgroundDrawList()->AddLine(ImGui::GetIO().DisplaySize / 2, { bone_screen_pos.x, bone_screen_pos.y }, ImColor(255, 255, 255));
			}
		}
	}

	auto get_scriptable_instanceContexts(const uint32_t id) -> game_struct::ScriptableInstanceContextSecure*
	{

		auto addr = (__int64*)((uintptr_t)GetModuleHandleA(0) + Settings::mem.scriptable.ClientContext);
		if (is_valid_ptr(addr))
		{
			auto ret = *addr + (static_cast<uint64_t>(id) * 0x98);

			return (game_struct::ScriptableInstanceContextSecure*)ret;
		}


		return nullptr;
	};

	game_struct::CG_ClientModel_RuntimeData* CG_ClientModel_GetRuntimeData(uint16_t id)
	{
		auto addr = (uintptr_t)((uintptr_t)GetModuleHandleA(0) + Settings::mem.scriptable.CG_ClientModel_RuntimeData.cast());
		auto ret = addr + (id * 0x338);
		return (game_struct::CG_ClientModel_RuntimeData*)ret;

	}


	enum RarityIndex
	{
		grey = 0,
		green = 1,
		blue = 2,
		purple = 3,
		gold = 4,
		custom_loot = 10
	};


	enum LootTypes
	{
		field_upgrade = 18,
		ammo = 1,
		weapon = 2,
		perk = 37,
		token = 15,
		crate = 21,
		plate = 7,
		money = 11,
		explosives = 9,
		tactical = 17,
		gasmask = 5,
		sell_item = 28,
		revivekit = 12,
		fuel = 35,
		contract = 20,
		streaks = 16
	};

	struct BG_SpawnGroup_Loot_ItemDef
	{
		const char* name;
		int8_t type; //0x0008
		char pad_0009[23]; //0x0009
		int8_t rarity; //0x0020
		const char pad_0021[7]; //0x0021
		const char* pickupString; //0x0028
		const char* pickupStringAsset; //0x0030
		const char* weaponFullString; //0x0038
		char pad_0040[128]; //0x0040
		int32_t weaponIndex; //0x00C0
		char pad_00C4[1992]; //0x00C4

	};

	struct loot_definition_t
	{
		const char* internal_name;
		const char* name;
	};

	const loot_definition_t definitions[] = {
		{"loot_gasmask","Gasmask"},
		{"jup_blue:military_loot_crate","Crate"},
		{"red::military_loot_perkpack_01","Perk Package"},
		{"accessory_money_bag_small","Money Bag"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},
		{"box_ v0","Armor Box"},


	};


	void loot()
	{

		//if (!game_sdk::in_game() || !Settings::Loot::b_enable_LootESP)
		//	return;

		//if (!Settings::client.cg)
		//	return;

		//if (!Settings::client.local_entity)
		//	return;

		//uintptr_t ImageBase;
		//ImageBase = (uint64_t)(iat(GetModuleHandleA).get()("cod.exe"));

		//uintptr_t s_CG_ClientModel_RuntimeData = 0xd969e557 + ImageBase; 

		//if (!Settings::Loot::b_enable_LootESP)
		//	return;

		//if (*(int*)(ImageBase + 0x119119C0) <= 1) 
		//	return;

		//CgGlobalsMP* cg = Settings::client.cg;
		//if (cg == nullptr)
		//	return;

		//for (int i = 0; i < 0x400; i++) 
		//{
		//	uintptr_t RuntimeData = s_CG_ClientModel_RuntimeData + 0x338 * i; 
		//	if (!RuntimeData)
		//		continue;

		//	auto& actualOrigin = *(math::vec3_t*)(RuntimeData + 0x1D0); 
		//	if ((actualOrigin.x + actualOrigin.y + actualOrigin.z) == 0)
		//		continue;

		//	static char buf[256];
		//	if (!*(bool*)(RuntimeData + 0xC8)) 
		//	{
		//		continue;
		//	}
		//	if (*(bool*)(RuntimeData + 0x11E))
		//	{
		//		continue;
		//	}

		//	math::vec2_t screen_pos;
		//	if (!game_sdk::world_to_screen(actualOrigin, screen_pos))
		//		continue;

		//	float distance = game_sdk::units_to_m(Settings::client.local_entity->get_pos().distance_to(actualOrigin));
		//	if (distance > 50) 
		//		continue;

		//	sprintf_s(buf, XOR("[%.1fm]"), distance);
		//	game_sdk::draw::draw_sketch_edge_text(g_menu::esp_font, buf, ImVec2(screen_pos.x, screen_pos.y), 14, ImColor(255, 255, 255, 252), true);
		//}

	}
}