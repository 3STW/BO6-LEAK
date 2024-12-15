#include"includes.h"

namespace imgui_custom
{

	void GoldenAimStyle()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.84f, 0.84f, 0.84f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.50f, 0.50f, 0.48f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.81f, 0.72f, 0.12f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.93f, 0.84f, 0.25f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.93f, 0.84f, 0.25f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.87f, 0.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.93f, 0.84f, 0.25f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.93f, 0.84f, 0.25f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.93f, 0.84f, 0.25f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.93f, 0.84f, 0.25f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.93f, 0.84f, 0.25f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.93f, 0.84f, 0.25f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.93f, 0.84f, 0.25f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.93f, 0.84f, 0.25f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.93f, 0.84f, 0.25f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.93f, 0.84f, 0.25f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.93f, 0.59f, 0.25f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.93f, 0.84f, 0.25f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);




	}

	void hotkey(const char* label, KeyBind& key, float samelineOffset, const ImVec2& size) 
	{
		const auto id = ImGui::GetID(label);
		ImGui::PushID(label);

		ImGui::TextUnformatted(label);
		ImGui::SameLine(samelineOffset);

		if (ImGui::GetActiveID() == id) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_ButtonActive));
			ImGui::Button("...", size);
			ImGui::PopStyleColor();

			ImGui::GetCurrentContext()->ActiveIdAllowOverlap = true;
			if ((!ImGui::IsItemHovered() && ImGui::GetIO().MouseClicked[0]) || key.setToPressedKey())
				ImGui::ClearActiveID();
		}
		else if (ImGui::Button(key.toString(), size)) {
			ImGui::SetActiveID(id, ImGui::GetCurrentWindow());
		}

		ImGui::PopID();
	}

	void Colorpicker(const char* ID, const char* text, float* color, bool sameline, float spacing)
	{

		auto window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;

		if (sameline)
			ImGui::SameLine(spacing);

		ImGui::PushID(ID);

		if (ImGui::ColorButton(text, ImVec4(color[0], color[1], color[2], color[3])))
			ImGui::OpenPopup(text);

		if (ImGui::BeginPopup(text))
		{
			ImGui::ColorPicker4(text, color, ImGuiColorEditFlags_::ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_::ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_::ImGuiColorEditFlags_NoInputs);
			ImGui::EndPopup();
		}
		ImGui::PopID();
	}
}


void   ExampleAppLog::Clear() { Buf.clear(); LineOffsets.clear(); }

void    ExampleAppLog::AddLog(const char* fmt, ...)
{
	int old_size = Buf.size();
	va_list args;
	va_start(args, fmt);
	Buf.appendfv(fmt, args);
	va_end(args);
	for (int new_size = Buf.size(); old_size < new_size; old_size++)
		if (Buf[old_size] == '\n')
			LineOffsets.push_back(old_size);
	ScrollToBottom = true;
}

void    ExampleAppLog::Draw_logs(const char* title, bool* p_opened)
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_::ImGuiCond_FirstUseEver);
	ImGui::Begin(title, p_opened);
	if (ImGui::Button("Clear")) Clear();
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);
	ImGui::Separator();
	ImGui::BeginChild("scrolling");
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
	if (copy) ImGui::LogToClipboard();

	if (Filter.IsActive())
	{
		const char* buf_begin = Buf.begin();
		const char* line = buf_begin;
		for (int line_no = 0; line != NULL; line_no++)
		{
			const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
			if (Filter.PassFilter(line, line_end))
				ImGui::TextUnformatted(line, line_end);
			line = line_end && line_end[1] ? line_end + 1 : NULL;
		}
	}
	else
	{
		ImGui::TextUnformatted(Buf.begin());
	}

	if (ScrollToBottom)
	//	ImGui::SetScrollHere(1.0f);
	ScrollToBottom = false;
	ImGui::PopStyleVar();
	ImGui::EndChild();
	ImGui::End();
}

void combosearch(const char* labelss, char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size, bool op )
{
	ImGui::PushItemWidth(size.x);
	// State
	char empty[1] = { "" };
	std::string str;
	str = input;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::string label = labelss + hint;
	// Code
	const bool is_input_text_enter_pressed = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), input, sizeof(input), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
	const bool is_input_text_active = ImGui::IsItemActive();
	const bool is_input_text_activated = ImGui::IsItemActivated();

	if (is_input_text_activated)
	{
		ImGui::OpenPopup(labelss);
	}
	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));
		ImGui::SetNextWindowSize(ImVec2(size.x, 70));
		if (ImGui::BeginPopup(labelss, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
		{
			for (int i = 0; i < list.size(); i++)
			{
				if (strstr(listLower[i].c_str(), str.c_str()) == NULL)
					continue;
				if (ImGui::Selectable(list[i].c_str()))
				{
					ImGui::ClearActiveID();
					strcpy(input, list[i].c_str());
					*index = i;
				}
			}

			if (!is_input_text_active && !ImGui::IsWindowFocused())
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}