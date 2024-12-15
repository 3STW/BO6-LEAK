#include"includes.h"
#include "imgui_settings.h"


namespace unlock
{
	int nightviskey;
	int slidekey;
	int airstuckkey;
	int aimkey;
	int aimkey2;
	int aimkey3;
	bool nightvision = false;
	bool airstuck = false;
	bool longmele = false;
	int Healthpos;
}

namespace Settings {
		namespace Visuals
		{
			float arrow_size = 40.f;
			int flCompassSize = 80;
			int cthick = 1.8;
			 bool b_showTeam = false;
			 bool b_showAI = false;
			 bool b_showMissile = false;
			 bool b_showItem = false;
		     bool b_showDistance = false;
			 bool b_showHealth = false;
			 bool b_showName = false;
			 bool b_showWeapon = false;
			 bool b_showteamid = false;
			 bool kills = false;
			 bool Damage = false;
			 bool assits = false;
			 bool score = false;
			 bool ping = false;
			 bool testnew = false;
			 bool b_showBox = false;
			 bool b_showBones = false;
			 bool b_headesp = false;
			 bool b_fov = false;
			 bool b_showCompass = false;
			 bool b_radar = false;
			 float radar_zoom = 24.70;
			 float radar_BlipSize = 8.0f;
			 float radar_size = 340.10;
			 bool show_aim_target = false;
			 float textsize = 12.f;
			 bool b_danger = false;
			 int box_type;
			 bool b_showVehicleBounds;
			 float max_ai_distance = 200.f;
			 float max_distance = 200.f;
			 float max_distance_compass = 100.f;
			 float max_danger_distance = 50.f;
			 bool RGB_tracer;
			 bool b_bulletTracer;
			 bool rgbmode = false;
			 int FadeTime = 1000;
			 bool b_lookingAtYou = false;
			 bool b_aimingAtYou = false;

			 bool rgbcircle;
			 bool rgbcrosshair;
		}
		namespace Loot
		{
			bool showGreyLoot = false;
			bool showGreenLoot = false;
			bool showBlueLoot = false;
			bool showGoldLoot = false;
			bool showRedLoot = false;
			bool showPurpleLoot = false;
			bool showCustomLoot = false;

			bool showweapons = false;
			bool dmz_random = false;
			bool itemShowCash = false;
			bool itemShowToken = false;
			bool itemShowFuel = false;

			bool itemShowPerk = false;

			bool itemShowKillStreak;
			bool itemShowCrates = false;
			bool itemShowArmor = false;
			bool itemShowFupgrade;
			bool itemShowAmmo = false;
			bool itemShowTactical = false;
			bool itemShowLethal = false;
			bool itemShowSelfRevive;
			bool itemShowGasMask;
			bool itemShowContracts;
			bool showAllLootColor;
			bool showOnlyRarity = false;
			bool Debug_loot = false;
			bool b_enable_LootESP = false;
			bool b_name = false;
			bool b_box = false;
			bool b_distance = false;
			int max_distance = 50.f; //5 ~ 1000
		}
		namespace Aimbot
		{
			bool aim_at_team = false;
			bool enabled = false;
			bool Enable2 = false;
			bool skip_vehicle = false;
			int delay;
			int aim_method2 = 0;
			int aim_method = 0;
			bool Disable_on_Kill = false;
			bool silent = false;
			bool Aim_at_ai = false;
			bool visible_only = false;
			bool skip_knocked = false;
			bool self_reviving = false;
			bool prediction = false;
			bool static_fov = false;
			uint32_t target_fov = 54;
			uint32_t aim_key;
			uint32_t bone_priority;
			uint32_t bone_priority2;
			uint32_t override_priority;
			uint32_t target_mode;
			uint32_t target_mode2;
			uint32_t fov_mode;
			uint32_t fov_mode2;

			float fov = 15.f;
			float fov2 = 15.f;
			float max_distance = 200.f;
			float smoothness = 1.f;
			float smoothness2 = 1.f;
			float acceleration = 1.f;
			float smoothness_strength = 1.f;
		    bool AntiAim;
			bool AntiAim_pitch;
			bool AntiAim_yaw;
			bool chinese;

			int Anti_aim_selection;
			int Anti_aim_pitch_selection;
			int Anti_aim_yaw_selection;
		    bool autoshoot;
			bool autowall;

			bool skip_riotshield;
			bool smart_bone_scan;
			bool rgbmode;
			bool prediction_circle;
			bool aimbot_visuals_hitbone;
			bool aimbot_visuals_snapline;
			float slider_dot = 50.0f;
			float slider_speed = 25.f;
			ImColor color_edit4[4] = { 155, 150, 219, 255 };
		}
		namespace Misc
		{
			ImColor CrosshairColor{ 255, 255, 255, 255 };
			bool crosshair = false;
			bool rotatingcrosshair = false;
			float f_recoilslider{0.0f};
			float f_fov = 120.f;
			bool noflash;
			bool nostun;
			bool rapidfire;
			bool fov;
			bool thirdperson;
			bool norecoil;
			bool nosway;
			bool nospread;
			bool rgbmenu = false;

		}
		namespace Outlines
		{

			bool b_Full_RGB = false;
			const char* outline_types[] = { ("Outline"),("Pixel"),"Heat","Shape","Chams" };
			bool b_outline_player = false;
			bool b_AI = false;

			bool outline_myself = false;
			bool b_outline_item = false;
			bool b_outline_vehicle = false;
			bool b_enable_outline = false;
			bool drawOccludedPixels = false;
			bool drawNonOccludedPixels = false;
			bool fill = false;
			int RenderMode = 0;
			int linewidth = 3;
			float distance_item = 25.f;

		}
		namespace Gamepad
		{
			 int buttonID = 0;
		}
		namespace Colors
		{

			ImColor red(255, 0, 0);         // red
			ImColor green(0, 255, 0);       // green
			ImColor blue(0, 0, 255);        // blue
			ImColor white(255, 255, 255);   // white
			ImColor black(0, 0, 0);         // black
			ImColor yellow(255, 255, 0);    // yellow
			ImColor magenta(255, 255, 2555);   // magenta
			ImColor cyan(0, 255, 255);      // cyan

			ImColor MenuColor(140, 140, 140, 255);

			

			ImColor AI_color = yellow;
			ImColor Missile_color = white;
			ImColor item_color = white;

			ImColor visible_team = blue;
			ImColor not_visible_team = blue;

			ImColor visible_box = red;
			ImColor not_visible_box = white;

			ImColor visible_distance = red;
			ImColor not_visible_distance = white;

			ImColor visible_name = red;
			ImColor not_visible_name = white;

			ImColor aimbot_visuals_hitbone_col = white;
			ImColor aimbot_visuals_snapline_col = white;

			ImColor visible_Weapon = red;
			ImColor not_visible_Weapon = white;

			ImColor visible_Bone = red;
			ImColor not_visible_Bone = white;

			ImColor visible_compass = red;
			ImColor not_visible_compass = white;

			ImColor visible_radar = red;
			ImColor not_visible_radar = white;

			ImColor outline_player = red;
			ImColor outline_vehicle = red;
			ImColor vehicle_bounds = red;
			ImColor aim_target = green;

			ImColor tracer_shadow = yellow;
			ImColor tracer = yellow;
			ImColor tracer_hitmarker = yellow;
			ImColor Crosshairnew = white;
			ImColor fovcirclenew = white;

			
		}
		namespace logging
		{
			 math::vec3_t _localpos;
			 math::vec3_t pos;
			 math::angle_t angle;
			 float spread = 0;
			 int counter = 0;
			 int counter2 = 0;
			 byte macaddr[6];
			 uintptr_t macAsUint64;
			 uintptr_t internaladdr;
			 uintptr_t externaladdr;
			 uintptr_t checksum;

			 char original_mac1;
			 char original_mac2;
			 char original_mac3;
			 char original_mac4;
			 char original_mac5;
			 char original_mac6;
			 char original_mac7;

			 char randomized_mac1;
			 char randomized_mac2;
			 char randomized_mac3;
			 char randomized_mac4;
			 char randomized_mac5;
			 char randomized_mac6;
			 char randomized_mac7;

		}
		BOOL WritePrivateProfileInt(LPCSTR lpAppName, LPCSTR lpKeyName, int nInteger, LPCSTR lpFileName) {
			char lpString[1024];
			sprintf(lpString, "%d", nInteger);
			return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
		}
		BOOL WritePrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, float nInteger, LPCSTR lpFileName) {
			char lpString[1024];
			sprintf(lpString, "%f", nInteger);
			return WritePrivateProfileStringA(lpAppName, lpKeyName, lpString, lpFileName);
		}
		float GetPrivateProfileFloat(LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName)
		{
			char szData[32];

			GetPrivateProfileStringA(lpAppName, lpKeyName, std::to_string(flDefault).c_str(), szData, 32, lpFileName);

			return (float)atof(szData);
		}
		void Save_Settings(std::string fileName) {
		
			char file[MAX_PATH];
			sprintf_s(file, XOR("C:\\Cheat+Blocker\\config\\\\%s%s"), fileName.c_str(), XOR(".ini"));

			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showTeam"), Visuals::b_showTeam, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showAI"), Visuals::b_showAI, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showMissile"), Visuals::b_showMissile, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showItem"), Visuals::b_showItem, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showDistance"), Visuals::b_showDistance, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showHealth"), Visuals::b_showHealth, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showName"), Visuals::b_showName, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showWeapon"), Visuals::b_showWeapon, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showBox"), Visuals::b_showBox, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showBones"), Visuals::b_showBones, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_fov"), Visuals::b_fov, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_showCompass"), Visuals::b_showCompass, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("show_aim_target"), Visuals::show_aim_target, file);-
			WritePrivateProfileFloat(XOR("Visuals"), XOR("max_distance_compass"), Visuals::max_distance_compass, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_radar"), Visuals::b_radar, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_bulletTracer"), Visuals::b_bulletTracer, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("RGB_tracer"), Visuals::RGB_tracer, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_lookingAtYou"), Visuals::b_lookingAtYou, file);
			WritePrivateProfileInt(XOR("Visuals"), XOR("b_aimingAtYou"), Visuals::b_aimingAtYou, file);

			WritePrivateProfileFloat(XOR("Visuals"), XOR("max_distance"), Visuals::max_distance, file);
			WritePrivateProfileFloat(XOR("Visuals"), XOR("max_ai_distance"), Visuals::max_ai_distance, file);
			WritePrivateProfileFloat(XOR("Visuals"), XOR("radar_zoom"), Visuals::radar_zoom, file);
			WritePrivateProfileFloat(XOR("Visuals"), XOR("radar_size"), Visuals::radar_size, file);
			WritePrivateProfileFloat(XOR("Visuals"), XOR("radar_BlipSize"), Visuals::radar_BlipSize, file);



			WritePrivateProfileInt(XOR("Aimbot"), XOR("aim_method"), Aimbot::aim_method, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("enabled"), Aimbot::enabled, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("Disable_on_Kill"), Aimbot::Disable_on_Kill, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("delay"), Aimbot::delay, file);

			WritePrivateProfileInt(XOR("Aimbot"), XOR("Aim_at_ai"), Aimbot::Aim_at_ai, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("prediction"), Aimbot::prediction, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("AntiAim_pitch"), Aimbot::AntiAim_pitch, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("AntiAim_yaw"), Aimbot::AntiAim_yaw, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("AntiAim"), Aimbot::AntiAim, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("visible_only"), Aimbot::visible_only, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("silent"), Aimbot::silent, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("skip_knocked"), Aimbot::skip_knocked, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("self_reviving"), Aimbot::self_reviving, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("static_fov"), Aimbot::static_fov, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("Anti_aim_selection"), Aimbot::Anti_aim_selection, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("Anti_aim_yaw_selection"), Aimbot::Anti_aim_yaw_selection, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("Anti_aim_pitch_selection"), Aimbot::Anti_aim_pitch_selection, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("fov_mode"), Aimbot::fov_mode, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("target_fov"), Aimbot::target_fov, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("bone_priority"), Aimbot::bone_priority, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("aim_key"), Aimbot::aim_key, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("target_mode"), Aimbot::target_mode, file);
			WritePrivateProfileFloat(XOR("Aimbot"), XOR("max_distance"), Aimbot::max_distance, file);
			WritePrivateProfileFloat(XOR("Aimbot"), XOR("fov"), Aimbot::fov, file);
			WritePrivateProfileFloat(XOR("Aimbot"), XOR("smoothness"), Aimbot::smoothness, file);
			WritePrivateProfileFloat(XOR("Aimbot"), XOR("acceleration"), Aimbot::acceleration, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("aim_at_team"), Aimbot::aim_at_team, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("skip_vehicle"), Aimbot::skip_vehicle, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("autoshoot"), Aimbot::autoshoot, file);
			WritePrivateProfileInt(XOR("Aimbot"), XOR("prediction_circle"), Aimbot::prediction_circle, file);




			WritePrivateProfileInt(XOR("Outlines"), XOR("b_enable_outline"), Outlines::b_enable_outline, file);
			WritePrivateProfileInt(XOR("Outlines"), XOR("fill"), Outlines::fill, file);
			WritePrivateProfileInt(XOR("Outlines"), XOR("RenderMode"), Outlines::RenderMode, file);
			WritePrivateProfileInt(XOR("Outlines"), XOR("linewidth"), Outlines::linewidth, file);


			WritePrivateProfileInt(XOR("Misc"), XOR("noflash"), Misc::noflash, file);
			WritePrivateProfileInt(XOR("Misc"), XOR("nostun"), Misc::nostun, file);
			WritePrivateProfileInt(XOR("Misc"), XOR("rapidfire"), Misc::rapidfire, file);
			WritePrivateProfileInt(XOR("Misc"), XOR("fov"), Misc::fov, file);
			WritePrivateProfileInt(XOR("Misc"), XOR("thirdperson"), Misc::thirdperson, file);
			WritePrivateProfileInt(XOR("Misc"), XOR("norecoil"), Misc::norecoil, file);
			WritePrivateProfileFloat(XOR("Misc"), XOR("f_recoilslider"), Misc::f_recoilslider, file);
			WritePrivateProfileFloat(XOR("Misc"), XOR("f_fov"), Misc::f_fov, file);
			WritePrivateProfileFloat(XOR("Misc"), XOR("Recoil_Slider"), Misc::f_recoilslider, file);


			WritePrivateProfileInt(XOR("Colors"), XOR("not_visible_team"), Colors::not_visible_team, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visible_team"), Colors::visible_team, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("lethal"), Colors::Missile_color, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("item"), Colors::Missile_color, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("bot_COLOR"), Colors::AI_color, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("notvisiblebox"), Colors::not_visible_box, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visiblebox"), Colors::visible_box, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("notvisibleweapon"), Colors::not_visible_Weapon, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visibleweapon"), Colors::visible_Weapon, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("notvisibleskeleton"), Colors::not_visible_Bone, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visibleskeleton"), Colors::visible_Bone, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("notvisiblename"), Colors::not_visible_name, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visiblename"), Colors::visible_name, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("notvisibledistance"), Colors::not_visible_distance, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visibledistance"), Colors::visible_distance, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("compass_not_visible"), Colors::not_visible_compass, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("compass_visible"), Colors::visible_compass, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("not_visible_radar"), Colors::not_visible_radar, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("visible_radar"), Colors::visible_radar, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("aim_target"), Colors::aim_target, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("outline_player"), Colors::outline_player, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("outline_vehicle"), Colors::outline_vehicle, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("vehicle_bounds"), Colors::vehicle_bounds, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("tracer"), Colors::tracer, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("tracer_hitmarker"), Colors::tracer_hitmarker, file);
			WritePrivateProfileInt(XOR("Colors"), XOR("tracer_shadow"), Colors::tracer_shadow, file);

		}
		void Load_Settings(std::string fileName)
		{
			char file[MAX_PATH];
			sprintf_s(file, XOR("C:\\Cheat+Blocker\\config\\\\%s%s"), fileName.c_str(), XOR(".ini"));

			Visuals::b_showTeam = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showTeam"), Visuals::b_showTeam, file);
			Visuals::b_showAI = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showAI"), Visuals::b_showAI, file);
			Visuals::b_showMissile = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showMissile"), Visuals::b_showMissile, file);
			Visuals::b_showItem = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showItem"), Visuals::b_showItem, file);
			Visuals::b_showDistance = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showDistance"), Visuals::b_showDistance, file);
			Visuals::b_showHealth = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showHealth"), Visuals::b_showHealth, file);
			Visuals::b_showName = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showName"), Visuals::b_showName, file);
			Visuals::b_showWeapon = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showWeapon"), Visuals::b_showWeapon, file);
			Visuals::b_showBox = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showBox"), Visuals::b_showBox, file);
			Visuals::b_showBones = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showBones"), Visuals::b_showBones, file);
			Visuals::b_fov = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_fov"), Visuals::b_fov, file);
			Visuals::b_showCompass = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_showCompass"), Visuals::b_showCompass, file);
			Visuals::b_radar = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_radar"), Visuals::b_radar, file);
			Visuals::b_bulletTracer = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_bulletTracer"), Visuals::b_bulletTracer, file);
			Visuals::RGB_tracer = GetPrivateProfileIntA(XOR("Visuals"), XOR("RGB_tracer"), Visuals::RGB_tracer, file);
			Visuals::b_lookingAtYou = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_lookingAtYou"), Visuals::b_lookingAtYou, file);
			Visuals::b_aimingAtYou = GetPrivateProfileIntA(XOR("Visuals"), XOR("b_aimingAtYou"), Visuals::b_aimingAtYou, file);

			Visuals::show_aim_target = GetPrivateProfileIntA(XOR("Visuals"), XOR("show_aim_target"), Visuals::show_aim_target, file);
			Visuals::max_distance_compass = GetPrivateProfileFloat(XOR("Visuals"), XOR("max_distance_compass"), Visuals::max_distance_compass, file);
			Visuals::max_distance = GetPrivateProfileFloat(XOR("Visuals"), XOR("max_distance"), Visuals::max_distance, file);
			Visuals::max_ai_distance = GetPrivateProfileFloat(XOR("Visuals"), XOR("max_ai_distance"), Visuals::max_ai_distance, file);
			Visuals::radar_BlipSize = GetPrivateProfileFloat(XOR("Visuals"), XOR("radar_BlipSize"), Visuals::radar_BlipSize, file);
			Visuals::radar_size = GetPrivateProfileFloat(XOR("Visuals"), XOR("radar_size"), Visuals::radar_size, file);
			Visuals::radar_zoom = GetPrivateProfileFloat(XOR("Visuals"), XOR("radar_zoom"), Visuals::radar_zoom, file);



			//aimbot
			Aimbot::delay = GetPrivateProfileIntA(XOR("Aimbot"), XOR("delay"), Aimbot::delay, file);
			Aimbot::aim_method = GetPrivateProfileIntA(XOR("Aimbot"), XOR("aim_method"), Aimbot::aim_method, file);
			Aimbot::enabled = GetPrivateProfileIntA(XOR("Aimbot"), XOR("enabled"), Aimbot::enabled, file);
			Aimbot::Disable_on_Kill = GetPrivateProfileIntA(XOR("Aimbot"), XOR("Disable_on_Kill"), Aimbot::Disable_on_Kill, file);

			Aimbot::Aim_at_ai = GetPrivateProfileIntA(XOR("Aimbot"), XOR("Aim_at_ai"), Aimbot::Aim_at_ai, file);
			Aimbot::prediction = GetPrivateProfileIntA(XOR("Aimbot"), XOR("prediction"), Aimbot::prediction, file);
			Aimbot::AntiAim_pitch = GetPrivateProfileIntA(XOR("Aimbot"), XOR("AntiAim_pitch"), Aimbot::AntiAim_pitch, file);
			Aimbot::AntiAim_yaw = GetPrivateProfileIntA(XOR("Aimbot"), XOR("AntiAim_yaw"), Aimbot::AntiAim_yaw, file);
			Aimbot::AntiAim = GetPrivateProfileIntA(XOR("Aimbot"), XOR("AntiAim"), Aimbot::AntiAim, file);
			Aimbot::visible_only = GetPrivateProfileIntA(XOR("Aimbot"), XOR("visible_only"), Aimbot::visible_only, file);
			Aimbot::silent = GetPrivateProfileIntA(XOR("Aimbot"), XOR("silent"), Aimbot::silent, file);
			Aimbot::skip_knocked = GetPrivateProfileIntA(XOR("Aimbot"), XOR("skip_knocked"), Aimbot::skip_knocked, file);
			Aimbot::self_reviving = GetPrivateProfileIntA(XOR("Aimbot"), XOR("self_reviving"), Aimbot::self_reviving, file);
			Aimbot::static_fov = GetPrivateProfileIntA(XOR("Aimbot"), XOR("static_fov"), Aimbot::static_fov, file);
			Aimbot::Anti_aim_selection = GetPrivateProfileIntA(XOR("Aimbot"), XOR("Anti_aim_selection"), Aimbot::Anti_aim_selection, file);
			Aimbot::Anti_aim_yaw_selection = GetPrivateProfileIntA(XOR("Aimbot"), XOR("Anti_aim_yaw_selection"), Aimbot::Anti_aim_yaw_selection, file);
			Aimbot::Anti_aim_pitch_selection = GetPrivateProfileIntA(XOR("Aimbot"), XOR("Anti_aim_pitch_selection"), Aimbot::Anti_aim_pitch_selection, file);
			Aimbot::fov_mode = GetPrivateProfileIntA(XOR("Aimbot"), XOR("fov_mode"), Aimbot::fov_mode, file);
			Aimbot::target_fov = GetPrivateProfileIntA(XOR("Aimbot"), XOR("target_fov"), Aimbot::target_fov, file);
			Aimbot::bone_priority = GetPrivateProfileIntA(XOR("Aimbot"), XOR("bone_priority"), Aimbot::bone_priority, file);
			Aimbot::aim_key = GetPrivateProfileIntA(XOR("Aimbot"), XOR("aim_key"), Aimbot::aim_key, file);
			Aimbot::target_mode = GetPrivateProfileIntA(XOR("Aimbot"), XOR("target_mode"), Aimbot::target_mode, file);
			Aimbot::max_distance = GetPrivateProfileFloat(XOR("Aimbot"), XOR("max_distance"), Aimbot::max_distance, file);
			Aimbot::fov = GetPrivateProfileFloat(XOR("Aimbot"), XOR("fov"), Aimbot::fov, file);
			Aimbot::smoothness = GetPrivateProfileFloat(XOR("Aimbot"), XOR("smoothness"), Aimbot::smoothness, file);
			Aimbot::acceleration = GetPrivateProfileFloat(XOR("Aimbot"), XOR("acceleration"), Aimbot::acceleration, file);
			Aimbot::aim_at_team = GetPrivateProfileIntA(XOR("Aimbot"), XOR("aim_at_team"), Aimbot::aim_at_team, file);
			Aimbot::skip_vehicle = GetPrivateProfileIntA(XOR("Aimbot"), XOR("skip_vehicle"), Aimbot::skip_vehicle, file);
			Aimbot::autoshoot = GetPrivateProfileIntA(XOR("Aimbot"), XOR("autoshoot"), Aimbot::autoshoot, file);
			Aimbot::prediction_circle = GetPrivateProfileIntA(XOR("Aimbot"), XOR("prediction_circle"), Aimbot::prediction_circle, file);



			Outlines::b_enable_outline = GetPrivateProfileIntA(XOR("Outlines"), XOR("b_enable_outline"), Outlines::b_enable_outline, file);
			Outlines::fill = GetPrivateProfileIntA(XOR("Outlines"), XOR("fill"), Outlines::fill, file);
			Outlines::RenderMode = GetPrivateProfileIntA(XOR("Outlines"), XOR("RenderMode"), Outlines::RenderMode, file);
			Outlines::linewidth = GetPrivateProfileIntA(XOR("Outlines"), XOR("linewidth"), Outlines::linewidth, file);


			Misc::noflash = GetPrivateProfileIntA(XOR("Misc"), XOR("noflash"), Misc::noflash, file);
			Misc::nostun = GetPrivateProfileIntA(XOR("Misc"), XOR("nostun"), Misc::nostun, file);
			Misc::rapidfire = GetPrivateProfileIntA(XOR("Misc"), XOR("rapidfire"), Misc::rapidfire, file);
			Misc::fov = GetPrivateProfileIntA(XOR("Misc"), XOR("fov"), Misc::fov, file);
			Misc::thirdperson = GetPrivateProfileIntA(XOR("Misc"), XOR("thirdperson"), Misc::thirdperson, file);
			Misc::norecoil = GetPrivateProfileIntA(XOR("Misc"), XOR("norecoil"), Misc::norecoil, file);
			Misc::f_recoilslider = GetPrivateProfileFloat(XOR("Misc"), XOR("f_recoilslider"), Misc::f_recoilslider, file);
			Misc::f_fov = GetPrivateProfileFloat(XOR("Misc"), XOR("f_fov"), Misc::f_fov, file);


			Colors::not_visible_team = GetPrivateProfileIntA(XOR("Colors"), XOR("not_visible_team"), Colors::not_visible_team, file);
			Colors::visible_team = GetPrivateProfileIntA(XOR("Colors"), XOR("visible_team"), Colors::visible_team, file);
			Colors::Missile_color = GetPrivateProfileIntA(XOR("Colors"), XOR("lethal"), Colors::Missile_color, file);
			Colors::Missile_color = GetPrivateProfileIntA(XOR("Colors"), XOR("item"), Colors::Missile_color, file);
			Colors::AI_color = GetPrivateProfileIntA(XOR("Colors"), XOR("bot_COLOR"), Colors::AI_color, file);
			Colors::not_visible_box = GetPrivateProfileIntA(XOR("Colors"), XOR("notvisiblebox"), Colors::not_visible_box, file);
			Colors::visible_box = GetPrivateProfileIntA(XOR("Colors"), XOR("visiblebox"), Colors::visible_box, file);
			Colors::not_visible_Weapon = GetPrivateProfileIntA(XOR("Colors"), XOR("notvisibleweapon"), Colors::not_visible_Weapon, file);
			Colors::visible_Weapon = GetPrivateProfileIntA(XOR("Colors"), XOR("visibleweapon"), Colors::visible_Weapon, file);
			Colors::not_visible_Bone = GetPrivateProfileIntA(XOR("Colors"), XOR("notvisibleskeleton"), Colors::not_visible_Bone, file);
			Colors::visible_Bone = GetPrivateProfileIntA(XOR("Colors"), XOR("visibleskeleton"), Colors::visible_Bone, file);
			Colors::not_visible_name = GetPrivateProfileIntA(XOR("Colors"), XOR("notvisiblename"), Colors::not_visible_name, file);
			Colors::visible_name = GetPrivateProfileIntA(XOR("Colors"), XOR("visiblename"), Colors::visible_name, file);
			Colors::not_visible_distance = GetPrivateProfileIntA(XOR("Colors"), XOR("notvisibledistance"), Colors::not_visible_distance, file);
			Colors::visible_distance = GetPrivateProfileIntA(XOR("Colors"), XOR("visibledistance"), Colors::visible_distance, file);
			Colors::not_visible_compass = GetPrivateProfileIntA(XOR("Colors"), XOR("compass_not_visible"), Colors::not_visible_compass, file);
			Colors::visible_compass = GetPrivateProfileIntA(XOR("Colors"), XOR("compass_visible"), Colors::visible_compass, file);
			Colors::not_visible_radar = GetPrivateProfileIntA(XOR("Colors"), XOR("not_visible_radar"), Colors::not_visible_radar, file);
			Colors::visible_radar = GetPrivateProfileIntA(XOR("Colors"), XOR("visible_radar"), Colors::visible_radar, file);
			Colors::aim_target = GetPrivateProfileIntA(XOR("Colors"), XOR("aim_target"), Colors::aim_target, file);
			Colors::outline_vehicle = GetPrivateProfileIntA(XOR("Colors"), XOR("outline_vehicle"), Colors::outline_vehicle, file);
			Colors::outline_player = GetPrivateProfileIntA(XOR("Colors"), XOR("outline_player"), Colors::outline_player, file);
			Colors::vehicle_bounds = GetPrivateProfileIntA(XOR("Colors"), XOR("vehicle_bounds"), Colors::vehicle_bounds, file);
			Colors::tracer = GetPrivateProfileIntA(XOR("Colors"), XOR("tracer"), Colors::tracer, file);
			Colors::tracer_hitmarker = GetPrivateProfileIntA(XOR("Colors"), XOR("tracer_hitmarker"), Colors::tracer_hitmarker, file);
			Colors::tracer_shadow = GetPrivateProfileIntA(XOR("Colors"), XOR("tracer_shadow"), Colors::tracer_shadow, file);

		}
		void Auto_Load()
		{
			if (!GetList().empty()) {
				Load_Settings(GetList().at(0));
			}
			else {
				CreateDirectoryA(XOR("C:\\Cheat+Blocker"), NULL);
				CreateDirectoryA(XOR("C:\\Cheat+Blocker\\config"), NULL);
			}
		}
		std::vector<std::string> GetList()
		{
			std::vector<std::string> configs;
			WIN32_FIND_DATA ffd;
			LPCSTR directory = XOR("C:\\Cheat+Blocker\\config\\*");
			auto hFind = FindFirstFile(directory, &ffd);
			while (FindNextFile(hFind, &ffd))
			{
				if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					std::string file_name = ffd.cFileName;
					if (file_name.size() < 4) // .cfg
						continue;
					std::string end = file_name;
					end.erase(end.begin(), end.end() - 4);
					if (end != XOR(".ini"))
						continue;
					file_name.erase(file_name.end() - 4, file_name.end());
					configs.push_back(file_name);
				}
			}
			return configs;
		}
}