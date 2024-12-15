#pragma once
#include "menufunctions.h"
#include <algorithm>
#include <vector>

using namespace ImGui;
#pragma warning(disable: 4996)

namespace custom {
    struct checkbox_state {
        ImVec4 background, text, circle, circle_outline, circle_shadow, circle_shadow_hovered, circle_shadow_hovered1;
        float move, line, line1, offset;
    };

    struct check_state
    {
        ImVec4 background, circle, text;
        float background_opticaly, circle_offset;
    };
    std::map<ImGuiID, check_state> CheckBoxAnim;
    bool Switchbox(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float square_sz = 18, y_size = 18;

        const ImVec2 pos = window->DC.CursorPos;

        const float w = GetContentRegionMax().x - style.WindowPadding.x;

        const ImRect total_bb(pos + ImVec2(0, 0), pos + ImVec2(w, y_size));
        ItemSize(total_bb, 0.f);

        if (!ItemAdd(total_bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(total_bb, id, &hovered, &held);

        auto it_anim = CheckBoxAnim.find(id);

        if (it_anim == CheckBoxAnim.end())
        {
            CheckBoxAnim.insert({ id, check_state() });
            it_anim = CheckBoxAnim.find(id);
        }

        it_anim->second.background_opticaly = ImLerp(it_anim->second.background_opticaly, *v ? 0.2f : 1.0f, g.IO.DeltaTime * 6.f);
        it_anim->second.circle_offset = ImLerp(it_anim->second.circle_offset, *v ? 0 : -square_sz * 2, g.IO.DeltaTime * 6.f);
        it_anim->second.background = ImLerp(it_anim->second.background, *v ? c::accent_color : c::widget::background, g.IO.DeltaTime * 6.f);
        it_anim->second.circle = ImLerp(it_anim->second.circle, *v ? c::accent_color : c::text::text, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, *v ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);

        if (pressed)
        {
            *v = !(*v);
            MarkItemEdited(id);
        }

        const ImRect check_bb(pos + ImVec2(w - (square_sz * 2), (y_size - square_sz) / 2), pos + ImVec2(w, (y_size + square_sz) / 2));

        //  GetWindowDrawList()->AddRectFilled(check_bb.Min, check_bb.Max, GetColorU32(it_anim->second.background, it_anim->second.background_opticaly), 30);
        GetWindowDrawList()->AddRect(check_bb.Min, check_bb.Max, GetColorU32(it_anim->second.background), 30, NULL, 1.1f);

        GetWindowDrawList()->AddCircleFilled(check_bb.Max - ImVec2(y_size - it_anim->second.circle_offset, y_size) / 2, 5.f, GetColorU32(it_anim->second.circle), 30);
        GetWindowDrawList()->AddText(pos + ImVec2(0, (y_size - CalcTextSize(label).y) / 2), GetColorU32(it_anim->second.text), label);

        return pressed;
    }

    std::map<ImGuiID, checkbox_state> anim_checkbox;
    bool checkbox(const char* label, bool* v)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const float square_sz = 24.f, w = (ImGui::GetContentRegionMax().x - g.Style.WindowPadding.x) - square_sz;
        // const float square_sz = GetFrameHeight()
        float active = 16.f;
        float inactive = -4.f;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(280, 20));
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
        {
            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
            return false;
        }
        bool hovered, held, pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);

        if (ImGui::IsItemClicked())
        {
            *v = !(*v);
            ImGui::MarkItemEdited(id);
        }

        auto it_anim = anim_checkbox.find(id);
        if (it_anim == anim_checkbox.end())
        {
            anim_checkbox.insert({ id, checkbox_state() });
            it_anim = anim_checkbox.find(id);
        }

        it_anim->second.circle = ImLerp(it_anim->second.circle, *v ? c::checkbox::accent_color : c::checkbox::accent_color_inact, g.IO.DeltaTime * 6.f);
        it_anim->second.circle_outline = ImLerp(it_anim->second.circle_outline, *v ? c::checkbox::circle_active : c::checkbox::circle_outline, g.IO.DeltaTime * 6.f);

        it_anim->second.text = ImLerp(it_anim->second.text, *v ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);
        it_anim->second.move = ImLerp(it_anim->second.move, *v ? active : inactive, g.IO.DeltaTime * 8.f);
        it_anim->second.background = ImLerp(it_anim->second.background, *v ? c::checkbox::background_active : c::checkbox::background_inactive, g.IO.DeltaTime * 9.f);
        it_anim->second.circle_shadow = ImLerp(it_anim->second.circle_shadow, *v ? c::checkbox::circle_shadow_activ : c::checkbox::circle_shadow_inactiv, g.IO.DeltaTime * 6.f);
        it_anim->second.line1 = ImLerp(it_anim->second.line1, hovered ? label_size.x : 0.f, g.IO.DeltaTime * 10.f);

        it_anim->second.line = ImLerp(it_anim->second.line, hovered ? label_size.x : 0, g.IO.DeltaTime * 10.f);

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));

        it_anim->second.circle_shadow_hovered = ImLerp(it_anim->second.circle_shadow_hovered, hovered ? ImColor(0, 255, 208, 255) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 10.f);

        ImGui::GetWindowDrawList()->AddRectFilled(check_bb.Min + ImVec2(w - 12, 6), check_bb.Max + ImVec2(w, -5), ImGui::GetColorU32(it_anim->second.background), 100.f);

        ImGui::GetWindowDrawList()->AddCircleFilled(check_bb.Min + ImVec2(w + it_anim->second.move, 12), 9.f, ImGui::GetColorU32(it_anim->second.circle), 100.f);

        ImGui::GetWindowDrawList()->AddText(ImVec2(check_bb.Max.x - square_sz, check_bb.Min.y + 2), ImGui::GetColorU32(it_anim->second.text), label);

        return pressed;
    }


    struct button_state_tab {
        ImVec4 ico_background, background, text, rect, rect_1, rect_2;
    };

    std::map<ImGuiID, button_state_tab> anim_tab;
    bool Tab(bool selected, const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags, ImFont* font)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        //PushFont(font::tab);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        // PopFont();

        ImVec2 pos = window->DC.CursorPos;

        ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x, label_size.y);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 8));
        const ImRect bb(pos, pos + size), rect(pos, pos);

        ImGui::ItemSize(size, 0.f);
        ImGui::PopStyleVar();

        if (!ImGui::ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);


        auto it_anim = anim_tab.find(id);

        if (it_anim == anim_tab.end())
        {
            anim_tab.insert({ id, button_state_tab() });
            it_anim = anim_tab.find(id);
        }

        it_anim->second.ico_background = ImLerp(it_anim->second.ico_background, selected ? c::tab::ibg : c::tab::i_bg, g.IO.DeltaTime * 10.f);
        it_anim->second.background = ImLerp(it_anim->second.background, selected ? c::tab::bg_active : c::tab::bg_inactive, g.IO.DeltaTime * 10.f);
        it_anim->second.text = ImLerp(it_anim->second.text, selected ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 10.f);
        it_anim->second.rect = ImLerp(it_anim->second.rect, selected ? c::tab::rect_active : c::tab::rect_inactive, g.IO.DeltaTime * 10.f);
        it_anim->second.rect_1 = ImLerp(it_anim->second.rect_1, selected ? c::tab::rect_active1 : c::tab::rect_inactive1, g.IO.DeltaTime * 10.f);
        it_anim->second.rect_2 = ImLerp(it_anim->second.rect_2, selected ? c::tab::rect_active2 : c::tab::rect_inactive2, g.IO.DeltaTime * 10.f);

        ImGui::GetWindowDrawList()->AddRect(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(it_anim->second.rect_2), 6.f);

        ImGui::GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(it_anim->second.background), 6.f);

        //ImGui::GetWindowDrawList()->AddRect(ImVec2(bb.Min.x + 5, bb.Max.y), ImVec2(bb.Max.x - 5, bb.Max.y), ImColor(it_anim->second.rect_1), 5.f);

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(rect.Min.x + 125, rect.Min.y + 10), ImVec2(rect.Max.x + 127, rect.Max.y + 30), ImGui::GetColorU32(it_anim->second.rect), 8.f);

        ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(it_anim->second.text));
        ImGui::PushFont(font);
        ImGui::RenderTextClipped(bb.Min + ImVec2((style.ItemSpacing.x * 2) - 5, -3), bb.Max, label, NULL, &label_size, ImVec2(0.0, 0.5), &bb);
        ImGui::PopFont();
        ImGui::PopStyleColor();


        return pressed;
    }



    struct suttab_state
    {
        ImVec4 background, shadow, line, icon, text;
    };

    std::map<ImGuiID, suttab_state> anim_sub_tab;
    bool Subtab(const char* label, bool selectable, const ImVec2& size_arg)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();

        if (window->SkipItems) return false;
        const ImGuiID id = window->GetID(label);
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect bb(pos, pos + size_arg);
        const ImRect image_bb(pos, pos + ImVec2(30, 30));

        ImGui::ItemSize(size_arg, 0.f);
        if (!ImGui::ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);


        auto it_anim = anim_sub_tab.find(id);

        if (it_anim == anim_sub_tab.end())
        {
            anim_sub_tab.insert({ id, suttab_state() });
            it_anim = anim_sub_tab.find(id);
        }

        it_anim->second.icon = ImLerp(it_anim->second.icon, selectable ? c::subtab::accent_color : c::subtab::white_color, g.IO.DeltaTime * 6.f);

        it_anim->second.shadow = ImLerp(it_anim->second.shadow, selectable ? c::subtab::line_red : c::subtab::line_default, g.IO.DeltaTime * 6.f);
        //it_anim->second.line = ImLerp(it_anim->second.line, selectable ? c::accent_color : c::tab::line_inactive, g.IO.DeltaTime * 6.f);

        ImGui::GetWindowDrawList()->AddRect(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImGui::GetColorU32(c::child::background), 3);

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(bb.Min.x + 21, bb.Min.y + 26), ImVec2(bb.Min.x + 46, bb.Min.y + 31), ImGui::GetColorU32(c::subtab::line_black), 10.f);

        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(bb.Min.x + 23, bb.Min.y + 27), ImVec2(bb.Min.x + 44, bb.Min.y + 28), ImGui::GetColorU32(it_anim->second.shadow), 10.f);



        ImGui::GetForegroundDrawList()->AddText(ImVec2(bb.Min.x + (size_arg.x - ImGui::CalcTextSize(label).x) / 2, bb.Min.y + 8), ImColor(255, 255, 255), label);


        return pressed;
    }


    struct slider_state
    {
        float speed;
        float value;
        ImVec4 color;
        ImVec4 color_text;
        ImVec4 color_text_label;
    };

    std::map<ImGuiID, float> nameanim_mark;
    std::map<ImGuiID, slider_state> filing;
    struct container {

        ImVec4 background, text;
        ImVec4 checkmark;
        float slider_slow;
        float tab_slow;

        bool opened_combo = false, hovered = false;
        float combo_size = 0.f, expand_rotation = 1.0f;

        float clip_mark;
        float circle_checkbox;
    };
    std::map<ImGuiID, container> Slideranim;
    bool Slider(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        const float w = 140;
        SetCursorPos(GetCursorPos() + ImVec2((GetContentRegionMax().x - style.WindowPadding.x) - w, 7));

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, 15));

        const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? label_size.x : 0.0f, 0.0f));

        const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
        ItemSize(ImRect(total_bb.Min, total_bb.Max + ImVec2(0, 3)));
        if (!ItemAdd(total_bb, id, &frame_bb, temp_input_allowed ? ImGuiItemFlags_Inputable : 0)) return false;

        if (format == NULL)
            format = DataTypeGetInfo(data_type)->PrintFmt;

        const bool hovered = ItemHoverable(frame_bb, id);
        bool temp_input_is_active = temp_input_allowed && TempInputIsActive(id);
        if (!temp_input_is_active)
        {

            const bool input_requested_by_tabbing = temp_input_allowed && (g.LastItemData.StatusFlags & ImGuiItemStatusFlags_FocusedByTabbing) != 0;
            const bool clicked = hovered && IsMouseClicked(0, id);
            const bool make_active = (input_requested_by_tabbing || clicked || g.NavActivateId == id);
            if (make_active && clicked)
                SetKeyOwner(ImGuiKey_MouseLeft, id);
            if (make_active && temp_input_allowed)
                if (input_requested_by_tabbing || (clicked && g.IO.KeyCtrl) || (g.NavActivateId == id && (g.NavActivateFlags & ImGuiActivateFlags_PreferInput)))
                    temp_input_is_active = true;

            if (make_active && !temp_input_is_active)
            {
                SetActiveID(id, window);
                SetFocusID(id, window);
                FocusWindow(window);
                g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
            }
        }

        auto it_anim = Slideranim.find(id);

        if (it_anim == Slideranim.end())
        {
            Slideranim.insert({ id, container() });
            it_anim = Slideranim.find(id);
        }

        it_anim->second.background = ImLerp(it_anim->second.background, hovered ? c::slider::bg_hov : c::slider::bg, g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, IsItemActive() ? c::text::text_active : hovered ? c::text::text_hov : c::text::text, g.IO.DeltaTime * 6.f);

        GetWindowDrawList()->AddRectFilled(frame_bb.Min + ImVec2(0, 5), frame_bb.Max - ImVec2(0, 5), GetColorU32(it_anim->second.background), c::slider::rounding);

        ImRect grab_bb;
        const bool value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);

        if (value_changed) MarkItemEdited(id);

        if (grab_bb.Max.x > grab_bb.Min.x) {

            it_anim->second.slider_slow = ImLerp(it_anim->second.slider_slow, grab_bb.Min.x + 5 - frame_bb.Min.x, g.IO.DeltaTime * 20.f);

            GetWindowDrawList()->AddRectFilled(frame_bb.Min + ImVec2(0, 5), frame_bb.Min + ImVec2(it_anim->second.slider_slow - 3, 10), GetColorU32(accent_color_low), c::slider::rounding);
            GetWindowDrawList()->AddCircleFilled(ImVec2(frame_bb.Min.x + it_anim->second.slider_slow, grab_bb.Max.y - 6), 7.f, GetColorU32(accent_color), 20.f);

            if (IsRectVisible(total_bb.Min, total_bb.Max)) (ImVec2(frame_bb.Min.x + it_anim->second.slider_slow, grab_bb.Max.y - 6), 7.f, GetColorU32(accent_color), 20.f, ImVec2(0, 0));

        }

        char value_buf[64];
        const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

        PushStyleColor(ImGuiCol_Text, GetColorU32(it_anim->second.text));
        RenderTextClipped(frame_bb.Min - ImVec2(w - 10, 4), frame_bb.Max + ImVec2(-w - 10, 4), value_buf, value_buf_end, NULL, ImVec2(1.0f, 0.5f));
        PopStyleColor();

        ImGui::GetWindowDrawList()->AddText(ImVec2(frame_bb.Max.x - GetContentRegionMax().x + style.WindowPadding.x, frame_bb.Min.y - 4), GetColorU32(it_anim->second.text), label);

        return value_changed;
    }

    bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return Slider(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
    }

    bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return Slider(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
    }

    const char* keys[] =
    {
        "None",
        "Mouse 1",
        "Mouse 2",
        "CN",
        "Mouse 3",
        "Mouse 4",
        "Mouse 5",
        "-",
        "Back",
        "Tab",
        "-",
        "-",
        "CLR",
        "Enter",
        "-",
        "-",
        "Shift",
        "CTL",
        "Menu",
        "Pause",
        "Caps Lock",
        "KAN",
        "-",
        "JUN",
        "FIN",
        "KAN",
        "-",
        "Escape",
        "CON",
        "NCO",
        "ACC",
        "MAD",
        "Space",
        "PGU",
        "PGD",
        "End",
        "Home",
        "Left",
        "Up",
        "Right",
        "Down",
        "SEL",
        "PRI",
        "EXE",
        "PRI",
        "INS",
        "Delete",
        "HEL",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "WIN",
        "WIN",
        "APP",
        "-",
        "SLE",
        "Numpad 0",
        "Numpad 1",
        "Numpad 2",
        "Numpad 3",
        "Numpad 4",
        "Numpad 5",
        "Numpad 6",
        "Numpad 7",
        "Numpad 8",
        "Numpad 9",
        "MUL",
        "ADD",
        "SEP",
        "MIN",
        "Delete",
        "DIV",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "F13",
        "F14",
        "F15",
        "F16",
        "F17",
        "F18",
        "F19",
        "F20",
        "F21",
        "F22",
        "F23",
        "F24",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "NUM",
        "SCR",
        "EQU",
        "MAS",
        "TOY",
        "OYA",
        "OYA",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "-",
        "Shift",
        "Shift",
        "Ctrl",
        "Ctrl",
        "Alt",
        "Alt"
    };

    struct key_state
    {
        ImVec4 background, text;
        bool active = false;
        bool hovered = false;
        float alpha = 0.f, slow_show;
        ImVec4 color_shadow;
    };

    std::map<ImGuiID, key_state> anim_keybind;

    bool Keybind(const char* label, int* key, bool show_label)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        ImGuiIO& io = g.IO;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const float width = (GetContentRegionMax().x - style.WindowPadding.x);

        const ImRect rect(window->DC.CursorPos + ImVec2(0, 0), window->DC.CursorPos + ImVec2(width, 30.f));

        ItemSize(ImRect(rect.Min, rect.Max - ImVec2(0, 7)));
        if (!ImGui::ItemAdd(rect, id))
            return false;

        char buf_display[64] = "None";


        bool value_changed = false;
        int k = *key;

        std::string active_key = "";
        active_key += keys[*key];

        if (*key != 0 && g.ActiveId != id) {
            strcpy_s(buf_display, active_key.c_str());
        }
        else if (g.ActiveId == id) {
            strcpy_s(buf_display, "...");
        }

        const ImVec2 label_size = CalcTextSize(buf_display, NULL, true);

        ImRect clickable(ImVec2(rect.Max.x - 8 - label_size.x, rect.Min.y), rect.Max);
        bool hovered = ItemHoverable(clickable, id);

        auto it_anim = anim_keybind.find(id);

        if (it_anim == anim_keybind.end())
        {
            anim_keybind.insert({ id, key_state() });
            it_anim = anim_keybind.find(id);
        }

        it_anim->second.text = ImLerp(it_anim->second.text, g.ActiveId == id ? ImColor(255, 255, 255) : hovered ? ImColor(150, 150, 150, 150) : ImColor(100, 100, 100, 255), ImGui::GetIO().DeltaTime * 6.f);
        it_anim->second.slow_show = ImLerp(it_anim->second.slow_show, clickable.Min.x - rect.Min.x, g.IO.DeltaTime * 15.f);
        it_anim->second.color_shadow = ImLerp(it_anim->second.color_shadow, IsItemActive() ? ImColor(0, 255, 208, 255) : hovered ? ImColor(0, 255, 208, 255) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 5.f);
        it_anim->second.background = ImLerp(it_anim->second.background, IsItemActive() ? c::keybind::background_active : c::keybind::background_inactive, g.IO.DeltaTime * 5.f);

        window->DrawList->AddRect(ImVec2(it_anim->second.slow_show + rect.Min.x, clickable.Min.y - 2), clickable.Max - ImVec2(0, 5), GetColorU32(it_anim->second.background), 3.f);

        if (show_label) window->DrawList->AddText(rect.Min + ImVec2(0, 1), GetColorU32(it_anim->second.text), label);

        PushStyleColor(ImGuiCol_Text, ImVec4(255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f));
        RenderTextClipped(ImVec2(it_anim->second.slow_show + rect.Min.x, clickable.Min.y - 7), clickable.Max, buf_display, NULL, &label_size, ImVec2(0.5f, 0.5f));
        PopStyleColor();

        if (hovered && io.MouseClicked[0])
        {
            if (g.ActiveId != id) {
                // Start edition
                memset(io.MouseDown, 0, sizeof(io.MouseDown));
                memset(io.KeysDown, 0, sizeof(io.KeysDown));
                *key = 0;
            }
            ImGui::SetActiveID(id, window);
            ImGui::FocusWindow(window);
        }
        else if (io.MouseClicked[0]) {
            // Release focus when we click outside
            if (g.ActiveId == id)
                ImGui::ClearActiveID();
        }

        if (g.ActiveId == id) {
            for (auto i = 0; i < 5; i++) {
                if (io.MouseDown[i]) {
                    switch (i) {
                    case 0:
                        k = 0x01;
                        break;
                    case 1:
                        k = 0x02;
                        break;
                    case 2:
                        k = 0x04;
                        break;
                    case 3:
                        k = 0x05;
                        break;
                    case 4:
                        k = 0x06;
                        break;
                    }
                    value_changed = true;
                    ImGui::ClearActiveID();
                }
            }
            if (!value_changed) {
                for (auto i = 0x08; i <= 0xA5; i++) {
                    if (io.KeysDown[i]) {
                        k = i;
                        value_changed = true;
                        ImGui::ClearActiveID();
                    }
                }
            }

            if (IsKeyPressedMap(ImGuiKey_Escape)) {
                *key = 0;
                ImGui::ClearActiveID();
            }
            else {
                *key = k;
            }
        }

        return value_changed;
    }

    void combosearch(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size = ImVec2(150, 70), bool op = false)
    {
        ImGui::PushItemWidth(size.x);
        // State
        char empty[1] = { "" };
        std::string str;
        str = input;
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        std::string label = "##input" + hint;
        // Code
        const bool is_input_text_enter_pressed = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), input, sizeof(input), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
        const bool is_input_text_active = ImGui::IsItemActive();
        const bool is_input_text_activated = ImGui::IsItemActivated();

        if (is_input_text_activated)
        {
            ImGui::OpenPopup(label.c_str());
        }
        {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));
            ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
            if (ImGui::BeginPopup(label.c_str(), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
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
        if (is_input_text_activated)
        {
            memset(input, NULL, sizeof(NULL));
        }
    }
}