#pragma once
#include"../shared/shared.hpp"

using namespace shared;
#include <windows.h>
#include<atlcomcli.h>
#include<vector>
#include<winnt.h>
#include"Imgui/imgui.h"
#include"Imgui/imgui_internal.h"
#include"Imgui/imgui_impl_win32.h"
#include"Imgui/imgui_impl_dx12.h"
#include"minhook/MinHook.h"
#include <d3d12.h>
#pragma comment(lib, "d3d12.lib")
#include <dxgi1_4.h>
#include<mutex>
#include <random>


#include"game_struct.h"
#include"d3d.h"
#include "Menu.h"
#include"Start.h"

#include "utility.h"
#include"LazyImporter.h"
#include "Start.h"
#include"mem.h"
#include "GameFunction.h"
#include"spoof.h"
#include "sdk.h"
#include "entities.h"
#include "Client.h"
#include"ModernWarfare3.h"
#include"CLActiveClient.h"
#include"Settings.h"
#include "esp.h"
#include "custom_imgui.h"
#include"Timer.h"
#include "SpinAnti.h"
#include "Aimbot.h"
#include"Hook.h"
#include "input_controls.h"
#include "custom_shared.h"
#include"soundeffect.h"
#include "fifo_map.h"


using nlohmann::fifo_map;
typedef std::chrono::high_resolution_clock Clock;
#define AngleToShort(a) ((int)((a)*(65536/360.0f))&65535)
#define ShortToAngle(a) ((float)((a)*(360.0f/65536)))
#define AngleNormalize(a) (ShortToAngle(AngleToShort((a))))
#define ClampChar(i) ((i) < -128 ? -128 : ((i) > 127 ? 127 : (i)))
#define RadiansToDegrees(a) ((a)*(180.0f/(float)M_PI))
#define DegreesToRadians(a) ((a)*((float)M_PI/180.0f))


#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))


inline HMODULE DLLModule{};

inline float normalizeAngle360(float angle) {
	while (angle < 0) {
		angle += 360;
	}
	while (angle >= 360) {
		angle -= 360;
	}
	return angle;
}
