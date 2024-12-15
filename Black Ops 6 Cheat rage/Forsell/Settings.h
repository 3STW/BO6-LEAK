#pragma once



namespace unlock
{
	extern int Healthpos;
	extern int aimkey2;
	extern int aimkey3;
	extern int nightviskey;
	extern int slidekey;
	extern int airstuckkey;
	extern int aimkey;
	extern bool longmele;
	extern bool nightvision;
	extern bool airstuck;
}

namespace Settings {
		namespace Visuals
		{
			extern int cthick;
			extern float arrow_size;
			extern int flCompassSize;
			extern bool b_showTeam;
			extern bool b_showAI;
			extern bool b_showMissile;
			extern bool b_showItem;
			extern bool b_showDistance;
			extern bool b_showHealth;
			extern bool b_showName;
			extern bool b_showWeapon;
			extern bool b_showteamid;
			extern bool assits;
			extern bool ping;
			extern bool score;
			extern bool kills;
			extern bool Damage;
			extern bool testnew;
			extern bool b_showBox;
			extern bool b_showBones;
			extern bool b_headesp;
			extern bool b_fov;
			extern bool b_showCompass;
			extern bool b_radar; 
			extern bool show_aim_target;
			extern bool b_danger;
			extern bool b_showVehicleBounds;
			extern bool b_bulletTracer;
			extern bool rgbmode;
			extern bool b_lookingAtYou;
			extern bool b_aimingAtYou;

			extern bool RGB_tracer;
			extern float textsize;
			extern int FadeTime;

			extern int box_type;

			extern float radar_zoom ;
			extern float radar_BlipSize;
			extern float radar_size ;
			 extern float max_distance_compass;
			 extern float max_danger_distance;

			extern float max_distance;
			extern float max_ai_distance;
			extern bool rgbcircle;
			extern bool rgbcrosshair;
		}
		namespace Loot
		{

			extern bool showGreyLoot;
			extern bool showGreenLoot;
			extern bool showBlueLoot;
			extern bool showGoldLoot;
			extern bool showRedLoot;
			extern bool showCustomLoot;
			extern bool showPurpleLoot;

			extern bool showweapons;
			extern bool dmz_random;
			extern bool itemShowCash;
			extern bool itemShowToken;
			extern bool itemShowFuel;
			extern bool itemShowPerk;
			extern bool itemShowKillStreak;
			extern bool itemShowCrates;
			extern bool itemShowArmor;
			extern bool itemShowFupgrade;
			extern bool itemShowAmmo;
			extern bool itemShowTactical;
			extern bool itemShowLethal;
			extern bool itemShowSelfRevive;
			extern bool itemShowGasMask;
			extern bool itemShowContracts;
			extern bool showAllLootColor;
			extern bool showOnlyRarity;

			extern bool Debug_loot;

			extern bool b_enable_LootESP;
			extern bool b_name;
			extern bool b_box;
			extern bool b_distance;
			extern int max_distance; //5 ~ 1000

		
		}
		namespace Aimbot
		{
			extern int aim_method2;
			extern int delay;
			extern int aim_method;
			extern bool Disable_on_Kill;
			extern bool aim_at_team;
			extern bool skip_vehicle;
			extern bool enabled;
			extern bool Enable2;
			extern bool Aim_at_ai;
			extern bool prediction;
			extern bool AntiAim_pitch;
			extern bool AntiAim_yaw;
			extern bool chinese;
			extern bool AntiAim;
			extern bool visible_only;
			extern bool silent;
			extern bool skip_knocked;
			extern bool self_reviving;
			extern bool static_fov;
			extern int Anti_aim_selection;
			extern int Anti_aim_pitch_selection;
			extern int Anti_aim_yaw_selection;
			extern bool autoshoot;
			extern bool autowall;
			extern bool skip_riotshield;
			extern bool smart_bone_scan;
			extern bool rgbmode;
			extern bool prediction_circle;
			extern bool aimbot_visuals_hitbone;
			extern bool aimbot_visuals_snapline;
			extern float slider_dot;
			extern float slider_speed ;
			extern ImColor color_edit4[4];


	
			extern uint32_t fov_mode;
			extern uint32_t fov_mode2;
			extern uint32_t target_fov;
			extern uint32_t target_mode2;
			extern float smoothness2;
			extern uint32_t bone_priority;
			extern uint32_t bone_priority2;
			extern uint32_t override_priority;
			extern uint32_t aim_key;
			extern uint32_t target_mode;
			extern float  max_distance;
			extern float fov;
			extern float fov2;
			extern float smoothness;
			extern float acceleration;
			extern float smoothness_strength;
		}
		namespace Misc
		{
			extern bool noflash;
			extern bool nostun;
			extern bool rapidfire;
			extern bool fov;
			extern bool thirdperson;
			extern bool norecoil;
			extern bool nosway;
			extern bool nospread;
			extern float f_recoilslider;
			extern bool crosshair;
			extern bool rotatingcrosshair;
			extern float f_fov;
			extern ImColor CrosshairColor;
			extern bool rgbmenu;

		}
		namespace Outlines
		{
			extern bool b_Full_RGB;
			const char* outline_types[];
			extern bool b_enable_outline;
			extern bool b_outline_player;
			extern bool outline_myself;
			extern bool b_AI;

			extern bool b_outline_item;
			extern bool b_outline_vehicle;
			extern bool drawOccludedPixels;
			extern bool drawNonOccludedPixels;
			extern bool fill;
			extern int RenderMode;
			extern int linewidth;
			extern float distance_item;

		}
		namespace Gamepad
		{
			extern int buttonID;
		}
		namespace Colors
		{
			extern ImColor red;         // red
			extern ImColor green;       // green
			extern ImColor blue;        // blue
			extern ImColor white;   // white
			extern ImColor black;         // black
			extern ImColor yellow;    // yellow
			extern ImColor magenta;   // magenta
			extern ImColor cyan;      // cyan
			extern ImColor MenuColor;

			extern ImColor AI_color;
			extern ImColor Missile_color;
			extern ImColor item_color;


			extern ImColor visible_team;
			extern ImColor not_visible_team;

			extern ImColor visible_box;
			extern ImColor not_visible_box;

			extern ImColor visible_distance;
			extern ImColor not_visible_distance;

			extern ImColor visible_name;
			extern ImColor not_visible_name;

			extern ImColor visible_Weapon;
			extern ImColor not_visible_Weapon;
			extern ImColor aimbot_visuals_snapline_col;
			extern ImColor aimbot_visuals_hitbone_col;

			extern ImColor visible_Bone;
			extern ImColor not_visible_Bone;

			extern ImColor visible_compass;
			extern ImColor not_visible_compass;
			extern ImColor visible_radar;
			extern ImColor not_visible_radar;
			extern ImColor aim_target;
			extern ImColor outline_player;
			extern ImColor outline_vehicle;
			extern ImColor vehicle_bounds;
			extern ImColor tracer_shadow;
			extern ImColor tracer;
			extern ImColor tracer_hitmarker;
			extern ImColor Crosshairnew;
			extern ImColor fovcirclenew;


		}
		namespace logging
		{
			extern math::vec3_t _localpos;
			extern math::vec3_t pos;
			extern math::angle_t angle;
			extern float spread;
			extern int counter ;
			extern int counter2;
			extern byte macaddr[6];
			extern uintptr_t macAsUint64;

			extern uintptr_t internaladdr;
			extern uintptr_t externaladdr;
			extern uintptr_t checksum;


			extern char original_mac1;
			extern char original_mac2;
			extern char original_mac3;
			extern char original_mac4;
			extern char original_mac5;
			extern char original_mac6;
			extern char original_mac7;

			extern char randomized_mac1;
			extern char randomized_mac2;
			extern char randomized_mac3;
			extern char randomized_mac4;
			extern char randomized_mac5;
			extern char randomized_mac6;
			extern char randomized_mac7;


		}
		void Load_Settings_byKey();
		void Save_Settings(std::string fileName);
		void Load_Settings(std::string fileName);
		void Auto_Load();
		std::vector<std::string> GetList();

}