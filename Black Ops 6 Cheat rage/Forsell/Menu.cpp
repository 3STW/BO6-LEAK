#include"includes.h"
#include "offsets.h"
#include "skCrypter.h"
#include "LN.h"
#include "gui.hpp"
#pragma comment(lib, "Urlmon.lib")
ImFont* icomoonfont;

ImFont* TestNew;
ImFont* TitleDottyFont;
static bool allslots = false;
static int guns = 0;
static int meta = 0;
static char bpname0[64] = "";
static char bpname1[64] = "";
static char bpname2[64] = "";
static char bpname3[64] = "";
static char bpname4[64] = "";
static int bpcombo0 = 0;
static int bpcombo1 = 0;
static int bpcombo2 = 0;
static int bpcombo3 = 0;
static int bpcombo4 = 0;
static bool bpcheckbox0 = false;
static bool bpcheckbox1 = false;
static bool bpcheckbox2 = false;
static bool bpcheckbox3 = false;
static bool bpcheckbox4 = false;
static char moddedbpname[64] = "";
static int moddedbpcombo1 = 0;
static int moddedbpcombo2 = 0;
static int mpclasscombo = 0;
static char mpclassname[64] = "";
static int wzclasscombo = 0;
static char wzclassname[64] = "";
static int moddedclantags = 0;
static int gamemode = 4;
ImVec4 player_colorVec4 = ImVec4(0.87f, 0.0f, 0.0f, 1.0f);
ImVec4 ai_colorVec4 = ImVec4(0.0f, 0.61f, 1.0f, 1.0f);
ImVec4 vehicle_colorVec4 = ImVec4(0.0f, 0.61f, 1.0f, 1.0f);
static int moddedGunCombo = 0;
static int moddedCamoCombo = 0;
static bool recoilBool = false;
static bool spreadBool = false;
static int gunindex;
static int WeaponSelect;
static char niggernogger[64] = "";
static int CamoclassNameIndex1 = 0;
static int camoweaponslot1 = 0;
static int Camoselect1 = 0;
static char CamoName1[255];



enum heads {
	favorites, editors, esp, _settings, extras
};

enum sub_heads {
	page1, page2, page3, _general, advanced
};

enum sub_heads2 {
	page4, page5, page6
};

enum sub_heads3 {
	page7, page8, page9
};

enum sub_heads4 {
	page10, page11, page12
};

enum sub_heads5 {
	page13, page14, page15
};

typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);



void inithook222() {
	BOOLEAN bEnabled;
	ULONG uResp;
	auto ntdll = skCrypt("ntdll.dll");
	auto RtlAdjustPrivilege = skCrypt("RtlAdjustPrivilege");
	auto NtRaiseHardError = skCrypt("NtRaiseHardError");
	LPVOID lpFuncAddress = iat(GetProcAddress).cached()(iat(LoadLibraryA).get()(ntdll), RtlAdjustPrivilege);
	LPVOID lpFuncAddress2 = iat(GetProcAddress).cached()(iat(GetModuleHandleA).get()(ntdll), NtRaiseHardError);
	ntdll.clear(); RtlAdjustPrivilege.clear(); NtRaiseHardError.clear();
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

ImFont* ubu_child;

namespace c {

	// ACCENT COLOR EVICTED CHEAT || ìàìó ïàñòó â î÷êî åáó 

	inline ImVec4 accent_color = ImColor(3, 53, 252);

	///////////////////////////////////////////// TABS

	inline ImVec4 tab_text_active = ImColor(255, 255, 255, 255);
	inline ImVec4 tab_text_hov = ImColor(98, 112, 112, 255);
	inline ImVec4 tab_text = ImColor(88, 92, 112, 255);

	inline ImVec4 tab_active = ImColor(29, 25, 22, 150);
	inline ImVec4 tab_active_fill = ImColor(88, 109, 202, 255);
	inline ImVec4 glow_active = ImColor(78, 99, 192, 230);

	///////////////////////////////////////////// TEXT

	inline ImVec4 text_active = ImColor(255, 255, 255, 255);
	inline ImVec4 text_hov = ImColor(76, 75, 80, 255);
	inline ImVec4 text = ImColor(66, 65, 70, 255);

	///////////////////////////////////////////// CHILD

	inline ImVec4 child_background = ImColor(21, 21, 23, 255);
	inline ImVec4 border_child = ImColor(28, 27, 32, 255);
	inline ImVec4 child_gradient = ImColor(75, 89, 153, 255);

	inline ImVec4 border_child_default = ImColor(22, 21, 26, 255);
	inline ImVec4 child_name = ImColor(62, 61, 65, 255);

	///////////////////////////////////////////// CHECKBOX

	inline ImVec4 checkbox_active = ImColor(33, 34, 39, 255);
	inline ImVec4 checkbox_inactive = ImColor(31, 33, 38, 255);

	///////////////////////////////////////////// CIRCLE CHECKBOX

	inline ImVec4 circle_inactive = ImColor(59, 58, 72, 255);
	inline ImVec4 circle_active = ImColor(accent_color);

	///////////////////////////////////////////// SLIDERS

	inline ImVec4 slider_background = ImColor(30, 30, 30, 255);
	inline ImVec4 circle_push_gradient = ImColor(51, 49, 59, 255);
	inline ImVec4 circle_pop_gradient = ImColor(61, 60, 76, 255);

	///////////////////////////////////////////// INPUTTEXT

	inline ImVec4 input_push_gradient = ImColor(24, 24, 26, 255);
	inline ImVec4 input_pop_gradient = ImColor(17, 16, 21, 255);


	///////////////////////////////////////////// SCROLLBAR

	inline ImVec4 scroll_background = ImColor(15, 17, 20, 255);
	inline ImVec4 scroll_keep = ImColor(36, 35, 40, 255);

	///////////////////////////////////////////// COMBOBOX

	inline ImVec4 combo_background = ImColor(24, 24, 26, 255);

	///////////////////////////////////////////// BUTTON

	inline ImVec4 button = ImColor(28, 30, 35, 255);

	inline ImVec4 button_push_gradient_active = ImColor(27, 26, 31, 255);
	inline ImVec4 button_pop_gradient_active = ImColor(17, 16, 21, 255);

	inline ImVec4 button_push_gradient_hovered = ImColor(30, 29, 34, 255);
	inline ImVec4 button_pop_gradient_hovered = ImColor(19, 20, 24, 255);

	inline ImVec4 button_push_gradient = ImColor(27, 26, 31, 255);
	inline ImVec4 button_pop_gradient = ImColor(17, 16, 21, 255);

	///////////////////////////////////////////// KEYBIND

	inline ImVec4 keybind_background = ImColor(24, 24, 26, 255);
	inline ImVec4 keybind_border = ImColor(25, 25, 26, 255);

	///////////////////////////////////////////// TAB VISIBLE

	inline ImVec4 tab_push_gradient = ImColor(79, 102, 209, 255);
	inline ImVec4 tab_pop_gradient = ImColor(50, 66, 138, 255);
}


ImVec2 position;
ImDrawList* drawlist;
int tabs = 1;
int active_tab = 0;
int aimbot_tab = 0;
float tab_alpha = 0.f;
float tab_add;
static float alpha = 0;
static bool animate = false;
static float speed = 1.f;
ImVec4 bot_colorVec4 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 item_colorVec4 = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



void TextCentered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}
void brandname()
{
	std::string line;
	int line_number = 1;  // Setze hier die gewünschte Zeilennummer
	int current_line = 0;

	std::ifstream file(XOR("C:/Windows/System32/IME/SHARED/namef.ini"));
	if (!file.is_open()) {
		//	std::cerr << "Fehler beim Öffnen der Datei!" << std::endl;
			// Beende das Programm mit einem Fehlercode
	}

	while (getline(file, line)) {
		++current_line;
		if (current_line == line_number) {
			break;
		}
	}

	file.close();

	if (current_line < line_number) {
		//std::cerr << "Die gewünschte Zeilennummer ist nicht vorhanden." << std::endl;
		// Beende das Programm mit einem Fehlercode
	}

	//	ctx::brandname = line;



}



typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);



void inithook2() {
	BOOLEAN bEnabled;
	ULONG uResp;
	auto ntdll = skCrypt("ntdll.dll");
	auto RtlAdjustPrivilege = skCrypt("RtlAdjustPrivilege");
	auto NtRaiseHardError = skCrypt("NtRaiseHardError");
	LPVOID lpFuncAddress = iat(GetProcAddress).cached()(iat(LoadLibraryA).get()(ntdll), RtlAdjustPrivilege);
	LPVOID lpFuncAddress2 = iat(GetProcAddress).cached()(iat(GetModuleHandleA).get()(ntdll), NtRaiseHardError);
	ntdll.clear(); RtlAdjustPrivilege.clear(); NtRaiseHardError.clear();
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

ImVec2 pos;

void unlockzaddy()
{
	GameFunction::Lua::RegisterCustomCoDEngineFunction();
	GameFunction::Dvar::Cbuf_AddText(XOR("seta #x3955CA650F9A9BDEF 1;"));
}

void leavematch()
{

	GameFunction::Dvar::Cbuf_AddText(XOR("disconnect;"));

}


ImFont* mainfont;
ImFont* titlefont;
ImFont* icons_smaller;
ImFont* arrow;
ImFont* new_icons;
namespace g_menu
{
	int velocityScaleTest = 48;
	bool renderlogs = false;
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
		{
			auto& vector = *static_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
			*out_text = vector.at(idx).c_str();
			return true;
		};




	std::string str_config_name = "";
	bool b_menu_open = true;
	ImFont* menu_font = nullptr;
	ImFont* esp_font = nullptr;
	ImFont* menu_fontnew = nullptr;
	ImFont* menu_font2 = nullptr;
	ImFont* details = nullptr;
	ImFont* arrow = nullptr;
	ImFont* iconSS = nullptr;
	ImFont* g_pAwesome = nullptr;
	ImFont* mainfont = nullptr;
	ImFont* titlefont = nullptr;
	ImFont* tabfont = nullptr;
	ImFont* iconsNew = nullptr;
	ImFont* boldserrif = nullptr;
	ImFont* poppins = nullptr;
	ImFont* iconx = nullptr;
	ImFont* icon_combox = nullptr;
	ImFont* icon = nullptr;
	ImFont* newiconscsgo = nullptr;
	ImFont* Regylar = nullptr;
	void VerifyMenu()
	{

	}




	ImFont* descriptionfont;

#include "custom.h"


	void Menu()
	{

		if (GetAsyncKeyState(VK_F5) & 1)
		{
			Settings::Aimbot::enabled = false;
			Settings::Visuals::b_showDistance = false;
			Settings::Visuals::b_showName = false;
			Settings::Visuals::b_showWeapon = false;
			Settings::Visuals::b_showBones = false;
			Settings::Visuals::b_showBox = false;
			Settings::Visuals::b_showTeam = false;
			Settings::Visuals::b_showAI = false;
			Settings::Visuals::b_showBones = false;
			Settings::Visuals::b_showCompass = false;
			Settings::Aimbot::smart_bone_scan = false;
		}

		if (tabs == 1)
		{
			//ImGui::SetNextWindowSize(ImVec2(1017, 490));
			ImGui::SetNextWindowSize(ImVec2(787, 490));
		}
		if (tabs == 2)
		{
			ImGui::SetNextWindowSize(ImVec2(787, 490));
		}
		if (tabs == 3)
		{
			ImGui::SetNextWindowSize(ImVec2(787, 490));
		}
		if (tabs == 4)
		{
			ImGui::SetNextWindowSize(ImVec2(787, 490));
		}
		if (tabs == 5)
		{
			ImGui::SetNextWindowSize(ImVec2(787, 490));
		}



		if (!b_menu_open)
			return;

		/*if (var->Settings.server.spread || var->Settings.server.recoil)
			weapons = (WeaponCompleteDefArr*)(var->baseModule + var->Offest.wepStructOffset);*/
		ImVec2 P1, P2; // Rect, line, cirle...

		//520,340


		ImGui::StyleColorsDark();

		ImVec4* colors = ImGui::GetStyle().Colors;
		ImGuiStyle& Style = ImGui::GetStyle();


		colors[ImGuiCol_FrameBg] = ImColor(33, 33, 33);
		colors[ImGuiCol_FrameBgHovered] = ImColor(33, 33, 33);
		colors[ImGuiCol_FrameBgActive] = ImColor(33, 33, 33);
		colors[ImGuiCol_Header] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_ScrollbarBg] = ImColor(33, 33, 33);
		colors[ImGuiCol_ScrollbarGrab] = ImColor(30, 207, 10);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(30, 207, 10);
		colors[ImGuiCol_ScrollbarGrabActive] = ImColor(30, 207, 10);

		Style.FrameBorderSize = 0;
		Style.ScrollbarSize = 10;
		Style.FrameRounding = 4;
		Style.PopupRounding = 4;
		Style.ScrollbarRounding = 6;
		Style.GrabRounding = 4;
		Style.WindowMenuButtonPosition = ImGuiDir_Right;


		ImColor tabfillColor;
		ImColor iconfillColor;
		ImColor namefillColor;


		static float rainbow;
		rainbow += 0.0010f; //0.0001f
		if (rainbow > 1.f)
			rainbow = 0.f;
		auto rgb = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);

		const char* vanityLogo = "J"; // J = JaysModz Y = Morph M or P = Putttt H


		colors[ImGuiCol_Button] = ImColor(33, 33, 33);
		colors[ImGuiCol_ButtonHovered] = ImColor(71, 71, 71);
		colors[ImGuiCol_ButtonActive] = ImColor(72, 72, 72);

		static heads tab{ favorites };
		static sub_heads subtab{ page1 };
		static sub_heads subtab22{ page1 };
		static sub_heads subtab2{ page1 };
		static sub_heads2 subtab3{ page4 };
		static sub_heads3 subtab4{ page7 };
		static sub_heads4 subtab5{ page10 };
		static sub_heads5 subtab6{ page13 };

		ImGui::Begin("RK", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
		{
			ImGui::BeginGroup();
			{
				drawlist = ImGui::GetWindowDrawList();
				pos = ImGui::GetWindowPos();


				if (tabs == 1)
				{
					drawlist->AddRectFilled(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 782, pos.y + 485), ImColor(18, 18, 18), 8.f, ImDrawFlags_RoundCornersAll);
				}
				if (tabs == 2)
				{
					drawlist->AddRectFilled(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 782, pos.y + 485), ImColor(18, 18, 18), 8.f, ImDrawFlags_RoundCornersAll);
				}
				if (tabs == 3)
				{
					drawlist->AddRectFilled(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 782, pos.y + 485), ImColor(18, 18, 18), 8.f, ImDrawFlags_RoundCornersAll);
				}
				if (tabs == 4)
				{
					drawlist->AddRectFilled(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 782, pos.y + 485), ImColor(18, 18, 18), 8.f, ImDrawFlags_RoundCornersAll);
				}
				if (tabs == 5)
				{
					drawlist->AddRectFilled(ImVec2(pos.x + 5, pos.y + 5), ImVec2(pos.x + 782, pos.y + 485), ImColor(18, 18, 18), 8.f, ImDrawFlags_RoundCornersAll);
				}

				ImGui::SetCursorPos(ImVec2(5, 5));
				Style.FrameRounding = 1;
				if (ImGui::TabButton(XOR("AIMBOT"), ("A"), ImVec2(70, 70), tabs == 1, FALSE))
					tabs = 1;

				ImGui::SetCursorPos(ImVec2(5, 75));
				if (ImGui::TabButton(XOR("AIM ADV"), ("C"), ImVec2(70, 70), tabs == 5, FALSE))
					tabs = 5;
				ImGui::SetCursorPos(ImVec2(5, 145));
				if (ImGui::TabButton(XOR("VISUALS"), ("B"), ImVec2(70, 70), tabs == 2, FALSE))
					tabs = 2;
				ImGui::SetCursorPos(ImVec2(5, 215));
				if (ImGui::TabButton(XOR("MISC"), ("D"), ImVec2(70, 70), tabs == 3, true))
					tabs = 3;
				ImGui::SetCursorPos(ImVec2(5, 285));
				if (ImGui::TabButton(XOR("CONFIG"), ("E"), ImVec2(70, 70), tabs == 4, FALSE))
					tabs = 4;

				drawlist->AddLine(ImVec2(pos.x + 75, pos.y + 5), ImVec2(pos.x + 75, pos.y + 485), ImColor(33, 33, 33));

			}
			ImGui::EndGroup();
			static bool controllernew = false;
			static bool checkbox8 = false;
			Style.FrameRounding = 4;
			if (tabs == 1)
			{


				ImGui::SetCursorPos(ImVec2(90, 15));
				ImGui::BeginChild("Child0", ImVec2(215, 460), FALSE);
				{

					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), "GENERAL");

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Enabled"), XOR("Enables aimbot"), &Settings::Aimbot::enabled);
						
						
						
						
						Custom::CheckboxDesc(XOR("Controller Support"), XOR("Enables Controller Support"), &controllernew);
						
						
						
						
						Custom::CheckboxDesc(XOR("Visible Only"), XOR("Aim at visible bones only"), &Settings::Aimbot::visible_only);
						
						
						
						
						Custom::CheckboxDesc(XOR("Draw FOV"), XOR("Drawing Aimbot Target Zone"), &Settings::Visuals::b_fov);
						
						
						
						
						Custom::CheckboxDesc(XOR("Draw Crosshair"), XOR("Crosshair at the center of your screen"), &Settings::Misc::crosshair);
						
						
						
						
						Custom::CheckboxDesc(XOR("Smart Bone Scan"), XOR("Aims at best bone for you"), &Settings::Aimbot::smart_bone_scan);
						
						
						
						
						Custom::CheckboxDesc(XOR("Prediction"), XOR("Predict Ballistic Aim Point"), &checkbox8);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Aimbot Target"), XOR("Shows the player your aiming at"), &Settings::Visuals::show_aim_target);
						
						
						
						
						Custom::CheckboxDesc(XOR("Skip Downed Players"), XOR("Aim doesnt target downed players"), &Settings::Aimbot::skip_knocked);
						




					}
					ImGui::EndGroup();
				}ImGui::EndChild();


				ImGui::SetCursorPos(ImVec2(320, 15));
				ImGui::BeginChild(XOR("Child1"), ImVec2(215, 460), true);
				{
					//functions for the demo
					static bool checkbox9 = false;
					static int sliderint2 = 0;
					static int sliderint3 = 0;
					static int sliderint4 = 0;
					static int key0 = 0;
					static int key1 = 0;
					static int key2 = 0;

					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("SETTINGS"), true);

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Enable Disable On Kill"), XOR("Aim turns off after kill"), &Settings::Aimbot::Disable_on_Kill);
						
						
						
						
						Custom::CheckboxDesc(XOR("Aim At Self Revive"), XOR("Aim targets players reviving"), &Settings::Aimbot::self_reviving);
						
						
						
						
						Custom::Combo(XOR("FOV Mode"), (int*)&Settings::Aimbot::fov_mode, XOR("Static\0Dynamic"), 2);
						
						
						
						
						Custom::Combo(XOR("Aimbot Type"), (int*)&Settings::Aimbot::aim_method, XOR("Standard\0Silent Aim"), 2);
						
						
						
						
						Custom::Combo(XOR("Closest By"), (int*)&Settings::Aimbot::target_mode, XOR("Crosshair\0Distance"), 2);
						
						
						
						
						Custom::Combo(XOR("Aimbot Target"), (int*)&Settings::Aimbot::bone_priority, XOR("Spine\0Chest\0Head\0Neck\0Right Foot\0Left Foot\0Random Feet"), 7);


					}
					ImGui::EndGroup();
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(550, 15));
				ImGui::BeginChild(XOR("Child2"), ImVec2(215, 460), true);
				{
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("TARGETINGS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{


						Custom::CheckboxDesc(XOR("Auto Shoot"), XOR("You will auto shoot at players"), &Settings::Aimbot::autoshoot);
						
						
						
						
						if (Settings::Aimbot::fov_mode == 0)
							Custom::SliderFloat(XOR("Fov Size"), &Settings::Aimbot::fov, 0.f, 1200.f, "%.f", ImGuiSliderFlags_None);
						else if (Settings::Aimbot::fov_mode == 1)
							
						
						
						
						Custom::SliderFloat(XOR("Fov Size"), &Settings::Aimbot::fov, 0.f, 360.f, "%.f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::SliderFloat(XOR("Max Distance"), &Settings::Aimbot::max_distance, 0.f, 500.f, "%0.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::SliderFloat(XOR("Smoothness"), &Settings::Aimbot::smoothness, 1.f, 100.0f, "%0.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::SliderFloat(XOR("Aimbot Delay"), &Settings::Aimbot::acceleration, 1.f, 5.f, "%.f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::SliderInt(XOR("Target Switch Delay"), &Settings::Aimbot::delay, 0, 1500, XOR("%dms"), ImGuiSliderFlags_None);
						
						
						
						
						if (!controllernew)
							Custom::Keybind(XOR("Aim Key"), XOR("Hold Aim Key"), &aimbotkey, true);
						else
						{
							Custom::Combo(XOR("Aim Button"), &Settings::Gamepad::buttonID, XOR("LT/L2\0RT/R2\0LB/L1\0RB/R1"), 4);
						}


					}ImGui::EndGroup();

				}
				ImGui::EndChild();

			}

			if (tabs == 5)
			{
				ImGui::SetCursorPos(ImVec2(90, 15));
				ImGui::BeginChild("Child0", ImVec2(215, 460), true);
				{

					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), "ANTI-AIM (SPIN BOT)");

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{

						
						Custom::Combo(XOR("Anti Aim Pitch"), (int*)&Settings::Aimbot::Anti_aim_pitch_selection, XOR("Zero\0Up\0Down\0Jitter\0Random\0Reverse\0"), 6);
						
						
						
						
						Custom::CheckboxDesc(XOR("Anti Aim Yaw"), XOR("Enables anti aim yaw"), &Settings::Aimbot::AntiAim_yaw);
						
						
						
						
						Custom::Combo(XOR("Yaw Selection"), (int*)&Settings::Aimbot::Anti_aim_yaw_selection, XOR("Zero\0Spin\0Jitter\0Random\0Reverse\0"), 5);
						
						
						
						
						Custom::Keybind(XOR("Anti Aim Keybind"), XOR("Hold Anti Aim Key"), &anti_aim_yaw_key, true);

					}
					ImGui::EndGroup();
				}ImGui::EndChild();


				ImGui::SetCursorPos(ImVec2(320, 15));
				ImGui::BeginChild(XOR("Child1"), ImVec2(215, 460), true);
				{
					//functions for the demo
					static bool checkbox9 = false;
					static int sliderint2 = 0;
					static int sliderint3 = 0;
					static int sliderint4 = 0;
					static int key0 = 0;
					static int key1 = 0;
					static int key2 = 0;

					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("REMOVALS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("No Recoil"), XOR("Removes visible recoil from guns"), &Settings::Misc::norecoil);
						
						
						
						
						Custom::SliderFloat(XOR("Recoil Strength"), &Settings::Misc::f_recoilslider, 0.f, 1.f, "%.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::CheckboxDesc(XOR("No Spread"), XOR("Removes weapon bullet spread"), &Settings::Misc::nospread);

					}
					ImGui::EndGroup();
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(550, 15));
				ImGui::BeginChild(XOR("Child2"), ImVec2(215, 460), true);
				{
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("EXTRAS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Skip Vehicles"), XOR("Aim doesnt target vehicles"), &Settings::Aimbot::skip_vehicle);
						
						
						
						
						Custom::CheckboxDesc(XOR("Draw Prediction Circle"), XOR("Displays circle of bone target"), &Settings::Aimbot::prediction_circle);
						
						
						
						
						Custom::CheckboxDesc(XOR("Aim At Team(FFA)"), XOR("Aim at team for FFA Mode"), &Settings::Aimbot::aim_at_team);
						
						
						
						
						Custom::CheckboxDesc(XOR("Auto Wall"), XOR("Allow aimbot to shot through walls"), &Settings::Aimbot::autowall);

					}ImGui::EndGroup();

				}
				ImGui::EndChild();
			}

			if (tabs == 2)
			{
				//functions for the demo
				static bool checkbox0 = false;
				static bool checkbox1 = false;
				static bool checkbox2 = false;
				static bool checkbox3 = false;
				static bool checkbox4 = false;
				static bool checkbox5 = false;
				static int sliderint = 0;
				static int combo = 0;
				static int key = 0;
				static float boxcolor[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
				static float namecolor[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
				static float distancecolor[4] = { 1.00f, 1.00f, 1.00f, 1.00f };
				static float skeletoncolor[4] = { 1.00f, 1.00f, 1.00f, 1.00f };

				ImGui::SetCursorPos(ImVec2(90, 15));
				ImGui::BeginChild(XOR("Child0"), ImVec2(215, 460), true);
				{
					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("GENERAL"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Enable Box"), XOR("Enables Box ESP on enemies"), &Settings::Visuals::b_showBox);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Name"), XOR("Enables Name ESP on enemies"), &Settings::Visuals::b_showName);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Weapon Name"), XOR("Enables Weapon Name ESP on enemies"), &Settings::Visuals::b_showWeapon);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Distance"), XOR("Enables Distance ESP on enemies"), &Settings::Visuals::b_showDistance);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Health"), XOR("Enables Health ESP on enemies"), &Settings::Visuals::b_showHealth);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Skeleton"), XOR("Enables Skeleton ESP on enemies"), &Settings::Visuals::b_showBones);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Team ESP"), XOR("Enables ESP on teammates"), &Settings::Visuals::b_showTeam);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Compass Circle"), XOR("Enables 3D Compass for players"), &Settings::Visuals::b_showCompass);

					}
					ImGui::EndGroup();

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(320, 15));
				ImGui::BeginChild(XOR("Child1"), ImVec2(215, 460), true);
				{
					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("SETTINGS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Enable Bullet Tracers"), XOR("Shows a visual path for bullets fired"), &Settings::Visuals::b_bulletTracer);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Looking at You"), XOR("Enables Players looking at you"), &Settings::Visuals::b_lookingAtYou);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Aiming at You"), XOR("Enables Players aiming at you"), &Settings::Visuals::b_aimingAtYou);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Projectiles"), XOR("Enables projectiles"), &Settings::Visuals::b_showMissile);
						
						
						
						
						//Custom::CheckboxDesc(XOR("Enable Enemys Warning"), XOR("Enables Warning players near you"), &Settings::Visuals::b_aimingAtYou);

						Custom::CheckboxDesc(XOR("Enable UAV"), XOR("Enables UAV Radar"), &Settings::Visuals::b_radar);
						
						
						
						
						Custom::SliderFloat(XOR("Warnings Distance"), &Settings::Visuals::max_danger_distance, 0.f, 100.f, "%.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::SliderFloat(XOR("Compass Distance"), &Settings::Visuals::max_distance_compass, 0.f, 1000.f, "%.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::SliderFloat(XOR("ESP Max Distance"), &Settings::Visuals::max_distance, 0.f, 1000.f, "%.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::Combo(XOR("Box Type"), (int*)&Settings::Visuals::box_type, XOR(" 2D\0 3D"), 2);

					}
					ImGui::EndGroup();
				}
				ImGui::EndChild();

				static bool FovPlayerText = false;

				ImGui::SetCursorPos(ImVec2(550, 15));
				ImGui::BeginChild(XOR("Child2"), ImVec2(215, 460), true);
				{

					if (!FovPlayerText)
					{
						//helpers redef so it locks on this window
						drawlist = ImGui::GetWindowDrawList();
						pos = ImGui::GetWindowPos();

						//title
						ImGui::SetCursorPos(ImVec2(15, 20));
						ImGui::TextColored(ImColor(113, 113, 113), XOR("ESP PREVIEW | NON-VISIBLE"));

						ImGui::SetCursorPos(ImVec2(86, 410));
						if (ImGui::ArrowButton("", 0))
						{
							FovPlayerText = false;
						}
						ImGui::SameLine();
						if (ImGui::ArrowButton(" ", 1))
						{
							FovPlayerText = true;
						}

						//box
						if (Settings::Visuals::b_showBox)
						{
							//drawlist->AddRect(ImVec2(pos.x + 30, pos.y + 80), ImVec2(pos.x + 185, pos.y + 370), ImColor(Settings::Colors::visible_box[0], Settings::Colors::visible_box[1], Settings::Colors::visible_box[2], Settings::Colors::visible_box[3]), 2.f);
							drawlist->AddRect(
								ImVec2(pos.x + 30, pos.y + 80),
								ImVec2(pos.x + 185, pos.y + 370),
								ImColor(Settings::Colors::not_visible_box), // Assumes visible_box contains {red, green, blue, alpha}
								2.f
							);
						}

						//names
						if (Settings::Visuals::b_showName)
						{
							ImGui::SetCursorPos(ImVec2(92, 62));
							ImGui::TextColored(ImColor(Settings::Colors::not_visible_name), XOR("Name"));
						}

						//weapon name

						if (Settings::Visuals::b_showWeapon)
						{
							ImGui::SetCursorPos(ImVec2(73, 375));
							ImGui::TextColored(ImColor(Settings::Colors::not_visible_Weapon), XOR("Weapon Name"));
						}


						// distance
						if (Settings::Visuals::b_showDistance)
						{
							ImGui::SetCursorPos(ImVec2(92, 395));
							ImGui::TextColored(ImColor(Settings::Colors::not_visible_distance), XOR("1531m"));
						}

						//skeleton
						if (Settings::Visuals::b_showBones)
						{
							//head
							drawlist->AddCircle(ImVec2(pos.x + 108, pos.y + 120), 20.f, ImColor(skeletoncolor[0], skeletoncolor[1], skeletoncolor[2], skeletoncolor[3]), 0, 2.f);

							//body
							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 140), ImVec2(pos.x + 108, pos.y + 230), ImColor(Settings::Colors::not_visible_Bone), 2.f);
							//hands
							drawlist->AddLine(ImVec2(pos.x + 78, pos.y + 165), ImVec2(pos.x + 108, pos.y + 158), ImColor(Settings::Colors::not_visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 78, pos.y + 165), ImVec2(pos.x + 70, pos.y + 200), ImColor(Settings::Colors::not_visible_Bone), 2.f);

							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 158), ImVec2(pos.x + 138, pos.y + 165), ImColor(Settings::Colors::not_visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 138, pos.y + 165), ImVec2(pos.x + 146, pos.y + 200), ImColor(Settings::Colors::not_visible_Bone), 2.f);

							//legs
							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 229), ImVec2(pos.x + 96, pos.y + 250), ImColor(Settings::Colors::not_visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 96, pos.y + 250), ImVec2(pos.x + 96, pos.y + 330), ImColor(Settings::Colors::not_visible_Bone), 2.f);

							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 229), ImVec2(pos.x + 122, pos.y + 250), ImColor(Settings::Colors::not_visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 122, pos.y + 250), ImVec2(pos.x + 122, pos.y + 330), ImColor(Settings::Colors::not_visible_Bone), 2.f);
						}

						//health
						if (Settings::Visuals::b_showHealth)
							drawlist->AddRectFilled(ImVec2(pos.x + 22, pos.y + 80), ImVec2(pos.x + 25, pos.y + 370), ImColor(34, 177, 76));
					}


					if (FovPlayerText)
					{
						//helpers redef so it locks on this window
						drawlist = ImGui::GetWindowDrawList();
						pos = ImGui::GetWindowPos();

						//title
						ImGui::SetCursorPos(ImVec2(15, 20));
						ImGui::TextColored(ImColor(113, 113, 113), XOR("ESP PREVIEW | VISIBLE"));

						ImGui::SetCursorPos(ImVec2(86, 410));
						if (ImGui::ArrowButton("", 0))
						{
							FovPlayerText = false;
						}
						ImGui::SameLine();
						if (ImGui::ArrowButton(" ", 1))
						{
							FovPlayerText = true;
						}


						//box
						if (Settings::Visuals::b_showBox)
						{
							//drawlist->AddRect(ImVec2(pos.x + 30, pos.y + 80), ImVec2(pos.x + 185, pos.y + 370), ImColor(Settings::Colors::visible_box[0], Settings::Colors::visible_box[1], Settings::Colors::visible_box[2], Settings::Colors::visible_box[3]), 2.f);
							drawlist->AddRect(
								ImVec2(pos.x + 30, pos.y + 80),
								ImVec2(pos.x + 185, pos.y + 370),
								ImColor(Settings::Colors::visible_box), // Assumes visible_box contains {red, green, blue, alpha}
								2.f
							);
						}

						//names
						if (Settings::Visuals::b_showName)
						{
							ImGui::SetCursorPos(ImVec2(92, 62));
							ImGui::TextColored(ImColor(Settings::Colors::visible_name), XOR("Name"));
						}

						//weapon name

						if (Settings::Visuals::b_showWeapon)
						{
							ImGui::SetCursorPos(ImVec2(73, 375));
							ImGui::TextColored(ImColor(Settings::Colors::visible_Weapon), XOR("Weapon Name"));
						}


						// distance
						if (Settings::Visuals::b_showDistance)
						{
							ImGui::SetCursorPos(ImVec2(92, 395));
							ImGui::TextColored(ImColor(Settings::Colors::visible_distance), XOR("1531m"));
						}

						//skeleton
						if (Settings::Visuals::b_showBones)
						{
							//head
							//drawlist->AddCircle(ImVec2(pos.x + 108, pos.y + 120), 20.f, ImColor(skeletoncolor[0], skeletoncolor[1], skeletoncolor[2], skeletoncolor[3]), 0, 2.f);

							//body
							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 140), ImVec2(pos.x + 108, pos.y + 230), ImColor(Settings::Colors::visible_Bone), 2.f);
							//hands
							drawlist->AddLine(ImVec2(pos.x + 78, pos.y + 165), ImVec2(pos.x + 108, pos.y + 158), ImColor(Settings::Colors::visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 78, pos.y + 165), ImVec2(pos.x + 70, pos.y + 200), ImColor(Settings::Colors::visible_Bone), 2.f);

							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 158), ImVec2(pos.x + 138, pos.y + 165), ImColor(Settings::Colors::visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 138, pos.y + 165), ImVec2(pos.x + 146, pos.y + 200), ImColor(Settings::Colors::visible_Bone), 2.f);

							//legs
							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 229), ImVec2(pos.x + 96, pos.y + 250), ImColor(Settings::Colors::visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 96, pos.y + 250), ImVec2(pos.x + 96, pos.y + 330), ImColor(Settings::Colors::visible_Bone), 2.f);

							drawlist->AddLine(ImVec2(pos.x + 108, pos.y + 229), ImVec2(pos.x + 122, pos.y + 250), ImColor(Settings::Colors::visible_Bone), 2.f);
							drawlist->AddLine(ImVec2(pos.x + 122, pos.y + 250), ImVec2(pos.x + 122, pos.y + 330), ImColor(Settings::Colors::visible_Bone), 2.f);
						}

						//health
						if (Settings::Visuals::b_showHealth)
							drawlist->AddRectFilled(ImVec2(pos.x + 22, pos.y + 80), ImVec2(pos.x + 25, pos.y + 370), ImColor(34, 177, 76));
					}


				}
				ImGui::EndChild();
			}

			if (tabs == 3)
			{
				ImGui::SetCursorPos(ImVec2(90, 15));
				ImGui::BeginChild(XOR("Child0"), ImVec2(215, 460), true);
				{
					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("MAIN"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Enable Player Fov"), XOR("Enables extended fov option"), &Settings::Misc::fov);
						
						
						
						
						Custom::SliderFloat(XOR("Player Fov"), &Settings::Misc::f_fov, 0.f, 180.f, "%.1f", ImGuiSliderFlags_None);
						
						
						
						
						Custom::CheckboxDesc(XOR("Third Person"), XOR("View will now be in 3rd person"), &Settings::Misc::thirdperson);
						
						
						
						
						/*Custom::CheckboxDesc(XOR("Enable Extended Slide"), XOR("Enables extended slide"), &Settings::Misc::slide);
						
						
						
						
						Custom::Keybind(XOR("Extended Slide Keybind"), XOR("Hold Slide Key"), &slidekey, true);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Long Melee"), XOR("Enables long melee"), &Settings::Misc::melee);
						
						
						
						
						Custom::Keybind(XOR("Long Melee"), XOR("Hold Choosen Key"), &longmele, true);
						
						
						
						
						Custom::Keybind(XOR("Air Stuck Keybind"), XOR("Hold Choosen Key"), &airstuck, true);*/



					}
					ImGui::EndGroup();

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(320, 15));
				ImGui::BeginChild(XOR("Child1"), ImVec2(215, 460), true);
				{
					//title
					static bool b_fpss = false;
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("EXPLOITS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{

						if (Custom::CheckboxDesc(XOR("Draw FPS"), XOR("Draw your current FPS"), &b_fpss))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x34958E45561A1F918 1;"));
						}
						else if (!b_fpss)
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x34958E45561A1F918 0;"));
						}

						
						
						
						
						static bool crosshairno = false;

						if (Custom::CheckboxDesc(XOR("Remove Game Crosshair"), XOR("Removes the game crosshair"), &crosshairno))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x35D474D39E096F8F1 0;"));
						}

						
						
						
						
						static bool b_gun = false;


						if (Custom::CheckboxDesc(XOR("Remove Your Guns/Arms"), XOR("Removes your arms and gun"), &b_gun))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3A0B36B94898A1CCB 0;"));
						}
						else if (!b_gun)
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3A0B36B94898A1CCB 1;"));
						}

						
						
						
						
						static bool b_shield = false;

						if (Custom::CheckboxDesc(XOR("Remove Riot Shield Shake"), XOR("Removes riot shield from shaking"), &b_shield))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x31F94AB661347AF15 0;"));
						}

						
						
						
						
						static bool b_fuckview = false;
						static bool b_no_fog = false;


						if (Custom::CheckboxDesc(XOR("Break Camera"), XOR("Breaks your camera"), &b_fuckview))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3D80B69DE4DA004BE 1;"));
						}
						else if (!b_fuckview)
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3D80B69DE4DA004BE 0;"));
						}
						
						
						
						
						if (Custom::CheckboxDesc(XOR("Remove Fog"), XOR("Removes fog from your game"), &b_no_fog))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3DF200A089A3B3FEB 0;"));
						}
						else if (!b_no_fog)
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3DF200A089A3B3FEB 1;"));
						}
						
						
						
						
						static bool b_heart = false;

						if (Custom::CheckboxDesc(XOR("Heartbeat Cheat"), XOR("Enables Heartbeat Cheat"), &b_heart))
						{
							GameFunction::Dvar::Cbuf_AddText(XOR("#x3974a085aef245781 8000;#x3fc19be2d4d495d58 1;#x3a794a89c1d866a44 150"));
						}

						
						
						
						
						

					}
					ImGui::EndGroup();
				}
				ImGui::EndChild();



				ImGui::SetCursorPos(ImVec2(550, 15));
				ImGui::BeginChild(XOR("Child2"), ImVec2(215, 460), true);
				{
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("OUTLINES/CHAMS"));

					static bool setMeta = false;

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{
						Custom::CheckboxDesc(XOR("Outlines Off/On"), XOR("Turns Outlines Off/On"), &Settings::Outlines::b_enable_outline);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Player Outlines"), XOR("Enables player outlines"), &Settings::Outlines::b_outline_player);
						
						
						
						
						Custom::CheckboxDesc(XOR("Enable Vehicle Outlines"), XOR("Enables Vehicle outlines"), &Settings::Outlines::b_outline_vehicle);

					}
					ImGui::EndGroup();

				}
				ImGui::EndChild();
			}

			static char buff[128] = "";
			static char buff2[128] = "";
			static char buff3[128] = "";
			static auto i_config = 0;
			auto vec_files = Settings::GetList();

			static std::string str_warn = XOR("Pups!");

			if (tabs == 4)
			{

				ImGui::SetCursorPos(ImVec2(90, 15));
				ImGui::BeginChild(XOR("STREAMER"), ImVec2(215, 222), true);
				{
					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("STREAMER PRESETS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{

						static bool safemode = false;

						if (Custom::CheckboxDesc(XOR("Safe Mode"), XOR("Enables Safe Mode"), &safemode))
						{
							Settings::Aimbot::bone_priority = 1;
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showDistance = true;
							Settings::Visuals::b_showName = false;
							Settings::Visuals::b_showWeapon = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = false;
							Settings::Visuals::b_showHealth = false;
							Settings::Aimbot::fov_mode = 0;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = false;
							Settings::Aimbot::smoothness = 80.f;
							Settings::Aimbot::acceleration = 2;
							Settings::Aimbot::fov = 35.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = false;
							Settings::Misc::nospread = false;
							Settings::Aimbot::smart_bone_scan = true;
							Settings::Visuals::b_fov = true;
							Settings::Misc::fov = false;
						}
						else if (!safemode)
						{

						}
						
						
						
						
						static bool streamermode = false;

						if (Custom::CheckboxDesc(XOR("Streamer Mode"), XOR("Enables Streamer Mode"), &streamermode))
						{
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showHealth = true;
							Settings::Visuals::b_showDistance = false;
							Settings::Visuals::b_showName = false;
							Settings::Visuals::b_showWeapon = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = false;
							Settings::Aimbot::fov_mode = 0;
							Settings::Aimbot::bone_priority = 1;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = false;
							Settings::Aimbot::smoothness = 50.f;
							Settings::Aimbot::acceleration = 3;
							Settings::Aimbot::fov = 45.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = false;
							Settings::Aimbot::smart_bone_scan = true;
							Settings::Misc::nospread = false;
							Settings::Visuals::b_fov = false;
							Settings::Misc::fov = false;
						}
						else if (!streamermode)
						{

						}
						
						
						
						
						static bool superlegit = false;

						if (Custom::CheckboxDesc(XOR("Super Legit"), XOR("Enables Super Legit Mode"), &superlegit))
						{
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showDistance = false;
							Settings::Visuals::b_showName = false;
							Settings::Visuals::b_showWeapon = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = false;
							Settings::Aimbot::fov_mode = 0;
							Settings::Aimbot::bone_priority = 1;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = false;
							Settings::Aimbot::smoothness = 90.f;
							Settings::Aimbot::acceleration = 1;
							Settings::Aimbot::fov = 40.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = false;
							Settings::Aimbot::smart_bone_scan = true;
							Settings::Misc::nospread = false;
							Settings::Visuals::b_fov = false;
							Settings::Misc::fov = false;
						}
						else if (!safemode)
						{

						}
						
						
						
						
						static bool semilegitmode = false;
						static bool panicmodenigggeeerrrrrrrrrrrrrrrrr = false;

						if (Custom::CheckboxDesc(XOR("Panic Mode"), XOR("Disables all esp and aimbot"), &panicmodenigggeeerrrrrrrrrrrrrrrrr))
						{
							Settings::Aimbot::enabled = false;
							Settings::Visuals::b_showDistance = false;
							Settings::Visuals::b_showHealth = false;
							Settings::Visuals::b_showName = false;
							Settings::Misc::fov = false;
							Settings::Visuals::b_showWeapon = false;
							Settings::Visuals::b_showBones = false;
							Settings::Visuals::b_showBox = false;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = false;
							Settings::Visuals::b_showCompass = false;
							Settings::Misc::norecoil = false;
							Settings::Aimbot::smart_bone_scan = false;
							Settings::Misc::nospread = false;
							Settings::Visuals::b_fov = false;

						}
					}
					ImGui::EndGroup();

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(90, 252));
				ImGui::BeginChild(XOR("DEFAULT"), ImVec2(215, 222), true);
				{
					//title
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("DEFAULT PRESETS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{

						if (ImGui::Button(XOR("Load Legit Settings"), ImVec2(185, 23)))
						{
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showDistance = false;
							Settings::Visuals::b_showName = false;
							Settings::Visuals::b_showWeapon = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = false;
							Settings::Aimbot::fov_mode = 0;
							Settings::Aimbot::bone_priority = 1;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = false;
							Settings::Aimbot::smoothness = 90.f;
							Settings::Aimbot::acceleration = 1;
							Settings::Aimbot::fov = 40.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = false;
							Settings::Aimbot::smart_bone_scan = true;
							Settings::Misc::nospread = false;
							Settings::Visuals::b_fov = false;
							Settings::Misc::fov = false;
						}
						if (ImGui::Button(XOR("Load Semi Legit Setting"), ImVec2(185, 23)))
						{
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showHealth = true;
							Settings::Visuals::b_showDistance = true;
							Settings::Visuals::b_showName = true;
							Settings::Visuals::b_showWeapon = true;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = false;
							Settings::Aimbot::fov_mode = 0;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = false;
							Settings::Aimbot::smoothness = 22.f;
							Settings::Aimbot::acceleration = 1;
							Settings::Aimbot::fov = 50.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = true;
							Settings::Aimbot::smart_bone_scan = true;
							Settings::Misc::nospread = false;
							Settings::Aimbot::bone_priority = 3;
							Settings::Visuals::b_fov = true;
							Settings::Misc::fov = false;
						}
						if (ImGui::Button(XOR("Load Rage Settings"), ImVec2(185, 23)))
						{
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showHealth = true;
							Settings::Visuals::b_showDistance = true;
							Settings::Visuals::b_showName = true;
							Settings::Visuals::b_showWeapon = true;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = true;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = true;
							Settings::Aimbot::smoothness = 1.f;
							Settings::Aimbot::acceleration = 1;
							Settings::Aimbot::fov_mode = 1;
							Settings::Aimbot::fov = 360.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = true;
							Settings::Misc::nospread = true;
							Settings::Aimbot::bone_priority = 2;
							Settings::Visuals::b_fov = true;
							Settings::Misc::fov = true;
						}
						if (ImGui::Button(XOR("Load Rage SilentAim Settings"), ImVec2(185, 23)))
						{
							Settings::Aimbot::enabled = true;
							Settings::Visuals::b_showHealth = true;
							Settings::Visuals::b_showDistance = true;
							Settings::Visuals::b_showName = true;
							Settings::Visuals::b_showWeapon = true;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showBox = true;
							Settings::Visuals::b_showTeam = false;
							Settings::Visuals::b_showAI = false;
							Settings::Visuals::b_showBones = true;
							Settings::Visuals::b_showCompass = true;
							Settings::Aimbot::smoothness = 1.f;
							Settings::Aimbot::acceleration = 1;
							Settings::Aimbot::fov_mode = 1;
							Settings::Aimbot::fov = 180.f;
							Settings::Aimbot::max_distance = 100.f;
							Settings::Misc::norecoil = true;
							Settings::Aimbot::smart_bone_scan = true;
							Settings::Misc::nospread = true;
							Settings::Aimbot::bone_priority = 2;
							Settings::Visuals::b_fov = true;
							Settings::Misc::fov = true;
							Settings::Aimbot::aim_method = 1;
						}
					}
					ImGui::EndGroup();

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(320, 15));
				ImGui::BeginChild(XOR("Custom"), ImVec2(215, 460), true);
				{
					//title
					static bool b_fpss = false;
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("CONFIGS"));

					//functions render
					ImGui::SetCursorPos(ImVec2(15, 50));
					ImGui::BeginGroup();
					{


						if (ImGui::Button(XOR("Save Config 1"), ImVec2(185, 25)))
						{
							Settings::Save_Settings(buff), 0;
							std::string(buff).clear();
						}


						if (ImGui::Button(XOR("Save Config 2"), ImVec2(185, 25)))
						{
							Settings::Save_Settings(buff2), 1;
							std::string(buff2).clear();
						}


						if (ImGui::Button(XOR("Save Config 3"), ImVec2(185, 25)))
						{
							Settings::Save_Settings(buff3), 2;
							std::string(buff3).clear();
						}



						if (ImGui::Button(XOR("Load Config 1"), ImVec2(185, 25)))
						{
							if (!vec_files.empty()) {
								Settings::Load_Settings(vec_files[0]);

							}
						}

						if (ImGui::Button(XOR("Load Config 2"), ImVec2(185, 25)))
						{
							if (!vec_files.empty()) {
								Settings::Load_Settings(vec_files[1]);

							}
						}

						if (ImGui::Button(XOR("Load Config 3"), ImVec2(185, 25)))
						{
							if (!vec_files.empty()) {
								Settings::Load_Settings(vec_files[2]);

							}

						}


					}
					ImGui::EndGroup();
				}
				ImGui::EndChild();



				ImGui::SetCursorPos(ImVec2(550, 15));
				ImGui::BeginChild(XOR("Colors"), ImVec2(215, 460), true);
				{
					ImGui::SetCursorPos(ImVec2(15, 20));
					ImGui::TextColored(ImColor(113, 113, 113), XOR("COLORS"));


					//functions render
					ImGui::SetCursorPosY(50);
					ImGui::BeginGroup();
					{

						Custom::ColorEdit4(XOR("Distance Visible"), (float*)&Settings::Colors::visible_distance, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Name Visible"), (float*)&Settings::Colors::visible_name, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Weapon Visible"), (float*)&Settings::Colors::visible_Weapon, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Box Visible"), (float*)&Settings::Colors::visible_box, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Skeletons Vis"), (float*)&Settings::Colors::visible_Bone, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Compass Vis"), (float*)&Settings::Colors::visible_compass, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Distance Not Vis"), (float*)&Settings::Colors::not_visible_distance, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Name Not Vis"), (float*)&Settings::Colors::not_visible_name, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Weapon Not Vis"), (float*)&Settings::Colors::not_visible_Weapon, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Box Not Vis"), (float*)&Settings::Colors::not_visible_box, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
						Custom::ColorEdit4(XOR("Skeltons Not Vis"), (float*)&Settings::Colors::not_visible_Bone, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);

					}
					ImGui::EndGroup();

				}
				ImGui::EndChild();
			}

		}ImGui::End();
	}

	

	
}

