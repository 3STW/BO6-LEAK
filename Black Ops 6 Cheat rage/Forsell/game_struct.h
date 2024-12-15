#pragma once
#include"includes.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define AutoPadding(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
#define AutoPadding_0(type, name, offset) type name

struct entity_t;
namespace game_struct
{


	struct Weapon_t;

	enum DWLobbyService_LobbyStatus : __int32
	{
		UNINITIALIZED = 0x0,
		NOT_CONNECTED = 0x1,
		CONNECTING = 0x2,
		WAITING_FOR_REPORT_PC_HARDWAREDETAILS = 0x3,
		CONNECTED = 0x4,
		DISCONNECTING = 0x5,
		DISCONNECTED = 0x6,
	};


	const struct _GUID
	{
		unsigned int Data1;
		unsigned __int16 Data2;
		unsigned __int16 Data3;
		unsigned __int8 Data4[8];
	};

	struct  XUID
	{
		unsigned __int64 m_id;
	};


	struct  bdMACAddr
	{
		unsigned __int8 m_data[6];
	};

	struct score_t
	{
		int ClientNumber;
		int status;
		int Score;
		int Ping;
		int Deaths;
		int Team;
		bool isBot;
		int Kills;
		int Rank;
		int prestige_mp;
		const char* rankDisplayLevel;
		int Assists;
		int extrascore0;
		int extrascore1;
		int Damage;
		int extrascore3;
		int extrascore4;
		int extrascore5;
		__int16 placement;
		int adrenaline;
		int deathTimerLength;
	};


	struct ClStatic
	{
		char pad[0xA40];
		BYTE m_activeGameTypeQuick[1];
	};


	enum WeapType {
		WEAPTYPE_NONE = 0,
		WEAPTYPE_MODEL_ONLY = 1,
		WEAPTYPE_BULLET = 2,
		WEAPTYPE_GRENADE = 3,
		WEAPTYPE_PROJECTILE = 4,
		WEAPTYPE_RIOTSHIELD = 5,
		WEAPTYPE_SCRIPT = 6,
		WEAPTYPE_SHIELD = 7,
		WEAPTYPE_CHARGE_SHIELD = 8,
		WEAPTYPE_LOCATION_SELECT = 9,
		WEAPTYPE_EQUIP_DEPLOY = 0x0A,
	};

	enum PenetrateType {


		PENETRATE_TYPE_NONE = 0,
		PENETRATE_TYPE_SMALL = 1,
		PENETRATE_TYPE_MEDIUM = 2,
		PENETRATE_TYPE_LARGE = 3,
		PENETRATE_TYPE_MAXIMUM = 4,
		PENETRATE_TYPE_TABLE_ENTRY_COUNT = 4,
		PENETRATE_TYPE_RICOCHET = 5,
		PENETRATE_TYPE_COUNT = 6
	};

	struct Bounds
	{
		math::vec3_t midPoint;
		math::vec3_t halfSize;
	};

	struct  XModel
	{
		char pad_0000[0x8]; //0x0000
		const char* name;
		//Bounds Bounds; //0x005C
	};

	enum rarity : unsigned int
	{
		grey = 0,
		green = 1,
		blue = 2,
		purple = 3,
		gold = 4,

		red = 5, //legendary 
		black = 13, //custom loadout weapon 

		secretGold = 10, //contracts
	};

	//class CG_ClientModel_RuntimeData
	//{
	//public:
	//	char pad_0000[200]; //0x0000
	//	uint8_t valid; //0x00C8
	//	char pad_00C9[1]; //0x00C9
	//	 Weapon_t* weapon; //0x00CA
	//	char pad_00D2[10]; //0x00D2
	//	int8_t Rarity; //0x00DC
	//	char pad_00DD[61]; //0x00DD
	//	uint8_t Loot_isopen; //0x011A
	//	char pad_011B[181]; //0x011B
	//	math::vec3_t vecOrigin; //0x01C8
	//	char pad_01D4[1728]; //0x01D4
	//}; //Size: 0x0894

	//class CG_ClientModel_RuntimeData
	//{
	//public:
	//	char pad_0000[286]; //0x0000
	//	int8_t valid; //0x011E
	//	char pad_011F[177]; //0x011F
	//	math::vec3_t position; //0x01D0
	//	char pad_01DC[8121]; //0x01DC
	//}; //Size: 0x2195

	class CG_ClientModel_RuntimeData
	{
	public:
		char pad_0000[103]; //0x0000
		game_struct::XModel* model; //0x0067
		char pad_006F[175]; //0x006F
		int8_t valid; //0x011E
		char pad_011F[177]; //0x011F
		math::vec3_t position; //0x01D0
		char pad_01DC[4028]; //0x01DC
	}; //Size: 0x1198

	struct BgWeaponParms
	{
		math::vec3_t forward;
		math::vec3_t right;
		math::vec3_t up;
		math::vec3_t muzzleTrace;
		math::vec3_t gunForward;
	};

	class GfxSceneHudOutlineInfo
	{
	public:
		char pad_0000[8]; //0x0000
		uint32_t color; //0x0008
		char pad_000C[8]; //0x000C
		bool drawOccludedPixels; //0x0014
		bool drawNonOccludedPixels; //0x0015
		char pad_0016[1]; //0x0018
		bool fill; //0x0016
		char pad_0017[5]; //0x0018
		uint8_t renderMode; //0x001D
		uint8_t lineWidth; //0x001E
		char pad_001E[8510]; //0x001F
	}; //Size: 0x215D


	struct GfxSceneEntityMutableShaderData
	{
		char pd[0xA8];
		GfxSceneHudOutlineInfo hudOutlineInfo;
	};

	struct cpose_t
	{
		unsigned __int8 eType;
		unsigned __int8 cullIn;
		unsigned __int8 isPosePrecise;
		unsigned __int8 entOriginSet;
		volatile int mdaoCullIn;
		unsigned __int8 ragdollFlags;
		unsigned __int8 isEntityPose;
		unsigned __int8 hasStaleEntityPose;
		unsigned __int8 mayhemInstanceId;
		bool isMayhem;
		bool reusePreviousSkelPose;
		int ragdollHandle;
		int killcamRagdollHandle;
		int physicsId;
	};




	class clientState_t
	{
	public:
		int32_t index; //0x0000
		char pad_0004[16]; //0x0004
		int32_t team; //0x0014
		char pad_0018[164]; //0x0018
		int32_t isMLGSpectator; //0x00BC
		char pad_00C0[452]; //0x00C0

	}; //Size: 0x0284


	class snapshot_t
	{
	public:
		char pad_0000[12]; //0x0000
		int32_t serverTime; //0x000C
		char pad_0010[237812]; //0x0010
		clientState_t clientstate[200]; //0x3A104
	}; //Size: 0x3A424


	struct BallisticInfoCalculated_t
	{
		float* distances;
		void* unkn;
		int numDistanceEntries;
	};


	struct BallisticInfo_t
	{
		BallisticInfoCalculated_t* calculated;
		char pad0[0x8];
		float muzzle_velocity;
		char pad1[0xC];
		float gravity_scale;
		float zeroing_distance;
		int lifetime_ms;
		bool enable_trajectory;
	};

	enum LocalClientNum_t
	{
		LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
		LOCAL_CLIENT_0 = 0x0,
		LOCAL_CLIENT_1 = 0x1,
		LOCAL_CLIENT_LAST = 0x1,
		LOCAL_CLIENT_COUNT = 0x2,
	};

	class secured_vec3_t
	{
	private:
		int keys[4];

		__forceinline uintptr_t base(int idx) const
		{
			return reinterpret_cast<uintptr_t>(&keys[idx]);
		}
	public:
		math::vec3_t get() const
		{
			//cod vec3_t encryption
			int v42 = 0, v54[3] = {};
			v42 = keys[3];
			v54[0] = static_cast<int>(keys[0] ^ ((base(0) ^ v42) * ((base(0) ^ v42) + 2)));
			v54[1] = static_cast<int>(keys[1] ^ ((base(1) ^ v42) * ((base(1) ^ v42) + 2)));
			v54[2] = static_cast<int>(keys[2] ^ ((v42 ^ base(2)) * ((v42 ^ base(2)) + 2)));
			return math::vec3_t(*reinterpret_cast<float*>(&v54[0]), *reinterpret_cast<float*>(&v54[1]), *reinterpret_cast<float*>(&v54[2]));
		}

		void set(float x, float y, float z)
		{
			//cod vec3_t decryption
			int v42, v43, v54[3];
			v42 = keys[3];
			v54[0] = static_cast<int>(keys[0] ^ ((base(0) ^ v42) * ((base(0) ^ v42) + 2)));
			v54[1] = static_cast<int>(keys[1] ^ ((base(1) ^ v42) * ((base(1) ^ v42) + 2)));
			v54[2] = static_cast<int>(keys[2] ^ ((v42 ^ base(2)) * ((v42 ^ base(2)) + 2)));

			*reinterpret_cast<float*>(&v54[0]) = x;
			*reinterpret_cast<float*>(&v54[1]) = y;
			*reinterpret_cast<float*>(&v54[2]) = z;

			v43 = v42 + keys[4];
			keys[3] = v43;
			keys[0] = static_cast<int>(v54[0] ^ ((v43 ^ base(0)) * ((v43 ^ base(0)) + 2)));
			keys[1] = static_cast<int>(v54[1] ^ ((v43 ^ base(1)) * ((v43 ^ base(1)) + 2)));
			keys[2] = static_cast<int>(v54[2] ^ ((v43 ^ base(2)) * ((v43 ^ base(2)) + 2)));
		}

		void set(math::vec3_t value)
		{
			return set(value.x, value.y, value.z);
		}
	};

	enum ShockViewTypes : __int32
	{
		SHELLSHOCK_VIEWTYPE_BLURRED = 0x0,
		SHELLSHOCK_VIEWTYPE_FLASHED = 0x1,
		SHELLSHOCK_VIEWTYPE_PHOTO = 0x2,
		SHELLSHOCK_VIEWTYPE_NONE = 0x3,
	};

	struct unnamed_type_screenBlend
	{
		int blurredFadeTime;
		int blurredEffectTime;
		int flashWhiteFadeTime;
		int flashShotFadeTime;
		ShockViewTypes type;
	};

	struct unnamed_type_view
	{
		int fadeTime;
		float kickRate;
		float kickRadius;
	};

	struct unnamed_type_sound
	{
		bool affect;
		char loop[64];
		char loopSilent[64];
		char end[64];
		char endAbort[64];
		int fadeInTime;
		int fadeOutTime;
		char audioZone[64];
		int modEndDelay;
		int loopFadeTime;
		int loopEndDelay;
	};

	struct unnamed_type_lookControl
	{
		bool affect;
		int fadeTime;
		float mouseSensitivity;
		float maxPitchSpeed;
		float maxYawSpeed;
	};
	struct Score_T {
		int ClientNumber;
		int status;
		int Score;
		int Ping;
		int Deaths;
		int Team;
		bool isBot;
		int Kills;
		int Rank;
		int prestige_mp;
		const char* rankDisplayLevel;
		int Assists;
		int extrascore0;
		int extrascore1;
		int Damage;
		int extrascore3;
		int extrascore4;
		int extrascore5;
		__int16 placement;
		int adrenaline;
		int deathTimerLength;
	};
	//E8 ?? ?? ?? ?? 4C 8B C8 45 8B C5 48 8B D6 48 8B CD E8 ?? ?? ?? ?? | Resolve Call
	struct unnamed_type_movement
	{
		bool affect;
		bool breakSprint;
		bool breakJog;
	};

	struct unnamed_type_mount
	{
		bool affect;
	};

	struct shellshock_parms_t
	{
		unnamed_type_screenBlend screenBlend;
		unnamed_type_view view;
		unnamed_type_sound sound;
		unnamed_type_lookControl lookControl;
		unnamed_type_movement movement;
		unnamed_type_mount mount;
	};


	struct shellshock_t
	{
		shellshock_parms_t* parms;
		int startTime;
		int duration;
		float sensitivity;
		math::vec2_t viewDelta;
		int wantSavedScreen;
		int hasSavedScreen;
		int hasScissor;
		bool lookControlActive;
		int loopEndTime;
	};

	struct GfxViewport
	{
		int x;
		int y;
		int Width;
		int Height;
	};

	class RefdefView
	{
	public:
		math::vec2_t tanHalfFov;
		unsigned int vieworigin[3];
		math::vec3_t axis[3];
		float zNear;
		char pad[0x34];
		unsigned int refdefViewOrg_aab; //: 0x70
		unsigned int refdefViewOrg_set_aab; //: 0x74

		math::vec3_t GetRefdefViewOrigin() const
		{
			int outData[3]{ 0 };
			auto aab = refdefViewOrg_aab;
			uintptr_t encptr[3]{ (uintptr_t)(&vieworigin[0]), (uintptr_t)(&vieworigin[1]), (uintptr_t)(&vieworigin[2]) };


			outData[0] = static_cast<int>(vieworigin[0] ^ ((encptr[0] ^ aab) * ((encptr[0] ^ aab) + 2)));
			outData[1] = static_cast<int>(vieworigin[1] ^ ((encptr[1] ^ aab) * ((encptr[1] ^ aab) + 2)));
			outData[2] = static_cast<int>(vieworigin[2] ^ ((encptr[2] ^ aab) * ((encptr[2] ^ aab) + 2)));

			return { *reinterpret_cast<float*>(&outData[0]), *reinterpret_cast<float*>(&outData[1]), *reinterpret_cast<float*>(&outData[2]) };
		}
	};

	struct refdef_t
	{
		GfxViewport displayViewport;
		RefdefView view;
		char __pad_0x4C[0x3C];
		math::vec3_t viewOffset;
	};

	enum RadarMode : __int8
	{
		RADAR_MODE_NORMAL = 0x0,
		RADAR_MODE_FAST = 0x1,
		RADAR_MODE_CONSTANT = 0x2,
		RADAR_MODE_SLOW = 0x3,
		RADAR_MODE_COUNT = 0x4,
	};

	enum CgEventLod : __int8
	{
		CG_EVENT_LOD_FULL_RES = 0x0,
		CG_EVENT_LOD0 = 0x1,
		CG_EVENT_LOD1 = 0x2,
		CG_EVENT_LOD2 = 0x3,
		CG_EVENT_LOD3 = 0x4,
		CG_EVENT_LOD4 = 0x5,
		CG_EVENT_LOD_COUNT = 0x6,
	};

	/* 2112 */
	enum CgEventLodFOV : __int8
	{
		CG_EVENT_LOD_NARROW_FOV = 0x0,
		CG_EVENT_LOD_WIDE_FOV = 0x1,
		CG_EVENT_LOD_NOT_IN_FOV = 0x2,
		CG_EVENT_LOD_FOV_COUNT = 0x3,
	};

	struct  CgEventLodEventTypeBits
	{
	};

	struct CgEventLodData
	{
		CgEventLod distanceLod;
		CgEventLodFOV fovLod;
		float distance;
		float cosAngleFromLookAt;
		CgEventLodEventTypeBits eventTypeDisabledOverride;
	};

	enum SndHitArmorType : __int32
	{
		SND_HIT_ARMOR_TYPE_NONE = 0x0,
		SND_HIT_ARMOR_TYPE_ARMOR = 0x1,
		SND_HIT_ARMOR_TYPE_COUNT = 0x2,
	};

	enum SndHitmarkerType : __int32
	{
		SND_HITMARKER_TYPE_STANDARD = 0x0,
		SND_HITMARKER_TYPE_BR_ARMOR_HIT = 0x1,
		SND_HITMARKER_TYPE_BR_ARMOR_BREAK = 0x2,
		SND_HITMARKER_TYPE_COUNT = 0x3,
	};


	struct Weapon_t
	{
		unsigned __int16 weaponIdx;
		unsigned __int16 stickerIndices[4];
		unsigned __int16 weaponClientLoadout;
		unsigned __int16 weaponOthers;
		unsigned __int8 weaponAttachments[13];
		unsigned __int8 attachmentVariationIndices[29];
		unsigned __int8 weaponCamo;
		unsigned __int8 weaponLootId;
		unsigned __int8 scopeVariation;
		unsigned __int8 visualAttachmentHighAddr;
		unsigned __int16 unknown;
		char pad[0xE];
		char pad1[0x4];
	};

	static_assert (sizeof(Weapon_t) == 0x50, "Weapon size is not correct");
	struct WeaponMapEntry
	{
		unsigned __int16 index;
		Weapon_t weapon;
	};

	static_assert (sizeof(WeaponMapEntry) == 0x52, "WeaponMapEntry size is not correct");
	struct BgWeaponMap
	{
		void* __vftable;
		WeaponMapEntry* m_entries;
	};

	struct CgWeaponMap : BgWeaponMap
	{
	};

	struct StringTable {
		char pad[12];
		int rowCount;
	};

	struct  ScriptableDef
	{
		char pad[0x18];
		int flags; //0x18;
		unsigned int numParts;//0x14;


	};


	struct ConstScriptableModelUnion
	{

	};

	struct  ScriptableInstanceContextSecure
	{
		char pad_0000[16]; //0x0000
		XModel* model; //0x0010
		char pad_0018[24]; //0x0018
		math::angle_t angles; //0x0030
		char pad_003C[76]; //0x003C
		math::vec3_t origin; //0x0088
		char pad_0094[64]; //0x0094

	};


	struct VehicleDef
	{
		char pad_0000[0x1B0];
		BYTE vehType;
	};


	enum entityType_s : __int16
	{
		ET_FIRST = 0x0,
		ET_GENERAL = 0x0,
		ET_PLAYER = 0x1,
		ET_PLAYER_CORPSE = 0x2,
		ET_ITEM = 0x3,
		ET_MISSILE = 0x4,
		ET_INVISIBLE = 0x5,
		ET_SCRIPTMOVER = 0x6,
		ET_SOUND = 0x7,
		ET_FX = 0x8,
		ET_LOOP_FX = 0x9,
		ET_PRIMARY_LIGHT = 0xA,
		ET_TURRET = 0xB,
		ET_HELICOPTER = 0xC,
		ET_PLANE = 0xD,
		ET_VEHICLE = 0xE,
		ET_VEHICLE_CORPSE = 0xF,
		ET_VEHICLE_SPAWNER = 0x10,
		ET_AGENT = 0x11,
		ET_AGENT_CORPSE = 0x12,
		ET_ACTOR = 0x13,
		ET_ACTOR_SPAWNER = 0x14,
		ET_ACTOR_CORPSE = 0x15,
		ET_PHYSICS_CHILD = 0x16,
		ET_BEAM = 0x17,
		ET_CLIENT_CHARACTER = 0x18,
		ET_RAGDOLL_CONSTRAINT = 0x19,
		ET_PHYSICS_VOLUME = 0x1A,
		ET_COVERWALL = 0x1B,
		ET_INFO_VOLUME_GRAPPLE = 0x1C,
		ET_EVENTS = 0x1D,
		ET_COUNT = 0x1E,
		ET_MAX = 0x100,
	};

	enum trType_t : __int32
	{
		TR_STATIONARY = 0x0,
		TR_INTERPOLATE = 0x1,
		TR_LINEAR = 0x2,
		TR_LINEAR_STOP = 0x3,
		TR_LINEAR_STOP_SECURE = 0x4,
		TR_SINE = 0x5,
		TR_GRAVITY = 0x6,
		TR_LOW_GRAVITY = 0x7,
		TR_ACCELERATE = 0x8,
		TR_DECELERATE = 0x9,
		TR_SLERP = 0xA,
		TR_PHYSICS_CLIENT_AUTH = 0xB,
		TR_PHYSICS_SERVER_AUTH = 0xC,
		TR_LINKED = 0xD,
		TR_FIRST_TRACK_LOCK = 0xE,
		TR_LAST_TRACK_LOCK = 0x12,
		TR_TRACK_FULL_LOCK = 0x13,
		TR_TRACK_ANGLE = 0x14,
		TR_ANGLE_ALONG_VELOCITY = 0x15,
		TR_ANIMATED_MOVER = 0x16,
		TR_FIRST_RAGDOLL = 0x17,
		TR_RAGDOLL = 0x17,
		TR_RAGDOLL_GRAVITY = 0x18,
		TR_RAGDOLL_GRAVITY_PLAYER_IMMEDIATE = 0x19,
		TR_RAGDOLL_INTERPOLATE = 0x1A,
		TR_RAGDOLL_INTERPOLATE_PLAYER_IMMEDIATE = 0x1B,
		TR_RAGDOLL_BLEND = 0x1C,
		TR_LAST_RAGDOLL = 0x1C,
		NUM_TRTYPES = 0x1D,
	};

	struct trajectory_t_secure
	{
		trType_t trType;  //pos=0x14    //apos=0x2c
		int trTime; //0x18          //0x30
		int trDuration; //0x1C      //0x34
		math::vec3_t trBase; //{0x20, 0x24, 0x28}
		math::vec3_t trDelta; //velocity {0x2C, 0x30, 0x34}

		static void Trajectory_GetTrBase(uintptr_t p_aab, trajectory_t_secure* traj, math::vec3_t* trBase) {

			//8B 3D ? ? ? ? B9 ? ? ? ? F7 D7 33
			struct {
				int X;      // 0x00
				int Y;      // 0x04
				int Z;		// 0x08
			} trbase_aab = *(decltype(trbase_aab)*)(p_aab);

			int keys[3] = { *reinterpret_cast<int*>(&traj->trBase.x),  *reinterpret_cast<int*>(&traj->trBase.y) ,  *reinterpret_cast<int*>(&traj->trBase.z) };

			int v1[3]{ 0 };
			v1[2] = trbase_aab.Z ^ keys[2] ^ keys[1];
			v1[1] = trbase_aab.Y ^ (keys[0] ^ keys[1]);
			v1[0] = keys[0] ^ ~trbase_aab.X;

			trBase->x = *reinterpret_cast<float*>(&v1[0]);
			trBase->y = *reinterpret_cast<float*>(&v1[1]);
			trBase->z = *reinterpret_cast<float*>(&v1[2]);
		}

		static void Trajectory_SetTrBase(uintptr_t p_aab, trajectory_t_secure* traj, const math::vec3_t* newTrBase) {
			struct s_trbase_aab {
				int X;      // 0x00
				int Y;      // 0x04
				int Z;		// 0x08
			};

			s_trbase_aab trbase_aab = *(s_trbase_aab*)(p_aab);
		}
	};

	enum LerpFlags
	{
		Lerp_Crouching = 1 << 0x3,
		Lerp_prone = 1 << 0x4

	};



	struct BgWeaponHandle
	{
		unsigned __int16 m_mapEntryId;
	};

	struct LerpEntityStateAnonymous
	{
		int data[9];
	};

	/* 22998 */
	struct LerpEntityStateTurret
	{
		math::vec3_t gunAngles;
		int lastBarrelRotChangeTime;
		int lastBarrelRotChangeRate;
		int turretFlags;
		int currentUserEnt;
		int shotCount;
		unsigned int stickerAndCamo;
	};

	/* 22999 */
	struct LerpEntityStateLoopFx
	{
		float cullDist;
		int period;
	};

	/* 23000 */
	struct ThreatSight
	{
		unsigned __int8 sight : 7;
		unsigned __int8 visible : 1;
		unsigned __int8 combat : 1;
	};

	/* 23001 */
	struct __declspec(align(4)) LerpEntityStateActor
	{
		unsigned __int8 species;
		unsigned __int8 unittype;
		unsigned __int8 stepMove;
		unsigned __int8 flags;
		ThreatSight threatSight[1];
		__int16 lookAtEntityNum;
		int hitLocation;
		math::vec3_t impactVector;
		float pupilDiameter;
		unsigned __int8 clothType;
	};

	/* 23002 */
	struct LerpEntityStatePrimaryLightPacked
	{
		unsigned int packedColorRG;
		unsigned int packedColorB_Fov;
		float intensity;
		float uvIntensity;
		float radius;
	};

	/* 23003 */
	struct LerpEntityStatePlayerExtraAnimDataGeneric
	{
		__int16 data[3];
	};

	/* 23004 */
	struct LerpEntityStatePlayerExtraAnimDataSkydive
	{
		__int16 pitch;
		__int16 roll;
		__int16 throttle;
	};

	/* 23005 */
	union LerpEntityStatePlayerExtraAnimData
	{
		LerpEntityStatePlayerExtraAnimDataGeneric anonymous;
		LerpEntityStatePlayerExtraAnimDataSkydive skydive;
	};

	/* 23006 */
	//#pragma pack(push, 1)
	struct LerpEntityStatePlayer
	{
		__int16 movementDir; //0x5c
		__int16 velocityDir; //0x5e
		unsigned __int16 torsoPitchPacked;
		unsigned __int16 waistPitchPacked;
		__int16 playerFlags; //0x64
		__int16 moveSpeedForAnimBlend;
		int worldUpAngles;
		unsigned __int16 leftStickPolarPacked;
		unsigned __int16 rightStickPolarPacked;
		BgWeaponHandle executionWeaponHandle; //0x70
		BgWeaponHandle accessoryWeaponHandle;  //0x72
		unsigned __int16 slopePacked; //0x74
		LerpEntityStatePlayerExtraAnimData extraAnimData;
	};
	//#pragma pack(pop)

	struct AgentAttachModelData
	{
		unsigned int m_data;
	};

	/* 23007 */
	struct LerpEntityStateAgentCorpse
	{
		int corpseInfo;
		AgentAttachModelData attachModels[8];
	};

	/* 23008 */
	struct LerpEntityStateVehicle
	{
		unsigned int indices;
		unsigned int flags;
		float bodyPitch;
		float bodyRoll;
		float steerYaw;
		float gunPitch;
		float gunYaw;
		unsigned int stickerAndCamo;
	};

	/* 23009 */
	struct LerpEntityStatePlane
	{
		int ownerNum;
		int enemyIcon;
		int friendIcon;
	};

	enum MissileFlightMode : __int32
	{
		MISSILEFLIGHTMODE_TOP = 0x0,
		MISSILEFLIGHTMODE_DIRECT = 0x1,
		MISSILEFLIGHTMODE_COUNT = 0x2,
	};

	/* 23010 */
	struct LerpEntityStateMissile
	{
		unsigned int predictionKey[2];
		int launchTime;
		MissileFlightMode flightMode;
		int flags;
		int targetEnt;
		int effectLength;
	};

	/* 23011 */
	struct LerpEntityStateSound
	{
		int subType;
		unsigned __int16 alias0;
		unsigned __int16 alias1;
		float lerp;
		unsigned int transientSoundbankBits1;
		unsigned int transientSoundbankBits2;
	};

	/* 23012 */
	struct LerpEntityStateScriptMover
	{
		int entToTakeMarksFrom;
		int xModelIndex;
		int flags;
		int animIndex;
		int animStartTime;
		int animPauseTime;
		unsigned int animRateQuantized;
		int mapEntLookup;
	};

	/* 23013 */
	struct LerpEntityStateBulletTracer
	{
		math::vec3_t end;
	};

	/* 23014 */
	struct __declspec(align(4)) LerpEntityStateBulletHitSP
	{
		math::vec3_t start;
		math::vec3_t relativeEnd;
		int hitImpactDelay;
		int partName;
		unsigned __int16 flags;
	};

	/* 23015 */
	struct BulletHitBoneInfo
	{
		unsigned __int32 boneId : 8;
		unsigned __int32 boneOffsetX : 8;
		unsigned __int32 boneOffsetY : 8;
		unsigned __int32 boneOffsetZ : 8;
	};

	/* 23016 */
	struct LerpEntityStateBulletHitMP
	{
		BulletHitBoneInfo boneInfo;
		int hitImpactDelay;
		unsigned int flags;
	};

	/* 23017 */
	struct LerpEntityStateCustomExplode
	{
		int startTime;
	};

	/* 23018 */
	struct LerpEntityStateExplosion
	{
		float innerRadius;
		float outerRadius;
		float magnitude;
	};

	/* 23019 */
	struct LerpEntityStateExplosionJolt
	{
		float innerRadius;
		float outerRadius;
		math::vec3_t impulse;
	};

	/* 23020 */
	struct LerpEntityStatePhysicsJitter
	{
		float innerRadius;
		float outerRadius;
		float minDisplacement;
		float maxDisplacement;
	};

	/* 23021 */
	struct LerpEntityStatePhysicsImpactSnd
	{
		int sndClass;
		float impactMomentum;
	};

	/* 23022 */
	struct LerpEntityStateRadiusDamage
	{
		float range;
		float delay;
		int damageMin;
		int damageMax;
		float forceScalar;
		int radiusDamageFlags;
	};

	/* 23023 */
	struct LerpEntityStateEarthquake
	{
		float scale;
		float radius;
		int duration;
	};

	/* 23024 */
	struct LerpEntityStateEffectPointToPoint
	{
		math::vec3_t end;
	};

	/* 23025 */
	struct LerpEntityStateRicochet
	{
		math::vec3_t direction;
		int ricochetCount;
		float distanceTraveled;
	};

	/* 23026 */
	struct LerpEntityStateMelee
	{
		int attackerEntNum;
	};

	/* 23027 */
	union LerpEntityStateEventUnion
	{
		LerpEntityStateBulletTracer bulletTracer;
		LerpEntityStateBulletHitSP bulletHitSP;
		LerpEntityStateBulletHitMP bulletHitMP;
		LerpEntityStateCustomExplode customExplode;
		LerpEntityStateExplosion explosion;
		LerpEntityStateExplosionJolt explosionJolt;
		LerpEntityStatePhysicsJitter physicsJitter;
		LerpEntityStatePhysicsImpactSnd physicsImpactSnd;
		LerpEntityStateRadiusDamage radiusDamage;
		LerpEntityStateEarthquake earthquake;
		LerpEntityStateEffectPointToPoint effectPointToPoint;
		LerpEntityStateRicochet ricochet;
		LerpEntityStateMelee melee;
	};

	enum LerpEntityStateBeamBeamSubtype : __int32
	{
		BEAMSUBTYPE_WEAPON = 0x0,
		BEAMSUBTYPE_SCRIPT = 0x1,
		BEAMSUBTYPE_COUNT = 0x2,
	};

	/* 21575 */
	struct LerpEntityStateBeamEntBonePair
	{
		unsigned int m_data;
	};

	/* 21576 */
	struct LerpEntityStateBeamScript
	{
		unsigned int m_data;
	};


	/* 23028 */
	struct LerpEntityStateBeam
	{
		LerpEntityStateBeamBeamSubtype subtype;
		LerpEntityStateBeamEntBonePair entBonePairs[7];
		LerpEntityStateBeamScript script;
	};

	/* 23029 */
	struct LerpEntityStateClientChar
	{
		unsigned int characterId;
		unsigned int assetId;
	};

	/* 23030 */
	struct RagdollHitLocationInfo
	{
		unsigned __int32 hitLocation : 8;
		__int32 offsetX : 8;
		__int32 offsetY : 8;
		__int32 offsetZ : 8;
	};

	/* 23031 */
	struct LerpEntityStateRagdollConstraint
	{
		RagdollHitLocationInfo point;
		unsigned int rootNodeControlledByAnim;
		unsigned int useImpalingSpikeVFX;
	};

	/* 23032 */
	struct LerpEntityStatePhysicsVolume
	{
		unsigned int flags;
		float scaleValue;
		float vectorX;
		float vectorY;
		float vectorZ;
		float limit;
	};

	/* 23033 */
	struct LerpEntityStateCoverWall
	{
		unsigned int coverGrid[7];
		unsigned int flags;
	};

	/* 23034 */
	struct LerpEntityStateInfoVolumeGrapple
	{
		unsigned int flags;
		math::vec3_t upVector;
	};

	/* 23035 */
	union LerpEntityStateTypeUnion
	{
		LerpEntityStateAnonymous anonymous;
		LerpEntityStateTurret turret;
		LerpEntityStateLoopFx loopFx;
		LerpEntityStateActor actor;
		LerpEntityStatePrimaryLightPacked primaryLight;
		LerpEntityStatePlayer player;
		LerpEntityStateAgentCorpse agentCorpse;
		LerpEntityStateVehicle vehicle;
		LerpEntityStatePlane plane;
		LerpEntityStateMissile missile;
		LerpEntityStateSound sound;
		LerpEntityStateScriptMover scriptMover;
		LerpEntityStateEventUnion event;
		LerpEntityStateBeam beam;
		LerpEntityStateClientChar clientCharacter;
		LerpEntityStateRagdollConstraint ragdollConstraint;
		LerpEntityStatePhysicsVolume physicsVolume;
		LerpEntityStateCoverWall coverWall;
		LerpEntityStateInfoVolumeGrapple infoVolumeGrapple;
	};

	struct StaticEntityStateGeneral
	{
		unsigned int xmodel;
	};

	struct StaticEntityStatePlayer
	{
		BgWeaponHandle offhandWeaponHandle;
		BgWeaponHandle stowedWeaponHandle;
	};

	/* 23039 */
	struct StaticEntityStateVehiclePlayer
	{
		unsigned __int8 playerIndex;
		unsigned __int8 teamId;
		unsigned __int8 pad[2];
	};

	/* 23040 */
	struct StaticEntityStateTurret
	{
		unsigned int xmodel;
		unsigned int carrierEntNum;
	};


	/* 23041 */
	struct StaticEntityStateMover__unnamed_type_u__unnamed_type_mapCircleInfo
	{
		unsigned __int32 colorIndex : 6;
		unsigned __int32 styleIndex : 6;
		unsigned __int32 iconIndex : 6;
	};

	/* 23042 */
	union StaticEntityStateMover__unnamed_type_u
	{
		unsigned int scriptableIndex;
		unsigned int reflectionProbeIndex;
		int clientNum;
		unsigned int weaponIndex;
		unsigned int headModelIndex;
		StaticEntityStateMover__unnamed_type_u__unnamed_type_mapCircleInfo mapCircleInfo;
	};

	/* 23043 */
	struct StaticEntityStateMover
	{
		int moverFlags;
		StaticEntityStateMover__unnamed_type_u u;
	};

	/* 23044 */
	struct StaticEntityStatePhysicsVolume
	{
		int shapeID;
	};

	/* 23045 */
	struct StaticEntityStatePrimaryLight
	{
		unsigned int offset;
	};

	/* 23046 */
	struct StaticEntityStatePlane
	{
		unsigned int xmodel;
	};

	/* 23047 */
	struct StaticEntityStateCoverWall
	{
		unsigned int xmodel;
	};

	/* 23048 */
	struct StaticEntityStateMissile
	{
		unsigned int attackerEnt;
	};

	/* 23049 */
	struct StaticEntityStateAgentCorpse
	{
		BgWeaponHandle stowedWeaponHandle;
	};

	/* 23050 */
	struct StaticEntityStateFX
	{
		unsigned int index;
		int killEffectDef;
	};

	/* 23051 */
	struct StaticEntityStateAnonymous
	{
		int data[2];
	};

	union StaticEntityStateTypeUnion
	{
		StaticEntityStateGeneral general;
		StaticEntityStatePlayer player;
		StaticEntityStateVehiclePlayer vehiclePlayer;
		StaticEntityStateTurret turret;
		StaticEntityStateMover mover;
		StaticEntityStatePhysicsVolume physicsVolume;
		StaticEntityStatePrimaryLight primaryLight;
		StaticEntityStatePlane plane;
		StaticEntityStateCoverWall coverwall;
		StaticEntityStateMissile missile;
		StaticEntityStateAgentCorpse agentCorpse;
		StaticEntityStateFX fx;
		StaticEntityStateAnonymous anonymous;
	};


	struct LerpEntityState
	{
		uint32_t nFlags; //0xC
		char m_pad[0x4];
		trajectory_t_secure pos; //0x14     //position
		trajectory_t_secure apos; //0x2C    //viewangles
		char m_pad01[0xA];
		LerpEntityStateTypeUnion u; //0x5C
		char m_pad00[0x4];
	};

#pragma pack(push, 1)
	struct entityState_t
	{
		__int16 number;
		__int16 otherEntityNum;
		__int16 attackerEntityNum;
		__int16 groundEntityNum;
		entityType_s eType;
		unsigned __int8 surfType;
		bool inAltWeaponMode; //0xB
		LerpEntityState lerp; //0xC
		StaticEntityStateTypeUnion staticState;
		char pad00[0x48];
		int animinfo; //0xE0
		char pad01[0x28];
		BgWeaponHandle weaponHandle; //0x98 //0x10C
		int time2;
		int loopSound;
		int clientNum;
	};
#pragma pack(pop)

	struct BGTrajectory
	{
		uintptr_t* unknown;
		LerpEntityState* m_es;
		uintptr_t* unknown2;
		uintptr_t* unknown3;
	};


	//class playerState_t
	//{
	//public:
	//	char pad_0000[312]; //0x0000
	//	int gravity; // 0x0138
	//	math::angle_t deltaAngle; //0x013C
	//	char pad_0148[376]; //0x0148
	//	int32_t clientnum; //0x02C0
	//	char pad_02CC[11428]; //0x02CC
	//}; //Size: 0x20A4
	typedef math::vec3_t vec3_t[3];
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
	struct playerState_s
	{
		float commandTime;
		DEFINE_MEMBER_N(float, serverTime, 0x4);
		DEFINE_MEMBER_N(float, inputTime, 0x8);
		DEFINE_MEMBER_N(float, prevInputTime, 0xC);
		DEFINE_MEMBER_N(float, pm_type, 0x10);
		DEFINE_MEMBER_N(float, pm_time, 0x14);
		DEFINE_MEMBER_N(math::vec3_t, m_origin, 0x40);
		DEFINE_MEMBER_N(math::vec3_t, m_velocity, 0x4C);
		DEFINE_MEMBER_N(math::angle_t, delta_angles, 0x13C);
		DEFINE_MEMBER_N(int, clientnum, 0x2C0);
		DEFINE_MEMBER_N(vec3_t, viewAngle, 0x2C4);
		DEFINE_MEMBER_N(float, viewHeightCurrent, 0x2F4);
		DEFINE_MEMBER_N(bool, radarEnabled, 0x459);
		DEFINE_MEMBER_N(bool, radarBlocked, 0x45A);
		DEFINE_MEMBER_N(RadarMode, radarMode, 0x45C);
		DEFINE_MEMBER_N(bool, radarShowEnemyDirection, 0x45B);
	};
	class playerState_t
	{
	public:
		char pad_0x0[0x40]; //0x0
		math::vec3_t origin; //0x40
		math::vec3_t velocity; //0x4C
		char pad_0x58[0xE4]; //0x58
		math::angle_t deltaAngle; //0x13C
		char pad_0x148[0x178]; //0x148
		int32_t clientnum; //0x2C0


	}; //Size: 0x0324

	enum BRDataFlags : uint32_t
	{
		InGulag = 0x2 << 8,
		InGulagMatch = 0x4 << 8,
		Downed = 0x08 << 8,
		BeingRevived = 0x10 << 8,
		SelfReviving = 0x20 << 8,
	};



	//class clientinfo_t {
	//public:
	//	union
	//	{
	//		AutoPadding(char, name[36], 0x4);
	//		AutoPadding(int, game_extrainfo, 0x70);
	//		AutoPadding(int32_t, health, 0x84);
	//		AutoPadding(int32_t, squadIndex, 0x90);
	//	};

	//};

	class clientinfo_t
	{
	public:
		char pad_0000[4]; //0x0000
		char name[36]; //0x0004
		char pad_0028[72]; //0x0028
		int32_t game_extrainfo; //0x0070
		char pad_0074[16]; //0x0074
		int32_t health; //0x0084
		char pad_0088[8]; //0x0088
		int32_t squadIndex; //0x0090
		char pad_0094[268]; //0x0094
	}; //Size: 0x01A0

	/*class clientInfo_t {
	public:
		union {
			DEFINE_MEMBER_N(char, name[36], 0x4);
			DEFINE_MEMBER_N(char, nameWithHash[36], 0x28);
			DEFINE_MEMBER_N(uint32_t, game_extrainfo, 0x70);
			DEFINE_MEMBER_N(int32_t, health, 0x84);
			DEFINE_MEMBER_N(int32_t, squadIndex, 0x90);
		};
	};*/

	struct UserClientBits_t
	{
		unsigned int data[7];
		bool isVisible(int entIndex)
		{
			auto v9 = 0x80000000 >> (entIndex & 0x1F);
			auto v10 = entIndex >> 5;
			return data[v10] & v9;
		}
	};




	//struct usercmd_t
	//{
	//	//shared::bitflag_t  buttons; //0
	//	//UserCommandStateFlags    stateFlags; //8
	//	//int    serverTime; //12
	//	//int    commandTime; //16
	//	//int    inputTime; //20
	//	//int angles[3]; //24
	//	//Weapon weapon; //36
	//	//Weapon offHand; //96
	//	//signed char forwardmove; //156 
	//	//signed char rightmove; //157
	//	//signed char pitchmove; //158
	//	//char yawmove; //159
	//	//short meleeChargeEnt; //160 
	//	//char packedControllerAim; //162
	//	//char selectedLoc[2];  //163
	//	//char selectedAngle;   //165
	//	//char remoteControlAngles[2];    //166
	//	//char remoteControlMove[3];      //168
	//	//char mlgSelectedLoc[2];         //171
	//	//char mlgSelectedAngle;          //173
	//	//LightSample lightSample;        //174
	//	//short    avoidForward;           //176
	//	//short    avoidRight;
	//	//unsigned char    upmove; //unsigned char, which gives you at least the 0 to 255 range.
	//	//unsigned char    downmove;
	//	//bool    inputFromGamepad;
	//	//bool    isAlternate;
	//	//short    vehAngles[3];
	//	//int random; //NOT SURE IF GOES HERE
	//	//int random1; //NOT SURE IF GOES HERE
	//	//float    vehOrgX;
	//	//float    vehOrgY;
	//	//float    vehOrgZ;
	//	//float    gunPitch;
	//	//float    gunYaw;
	//	//float    gunXOfs;
	//	//float    gunYOfs;
	//	//float    gunZOfs;
	//	//float    rollSensitivity;
	//	//short    scriptedMeleeTarget;
	//	//short    airburstMarkDistance;
	//	//UserCmdClientBits sightedClientMask;
	//	//short    extrapolationMax;
	//	//short    interpolationMax;
	//	////float random1; //NOT SURE IF GOES HERE
	//	union
	//	{
	//		AutoPadding_0(shared::bitflag_t, buttons, 0x0);
	//		AutoPadding(int, servertime, 0x20);
	//		AutoPadding(int, commandtime, 0x24);
	//		AutoPadding(int, cmdAngle[3], 0x2C);
	//		AutoPadding(secured_vec3_t, vehangle, 0x128);

	//	};



	//};

	struct usercmd_t
	{
		bitflag_t buttons; //0x0000
		char pad_0008[32]; //0x0008
		int commandTime; //0x0028
		char pad_002C[4]; //0x002C
		int angle[3]; //0x0030
		char pad_003C[516]; //0x003C

		char forwardmove; //156 
		char rightmove; //157

		math::angle_t GetAngle();

	};

	//struct usercmd_t
	//{

	//	char pad_0000[8]; //0x0000
	//	bitflag_t  buttons; //0x0008
	//	char pad_0010[12]; //0x0010
	//	int32_t servertime; //0x001C
	//	char pad_0020[8]; //0x0020
	//	int32_t commandTime; //0x0028
	//	char pad_002C[4]; //0x002C
	//	int angle[3]; //0x0030
	//	char pad_003C[1104]; //0x003C
	//	 math::angle_t GetAngle();
	//};



	struct AimAssistGlobals_t
	{
		char      m_pad_0x160[0x160];
		secured_vec3_t    m_viewOrigin;
	};

	enum GamePadButton : __int32
	{
		GPAD_NONE = 0x0,
		GPAD_UP = 0x10000100,
		GPAD_DOWN = 0x10000200,
		GPAD_LEFT = 0x10000400,
		GPAD_RIGHT = 0x10000800,
		GPAD_START = 0x10000004,
		GPAD_BACK = 0x10000008,
		GPAD_L3 = 0x10004000,
		GPAD_R3 = 0x10008000,
		GPAD_A = 0x10000010,
		GPAD_B = 0x10000020,
		GPAD_X = 0x10000040,
		GPAD_Y = 0x10000080,
		GPAD_L_SHLDR = 0x10001000,
		GPAD_R_SHLDR = 0x10002000,
		GPAD_L_TRIG = 0x20000000,
		GPAD_R_TRIG = 0x20000001,
	};

	enum Physics_WorldId
	{
		PHYSICS_WORLD_ID_INVALID = 0xFFFFFFFF,
		PHYSICS_WORLD_ID_FIRST = 0x0,
		PHYSICS_WORLD_ID_SERVER_FIRST = 0x0,
		PHYSICS_WORLD_ID_SERVER_MAIN = 0x0,
		PHYSICS_WORLD_ID_SERVER_DETAIL = 0x1,
		PHYSICS_WORLD_ID_SERVER_LAST = 0x1,
		PHYSICS_WORLD_ID_CLIENT_FIRST = 0x2,
		PHYSICS_WORLD_ID_CLIENT0_FIRST = 0x2,
		PHYSICS_WORLD_ID_CLIENT0_PREDICTIVE = 0x2,
		PHYSICS_WORLD_ID_CLIENT0_AUTHORITATIVE = 0x3,
		PHYSICS_WORLD_ID_CLIENT0_DETAIL = 0x4,
		PHYSICS_WORLD_ID_CLIENT0_LAST = 0x4,
		PHYSICS_WORLD_ID_CLIENT1_FIRST = 0x5,
		PHYSICS_WORLD_ID_CLIENT1_PREDICTIVE = 0x5,
		PHYSICS_WORLD_ID_CLIENT1_AUTHORITATIVE = 0x6,
		PHYSICS_WORLD_ID_CLIENT1_DETAIL = 0x7,
		PHYSICS_WORLD_ID_CLIENT1_LAST = 0x7,
		PHYSICS_WORLD_ID_CLIENT_LAST = 0x7,
		PHYSICS_WORLD_ID_LAST = 0x7,
		PHYSICS_WORLD_ID_COUNT = 0x8,
	};

	enum TraceHitType : __int32
	{
		TRACE_HITTYPE_BEGIN = 0x0,
		TRACE_HITTYPE_NONE = 0x0,
		TRACE_HITTYPE_ENTITY = 0x1,
		TRACE_HITTYPE_DYNENT_MODEL = 0x2,
		TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
		TRACE_HITTYPE_GLASS = 0x4,
		TRACE_HITTYPE_SCRIPTABLE = 0x5,
		TRACE_HITTYPE_CLIENT_MODEL = 0x6,
		TRACE_HITTYPE_END = 0x6,
	};



	/* 1037 */
	enum TraceHitSubType : __int32
	{
		TRACE_HITSUBTYPE_NONE = 0x0,
		TRACE_HITSUBTYPE_COVERWALL = 0x1,
	};

	/* 962 */

	/* 21856 */
	struct TraceSubTypeData_CoverWall
	{
		unsigned __int16 id;
	};

	/* 21857 */
	union TraceHitSubTypeData
	{
		TraceSubTypeData_CoverWall coverWall;
	};

	/* 21858 */
	//struct trace_t
	//{
	//	float fraction;
	//	math::vec3_t position;
	//	math::vec3_t normal;
	//	int surfaceFlags;
	//	int contents;
	//	TraceHitType hitType;
	//	TraceHitSubType hitSubType;
	//	unsigned int hitId;
	//	float fractionForHitType;
	//	unsigned __int16 modelIndex;
	//	const char* partName;
	//	unsigned __int16 partGroup;
	//	TraceHitSubTypeData subTypeData;
	//	bool allsolid;
	//	bool startsolid;
	//	bool walkable;
	//	bool getPenetration;
	//	bool removePitchAndRollRotations;
	//	float closestPointsPenetration;
	//	char surfaceIndex;
	//};


	// struct BulletTraceResults
	//{
	//	trace_t trace;
	//	entity_t* hitEnt;
	//	math::vec3_t hitPos;
	//	bool ignoreHitEnt;
	//	int depthSurfaceType;
	//	int hitClientNum;
	//};

	struct trace_t
	{
		float fraction;
		math::vec3_t position;
		math::vec3_t normal;
		int surfaceFlags;
		int contents;
		TraceHitType hitType;
		TraceHitSubType hitSubType;
		unsigned int hitId;
		float fractionForHitType;
		unsigned __int16 modelIndex;
		uint32_t partName;
		unsigned __int16 partGroup;
		TraceHitSubTypeData subTypeData;
		bool allsolid;
		bool startsolid;
		bool walkable;
		bool getPenetration;
		bool removePitchAndRollRotations;
		float closestPointsPenetration;
		char surfaceIndex;
		const char* debugHitName;
	};

	/* 42378 */
	struct BulletTraceResults
	{
		trace_t trace;
		entity_t* hitEnt;
		math::vec3_t hitPos;
		bool ignoreHitEnt;
		int depthSurfaceType;
		int hitClientNum;
	};
	static_assert (sizeof(BulletTraceResults) == 0x78, "BulletTraceResults size is not correct");


	struct BulletFireParams
	{
		int weaponEntIndex;
		int ignoreHitEntityQueue[22];
		int ignoreHitEntCount;
		float rangeScale;
		float damageMultiplier;
		float penetrationMultiplier;
		float chargedDamageMultiplier;
		int methodOfDeath;
		math::vec3_t initialPos;
		math::vec3_t pad;
		math::vec3_t start;
		math::vec3_t end;
		math::vec3_t dir;
		float travelDistance;
		unsigned int shotCount;
		int ballisticsTickStartTime;
		int ballisticsTickEndTime;
		bool isBallistics;
		bool NOTfirstImpactOccurred;
		char pad1[10];
		float unk1;
		bool pad2;
		bool firstImpactOccurred;
		bool unk2;
		char pad3[3];
		bool unk3;
		bool unk4;
		bool unk5;
		char pad4[100];
	};
	/*inline void fgssfg()
	{
		sizeof(BulletTraceResults);
	}*/

}
