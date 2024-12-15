#pragma once

class refdefKeyStruct {
public:
	DWORD ref0;      // 0x00
	DWORD ref1;      // 0x04
	DWORD ref2;		// 0x08
};

void start_tick();
void update_vel_map(int index, math::vec3_t vPos);
void clear_vel_map();
namespace game_sdk
{

	inline struct sCompass
	{
		float flCompassSize, flArrowSize;
		ImVec2 vCompassPosition, vArrowPosition;
	} Compass;

	inline struct sRadar
	{
		float flScale = 10.f, flRadarSize = 200, flBlipSize = 8.0f;
		ImVec2 vRadarPosition, vBlipPosition;
	} Radar;

	enum BONE_INDEX : unsigned long
	{

		BONE_POS_HELMET = 8,

		BONE_POS_HEAD = 7,
		BONE_POS_NECK = 6,
		BONE_POS_CHEST = 5,
		BONE_POS_MID = 4,
		BONE_POS_TUMMY = 3,
		BONE_POS_PELVIS = 2,


		BONE_POS_RIGHT_FOOT_1 = 21,
		BONE_POS_RIGHT_FOOT_2 = 22,
		BONE_POS_RIGHT_FOOT_3 = 23,
		BONE_POS_RIGHT_FOOT_4 = 24,

		BONE_POS_LEFT_FOOT_1 = 17,
		BONE_POS_LEFT_FOOT_2 = 18,
		BONE_POS_LEFT_FOOT_3 = 19,
		BONE_POS_LEFT_FOOT_4 = 20,

		BONE_POS_LEFT_HAND_1 = 13,
		BONE_POS_LEFT_HAND_2 = 14,
		BONE_POS_LEFT_HAND_3 = 15,
		BONE_POS_LEFT_HAND_4 = 16,

		BONE_POS_RIGHT_HAND_1 = 9,
		BONE_POS_RIGHT_HAND_2 = 10,
		BONE_POS_RIGHT_HAND_3 = 11,
		BONE_POS_RIGHT_HAND_4 = 12
	};

	struct sTracer
	{
		bool bW2SSuccess;
		int iStartTime;
		math::vec2_t vHitPos2D, vStartPos2D;
		math::vec3_t vHitPos3D, vStartPos3D;
		ImColor cColorShadow, cColorHitMarker, cColorTracer;
		float flAlphaShadow, flAlphaHitMarker, flAlphaTracer;
	};
	inline std::vector<sTracer> vTracers;

	game_struct::Weapon_t* GetWeaponByIndex(unsigned short index);
	math::angle_t GetSpread();
	void CalculateTracers();
	void DrawTracers();

	void DrawAimingAtYOu(entity_t* ent,bool visible);
	float units_to_m(float units);
	game_struct::refdef_t* GetRefDef();
	bool world_to_screen(const math::vec3_t& origin, math::vec2_t& screen);
	bool bones_to_screen(math::vec3_t* BonePosArray, math::vec2_t* ScreenPosArray, const long Count);
	bool w2s(const math::vec3_t& WorldPos, math::vec2_t* ScreenPos, math::vec2_t* BoxSize);
	bool WorldToEnemyBox(math::vec3_t& WorldPos, math::vec3_t& headpos, math::vec2_t* ScreenPos, math::vec2_t* BoxSize);
	bool WorldToBox(math::vec3_t WorldPos, math::vec2_t* ScreenPos, math::vec2_t* BoxSize);

	void for_every_player(const std::function<bool(entity_t* pl)>& func, bitflag_t flags = {});
	bool in_game();
	bool in_game2();
	float get_ingame_fov_value(float actualFov);
	float get_actual_fov_value(float ingameFOV);
	float get_fov(const math::angle_t viewangle, const math::angle_t aim_angle);
	float get_entity_fov(entity_t* ent);
	int GamePadkey(int index);
	void VecToAngle(const math::vec3_t vec, math::angle_t& angle);
	math::vec3_t Get_Velocity(int index);
	math::vec3_t get_prediction(entity_t* ent, int index, math::vec3_t source, math::vec3_t destination);
	void GetPlayerBounds(game_struct::entityState_t* es, game_struct::Bounds& bounds);
	void DrawCompass(entity_t* ent, math::vec3_t localpos, math::vec3_t pos,ImColor color);
	void DrawRadar(entity_t* ent, ImColor color);
	void DrawProjectilePrediction(entity_t* ent);


	namespace draw
	{
		void DrawRotatingCrosshair(const ImVec2& center, float size, float rotationDegrees);
		void DrawString(std::string text, float x, float y, float size, bool shadow, ImVec4 color);
		void draw_sketch_edge_text(ImFont* pFont, const std::string_view& text, const ImVec2& pos, float size, uint32_t color, bool center, uint32_t EdgeColor = 0xFF000000);
		void draw_bone(math::vec2_t* bones_screenPos, long count, DWORD color);
		void draw_bone(entity_t* pl, int bone_1, int bone_2, ImColor col);
		void draw_bones(unsigned long i, DWORD color);
		void draw_health(int i_health, math::vec4_t pos);
		void fill_rectangle(const float x, const float y, const float width, const float hight, const uint32_t color);
		void draw_box(float x,
			float y,
			float w,
			float h,
			bool border,
			const uint32_t color);
		// bend over and strip bby ;)
		void draw_3d_box(const game_struct::Bounds& bounds, const math::vec3_t& origin, const  math::angle_t& angle, ImColor color);
		void draw_3d_box_filled(const game_struct::Bounds& bounds, const math::vec3_t& origin, const math::angle_t& angle, ImColor faceColor);




		void draw_line(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness);
		void draw_circle(const ImVec2& position, float radius, uint32_t color, float thickness);
		void rect_filled(const math::vec2_t& pos, const math::vec2_t& size, const ImColor& col);
		void rect(const math::vec2_t& pos, const math::vec2_t& size, const ImColor& col);
		void DrawBox(
			float x,
			float y,
			float w,
			float h,
			bool border,
			const uint32_t color
		);
	}

}

