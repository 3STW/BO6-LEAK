#pragma once


struct KeyBind;
namespace imgui_custom
{
	void GoldenAimStyle();
	void hotkey(const char* label, KeyBind& key, float samelineOffset, const ImVec2& size);
	void Colorpicker(const char* ID, const char* text, float* color, bool sameline, float spacing = 0.0f);
}

struct ExampleAppLog
{
		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		ImVector<int>       LineOffsets;        // Index to lines offset
		bool                ScrollToBottom;

		inline void    Clear();

		inline void    AddLog(const char* fmt, ...);

		void      Draw_logs(const char* title, bool* p_opened);
};
 inline ExampleAppLog IMGUI_Log;
 void combosearch(const char* labelss, char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size, bool op = false);