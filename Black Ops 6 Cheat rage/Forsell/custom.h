#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include <d3d11.h>
#include <tchar.h>

#include "imgui_settings.h"
#include <map>
#include <vector>
#include <string>
#include "Menu.h"
#include <d3d9.h>

using namespace ImGui;
using namespace std;

namespace font {
    ImFont* poppins;
    ImFont* icon;
    ImFont* icon_combo;

    ImFont* descriptionfont;

}

namespace Custom {

    struct container {

        ImVec4 background, text;
        ImVec4 checkmark;
        float slider_slow;
        float tab_slow;

        float alpha = 0.f;
        float clip_mark;
        float circle_checkbox;
        float element_opacity;
        float rect_opacity;
        float text_opacity;
        ImVec4 framecol;
        ImVec4 checkmark1;
        ImVec4 background_color, background_slider, circle_color;
        float slow, hint_slider;
        ImVec4 text2;
        ImVec4 bg;
        ImVec4 bg2;
        float animation;
        float element_opacity1;
        float rect_opacity1;
        float text_opacity1;
        float alpha_animation;

        ImVec4 background_combo, text_color;

        bool opened_combo = false, hovered = false;
        float combo_size = 0.f;
    };
    map<ImGuiID, container> checkboxanim;
    ////////////////////////////////////////////////////////////////////////////////////////////
    // CHECKBOX
    ////////////////////////////////////////////////////////////////////////////////////////////

    std::map<ImGuiID, container> checkboxanimasdasdsadccc;

    const char* keys2[] = {
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
    "Caps",
    "KAN",
    "-",
    "JUN",
    "FIN",
    "KAN",
    "-",
    "ESC",
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
    "DEL",
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

    std::map<ImGuiID, container> sakdskadkaskdsadsadasda;
    std::map<ImGuiID, container> asdjsajdajsdn2n22dasdsa;
    std::map < ImGuiID, container> alpha_animation2;

    bool Keybind(const char* label, const char* description, int* key, bool widget_label) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        ImGuiIO& io = g.IO;
        const ImGuiStyle& style = g.Style;

        ImVec2 mode_size;
        ImVec2 key_size;

        const ImGuiID id = window->GetID(label);
        const float size = GetWindowWidth() - 30;
        const ImRect rect(window->DC.CursorPos, window->DC.CursorPos + ImVec2(size, 30));
        ImRect mode_rect(window->DC.CursorPos + ImVec2(size - 0, 0), window->DC.CursorPos + ImVec2(size, 40));
        ImRect key_rect;

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(270, 35));

        ImGui::ItemSize(rect, style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool popup_open = ImGui::IsPopupOpen(id, ImGuiPopupFlags_None);
        bool hovered_rect = ItemHoverable(rect, id);

        bool value_changed = false;
        int k = *key;

        mode_rect.Min.x -= mode_size.x;
        key_rect = ImRect(mode_rect.Min - ImVec2(CalcItemWidth(), 0), ImVec2(mode_rect.Min.x - 1, mode_rect.Max.y));

        bool hovered_mode = ItemHoverable(mode_rect, id);

        char buf_display1[64] = "None";

        std::string active_key = "";
        active_key += keys2[*key];

        if (*key != 0 && g.ActiveId != id) {
            strcpy_s(buf_display1, active_key.c_str());
        }
        else if (g.ActiveId == id) {
            strcpy_s(buf_display1, "-");
        }
        key_size = CalcTextSize(buf_display1, NULL, true);
        key_rect.Min.x -= key_size.x;

        bool hovered_key = ItemHoverable(key_rect, id);

        std::string nametwo = "keybind_state";
        nametwo += label;


        if (hovered_key && io.MouseClicked[0])
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

        auto it_anim = sakdskadkaskdsadsadasda.find(id);

        if (it_anim == sakdskadkaskdsadsadasda.end())
        {
            sakdskadkaskdsadsadasda.insert({ id, container() });
            it_anim = sakdskadkaskdsadsadasda.find(id);
        }

        auto it_alpha = alpha_animation2.find(id);
        if (it_alpha == alpha_animation2.end())
        {
            alpha_animation2.insert({ id, container() });
            it_alpha = alpha_animation2.find(id);
        }

        //it_alpha->second = ImLerp(it_alpha->second, hovered_rect ? 0.2f : 0.f, g.IO.DeltaTime * 6.f);

        //it_alpha->second *= style.Alpha;

        if (widget_label) window->DrawList->AddText(rect.Min + ImVec2(0, 2), GetColorU32(ImGuiCol_Text), label);

        window->DrawList->AddRectFilled(key_rect.Min + ImVec2(CalcItemWidth() - 21, -1), key_rect.Max - ImVec2(2, 12), ImColor(33, 33, 33), style.FrameRounding);

        RenderTextClipped(key_rect.Min - ImVec2(60, 31), key_rect.Max + ImVec2(CalcItemWidth() + 38, 16), buf_display1, NULL, NULL, ImVec2(0.5f, 0.5f));
        PushFont(descriptionfont);
        window->DrawList->AddText(rect.Min + ImVec2(0, 18), ImColor(63, 65, 68), description);
        PopFont();

        return value_changed;
    }

    bool CheckboxDesc(const char* label, const char* description, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float w = GetWindowWidth() - 30;
        const float square_sz = 17;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect frame_bb(pos + ImVec2(w - square_sz - 13, 0), window->DC.CursorPos + ImVec2(w, square_sz - 1));
        const ImRect total_bb(pos, pos + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
        const ImRect rect(pos, pos + ImVec2(30 + label_size.x, 20));

        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id))
        {
            IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
            return false;
        }

        bool hovered, held;
        bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
        if (pressed)
        {
            *v = !(*v);
            MarkItemEdited(id);
        }

        auto it_anim = checkboxanimasdasdsadccc.find(id);

        if (it_anim == checkboxanimasdasdsadccc.end())
        {
            checkboxanimasdasdsadccc.insert({ id, container() });
            it_anim = checkboxanimasdasdsadccc.find(id);
        }

        it_anim->second.animation = ImLerp(it_anim->second.animation, *v ? 1.0f : 0.0f, 0.12f * (1.0f - ImGui::GetIO().DeltaTime));

        RenderNavHighlight(total_bb, id);

        //background
        RenderFrame(frame_bb.Min, frame_bb.Max, ImColor(36, 36, 36), false, 9.0f);

        //circle
        if (*v)
            window->DrawList->AddCircleFilled(ImVec2(frame_bb.Min.x + 8 + 14 * it_anim->second.animation, frame_bb.Min.y + 8), 5.0f, ImColor(255, 0, 0), 30);
        else
            window->DrawList->AddCircleFilled(ImVec2(frame_bb.Min.x + 8 + 14 * it_anim->second.animation, frame_bb.Min.y + 8), 5.0f, ImColor(124, 124, 124), 30);

        //label
        if (label_size.x > 0.0f)
            RenderText(ImVec2(total_bb.Min.x, total_bb.Min.y + 1), label);

        // description text
        ImGui::PushFont(descriptionfont);
        window->DrawList->AddText(rect.Min + ImVec2(0, 17), ImColor(63, 65, 68), description);
        ImGui::PopFont();

        return pressed;
    }

    ImVec4 accentcolor = ImColor(255, 0, 0);

    bool Checkbox(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float square_sz = 18.f, checkmark = 10.f;
        const float w = (GetContentRegionMax().x - style.WindowPadding.x) - square_sz;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(square_sz + label_size.x + w, label_size.y));

        ItemSize(ImRect(total_bb.Min, total_bb.Max - ImVec2(0, 1)));

        if (!ItemAdd(total_bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(total_bb, id, &hovered, &held);

        if (IsItemClicked())
        {
            *v = !(*v);
            MarkItemEdited(id);
        }

        auto it_anim = checkboxanim.find(id);

        if (it_anim == checkboxanim.end())
        {
            checkboxanim.insert({ id, container() });
            it_anim = checkboxanim.find(id);
        }

        it_anim->second.background = ImLerp(it_anim->second.background, *v ? accent_color : hovered ? checkbox::bg_hov : checkbox::bg, g.IO.DeltaTime * 8.f);
        it_anim->second.checkmark = ImLerp(it_anim->second.checkmark, *v ? checkbox::checkmark : hovered ? checkbox::bg_hov : checkbox::bg, g.IO.DeltaTime * 8.f);
        it_anim->second.clip_mark = ImLerp(it_anim->second.clip_mark, *v ? checkmark : 0.f, g.IO.DeltaTime * 8.f);
        it_anim->second.text = ImLerp(it_anim->second.text, *v ? text::text_active : hovered ? text::text_hov : text::text, g.IO.DeltaTime * 8.f);

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));

        GetWindowDrawList()->AddRectFilled(check_bb.Min + ImVec2(w, 0), check_bb.Max + ImVec2(w, 0), GetColorU32(it_anim->second.background), checkbox::rounding);

        if (*v && IsRectVisible(check_bb.Min + ImVec2(w, 0), check_bb.Max + ImVec2(w, 0)))
            GetForegroundDrawList()->AddShadowRect(check_bb.Min + ImVec2(w + 5, 5), check_bb.Max + ImVec2(w - 5, -5), GetColorU32(accent_color), 30.f, ImVec2(0, 0), checkbox::rounding);

        ImGui::RenderCheckMark(window->DrawList, check_bb.Min + ImVec2((square_sz / 2) - (checkmark / 2) + w, (square_sz / 2) - (checkmark / 2)), GetColorU32(it_anim->second.checkmark), checkmark);

        ImGui::GetWindowDrawList()->AddText(ImVec2(check_bb.Max.x - square_sz, check_bb.Min.y - 1), GetColorU32(it_anim->second.text), label);

        return pressed;
    }

    static const ImGuiDataTypeInfo GDataTypeInfo[] =
    {
        { sizeof(char),             "S8",   "%d",   "%d"    },  // ImGuiDataType_S8
        { sizeof(unsigned char),    "U8",   "%u",   "%u"    },
        { sizeof(short),            "S16",  "%d",   "%d"    },  // ImGuiDataType_S16
        { sizeof(unsigned short),   "U16",  "%u",   "%u"    },
        { sizeof(int),              "S32",  "%d",   "%d"    },  // ImGuiDataType_S32
        { sizeof(unsigned int),     "U32",  "%u",   "%u"    },
    #ifdef _MSC_VER
        { sizeof(ImS64),            "S64",  "%I64d","%I64d" },  // ImGuiDataType_S64
        { sizeof(ImU64),            "U64",  "%I64u","%I64u" },
    #else
        { sizeof(ImS64),            "S64",  "%lld", "%lld"  },  // ImGuiDataType_S64
        { sizeof(ImU64),            "U64",  "%llu", "%llu"  },
    #endif
        { sizeof(float),            "float", "%.3f","%f"    },  // ImGuiDataType_Float (float are promoted to double in va_arg)
        { sizeof(double),           "double","%f",  "%lf"   },  // ImGuiDataType_Double
    };
    IM_STATIC_ASSERT(IM_ARRAYSIZE(GDataTypeInfo) == ImGuiDataType_COUNT);

    static const char* PatchFormatStringFloatToInt(const char* fmt)
    {
        if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0) // Fast legacy path for "%.0f" which is expected to be the most common case.
            return "%d";
        const char* fmt_start = ImParseFormatFindStart(fmt);    // Find % (if any, and ignore %%)
        const char* fmt_end = ImParseFormatFindEnd(fmt_start);  // Find end of format specifier, which itself is an exercise of confidence/recklessness (because snprintf is dependent on libc or user).
        if (fmt_end > fmt_start && fmt_end[-1] == 'f')
        {
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
            if (fmt_start == fmt && fmt_end[0] == 0)
                return "%d";
            const char* tmp_format;
            ImFormatStringToTempBuffer(&tmp_format, NULL, "%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end); // Honor leading and trailing decorations, but lose alignment/precision.
            return tmp_format;
#else
            IM_ASSERT(0 && "DragInt(): Invalid format string!"); // Old versions used a default parameter of "%.0f", please replace with e.g. "%d"
#endif
        }
        return fmt;
    }

    // FIXME: Try to move more of the code into shared SliderBehavior()
    template<typename TYPE, typename SIGNEDTYPE, typename FLOATTYPE>
    bool SliderBehaviorT(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, TYPE* v, const TYPE v_min, const TYPE v_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb)
    {
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiAxis axis = (flags & ImGuiSliderFlags_Vertical) ? ImGuiAxis_Y : ImGuiAxis_X;
        const bool is_logarithmic = (flags & ImGuiSliderFlags_Logarithmic) != 0;
        const bool is_floating_point = (data_type == ImGuiDataType_Float) || (data_type == ImGuiDataType_Double);
        const SIGNEDTYPE v_range = (v_min < v_max ? v_max - v_min : v_min - v_max);

        // Calculate bounds
        const float grab_padding = 2.0f; // FIXME: Should be part of style.
        const float slider_sz = (bb.Max[axis] - bb.Min[axis]) - grab_padding * 2.0f;
        float grab_sz = style.GrabMinSize;
        if (!is_floating_point && v_range >= 0)                                     // v_range < 0 may happen on integer overflows
            grab_sz = ImMax((float)(slider_sz / (v_range + 1)), style.GrabMinSize); // For integer sliders: if possible have the grab size represent 1 unit
        grab_sz = ImMin(grab_sz, slider_sz);
        const float slider_usable_sz = slider_sz - grab_sz;
        const float slider_usable_pos_min = bb.Min[axis] + grab_padding + grab_sz * 0.5f;
        const float slider_usable_pos_max = bb.Max[axis] - grab_padding - grab_sz * 0.5f;

        float logarithmic_zero_epsilon = 0.0f; // Only valid when is_logarithmic is true
        float zero_deadzone_halfsize = 0.0f; // Only valid when is_logarithmic is true
        if (is_logarithmic)
        {
            // When using logarithmic sliders, we need to clamp to avoid hitting zero, but our choice of clamp value greatly affects slider precision. We attempt to use the specified precision to estimate a good lower bound.
            const int decimal_precision = is_floating_point ? ImParseFormatPrecision(format, 3) : 1;
            logarithmic_zero_epsilon = ImPow(0.1f, (float)decimal_precision);
            zero_deadzone_halfsize = (style.LogSliderDeadzone * 0.5f) / ImMax(slider_usable_sz, 1.0f);
        }

        // Process interacting with the slider
        bool value_changed = false;
        if (g.ActiveId == id)
        {
            bool set_new_value = false;
            float clicked_t = 0.0f;
            if (g.ActiveIdSource == ImGuiInputSource_Mouse)
            {
                if (!g.IO.MouseDown[0])
                {
                    ClearActiveID();
                }
                else
                {
                    const float mouse_abs_pos = g.IO.MousePos[axis];
                    if (g.ActiveIdIsJustActivated)
                    {
                        float grab_t = ScaleRatioFromValueT<TYPE, SIGNEDTYPE, FLOATTYPE>(data_type, *v, v_min, v_max, is_logarithmic, logarithmic_zero_epsilon, zero_deadzone_halfsize);
                        if (axis == ImGuiAxis_Y)
                            grab_t = 1.0f - grab_t;
                        const float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
                        const bool clicked_around_grab = (mouse_abs_pos >= grab_pos - grab_sz * 0.5f - 1.0f) && (mouse_abs_pos <= grab_pos + grab_sz * 0.5f + 1.0f); // No harm being extra generous here.
                        g.SliderGrabClickOffset = (clicked_around_grab && is_floating_point) ? mouse_abs_pos - grab_pos : 0.0f;
                    }
                    if (slider_usable_sz > 0.0f)
                        clicked_t = ImSaturate((mouse_abs_pos - g.SliderGrabClickOffset - slider_usable_pos_min) / slider_usable_sz);
                    if (axis == ImGuiAxis_Y)
                        clicked_t = 1.0f - clicked_t;
                    set_new_value = true;
                }
            }
            else if (g.ActiveIdSource == ImGuiInputSource_Keyboard || g.ActiveIdSource == ImGuiInputSource_Gamepad)
            {
                if (g.ActiveIdIsJustActivated)
                {
                    g.SliderCurrentAccum = 0.0f; // Reset any stored nav delta upon activation
                    g.SliderCurrentAccumDirty = false;
                }

                float input_delta = (axis == ImGuiAxis_X) ? GetNavTweakPressedAmount(axis) : -GetNavTweakPressedAmount(axis);
                if (input_delta != 0.0f)
                {
                    const bool tweak_slow = IsKeyDown((g.NavInputSource == ImGuiInputSource_Gamepad) ? ImGuiKey_NavGamepadTweakSlow : ImGuiKey_NavKeyboardTweakSlow);
                    const bool tweak_fast = IsKeyDown((g.NavInputSource == ImGuiInputSource_Gamepad) ? ImGuiKey_NavGamepadTweakFast : ImGuiKey_NavKeyboardTweakFast);
                    const int decimal_precision = is_floating_point ? ImParseFormatPrecision(format, 3) : 0;
                    if (decimal_precision > 0)
                    {
                        input_delta /= 100.0f;    // Gamepad/keyboard tweak speeds in % of slider bounds
                        if (tweak_slow)
                            input_delta /= 10.0f;
                    }
                    else
                    {
                        if ((v_range >= -100.0f && v_range <= 100.0f) || tweak_slow)
                            input_delta = ((input_delta < 0.0f) ? -1.0f : +1.0f) / (float)v_range; // Gamepad/keyboard tweak speeds in integer steps
                        else
                            input_delta /= 100.0f;
                    }
                    if (tweak_fast)
                        input_delta *= 10.0f;

                    g.SliderCurrentAccum += input_delta;
                    g.SliderCurrentAccumDirty = true;
                }

                float delta = g.SliderCurrentAccum;
                if (g.NavActivatePressedId == id && !g.ActiveIdIsJustActivated)
                {
                    ClearActiveID();
                }
                else if (g.SliderCurrentAccumDirty)
                {
                    clicked_t = ScaleRatioFromValueT<TYPE, SIGNEDTYPE, FLOATTYPE>(data_type, *v, v_min, v_max, is_logarithmic, logarithmic_zero_epsilon, zero_deadzone_halfsize);

                    if ((clicked_t >= 1.0f && delta > 0.0f) || (clicked_t <= 0.0f && delta < 0.0f)) // This is to avoid applying the saturation when already past the limits
                    {
                        set_new_value = false;
                        g.SliderCurrentAccum = 0.0f; // If pushing up against the limits, don't continue to accumulate
                    }
                    else
                    {
                        set_new_value = true;
                        float old_clicked_t = clicked_t;
                        clicked_t = ImSaturate(clicked_t + delta);

                        // Calculate what our "new" clicked_t will be, and thus how far we actually moved the slider, and subtract this from the accumulator
                        TYPE v_new = ScaleValueFromRatioT<TYPE, SIGNEDTYPE, FLOATTYPE>(data_type, clicked_t, v_min, v_max, is_logarithmic, logarithmic_zero_epsilon, zero_deadzone_halfsize);
                        if (is_floating_point && !(flags & ImGuiSliderFlags_NoRoundToFormat))
                            v_new = RoundScalarWithFormatT<TYPE>(format, data_type, v_new);
                        float new_clicked_t = ScaleRatioFromValueT<TYPE, SIGNEDTYPE, FLOATTYPE>(data_type, v_new, v_min, v_max, is_logarithmic, logarithmic_zero_epsilon, zero_deadzone_halfsize);

                        if (delta > 0)
                            g.SliderCurrentAccum -= ImMin(new_clicked_t - old_clicked_t, delta);
                        else
                            g.SliderCurrentAccum -= ImMax(new_clicked_t - old_clicked_t, delta);
                    }

                    g.SliderCurrentAccumDirty = false;
                }
            }

            if (set_new_value)
            {
                TYPE v_new = ScaleValueFromRatioT<TYPE, SIGNEDTYPE, FLOATTYPE>(data_type, clicked_t, v_min, v_max, is_logarithmic, logarithmic_zero_epsilon, zero_deadzone_halfsize);

                // Round to user desired precision based on format string
                if (is_floating_point && !(flags & ImGuiSliderFlags_NoRoundToFormat))
                    v_new = RoundScalarWithFormatT<TYPE>(format, data_type, v_new);

                // Apply result
                if (*v != v_new)
                {
                    *v = v_new;
                    value_changed = true;
                }
            }
        }

        if (slider_sz < 1.0f)
        {
            *out_grab_bb = ImRect(bb.Min, bb.Min);
        }
        else
        {
            // Output grab position so it can be displayed by the caller
            float grab_t = ScaleRatioFromValueT<TYPE, SIGNEDTYPE, FLOATTYPE>(data_type, *v, v_min, v_max, is_logarithmic, logarithmic_zero_epsilon, zero_deadzone_halfsize);
            if (axis == ImGuiAxis_Y)
                grab_t = 1.0f - grab_t;
            const float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
            if (axis == ImGuiAxis_X)
                *out_grab_bb = ImRect(grab_pos - grab_sz * 0.5f, bb.Min.y + grab_padding, grab_pos + grab_sz * 0.5f, bb.Max.y - grab_padding);
            else
                *out_grab_bb = ImRect(bb.Min.x + grab_padding, grab_pos - grab_sz * 0.5f, bb.Max.x - grab_padding, grab_pos + grab_sz * 0.5f);
        }

        return value_changed;
    }

    // For 32-bit and larger types, slider bounds are limited to half the natural type range.
    // So e.g. an integer Slider between INT_MAX-10 and INT_MAX will fail, but an integer Slider between INT_MAX/2-10 and INT_MAX/2 will be ok.
    // It would be possible to lift that limitation with some work but it doesn't seem to be worth it for sliders.
    bool SliderBehavior(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, void* p_v, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb)
    {
        // Read imgui.cpp "API BREAKING CHANGES" section for 1.78 if you hit this assert.
        IM_ASSERT((flags == 1 || (flags & ImGuiSliderFlags_InvalidMask_) == 0) && "Invalid ImGuiSliderFlags flag!  Has the 'float power' argument been mistakenly cast to flags? Call function with ImGuiSliderFlags_Logarithmic flags instead.");

        // Those are the things we can do easily outside the SliderBehaviorT<> template, saves code generation.
        ImGuiContext& g = *GImGui;
        if ((g.LastItemData.InFlags & ImGuiItemFlags_ReadOnly) || (flags & ImGuiSliderFlags_ReadOnly))
            return false;

        switch (data_type)
        {
        case ImGuiDataType_S8: { ImS32 v32 = (ImS32) * (ImS8*)p_v;  bool r = SliderBehaviorT<ImS32, ImS32, float>(bb, id, ImGuiDataType_S32, &v32, *(const ImS8*)p_min, *(const ImS8*)p_max, format, flags, out_grab_bb); if (r) *(ImS8*)p_v = (ImS8)v32;  return r; }
        case ImGuiDataType_U8: { ImU32 v32 = (ImU32) * (ImU8*)p_v;  bool r = SliderBehaviorT<ImU32, ImS32, float>(bb, id, ImGuiDataType_U32, &v32, *(const ImU8*)p_min, *(const ImU8*)p_max, format, flags, out_grab_bb); if (r) *(ImU8*)p_v = (ImU8)v32;  return r; }
        case ImGuiDataType_S16: { ImS32 v32 = (ImS32) * (ImS16*)p_v; bool r = SliderBehaviorT<ImS32, ImS32, float>(bb, id, ImGuiDataType_S32, &v32, *(const ImS16*)p_min, *(const ImS16*)p_max, format, flags, out_grab_bb); if (r) *(ImS16*)p_v = (ImS16)v32; return r; }
        case ImGuiDataType_U16: { ImU32 v32 = (ImU32) * (ImU16*)p_v; bool r = SliderBehaviorT<ImU32, ImS32, float>(bb, id, ImGuiDataType_U32, &v32, *(const ImU16*)p_min, *(const ImU16*)p_max, format, flags, out_grab_bb); if (r) *(ImU16*)p_v = (ImU16)v32; return r; }
        case ImGuiDataType_S32:
            IM_ASSERT(*(const ImS32*)p_min >= IM_S32_MIN / 2 && *(const ImS32*)p_max <= IM_S32_MAX / 2);
            return SliderBehaviorT<ImS32, ImS32, float >(bb, id, data_type, (ImS32*)p_v, *(const ImS32*)p_min, *(const ImS32*)p_max, format, flags, out_grab_bb);
        case ImGuiDataType_U32:
            IM_ASSERT(*(const ImU32*)p_max <= IM_U32_MAX / 2);
            return SliderBehaviorT<ImU32, ImS32, float >(bb, id, data_type, (ImU32*)p_v, *(const ImU32*)p_min, *(const ImU32*)p_max, format, flags, out_grab_bb);
        case ImGuiDataType_S64:
            IM_ASSERT(*(const ImS64*)p_min >= IM_S64_MIN / 2 && *(const ImS64*)p_max <= IM_S64_MAX / 2);
            return SliderBehaviorT<ImS64, ImS64, double>(bb, id, data_type, (ImS64*)p_v, *(const ImS64*)p_min, *(const ImS64*)p_max, format, flags, out_grab_bb);
        case ImGuiDataType_U64:
            IM_ASSERT(*(const ImU64*)p_max <= IM_U64_MAX / 2);
            return SliderBehaviorT<ImU64, ImS64, double>(bb, id, data_type, (ImU64*)p_v, *(const ImU64*)p_min, *(const ImU64*)p_max, format, flags, out_grab_bb);
        case ImGuiDataType_Float:
            IM_ASSERT(*(const float*)p_min >= -FLT_MAX / 2.0f && *(const float*)p_max <= FLT_MAX / 2.0f);
            return SliderBehaviorT<float, float, float >(bb, id, data_type, (float*)p_v, *(const float*)p_min, *(const float*)p_max, format, flags, out_grab_bb);
        case ImGuiDataType_Double:
            IM_ASSERT(*(const double*)p_min >= -DBL_MAX / 2.0f && *(const double*)p_max <= DBL_MAX / 2.0f);
            return SliderBehaviorT<double, double, double>(bb, id, data_type, (double*)p_v, *(const double*)p_min, *(const double*)p_max, format, flags, out_grab_bb);
        case ImGuiDataType_COUNT: break;
        }
        IM_ASSERT(0);
        return false;
    }

    // Note: p_data, p_min and p_max are _pointers_ to a memory address holding the data. For a slider, they are all required.
    // Read code of e.g. SliderFloat(), SliderInt() etc. or examples in 'Demo->Widgets->Data Types' to understand how to use this function directly.
    bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const float w = GetWindowWidth() - 30;

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImRect total_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w, label_size.y + 16));
        const ImRect frame_bb(total_bb.Min + ImVec2(0, label_size.y + 10), total_bb.Max);

        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id, &frame_bb))
            return false;

        // Default format string when passing NULL
        if (format == NULL)
            format = DataTypeGetInfo(data_type)->PrintFmt;
        else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0) // (FIXME-LEGACY: Patch old "%.0f" format string to use "%d", read function more details.)
            format = PatchFormatStringFloatToInt(format);

        // Tabbing or CTRL-clicking on Slider turns it into an input box
        const bool hovered = ItemHoverable(frame_bb, id);
        const bool clicked = (hovered && g.IO.MouseClicked[0]);
        if (clicked)
        {
            SetActiveID(id, window);
            SetFocusID(id, window);
            FocusWindow(window);
            g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
        }

        ImRect grab_bb;
        const bool value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);
        if (value_changed)
            MarkItemEdited(id);

        char value_buf[64];
        const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

        //background
        window->DrawList->AddRectFilled(frame_bb.Min, frame_bb.Max, ImColor(36, 36, 36), 5.0f);

        //active slider
        window->DrawList->AddRectFilled(frame_bb.Min, ImVec2(grab_bb.Min.x + 3, frame_bb.Max.y), ImColor(255, 0, 0), 5.0f);

        //slider grab
        window->DrawList->AddCircleFilled(ImVec2(grab_bb.Min.x + 7, grab_bb.Min.y + 1), 6.0f, ImColor(255, 0, 0), 30);

        //label
        RenderText(total_bb.Min, label);

        //value
        RenderTextClipped(total_bb.Min, total_bb.Max, value_buf, value_buf_end, NULL, ImVec2(1.f, 0.f));

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
        return value_changed;
    }
    // Add multiple sliders on 1 line for compact edition of multiple components
    bool SliderScalarN(const char* label, ImGuiDataType data_type, void* v, int components, const void* v_min, const void* v_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        bool value_changed = false;
        BeginGroup();
        PushID(label);
        PushMultiItemsWidths(components, CalcItemWidth());
        size_t type_size = GDataTypeInfo[data_type].Size;
        for (int i = 0; i < components; i++)
        {
            PushID(i);
            if (i > 0)
                SameLine(0, g.Style.ItemInnerSpacing.x);
            value_changed |= SliderScalar("", data_type, v, v_min, v_max, format, flags);
            PopID();
            PopItemWidth();
            v = (void*)((char*)v + type_size);
        }
        PopID();

        const char* label_end = FindRenderedTextEnd(label);
        if (label != label_end)
        {
            SameLine(0, g.Style.ItemInnerSpacing.x);
            TextEx(label, label_end);
        }

        EndGroup();
        return value_changed;
    }

    bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
    }

    bool SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalarN(label, ImGuiDataType_Float, v, 2, &v_min, &v_max, format, flags);
    }

    bool SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalarN(label, ImGuiDataType_Float, v, 3, &v_min, &v_max, format, flags);
    }

    bool SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalarN(label, ImGuiDataType_Float, v, 4, &v_min, &v_max, format, flags);
    }

    bool SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, ImGuiSliderFlags flags)
    {
        if (format == NULL)
            format = "%.0f deg";
        float v_deg = (*v_rad) * 360.0f / (2 * IM_PI);
        bool value_changed = SliderFloat(label, &v_deg, v_degrees_min, v_degrees_max, format, flags);
        *v_rad = v_deg * (2 * IM_PI) / 360.0f;
        return value_changed;
    }

    bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
    }

    bool SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalarN(label, ImGuiDataType_S32, v, 2, &v_min, &v_max, format, flags);
    }

    bool SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalarN(label, ImGuiDataType_S32, v, 3, &v_min, &v_max, format, flags);
    }

    bool SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return SliderScalarN(label, ImGuiDataType_S32, v, 4, &v_min, &v_max, format, flags);
    }

    bool VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
        const ImRect bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(frame_bb, id))
            return false;

        // Default format string when passing NULL
        if (format == NULL)
            format = DataTypeGetInfo(data_type)->PrintFmt;

        const bool hovered = ItemHoverable(frame_bb, id);
        const bool clicked = hovered && IsMouseClicked(0, id);
        if (clicked || g.NavActivateId == id)
        {
            if (clicked)
                SetKeyOwner(ImGuiKey_MouseLeft, id);
            SetActiveID(id, window);
            SetFocusID(id, window);
            FocusWindow(window);
            g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Up) | (1 << ImGuiDir_Down);
        }

        // Draw frame
        const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
        RenderNavHighlight(frame_bb, id);
        RenderFrame(frame_bb.Min, frame_bb.Max, frame_col, true, g.Style.FrameRounding);

        // Slider behavior
        ImRect grab_bb;
        const bool value_changed = SliderBehavior(frame_bb, id, data_type, p_data, p_min, p_max, format, flags | ImGuiSliderFlags_Vertical, &grab_bb);
        if (value_changed)
            MarkItemEdited(id);

        // Render grab
        if (grab_bb.Max.y > grab_bb.Min.y)
            window->DrawList->AddRectFilled(grab_bb.Min, grab_bb.Max, GetColorU32(g.ActiveId == id ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab), style.GrabRounding);

        // Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
        // For the vertical slider we allow centered text to overlap the frame padding
        char value_buf[64];
        const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);
        RenderTextClipped(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), frame_bb.Max, value_buf, value_buf_end, NULL, ImVec2(0.5f, 0.0f));
        if (label_size.x > 0.0f)
            RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, frame_bb.Min.y + style.FramePadding.y), label);

        return value_changed;
    }

    bool VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
    {
        return VSliderScalar(label, size, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
    }

    bool VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
    {
        return VSliderScalar(label, size, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
    }

    map<ImGuiID, container> Switchboxanim;
    bool Switchbox(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        const float square_sz = 19, checkmark = 10.f;
        const float w = (GetContentRegionMax().x - style.WindowPadding.x) - square_sz;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect total_bb(pos, pos + ImVec2(square_sz + label_size.x + w, label_size.y));

        ItemSize(ImRect(total_bb.Min, total_bb.Max - ImVec2(0, 1)));

        if (!ItemAdd(total_bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(total_bb, id, &hovered, &held);

        if (IsItemClicked())
        {
            *v = !(*v);
            MarkItemEdited(id);
        }

        auto it_anim = Switchboxanim.find(id);

        if (it_anim == Switchboxanim.end())
        {
            Switchboxanim.insert({ id, container() });
            it_anim = Switchboxanim.find(id);
        }


        it_anim->second.circle_checkbox = ImLerp(it_anim->second.circle_checkbox, *v ? 19.f : 0.f, g.IO.DeltaTime * 8.f);
        it_anim->second.background = ImLerp(it_anim->second.background, *v ? accent_color : hovered ? checkbox::bg_hov : checkbox::bg, g.IO.DeltaTime * 8.f);
        it_anim->second.clip_mark = ImLerp(it_anim->second.clip_mark, *v ? checkmark : 0.f, g.IO.DeltaTime * 8.f);
        it_anim->second.text = ImLerp(it_anim->second.text, *v ? text::text_active : hovered ? text::text_hov : text::text, g.IO.DeltaTime * 8.f);

        const ImRect check_bb(pos, pos + ImVec2(square_sz, square_sz));

        GetWindowDrawList()->AddRect(check_bb.Min + ImVec2(w - 20, 1), check_bb.Max + ImVec2(w, 1), GetColorU32(checkbox::bg), 100.f, ImDrawFlags_None, 2.5f);

        GetForegroundDrawList()->AddCircleFilled(check_bb.Min + ImVec2(w - 10 + it_anim->second.circle_checkbox, 10.2f), 5.5f, GetColorU32(it_anim->second.background), 100.f);

        if (*v && IsRectVisible(check_bb.Min + ImVec2(w, 0), check_bb.Max + ImVec2(w, 0)))
            GetForegroundDrawList()->AddShadowCircle(check_bb.Min + ImVec2(w - 10 + it_anim->second.circle_checkbox, 10), 3.f, GetColorU32(it_anim->second.background), 25.f, ImVec2(0, 0), ImDrawFlags_None, 100.f);

        ImGui::GetWindowDrawList()->AddText(ImVec2(check_bb.Max.x - square_sz, check_bb.Min.y - 1), GetColorU32(it_anim->second.text), label);

        return pressed;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // SLIDER
    ////////////////////////////////////////////////////////////////////////////////////////////
    IMGUI_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.1f", ImGuiSliderFlags flags = 0);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display.



    ////////////////////////////////////////////////////////////////////////////////////////////
    // COMBO
    ////////////////////////////////////////////////////////////////////////////////////////////

    // Getter for the old Combo() API: "item1\0item2\0item3\0"

    static float CalcMaxPopupHeightFromItemCount(int items_count)
    {
        ImGuiContext& g = *GImGui;
        if (items_count <= 0)
            return FLT_MAX;
        return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
    }

    std::map<ImGuiID, container> combonewsexyhottie;
    int num_options;

    bool BeginCombo(const char* label, const char* preview_value, float val, ImGuiComboFlags flags, int num_options)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = GetCurrentWindow();

        SetCursorPos(GetCursorPos() + ImVec2(-1, 25));

        ImGuiNextWindowDataFlags backup_next_window_data_flags = g.NextWindowData.Flags;
        g.NextWindowData.ClearFlags(); // We behave like Begin() and need to consume those values
        if (window->SkipItems)
            return false;

        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        IM_ASSERT((flags & (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)) != (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)); // Can't use both flags together

        const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : GetFrameHeight();
        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const float w = (flags & ImGuiComboFlags_NoPreview) ? arrow_size : CalcItemWidth() - 5;
        const ImRect bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(w + 54, label_size.y + style.FramePadding.y * 7.0f));
        const ImRect total_bb(bb.Min, bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
        ItemSize(total_bb, style.FramePadding.y);
        if (!ItemAdd(total_bb, id, &bb))
            return false;

        // Open on click
        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held);
        const ImGuiID popup_id = ImHashStr("##ComboPopup", 0, id);

        auto it_anim = combonewsexyhottie.find(id);

        if (it_anim == combonewsexyhottie.end())
        {
            combonewsexyhottie.insert({ id, container() });
            it_anim = combonewsexyhottie.find(id);
        }

        if (hovered && g.IO.MouseClicked[0] || it_anim->second.opened_combo && g.IO.MouseClicked[0] && !it_anim->second.hovered)
            it_anim->second.opened_combo = !it_anim->second.opened_combo;

        it_anim->second.combo_size = ImLerp(it_anim->second.combo_size, it_anim->second.opened_combo ? 17 * val * 1 : 0.f, g.IO.DeltaTime * 8.f);

        const float value_x2 = ImMax(bb.Min.x, bb.Max.x - arrow_size);
        const int vtx_idx_1 = ImGui::GetWindowDrawList()->VtxBuffer.Size;
        window->DrawList->AddRectFilled(bb.Min, ImVec2(value_x2 + 21, bb.Max.y), ImColor(30, 30, 30), style.FrameRounding);



        RenderTextClipped(bb.Min + ImVec2(9, 10), ImVec2(value_x2, bb.Max.y + 5), preview_value, NULL, NULL);

        PushFont(g_menu::arrow);
        RenderTextClipped(bb.Min + ImVec2(w + 25, 10), ImVec2(value_x2 + 20, bb.Max.y + 5), "E", NULL, NULL);
        PopFont();

        window->DrawList->AddText(ImVec2(bb.Max.x - w - 51, bb.Min.y - 25), GetColorU32(ImGuiCol_Text), label);

        if (!it_anim->second.opened_combo && it_anim->second.combo_size < 2.f)
            return false;

        ImGui::SetNextWindowPos(ImVec2(bb.Min.x, bb.Max.y + 4));

        float dropdown_height = ImGui::GetFrameHeight() * num_options;

        // Set the size of the dropdown window dynamically
        ImGui::SetNextWindowSize(ImVec2(bb.GetWidth(), dropdown_height));


        ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoFocusOnAppearing;
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(g.Style.FramePadding.x, g.Style.WindowPadding.y + 9));
        PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(30, 30, 30)));
        bool ret = Begin(label, NULL, window_flags);
        PopStyleVar(1);
        PopStyleColor();

        it_anim->second.hovered = IsWindowHovered();

        return true;
    }
    bool BeginComboPopup(ImGuiID popup_id, const ImRect& bb, ImGuiComboFlags flags)
    {
        ImGuiContext& g = *GImGui;
        if (!IsPopupOpen(popup_id, ImGuiPopupFlags_None))
        {
            g.NextWindowData.ClearFlags();
            return false;
        }

        // Set popup size
        float w = bb.GetWidth();
        if (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint)
        {
            g.NextWindowData.SizeConstraintRect.Min.x = ImMax(g.NextWindowData.SizeConstraintRect.Min.x, w);
        }
        else
        {
            if ((flags & ImGuiComboFlags_HeightMask_) == 0)
                flags |= ImGuiComboFlags_HeightRegular;
            IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiComboFlags_HeightMask_)); // Only one
            int popup_max_height_in_items = -1;
            if (flags & ImGuiComboFlags_HeightRegular)     popup_max_height_in_items = 8;
            else if (flags & ImGuiComboFlags_HeightSmall)  popup_max_height_in_items = 4;
            else if (flags & ImGuiComboFlags_HeightLarge)  popup_max_height_in_items = 20;
            ImVec2 constraint_min(0.0f, 0.0f), constraint_max(FLT_MAX, FLT_MAX);
            if ((g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSize) == 0 || g.NextWindowData.SizeVal.x <= 0.0f) // Don't apply constraints if user specified a size
                constraint_min.x = w;
            if ((g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSize) == 0 || g.NextWindowData.SizeVal.y <= 0.0f)
                constraint_max.y = CalcMaxPopupHeightFromItemCount(popup_max_height_in_items);
            SetNextWindowSizeConstraints(constraint_min, constraint_max);
        }

        // This is essentially a specialized version of BeginPopupEx()
        char name[16];
        ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size); // Recycle windows based on depth

        // Set position given a custom constraint (peak into expected window size so we can position it)
        // FIXME: This might be easier to express with an hypothetical SetNextWindowPosConstraints() function?
        // FIXME: This might be moved to Begin() or at least around the same spot where Tooltips and other Popups are calling FindBestWindowPosForPopupEx()?
        if (ImGuiWindow* popup_window = FindWindowByName(name))
            if (popup_window->WasActive)
            {
                // Always override 'AutoPosLastDirection' to not leave a chance for a past value to affect us.
                ImVec2 size_expected = CalcWindowNextAutoFitSize(popup_window);
                popup_window->AutoPosLastDirection = (flags & ImGuiComboFlags_PopupAlignLeft) ? ImGuiDir_Left : ImGuiDir_Down; // Left = "Below, Toward Left", Down = "Below, Toward Right (default)"
                ImRect r_outer = GetPopupAllowedExtentRect(popup_window);
                ImVec2 pos = FindBestWindowPosForPopupEx(bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, bb, ImGuiPopupPositionPolicy_ComboBox);
                SetNextWindowPos(pos);
            }

        // We don't use BeginPopupEx() solely because we have a custom name string, which we could make an argument to BeginPopupEx()
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(g.Style.FramePadding.x, g.Style.WindowPadding.y)); // Horizontally align ourselves with the framed text
        bool ret = Begin(name, NULL, window_flags);
        PopStyleVar();
        if (!ret)
        {
            EndPopup();
            IM_ASSERT(0);   // This should never happen as we tested for IsPopupOpen() above
            return false;
        }
        return true;
    }

    void EndCombo()
    {
        End();
    }

    // Call directly after the BeginCombo/EndCombo block. The preview is designed to only host non-interactive elements
    // (Experimental, see GitHub issues: #1658, #4168)
    bool BeginComboPreview()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        ImGuiComboPreviewData* preview_data = &g.ComboPreviewData;

        if (window->SkipItems || !(g.LastItemData.StatusFlags & ImGuiItemStatusFlags_Visible))
            return false;
        IM_ASSERT(g.LastItemData.Rect.Min.x == preview_data->PreviewRect.Min.x && g.LastItemData.Rect.Min.y == preview_data->PreviewRect.Min.y); // Didn't call after BeginCombo/EndCombo block or forgot to pass ImGuiComboFlags_CustomPreview flag?
        if (!window->ClipRect.Overlaps(preview_data->PreviewRect)) // Narrower test (optional)
            return false;

        // FIXME: This could be contained in a PushWorkRect() api
        preview_data->BackupCursorPos = window->DC.CursorPos;
        preview_data->BackupCursorMaxPos = window->DC.CursorMaxPos;
        preview_data->BackupCursorPosPrevLine = window->DC.CursorPosPrevLine;
        preview_data->BackupPrevLineTextBaseOffset = window->DC.PrevLineTextBaseOffset;
        preview_data->BackupLayout = window->DC.LayoutType;
        window->DC.CursorPos = preview_data->PreviewRect.Min + g.Style.FramePadding;
        window->DC.CursorMaxPos = window->DC.CursorPos;
        window->DC.LayoutType = ImGuiLayoutType_Horizontal;
        window->DC.IsSameLine = false;
        PushClipRect(preview_data->PreviewRect.Min, preview_data->PreviewRect.Max, true);

        return true;
    }

    void EndComboPreview()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        ImGuiComboPreviewData* preview_data = &g.ComboPreviewData;

        // FIXME: Using CursorMaxPos approximation instead of correct AABB which we will store in ImDrawCmd in the future
        ImDrawList* draw_list = window->DrawList;
        if (window->DC.CursorMaxPos.x < preview_data->PreviewRect.Max.x && window->DC.CursorMaxPos.y < preview_data->PreviewRect.Max.y)
            if (draw_list->CmdBuffer.Size > 1) // Unlikely case that the PushClipRect() didn't create a command
            {
                draw_list->_CmdHeader.ClipRect = draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 1].ClipRect = draw_list->CmdBuffer[draw_list->CmdBuffer.Size - 2].ClipRect;
                draw_list->_TryMergeDrawCmds();
            }
        PopClipRect();
        window->DC.CursorPos = preview_data->BackupCursorPos;
        window->DC.CursorMaxPos = ImMax(window->DC.CursorMaxPos, preview_data->BackupCursorMaxPos);
        window->DC.CursorPosPrevLine = preview_data->BackupCursorPosPrevLine;
        window->DC.PrevLineTextBaseOffset = preview_data->BackupPrevLineTextBaseOffset;
        window->DC.LayoutType = preview_data->BackupLayout;
        window->DC.IsSameLine = false;
        preview_data->PreviewRect = ImRect();
    }

    // Getter for the old Combo() API: const char*[]
    static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
    {
        const char* const* items = (const char* const*)data;
        if (out_text)
            *out_text = items[idx];
        return true;
    }

    // Getter for the old Combo() API: "item1\0item2\0item3\0"
    static bool Items_SingleStringGetter(void* data, int idx, const char** out_text)
    {
        // FIXME-OPT: we could pre-compute the indices to fasten this. But only 1 active combo means the waste is limited.
        const char* items_separated_by_zeros = (const char*)data;
        int items_count = 0;
        const char* p = items_separated_by_zeros;
        while (*p)
        {
            if (idx == items_count)
                break;
            p += strlen(p) + 1;
            items_count++;
        }
        if (!*p)
            return false;
        if (out_text)
            *out_text = p;
        return true;
    }

    // Old API, prefer using BeginCombo() nowadays if you can.
    bool Combo(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int popup_max_height_in_items)
    {
        ImGuiContext& g = *GImGui;

        // Call the getter to obtain the preview string which is a parameter to BeginCombo()
        const char* preview_value = NULL;
        if (*current_item >= 0 && *current_item < items_count)
            items_getter(data, *current_item, &preview_value);

        // The old Combo() API exposed "popup_max_height_in_items". The new more general BeginCombo() API doesn't have/need it, but we emulate it here.
        if (popup_max_height_in_items != -1 && !(g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint))
            SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));

        if (!BeginCombo(label, preview_value, popup_max_height_in_items, ImGuiComboFlags_None, num_options))
            return false;

        // Display items
        // FIXME-OPT: Use clipper (but we need to disable it on the appearing frame to make sure our call to SetItemDefaultFocus() is processed)
        bool value_changed = false;
        PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 18));
        for (int i = 0; i < items_count; i++)
        {
            PushID(i);
            const bool item_selected = (i == *current_item);
            const char* item_text;
            if (!items_getter(data, i, &item_text))
                item_text = "*Unknown item*";
            if (Selectable(item_text, item_selected))
            {
                value_changed = true;
                *current_item = i;
            }
            if (item_selected)
                SetItemDefaultFocus();
            PopID();
        }
        PopStyleVar(1);
        EndCombo();

        if (value_changed)
            MarkItemEdited(g.LastItemData.ID);

        return value_changed;
    }
    // Combo box helper allowing to pass an array of strings.
    bool Combo(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
    {
        const bool value_changed = Combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
        return value_changed;
    }

    // Combo box helper allowing to pass all items in a single string literal holding multiple zero-terminated items "item1\0item2\0"
    bool Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
    {
        int items_count = 0;
        const char* p = items_separated_by_zeros;       // FIXME-OPT: Avoid computing this, or at least only when combo is open
        while (*p)
        {
            p += strlen(p) + 1;
            items_count++;
        }
        bool value_changed = Combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
        return value_changed;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // COLORPICKER
    ////////////////////////////////////////////////////////////////////////////////////////////

    static void ColorEditRestoreHS(const float* col, float* H, float* S, float* V)
    {
        ImGuiContext& g = *GImGui;
        IM_ASSERT(g.ColorEditCurrentID != 0);
        if (g.ColorEditSavedID != g.ColorEditCurrentID || g.ColorEditSavedColor != ImGui::ColorConvertFloat4ToU32(ImVec4(col[0], col[1], col[2], 0)))
            return;

        // When S == 0, H is undefined.
        // When H == 1 it wraps around to 0.
        if (*S == 0.0f || (*H == 0.0f && g.ColorEditSavedHue == 1))
            *H = g.ColorEditSavedHue;

        // When V == 0, S is undefined.
        if (*V == 0.0f)
            *S = g.ColorEditSavedSat;
    }

    bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const float square_sz = GetFrameHeight();
        const float w_full = CalcItemWidth();
        const float w_button = (flags & ImGuiColorEditFlags_NoSmallPreview) ? 0.0f : (square_sz + style.ItemInnerSpacing.x);
        const float w_inputs = w_full - w_button;
        const char* label_display_end = FindRenderedTextEnd(label);
        g.NextItemData.ClearFlags();

        BeginGroup();
        PushID(label);
        const bool set_current_color_edit_id = (g.ColorEditCurrentID == 0);
        if (set_current_color_edit_id)
            g.ColorEditCurrentID = window->IDStack.back();

        // If we're not showing any slider there's no point in doing any HSV conversions
        const ImGuiColorEditFlags flags_untouched = flags;
        if (flags & ImGuiColorEditFlags_NoInputs)
            flags = (flags & (~ImGuiColorEditFlags_DisplayMask_)) | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoOptions;

        // Context menu: display and modify options (before defaults are applied)
        if (!(flags & ImGuiColorEditFlags_NoOptions))
            ColorEditOptionsPopup(col, flags);

        // Read stored options
        if (!(flags & ImGuiColorEditFlags_DisplayMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DisplayMask_);
        if (!(flags & ImGuiColorEditFlags_DataTypeMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_DataTypeMask_);
        if (!(flags & ImGuiColorEditFlags_PickerMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_PickerMask_);
        if (!(flags & ImGuiColorEditFlags_InputMask_))
            flags |= (g.ColorEditOptions & ImGuiColorEditFlags_InputMask_);
        flags |= (g.ColorEditOptions & ~(ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_));
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_DisplayMask_)); // Check that only 1 is selected
        IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiColorEditFlags_InputMask_));   // Check that only 1 is selected

        const bool alpha = (flags & ImGuiColorEditFlags_NoAlpha) == 0;
        const bool hdr = (flags & ImGuiColorEditFlags_HDR) != 0;
        const int components = alpha ? 4 : 3;

        // Convert to the formats we need
        float f[4] = { col[0], col[1], col[2], alpha ? col[3] : 1.0f };
        if ((flags & ImGuiColorEditFlags_InputHSV) && (flags & ImGuiColorEditFlags_DisplayRGB))
            ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
        else if ((flags & ImGuiColorEditFlags_InputRGB) && (flags & ImGuiColorEditFlags_DisplayHSV))
        {
            // Hue is lost when converting from grayscale rgb (saturation=0). Restore it.
            ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);
            ColorEditRestoreHS(col, &f[0], &f[1], &f[2]);
        }
        int i[4] = { IM_F32_TO_INT8_UNBOUND(f[0]), IM_F32_TO_INT8_UNBOUND(f[1]), IM_F32_TO_INT8_UNBOUND(f[2]), IM_F32_TO_INT8_UNBOUND(f[3]) };

        bool value_changed = false;
        bool value_changed_as_float = false;

        const ImVec2 pos = window->DC.CursorPos;
        const float inputs_offset_x = (style.ColorButtonPosition == ImGuiDir_Left) ? w_button : 0.0f;
        window->DC.CursorPos.x = pos.x + inputs_offset_x;

        if ((flags & (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV)) != 0 && (flags & ImGuiColorEditFlags_NoInputs) == 0)
        {
            // RGB/HSV 0..255 Sliders
            const float w_item_one = ImMax(1.0f, IM_FLOOR((w_inputs - (style.ItemInnerSpacing.x) * (components - 1)) / (float)components));
            const float w_item_last = ImMax(1.0f, IM_FLOOR(w_inputs - (w_item_one + style.ItemInnerSpacing.x) * (components - 1)));

            const bool hide_prefix = (w_item_one <= CalcTextSize((flags & ImGuiColorEditFlags_Float) ? "M:0.000" : "M:000").x);
            static const char* ids[4] = { "##X", "##Y", "##Z", "##W" };
            static const char* fmt_table_int[3][4] =
            {
                {   "%3d",   "%3d",   "%3d",   "%3d" }, // Short display
                { "R:%3d", "G:%3d", "B:%3d", "A:%3d" }, // Long display for RGBA
                { "H:%3d", "S:%3d", "V:%3d", "A:%3d" }  // Long display for HSVA
            };
            static const char* fmt_table_float[3][4] =
            {
                {   "%0.3f",   "%0.3f",   "%0.3f",   "%0.3f" }, // Short display
                { "R:%0.3f", "G:%0.3f", "B:%0.3f", "A:%0.3f" }, // Long display for RGBA
                { "H:%0.3f", "S:%0.3f", "V:%0.3f", "A:%0.3f" }  // Long display for HSVA
            };
            const int fmt_idx = hide_prefix ? 0 : (flags & ImGuiColorEditFlags_DisplayHSV) ? 2 : 1;

            for (int n = 0; n < components; n++)
            {
                if (n > 0)
                    SameLine(0, style.ItemInnerSpacing.x);
                SetNextItemWidth((n + 1 < components) ? w_item_one : w_item_last);

                // FIXME: When ImGuiColorEditFlags_HDR flag is passed HS values snap in weird ways when SV values go below 0.
                if (flags & ImGuiColorEditFlags_Float)
                {
                    value_changed |= DragFloat(ids[n], &f[n], 1.0f / 255.0f, 0.0f, hdr ? 0.0f : 1.0f, fmt_table_float[fmt_idx][n]);
                    value_changed_as_float |= value_changed;
                }
                else
                {
                    value_changed |= DragInt(ids[n], &i[n], 1.0f, 0, hdr ? 0 : 255, fmt_table_int[fmt_idx][n]);
                }
                if (!(flags & ImGuiColorEditFlags_NoOptions))
                    OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
            }
        }
        else if ((flags & ImGuiColorEditFlags_DisplayHex) != 0 && (flags & ImGuiColorEditFlags_NoInputs) == 0)
        {
            // RGB Hexadecimal Input
            char buf[64];
            if (alpha)
                ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255), ImClamp(i[3], 0, 255));
            else
                ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255));
            SetNextItemWidth(w_inputs);

            if (!(flags & ImGuiColorEditFlags_NoOptions))
                OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);
        }

        ImGuiWindow* picker_active_window = NULL;
        if (!(flags & ImGuiColorEditFlags_NoSmallPreview))
        {
            const float button_offset_x = ((flags & ImGuiColorEditFlags_NoInputs) || (style.ColorButtonPosition == ImGuiDir_Left)) ? 0.0f : w_inputs + style.ItemInnerSpacing.x;
            window->DC.CursorPos = ImVec2(pos.x + button_offset_x, pos.y);

            const ImVec4 col_v4(col[0], col[1], col[2], alpha ? col[3] : 1.0f);
            if (ColorButton("##ColorButton", col_v4, flags))
            {
                if (!(flags & ImGuiColorEditFlags_NoPicker))
                {
                    // Store current color and open a picker
                    g.ColorPickerRef = col_v4;
                    OpenPopup("picker");
                    SetNextWindowPos(g.LastItemData.Rect.GetBL() + ImVec2(0.0f, style.ItemSpacing.y));
                }
            }
            if (!(flags & ImGuiColorEditFlags_NoOptions))
                OpenPopupOnItemClick("context", ImGuiPopupFlags_MouseButtonRight);

            PushStyleColor(ImGuiCol_PopupBg, GetColorU32(picker::bg));
            PushStyleVar(ImGuiStyleVar_PopupRounding, (picker::rounding));

            if (BeginPopup("picker"))
            {
                if (g.CurrentWindow->BeginCount == 1)
                {
                    picker_active_window = g.CurrentWindow;

                    ImGuiColorEditFlags picker_flags_to_forward = ImGuiColorEditFlags_DataTypeMask_ | ImGuiColorEditFlags_PickerMask_ | ImGuiColorEditFlags_InputMask_ | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_AlphaBar;
                    ImGuiColorEditFlags picker_flags = (flags_untouched & picker_flags_to_forward) | ImGuiColorEditFlags_DisplayMask_ | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf;
                    SetNextItemWidth(square_sz * 12.0f); // Use 256 + bar sizes?
                    value_changed |= ColorPicker4("##picker", col, picker_flags, &g.ColorPickerRef.x);
                }
                EndPopup();
            }
        }

        PopStyleVar(1);
        PopStyleColor(1);

        char buf[64];

        SameLine(0.0f, style.ItemInnerSpacing.x);
        window->DC.CursorPos.x = pos.x + ((flags & ImGuiColorEditFlags_NoInputs) ? w_button : w_full + style.ItemInnerSpacing.x);

        if (label != label_display_end && !(flags & ImGuiColorEditFlags_NoLabel)) GetWindowDrawList()->AddText(window->DC.CursorPos - ImVec2(w_button, -1), GetColorU32(text::text), label);

        ImFormatString(buf, IM_ARRAYSIZE(buf), "#%02X%02X%02X", ImClamp(i[0], 0, 255), ImClamp(i[1], 0, 255), ImClamp(i[2], 0, 255));
        // GetWindowDrawList()->AddText(window->DC.CursorPos + ImVec2(GetWindowContentRegionMax().x - 140, 1), GetColorU32(text::text), buf);

        PushStyleColor(ImGuiCol_Text, GetColorU32(text::text));
        ImGui::RenderTextClipped(window->DC.CursorPos + ImVec2(GetWindowContentRegionMax().x - 350, 0), window->DC.CursorPos + ImVec2(GetWindowContentRegionMax().x - 80, 19), buf, NULL, NULL, ImVec2(1.0f, 0.5f));
        PopStyleColor();

        // Convert back
        if (value_changed && picker_active_window == NULL)
        {
            if (!value_changed_as_float)
                for (int n = 0; n < 4; n++)
                    f[n] = i[n] / 255.0f;
            if ((flags & ImGuiColorEditFlags_DisplayHSV) && (flags & ImGuiColorEditFlags_InputRGB))
            {
                g.ColorEditSavedHue = f[0];
                g.ColorEditSavedSat = f[1];
                ColorConvertHSVtoRGB(f[0], f[1], f[2], f[0], f[1], f[2]);
                g.ColorEditSavedID = g.ColorEditCurrentID;
                g.ColorEditSavedColor = ColorConvertFloat4ToU32(ImVec4(f[0], f[1], f[2], 0));
            }
            if ((flags & ImGuiColorEditFlags_DisplayRGB) && (flags & ImGuiColorEditFlags_InputHSV))
                ColorConvertRGBtoHSV(f[0], f[1], f[2], f[0], f[1], f[2]);

            col[0] = f[0];
            col[1] = f[1];
            col[2] = f[2];
            if (alpha)
                col[3] = f[3];
        }

        if (set_current_color_edit_id)
            g.ColorEditCurrentID = 0;
        PopID();
        EndGroup();

        // Drag and Drop Target
        // NB: The flag test is merely an optional micro-optimization, BeginDragDropTarget() does the same test.
        if ((g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect) && !(flags & ImGuiColorEditFlags_NoDragDrop) && BeginDragDropTarget())
        {
            bool accepted_drag_drop = false;
            if (const ImGuiPayload* payload = AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
            {
                memcpy((float*)col, payload->Data, sizeof(float) * 3); // Preserve alpha if any //-V512 //-V1086
                value_changed = accepted_drag_drop = true;
            }
            if (const ImGuiPayload* payload = AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
            {
                memcpy((float*)col, payload->Data, sizeof(float) * components);
                value_changed = accepted_drag_drop = true;
            }

            // Drag-drop payloads are always RGB
            if (accepted_drag_drop && (flags & ImGuiColorEditFlags_InputHSV))
                ColorConvertRGBtoHSV(col[0], col[1], col[2], col[0], col[1], col[2]);
            EndDragDropTarget();
        }

        // When picker is being actively used, use its active id so IsItemActive() will function on ColorEdit4().
        if (picker_active_window && g.ActiveId != 0 && g.ActiveIdWindow == picker_active_window)
            g.LastItemData.ID = g.ActiveId;

        if (value_changed && g.LastItemData.ID != 0) // In case of ID collision, the second EndGroup() won't catch g.ActiveId
            MarkItemEdited(g.LastItemData.ID);

        return value_changed;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // BEGINCHILD
    std::map<ImGuiID, container> tabanimmmnnnnnnnnwwwwwwwwww;


    std::map<ImGuiID, container> tabanimmmnnnnnnnn22222222222222211;

    bool Tab(const char* label, bool active)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect rect(pos, pos + ImVec2(50, 35));
        ItemSize(rect, style.FramePadding.y);
        if (!ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(rect, id, &hovered, &held);
        if (pressed)
            MarkItemEdited(id);

        auto it_anim = tabanimmmnnnnnnnn22222222222222211.find(id);

        if (it_anim == tabanimmmnnnnnnnn22222222222222211.end())
        {
            tabanimmmnnnnnnnn22222222222222211.insert({ id, container() });
            it_anim = tabanimmmnnnnnnnn22222222222222211.find(id);
        }


        it_anim->second.text = ImLerp(it_anim->second.text2, active ? ImColor(255, 255, 255) : hovered ? ImColor(71, 71, 73) : ImColor(71, 71, 73), g.IO.DeltaTime * 6.f);
        it_anim->second.bg = ImLerp(it_anim->second.bg, active ? ImColor(20, 20, 20) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);
        it_anim->second.bg2 = ImLerp(it_anim->second.bg2, active ? ImColor(accentcolor) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);

        window->DrawList->AddRectFilled(rect.Min + ImVec2(10, 5), rect.Min + ImVec2(130, 35), ImColor(it_anim->second.bg), 3);
        window->DrawList->AddRectFilled(rect.Min + ImVec2(0, 10), rect.Min + ImVec2(2.5f, 30), ImColor(it_anim->second.bg2), 10, ImDrawCornerFlags_Right);
        window->DrawList->AddText(g_menu::menu_font2, 18, rect.Min + ImVec2(40, 10), ImColor(it_anim->second.text2), label);
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
    }


    std::map<ImGuiID, container> tabanimmmmmmm22221112xx22111xx;
    bool TextLine(const char* label)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect rect(pos, pos + ImVec2(50, 30));
        ItemSize(rect, style.FramePadding.y);
        if (!ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(rect, id, &hovered, &held);
        if (pressed)
            MarkItemEdited(id);

        auto it_anim = tabanimmmmmmm22221112xx22111xx.find(id);

        if (it_anim == tabanimmmmmmm22221112xx22111xx.end())
        {
            tabanimmmmmmm22221112xx22111xx.insert({ id, container() });
            it_anim = tabanimmmmmmm22221112xx22111xx.find(id);
        }

        window->DrawList->AddText(g_menu::menu_font2, 18, rect.Min + ImVec2(10, 5), ImColor(140, 140, 140), label);
        float xOffset = 25; // Adjust this offset value as needed
        window->DrawList->AddRectFilled(rect.Min + ImVec2(ImGui::CalcTextSize(label).x + xOffset, 13), rect.Min + ImVec2(110 + xOffset, 15), ImColor(15, 15, 15), 12);
        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;
    }


    std::map<ImGuiID, container> tabanimmmmmmm22221112xx;
    bool Checkbox1(const char* label, bool* v)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, 0, 1);

        const float square_sz = 16.f;
        const float ROUNDING = 4.f;
        const ImVec2 pos = window->DC.CursorPos;
        const ImRect frame_bb(pos, pos + ImVec2(square_sz, square_sz));
        const ImRect total_bb(pos, pos + ImVec2(square_sz + label_size.x + style.ItemInnerSpacing.x + 2, square_sz));
        ItemAdd(total_bb, id, &frame_bb);
        ItemSize(total_bb, style.FramePadding.y);

        bool hovered, held;
        bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);
        if (pressed) {

            *v = !(*v);
            MarkItemEdited(id);
        }

        auto it_anim = tabanimmmmmmm22221112xx.find(id);

        if (it_anim == tabanimmmmmmm22221112xx.end())
        {
            tabanimmmmmmm22221112xx.insert({ id, container() });
            it_anim = tabanimmmmmmm22221112xx.find(id);
        }

        it_anim->second.checkmark1 = ImLerp(it_anim->second.checkmark1, *v ? ImColor(1, 1, 1) : hovered ? ImColor(71, 71, 73) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 4.f);
        it_anim->second.framecol = ImLerp(it_anim->second.framecol, *v ? ImColor(accentcolor) : hovered ? ImColor(30, 30, 30) : ImColor(25, 25, 25), g.IO.DeltaTime * 4.f);


        RenderFrame(frame_bb.Min, frame_bb.Max, ImColor(it_anim->second.framecol), 0, ROUNDING);
        RenderCheckMark(window->DrawList, frame_bb.GetCenter() - ImVec2((square_sz / 2 + 1) / 2, (square_sz / 2 + 1) / 2), GetColorU32(it_anim->second.checkmark1), square_sz / 2 + 1);

        ImVec2 label_pos = ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x + 3, frame_bb.GetCenter().y - label_size.y + 28 / 2);
        if (label_size.x > 0.f)
            ImGui::PushFont(g_menu::Regylar);
        RenderText(label_pos, label);
        ImGui::PopFont();
        return pressed;
    }

    template<typename T>
    bool CheckboxFlagsT(const char* label, T* flags, T flags_value)
    {
        bool all_on = (*flags & flags_value) == flags_value;
        bool any_on = (*flags & flags_value) != 0;
        bool pressed;
        if (!all_on && any_on)
        {
            ImGuiContext& g = *GImGui;
            ImGuiItemFlags backup_item_flags = g.CurrentItemFlags;
            g.CurrentItemFlags |= ImGuiItemFlags_MixedValue;
            pressed = Checkbox(label, &all_on);
            g.CurrentItemFlags = backup_item_flags;
        }
        else
        {
            pressed = Checkbox(label, &all_on);

        }
        if (pressed)
        {
            if (all_on)
                *flags |= flags_value;
            else
                *flags &= ~flags_value;
        }
        return pressed;
    }

    // 
    ////////////////////////////////////////////////////////////////////////////////////////////

    bool BeginChildEx(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* parent_window = g.CurrentWindow;

        flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
        flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

        // Size
        const ImVec2 content_avail = GetContentRegionAvail();
        ImVec2 size = ImFloor(size_arg);
        const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
        if (size.x <= 0.0f)
            size.x = ImMax(content_avail.x + size.x, 4.0f);
        if (size.y <= 0.0f)
            size.y = ImMax(content_avail.y + size.y, 4.0f);
        SetNextWindowPos(ImVec2(parent_window->DC.CursorPos + ImVec2(0, 35)));
        SetNextWindowSize(ImVec2(size.x, (size.y - 35)));

        GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos + ImVec2(0, 0), parent_window->DC.CursorPos + ImVec2(size_arg.x, size_arg.y), GetColorU32(child::bg), child::rounding);
        GetWindowDrawList()->AddRect(parent_window->DC.CursorPos + ImVec2(0, 0), parent_window->DC.CursorPos + ImVec2(size_arg), GetColorU32(child::border), child::rounding, ImDrawFlags_None, 1.f);

        GetWindowDrawList()->AddLine(parent_window->DC.CursorPos + ImVec2(0, 35), parent_window->DC.CursorPos + ImVec2(size_arg.x, 35), GetColorU32(child::line), 1.f);

        ImGui::GetWindowDrawList()->AddText(parent_window->DC.CursorPos + ImVec2(25, 35 - ImGui::CalcTextSize(name).y) / 2.f, ImGui::GetColorU32(text::text_active), name);

        const char* temp_window_name;
        if (name)
            ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
        else
            ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

        const float backup_border_size = g.Style.ChildBorderSize;
        if (!border) g.Style.ChildBorderSize = 0.0f;
        bool ret = Begin(temp_window_name, NULL, flags);
        g.Style.ChildBorderSize = backup_border_size;

        ImGuiWindow* child_window = g.CurrentWindow;
        child_window->ChildId = id;
        child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

        if (child_window->BeginCount == 1)
            parent_window->DC.CursorPos = child_window->Pos;

        if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
        {
            FocusWindow(child_window);
            NavInitWindow(child_window, false);
            SetActiveID(id + 1, child_window);
            g.ActiveIdSource = ImGuiInputSource_Nav;
        }
        return ret;
    }

    //TitleDottyFont

    bool begin_child(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);

    std::map<ImGuiID, container> tabanimmm;
    bool tabmain(const char* name, bool boolean)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name);
        const ImVec2 label_size = g_menu::iconSS->CalcTextSizeA(15.0f, FLT_MAX, 0.0f, name);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos, ImVec2(pos.x + 31, pos.y + 31));
        ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 5), style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

        auto it_anim = tabanimmm.find(id);

        if (it_anim == tabanimmm.end())
        {
            tabanimmm.insert({ id, container() });
            it_anim = tabanimmm.find(id);
        }

        it_anim->second.element_opacity1 = ImLerp(it_anim->second.element_opacity1, (boolean ? 0.04f : hovered ? 0.01f : 0.0f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));
        it_anim->second.rect_opacity1 = ImLerp(it_anim->second.rect_opacity1, (boolean ? 1.0f : 0.0f), 0.15f * (1.0f - ImGui::GetIO().DeltaTime));
        it_anim->second.text_opacity1 = ImLerp(it_anim->second.text_opacity1, (boolean ? 1.0f : hovered ? 0.5f : 0.3f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));

        window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.element_opacity1), 3.0f);
        window->DrawList->AddText(g_menu::iconSS, 15.0f, (rect.Min + rect.Max - label_size) / 2, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity1), name);

        window->DrawList->AddRectFilled(ImVec2(rect.Max.x + 4, rect.Min.y + 6), ImVec2(rect.Max.x + 8, rect.Max.y - 6), ImColor(3 / 255.0f, 53 / 255.0f, 252 / 255.0f, it_anim->second.rect_opacity1), 7.0f, ImDrawFlags_RoundCornersLeft);

        return pressed;
    }
    //tabmainnnn

    /// new tabs


    bool TabButtonEx(const char* label, const char* icon, const ImVec2& size_arg, ImGuiButtonFlags flags, bool selected, bool bugfix)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;



        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const ImVec2 icon_size = CalcTextSize(icon, NULL, true);
        g.Style.FrameRounding = 1;

        ImVec2 pos = window->DC.CursorPos;
        if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
            pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
        ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect bb(pos, pos + size);
        ItemSize(size, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        if (g.LastItemData.InFlags & ImGuiItemFlags_ButtonRepeat)
            flags |= ImGuiButtonFlags_Repeat;

        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        if (g.LogEnabled)
            LogSetNextTextDecoration("[", "]");

        // Render
        RenderNavHighlight(bb, id);
        PushFont(descriptionfont);
        if (selected)
        {
            //background
            RenderFrame(bb.Min, bb.Max, ImColor(27, 27, 27), true, style.FrameRounding);

            PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0)));
            //label
            if (bugfix)
                RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &icon_size, ImVec2(0.4, 0.8), &bb);
            else
                RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &icon_size, ImVec2(0.27, 0.8), &bb);

            PushFont(icomoonfont);
            //icon
            RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, icon, NULL, &icon_size, ImVec2(0.5, 0.4), &bb);
            PopFont();
            PopStyleColor();
        }
        else
        {
            //background
            RenderFrame(bb.Min, bb.Max, ImColor(18, 18, 18), true, style.FrameRounding);

            PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(113, 113, 113)));
            //label
            if (bugfix)
                RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &icon_size, ImVec2(0.4, 0.8), &bb);
            else
                RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &icon_size, ImVec2(0.27, 0.8), &bb);

            PushFont(icomoonfont);
            //icon
            RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, icon, NULL, &icon_size, ImVec2(0.5, 0.4), &bb);
            PopFont();
            PopStyleColor();
        }
        PopFont();

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
        return pressed;

    }

    bool TabButton(const char* label, const char* icon, const ImVec2& size_arg, bool selected, bool bugfix)
    {
        return TabButtonEx(label, icon, size_arg, ImGuiButtonFlags_None, selected, bugfix);
    }

    bool begin_child_ex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* parent_window = g.CurrentWindow;
        const ImGuiStyle& style = g.Style;
        const ImVec2 label_size = CalcTextSize(name, NULL, true);
        const ImRect frame_bb(parent_window->DC.CursorPos + ImVec2(10, 8), parent_window->DC.CursorPos + ImVec2(220, label_size.y + 34));
        const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));
        flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
        flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

        // Size
        const ImVec2 content_avail = GetContentRegionAvail();
        ImVec2 size = ImFloor(size_arg);
        const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
        if (size.x <= 0.0f)
            size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
        if (size.y <= 0.0f)
            size.y = ImMax(content_avail.y + size.y, 4.0f);

        SetNextWindowPos(ImVec2(parent_window->DC.CursorPos.x, parent_window->DC.CursorPos.y + 34.0f));
        SetNextWindowSize(size - ImVec2(0, 36));

        // Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
        const char* temp_window_name;
        if (name)
            ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
        else
            ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

        const float backup_border_size = g.Style.ChildBorderSize;
        if (!border)
            g.Style.ChildBorderSize = 0.0f;
        bool ret = Begin(temp_window_name, NULL, flags);
        g.Style.ChildBorderSize = backup_border_size;

        ImGuiWindow* child_window = g.CurrentWindow;
        child_window->ChildId = id;
        child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

        // Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
        // While this is not really documented/defined, it seems that the expected thing to do.
        if (child_window->BeginCount == 1)
            parent_window->DC.CursorPos = child_window->Pos;
        ImGui::PushFont(g_menu::menu_font2);
        ImGui::GetWindowDrawList()->AddText(parent_window->DC.CursorPos + ImVec2(9, 8), ImColor(accentcolor), name);
        ImGui::PopFont();
        //parent_window->DrawList->AddRectFilled(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 54), ImVec2(total_bb.Min.x + 380, total_bb.Min.y + 56), ImColor(40, 40, 40, 255), 0, 0);
        // Process navigation-in immediately so NavInit can run on first frame
        if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
        {
            FocusWindow(child_window);
            NavInitWindow(child_window, false);
            SetActiveID(id + 1, child_window); // Steal ActiveId with another arbitrary id so that key-press won't activate child item
            g.ActiveIdSource = ImGuiInputSource_Nav;
        }
        return ret;
    }

    bool begin_child(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 11));
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16, 16));
        return begin_child_ex(str_id, window->GetID(str_id), size_arg, border, extra_flags | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar);
    }

    bool begin_child(ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
    {
        IM_ASSERT(id != 0);
        return begin_child_ex(NULL, id, size_arg, border, extra_flags);
    }

    void end_child()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;

        IM_ASSERT(g.WithinEndChild == false);
        IM_ASSERT(window->Flags & ImGuiWindowFlags_ChildWindow);   // Mismatched BeginChild()/EndChild() calls

        g.WithinEndChild = true;
        if (window->BeginCount > 1)
        {
            End();
        }
        else
        {
            ImVec2 sz = window->Size;
            if (window->AutoFitChildAxises & (1 << ImGuiAxis_X)) // Arbitrary minimum zero-ish child size of 4.0f causes less trouble than a 0.0f
                sz.x = ImMax(4.0f, sz.x);
            if (window->AutoFitChildAxises & (1 << ImGuiAxis_Y))
                sz.y = ImMax(4.0f, sz.y);
            End();

            ImGuiWindow* parent_window = g.CurrentWindow;
            ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + sz);
            ItemSize(sz);
            if ((window->DC.NavLayersActiveMask != 0 || window->DC.NavHasScroll) && !(window->Flags & ImGuiWindowFlags_NavFlattened))
            {
                ItemAdd(bb, window->ChildId);
                RenderNavHighlight(bb, window->ChildId);

                // When browsing a window that has no activable items (scroll only) we keep a highlight on the child (pass g.NavId to trick into always displaying)
                if (window->DC.NavLayersActiveMask == 0 && window == g.NavWindow)
                    RenderNavHighlight(ImRect(bb.Min - ImVec2(2, 2), bb.Max + ImVec2(2, 2)), g.NavId, ImGuiNavHighlightFlags_TypeThin);
            }
            else
            {
                // Not navigable into
                ItemAdd(bb, 0);
            }
            if (g.HoveredWindow == window)
                g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
        }
        ImGui::PopStyleVar(2);
        g.WithinEndChild = false;
        g.LogLinePosY = -FLT_MAX; // To enforce a carriage return
    }


    ///

    std::map<ImGuiID, container> tabanimmmmmmmmmmmmmmm;
    bool tabmainnnn(const char* name, bool boolean)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name);
        const ImVec2 label_size = TitleDottyFont->CalcTextSizeA(15.0f, FLT_MAX, 0.0f, name);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos, ImVec2(pos.x + 31, pos.y + 31));
        ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 5), style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

        auto it_anim = tabanimmmmmmmmmmmmmmm.find(id);

        if (it_anim == tabanimmmmmmmmmmmmmmm.end())
        {
            tabanimmmmmmmmmmmmmmm.insert({ id, container() });
            it_anim = tabanimmmmmmmmmmmmmmm.find(id);
        }

        it_anim->second.element_opacity1 = ImLerp(it_anim->second.element_opacity1, (boolean ? 0.04f : hovered ? 0.01f : 0.0f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));
        it_anim->second.rect_opacity1 = ImLerp(it_anim->second.rect_opacity1, (boolean ? 1.0f : 0.0f), 0.15f * (1.0f - ImGui::GetIO().DeltaTime));
        it_anim->second.text_opacity1 = ImLerp(it_anim->second.text_opacity1, (boolean ? 1.0f : hovered ? 0.5f : 0.3f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));

        window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.element_opacity1), 3.0f);
        window->DrawList->AddText(ubu_child, 15.0f, (rect.Min + rect.Max - label_size) / 2, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity1), name);

        window->DrawList->AddRectFilled(ImVec2(rect.Max.x + 4, rect.Min.y + 6), ImVec2(rect.Max.x + 8, rect.Max.y - 6), ImColor(3 / 255.0f, 53 / 255.0f, 252 / 255.0f, it_anim->second.rect_opacity1), 7.0f, ImDrawFlags_RoundCornersLeft);

        return pressed;
    }

    std::map<ImGuiID, container> tabanimmmm;
    bool tabmainn(const char* name, bool boolean)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name);
        const ImVec2 label_size = TitleDottyFont->CalcTextSizeA(15.0f, FLT_MAX, 0.0f, name);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos, ImVec2(pos.x + 31, pos.y + 31));
        ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 5), style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

        auto it_anim = tabanimmmm.find(id);

        if (it_anim == tabanimmmm.end())
        {
            tabanimmmm.insert({ id, container() });
            it_anim = tabanimmmm.find(id);
        }

        it_anim->second.element_opacity1 = ImLerp(it_anim->second.element_opacity1, (boolean ? 0.04f : hovered ? 0.01f : 0.0f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));
        it_anim->second.rect_opacity1 = ImLerp(it_anim->second.rect_opacity1, (boolean ? 1.0f : 0.0f), 0.15f * (1.0f - ImGui::GetIO().DeltaTime));
        it_anim->second.text_opacity1 = ImLerp(it_anim->second.text_opacity1, (boolean ? 1.0f : hovered ? 0.5f : 0.3f), 0.07f * (1.0f - ImGui::GetIO().DeltaTime));

        window->DrawList->AddRectFilled(rect.Min, rect.Max, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.element_opacity1), 3.0f);
        window->DrawList->AddText(TitleDottyFont, 15.0f, (rect.Min + rect.Max - label_size) / 2, ImColor(1.0f, 1.0f, 1.0f, it_anim->second.text_opacity1), name);

        window->DrawList->AddRectFilled(ImVec2(rect.Max.x + 4, rect.Min.y + 6), ImVec2(rect.Max.x + 8, rect.Max.y - 6), ImColor(3 / 255.0f, 53 / 255.0f, 252 / 255.0f, it_anim->second.rect_opacity1), 7.0f, ImDrawFlags_RoundCornersLeft);

        return pressed;
    }

    std::map<ImGuiID, container> tabanimmmmdadasdadads;
    bool subtabtest(const char* name, const char* icon, bool active)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name);
        const ImVec2 label_size = ImGui::CalcTextSize(name);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos, pos + ImVec2(120, 35));
        ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 3), style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

        auto it_anim = tabanimmmmdadasdadads.find(id);

        if (it_anim == tabanimmmmdadasdadads.end())
        {
            tabanimmmmdadasdadads.insert({ id, container() });
            it_anim = tabanimmmmdadasdadads.find(id);
        }

        it_anim->second.text = ImLerp(it_anim->second.text, active ? ImColor(255, 255, 255) : hovered ? ImColor(71, 71, 73) : ImColor(71, 71, 73), g.IO.DeltaTime * 6.f);
        it_anim->second.bg = ImLerp(it_anim->second.bg, active ? ImColor(20, 20, 20) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);
        it_anim->second.bg2 = ImLerp(it_anim->second.bg2, active ? ImColor(accentcolor) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);

        window->DrawList->AddRectFilled(rect.Min + ImVec2(10, 5), rect.Min + ImVec2(130, 35), ImColor(it_anim->second.bg), 3);
        window->DrawList->AddRectFilled(rect.Min + ImVec2(0, 10), rect.Min + ImVec2(2.5f, 30), ImColor(it_anim->second.bg2), 10, ImDrawCornerFlags_Right);

        // Draw Icon
        ImVec2 iconPos = ImVec2(rect.Min.x + 15, rect.Min.y + 10); // Adjust icon position as needed
        window->DrawList->AddText(g_menu::iconSS, 18, iconPos, ImColor(it_anim->second.text), icon);

        // Draw Text
        ImVec2 textPos = ImVec2(iconPos.x + 25, rect.Min.y + 10); // Adjust text position as needed
        window->DrawList->AddText(g_menu::menu_font2, 18, textPos, ImColor(it_anim->second.text), name);

        return pressed;
    }

    std::map<ImGuiID, container> tabanimmmmdadasdadads22211;
    bool subtabtest3(const char* name, const char* icon, bool active)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name);
        const ImVec2 label_size = ImGui::CalcTextSize(name);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos, pos + ImVec2(120, 35));
        ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 3), style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

        auto it_anim = tabanimmmmdadasdadads22211.find(id);

        if (it_anim == tabanimmmmdadasdadads22211.end())
        {
            tabanimmmmdadasdadads22211.insert({ id, container() });
            it_anim = tabanimmmmdadasdadads22211.find(id);
        }

        it_anim->second.text = ImLerp(it_anim->second.text, active ? ImColor(255, 255, 255) : hovered ? ImColor(71, 71, 73) : ImColor(71, 71, 73), g.IO.DeltaTime * 6.f);
        it_anim->second.bg = ImLerp(it_anim->second.bg, active ? ImColor(20, 20, 20) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);
        it_anim->second.bg2 = ImLerp(it_anim->second.bg2, active ? ImColor(accentcolor) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);

        window->DrawList->AddRectFilled(rect.Min + ImVec2(10, 5), rect.Min + ImVec2(130, 35), ImColor(it_anim->second.bg), 3);
        window->DrawList->AddRectFilled(rect.Min + ImVec2(0, 10), rect.Min + ImVec2(2.5f, 30), ImColor(it_anim->second.bg2), 10, ImDrawCornerFlags_Right);

        // Draw Icon
        ImVec2 iconPos = ImVec2(rect.Min.x + 15, rect.Min.y + 10); // Adjust icon position as needed
        window->DrawList->AddText(ubu_child, 18, iconPos, ImColor(it_anim->second.text), icon);

        // Draw Text
        ImVec2 textPos = ImVec2(iconPos.x + 25, rect.Min.y + 10); // Adjust text position as needed
        window->DrawList->AddText(g_menu::menu_font2, 18, textPos, ImColor(it_anim->second.text), name);

        return pressed;
    }

    std::map<ImGuiID, container> tabanimmmmdadasdadads2;
    bool subtabtest2(const char* name, const char* icon, bool active)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name);
        const ImVec2 label_size = ImGui::CalcTextSize(name);
        ImVec2 pos = window->DC.CursorPos;

        const ImRect rect(pos, pos + ImVec2(120, 35));
        ImGui::ItemSize(ImVec4(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y + 3), style.FramePadding.y);
        if (!ImGui::ItemAdd(rect, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(rect, id, &hovered, &held, NULL);

        auto it_anim = tabanimmmmdadasdadads2.find(id);

        if (it_anim == tabanimmmmdadasdadads2.end())
        {
            tabanimmmmdadasdadads2.insert({ id, container() });
            it_anim = tabanimmmmdadasdadads2.find(id);
        }

        it_anim->second.text = ImLerp(it_anim->second.text, active ? ImColor(255, 255, 255) : hovered ? ImColor(71, 71, 73) : ImColor(71, 71, 73), g.IO.DeltaTime * 6.f);
        it_anim->second.bg = ImLerp(it_anim->second.bg, active ? ImColor(20, 20, 20) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);
        it_anim->second.bg2 = ImLerp(it_anim->second.bg2, active ? ImColor(accentcolor) : hovered ? ImColor(22, 22, 22, 150) : ImColor(0, 0, 0, 0), g.IO.DeltaTime * 6.f);

        window->DrawList->AddRectFilled(rect.Min + ImVec2(10, 5), rect.Min + ImVec2(130, 35), ImColor(it_anim->second.bg), 3);
        window->DrawList->AddRectFilled(rect.Min + ImVec2(0, 10), rect.Min + ImVec2(2.5f, 30), ImColor(it_anim->second.bg2), 10, ImDrawCornerFlags_Right);

        // Draw Icon
        ImVec2 iconPos = ImVec2(rect.Min.x + 15, rect.Min.y + 10); // Adjust icon position as needed
        window->DrawList->AddText(TitleDottyFont, 18, iconPos, ImColor(it_anim->second.text), icon);

        // Draw Text
        ImVec2 textPos = ImVec2(iconPos.x + 25, rect.Min.y + 10); // Adjust text position as needed
        window->DrawList->AddText(g_menu::menu_font2, 18, textPos, ImColor(it_anim->second.text), name);

        return pressed;
    }

    bool SubTab(const char* label, const bool selected, const ImVec2& size_arg) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        const ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = ImGui::GetStyle().Colors;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        ImVec2 pos = window->DC.CursorPos;

        ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

        std::string s_label;

        if (selected)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, GetColorU32(ImGuiCol_CheckMark));
            std::string new_label(label);
            std::transform(new_label.begin(), new_label.end(), new_label.begin(), ::toupper);
            s_label = new_label;

            window->DrawList->AddText(ImVec2(bb.Min.x + size_arg.x / 2 - ImGui::CalcTextSize(label).x / 2, bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2),
                ImColor(GetColorU32(ImGuiCol_Text, style.Alpha)), s_label.c_str());
            ImGui::PopStyleColor();
        }
        else
        {
            window->DrawList->AddText(ImVec2(bb.Min.x + size_arg.x / 2 - ImGui::CalcTextSize(label).x / 2, bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2),
                ImColor(GetColorU32(ImGuiCol_Text, style.Alpha)), label);
        }

        return pressed;
    }

    bool BeginChild(const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();

        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 12));
        PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12, 9));
        return BeginChildEx(str_id, window->GetID(str_id), size_arg, border, extra_flags | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoBackground);
    }

    IDirect3DTexture9* settings_img = nullptr;

    bool BeginChild(ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
    {
        IM_ASSERT(id != 0);
        return BeginChildEx(NULL, id, size_arg, border, extra_flags);
    }

    /*  IMGUI_API bool          BeginChildPos(ImTextureID icon, const char* str_id, const ImVec2& size_arg, bool border = false, ImGuiWindowFlags extra_flags = 0);*/

      /*bool BeginChildPosEx(ImTextureID icon, const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
      {
          ImGuiContext& g = *GImGui;
          ImGuiWindow* parent_window = g.CurrentWindow;

          flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow | ImGuiWindowFlags_NoBackground;
          flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

          // Size
          const ImVec2 content_avail = GetContentRegionAvail();
          ImVec2 size = ImFloor(size_arg);
          const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
          if (size.x <= 0.0f)
              size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too many issues)
          if (size.y <= 0.0f)
              size.y = ImMax(content_avail.y + size.y, 4.0f);
          SetNextWindowSize(size);

          // Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
          const char* temp_window_name;
          if (name)
              ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%s_%08X", parent_window->Name, name, id);
          else
              ImFormatStringToTempBuffer(&temp_window_name, NULL, "%s/%08X", parent_window->Name, id);

          if (!border) {

              ImGui::GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos + ImVec2(0.0f, 0.0f), parent_window->DC.CursorPos + ImVec2(size_arg.x + 0.2f, size_arg.y), GetColorU32(c::child_background), g.Style.ChildRounding + 2, ImGuiWindowFlags_None);

              ImGui::GetWindowDrawList()->AddRect(parent_window->DC.CursorPos + ImVec2(1, 1.0f), parent_window->DC.CursorPos + ImVec2(size_arg.x - 1, size_arg.y - 1), GetColorU32(c::accent_color, 0.1f), g.Style.ChildRounding, ImGuiWindowFlags_None, 2);

              ImGui::GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos + ImVec2(0.0f, 7.0f), parent_window->DC.CursorPos + ImVec2(4, size_arg.y - 7), GetColorU32(c::border_child_default), 10, ImGuiWindowFlags_None);
              ImGui::GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos + ImVec2(size_arg.x - 4, 7.0f), parent_window->DC.CursorPos + ImVec2(size_arg.x, size_arg.y - 7), GetColorU32(c::border_child_default), 10, ImGuiWindowFlags_None);

              ImGui::GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos + ImVec2(0.0f, 7.0f), parent_window->DC.CursorPos + ImVec2(4, size_arg.y - 7), GetColorU32(c::border_child_default), 10, ImGuiWindowFlags_None);
              ImGui::GetWindowDrawList()->AddRectFilled(parent_window->DC.CursorPos + ImVec2(size_arg.x - 4, 7.0f), parent_window->DC.CursorPos + ImVec2(size_arg.x, size_arg.y - 7), GetColorU32(c::border_child_default), 10, ImGuiWindowFlags_None);

              ImGui::GetWindowDrawList()->AddRectFilledMultiColor(parent_window->DC.CursorPos + ImVec2(8, 0.0f), parent_window->DC.CursorPos + ImVec2(size_arg.x / 2, 3), GetColorU32(c::accent_color, 0), GetColorU32(c::accent_color), GetColorU32(c::accent_color), GetColorU32(c::accent_color, 0));
              ImGui::GetWindowDrawList()->AddRectFilledMultiColor(parent_window->DC.CursorPos + ImVec2(size_arg.x - 8, 0.0f), parent_window->DC.CursorPos + ImVec2(size_arg.x / 2, 3), GetColorU32(c::accent_color, 0), GetColorU32(c::accent_color), GetColorU32(c::accent_color), GetColorU32(c::accent_color, 0));

              ImGui::GetWindowDrawList()->AddRectFilledMultiColor(parent_window->DC.CursorPos + ImVec2(8, size_arg.y), parent_window->DC.CursorPos + ImVec2(size_arg.x / 2, size_arg.y - 3), GetColorU32(c::accent_color, 0), GetColorU32(c::accent_color), GetColorU32(c::accent_color), GetColorU32(c::accent_color, 0));
              ImGui::GetWindowDrawList()->AddRectFilledMultiColor(parent_window->DC.CursorPos + ImVec2(size_arg.x - 8, size_arg.y), parent_window->DC.CursorPos + ImVec2(size_arg.x / 2, size_arg.y - 3), GetColorU32(c::accent_color, 0), GetColorU32(c::accent_color), GetColorU32(c::accent_color), GetColorU32(c::accent_color, 0));

              ImGui::GetWindowDrawList()->AddText(g_menu::uwu_child, 15.f, parent_window->DC.CursorPos + ImVec2(20, 13), GetColorU32(c::child_name), name);

              ImGui::GetWindowDrawList()->AddImage(icon, parent_window->DC.CursorPos + ImVec2(240, 11), parent_window->DC.CursorPos + ImVec2(256, 27), ImVec2(0, 0), ImVec2(1, 1), GetColorU32(c::child_name));

          }
          bool ret = Begin(temp_window_name, NULL, flags);

          ImGuiWindow* child_window = g.CurrentWindow;
          child_window->ChildId = id;
          child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

          if (child_window->BeginCount == 1)
              parent_window->DC.CursorPos = child_window->Pos;

          // Process navigation-in immediately so NavInit can run on first frame
          if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayersActiveMask != 0 || child_window->DC.NavHasScroll))
          {
              FocusWindow(child_window);
              NavInitWindow(child_window, false);
              SetActiveID(id + 1, child_window); // Steal ActiveId with another arbitrary id so that key-press won't activate child item
              g.ActiveIdSource = ImGuiInputSource_Nav;
          }
          return ret;
      }*/

      //bool BeginChildPos(ImTextureID icon, const char* str_id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
      //{
      //    ImGuiWindow* window = GetCurrentWindow();
      //    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 50));
      //    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 28));
      //    return BeginChildPosEx(icon, str_id, window->GetID(str_id), size_arg, border, extra_flags | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar);
      //}

      //bool BeginChildPos(ImTextureID icon, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags extra_flags)
      //{
      //    IM_ASSERT(id != 0);
      //    return BeginChildPosEx(icon, NULL, id, size_arg, border, extra_flags);
      //}

    void EndChildPos()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        PopStyleVar(2);
        IM_ASSERT(g.WithinEndChild == false);
        IM_ASSERT(window->Flags & ImGuiWindowFlags_ChildWindow);   // Mismatched BeginChild()/EndChild() calls

        g.WithinEndChild = true;
        if (window->BeginCount > 1)
        {
            End();
        }
        else
        {
            ImVec2 sz = window->Size;
            if (window->AutoFitChildAxises & (1 << ImGuiAxis_X)) // Arbitrary minimum zero-ish child size of 4.0f causes less trouble than a 0.0f
                sz.x = ImMax(4.0f, sz.x);
            if (window->AutoFitChildAxises & (1 << ImGuiAxis_Y))
                sz.y = ImMax(4.0f, sz.y);
            End();

            ImGuiWindow* parent_window = g.CurrentWindow;
            ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + sz);
            ItemSize(sz);
            if ((window->DC.NavLayersActiveMask != 0 || window->DC.NavHasScroll) && !(window->Flags & ImGuiWindowFlags_NavFlattened))
            {
                ItemAdd(bb, window->ChildId);
                RenderNavHighlight(bb, window->ChildId);

                // When browsing a window that has no activable items (scroll only) we keep a highlight on the child (pass g.NavId to trick into always displaying)
                if (window->DC.NavLayersActiveMask == 0 && window == g.NavWindow)
                    RenderNavHighlight(ImRect(bb.Min - ImVec2(2, 2), bb.Max + ImVec2(2, 2)), g.NavId, ImGuiNavHighlightFlags_TypeThin);
            }
            else
            {
                // Not navigable into
                ItemAdd(bb, 0);
            }
            if (g.HoveredWindow == window)
                g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
        }
        g.WithinEndChild = false;
        g.LogLinePosY = -FLT_MAX; // To enforce a carriage return

        ImGui::Spacing();
    }

    // Helper to create a child window / scrolling region that looks like a normal widget frame.
    bool BeginChildFrame(ImGuiID id, const ImVec2& size, ImGuiWindowFlags extra_flags)
    {
        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        PushStyleColor(ImGuiCol_ChildBg, style.Colors[ImGuiCol_FrameBg]);
        PushStyleVar(ImGuiStyleVar_ChildRounding, style.FrameRounding);
        PushStyleVar(ImGuiStyleVar_ChildBorderSize, style.FrameBorderSize);
        PushStyleVar(ImGuiStyleVar_WindowPadding, style.FramePadding);
        bool ret = BeginChild(id, size, true, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysUseWindowPadding | extra_flags);
        PopStyleVar(3);
        PopStyleColor();
        return ret;
    }

    void EndChild()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;

        PopStyleVar(2);

        IM_ASSERT(g.WithinEndChild == false);
        IM_ASSERT(window->Flags & ImGuiWindowFlags_ChildWindow);

        g.WithinEndChild = true;
        if (window->BeginCount > 1)
        {
            End();
        }
        else
        {
            ImVec2 sz = window->Size;
            if (window->AutoFitChildAxises & (1 << ImGuiAxis_X))
                sz.x = ImMax(4.0f, sz.x);
            if (window->AutoFitChildAxises & (1 << ImGuiAxis_Y))
                sz.y = ImMax(4.0f, sz.y);
            End();

            ImGuiWindow* parent_window = g.CurrentWindow;
            ImRect bb(parent_window->DC.CursorPos, parent_window->DC.CursorPos + sz);
            ItemSize(sz);
            if ((window->DC.NavLayersActiveMask != 0 || window->DC.NavHasScroll) && !(window->Flags & ImGuiWindowFlags_NavFlattened))
            {
                ItemAdd(bb, window->ChildId);
                RenderNavHighlight(bb, window->ChildId);

                if (window->DC.NavLayersActiveMask == 0 && window == g.NavWindow)
                    RenderNavHighlight(ImRect(bb.Min - ImVec2(2, 2), bb.Max + ImVec2(2, 2)), g.NavId, ImGuiNavHighlightFlags_TypeThin);
            }
            else
            {
                ItemAdd(bb, 0);
            }
            if (g.HoveredWindow == window)
                g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HoveredWindow;
        }
        g.WithinEndChild = false;
        g.LogLinePosY = -FLT_MAX;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // TABS
    ////////////////////////////////////////////////////////////////////////////////////////////

    std::map<ImGuiID, container> tabanim;
    bool Tabs(bool selected, const char* ico, const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        PushFont(g_menu::iconx);
        const ImVec2 ico_size = CalcTextSize(ico, NULL, true);
        PopFont();

        ImVec2 pos = window->DC.CursorPos, size = CalcItemSize(size_arg, label_size.x, label_size.y);

        const ImRect bb(pos, pos + size);
        ItemSize(size, 0.f);

        if (!ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        auto it_anim = tabanim.find(id);

        if (it_anim == tabanim.end())
        {
            tabanim.insert({ id, container() });
            it_anim = tabanim.find(id);
        }

        it_anim->second.background = ImLerp(it_anim->second.background, selected ? accent_color : ImVec4(0, 0, 0, 0), g.IO.DeltaTime * 6.f);
        it_anim->second.text = ImLerp(it_anim->second.text, selected ? text::text_active : text::text_hov, g.IO.DeltaTime * 6.f);

        GetWindowDrawList()->AddRectFilled(bb.Min + ImVec2(0, size_arg.y - 3), bb.Max, GetColorU32(it_anim->second.background), 10.f, ImDrawCornerFlags_Top);

        PushStyleColor(ImGuiCol_Text, GetColorU32(it_anim->second.text));

        PushFont(g_menu::iconx);
        RenderTextClipped(bb.Min, bb.Max, ico, NULL, &ico_size, ImVec2(0.5f, 0.26f), &bb);
        PopFont();

        RenderTextClipped(bb.Min, bb.Max, label, NULL, &label_size, ImVec2(0.5f, 0.74f), &bb);

        PopStyleColor();

        PushStyleVar(ImGuiStyleVar_Alpha, 0.1f);
        GetWindowDrawList()->AddRectFilledMultiColor(bb.Min + ImVec2(0, (size_arg.y / 2.3f)), bb.Max, GetColorU32(accent_alpha), GetColorU32(accent_alpha), GetColorU32(it_anim->second.background), GetColorU32(it_anim->second.background));
        PopStyleVar();

        ImGui::Dummy(ImVec2(25, 10));

        return pressed;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////
    // INPUT-TEXT
    ////////////////////////////////////////////////////////////////////////////////////////////

    bool InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
    {
        IM_ASSERT(!(flags & ImGuiInputTextFlags_Multiline)); // call InputTextMultiline()
        return InputTextEx(label, NULL, buf, (int)buf_size, ImVec2(0, 0), flags, callback, user_data);
    }

    bool InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
    {
        return InputTextEx(label, NULL, buf, (int)buf_size, size, flags | ImGuiInputTextFlags_Multiline, callback, user_data);
    }

    bool InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
    {
        IM_ASSERT(!(flags & ImGuiInputTextFlags_Multiline)); // call InputTextMultiline() or  InputTextEx() manually if you need multi-line + hint.
        return InputTextEx(label, hint, buf, (int)buf_size, ImVec2(0, 0), flags, callback, user_data);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // SEPARATOR
    ////////////////////////////////////////////////////////////////////////////////////////////

    void SeparatorEx(ImGuiSeparatorFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return;

        ImGuiContext& g = *GImGui;
        IM_ASSERT(ImIsPowerOfTwo(flags & (ImGuiSeparatorFlags_Horizontal | ImGuiSeparatorFlags_Vertical)));   // Check that only 1 option is selected

        const float thickness = 1.0f; // Cannot use g.Style.SeparatorTextSize yet for various reasons.
        if (flags & ImGuiSeparatorFlags_Vertical)
        {
            // Vertical separator, for menu bars (use current line height).
            float y1 = window->DC.CursorPos.y;
            float y2 = window->DC.CursorPos.y + window->DC.CurrLineSize.y;
            const ImRect bb(ImVec2(window->DC.CursorPos.x, y1), ImVec2(window->DC.CursorPos.x + thickness, y2));
            ItemSize(ImVec2(thickness, 0.0f));
            if (!ItemAdd(bb, 0))
                return;

            window->DrawList->AddRectFilled(bb.Min, bb.Max, GetColorU32(separator::bg));

        }
        else if (flags & ImGuiSeparatorFlags_Horizontal)
        {

            float x1 = window->Pos.x;
            float x2 = window->Pos.x + window->Size.x;

            if (g.GroupStack.Size > 0 && g.GroupStack.back().WindowID == window->ID)
                x1 += window->DC.Indent.x;

            if (ImGuiTable* table = g.CurrentTable)
            {
                x1 = table->Columns[table->CurrentColumn].MinX;
                x2 = table->Columns[table->CurrentColumn].MaxX;
            }

            ImGuiOldColumns* columns = (flags & ImGuiSeparatorFlags_SpanAllColumns) ? window->DC.CurrentColumns : NULL;

            if (columns) PushColumnsBackground();

            const float thickness_for_layout = (thickness == 1.0f) ? 0.0f : thickness;
            const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y + thickness));
            ItemSize(ImVec2(0.0f, thickness_for_layout));
            const bool item_visible = ItemAdd(bb, 0);
            if (item_visible)
            {
                // Draw
                window->DrawList->AddRectFilled(bb.Min + ImVec2(GetStyle().WindowPadding.x, 0), bb.Max - ImVec2(GetStyle().WindowPadding.x, 0), GetColorU32(separator::bg));
                if (g.LogEnabled)
                    LogRenderedText(&bb.Min, "--------------------------------\n");

            }
            if (columns)
            {
                PopColumnsBackground();
                columns->LineMinY = window->DC.CursorPos.y;
            }
        }
    }

    void Separator()
    {
        ImGuiContext& g = *GImGui;
        ImGuiWindow* window = g.CurrentWindow;
        if (window->SkipItems)
            return;

        ImGuiSeparatorFlags flags = (window->DC.LayoutType == ImGuiLayoutType_Horizontal) ? ImGuiSeparatorFlags_Vertical : ImGuiSeparatorFlags_Horizontal;
        flags |= ImGuiSeparatorFlags_SpanAllColumns;
        SeparatorEx(flags);
    }


    std::map<ImGuiID, container> buttonanim;
    bool Button(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags)
    {
        ImGuiWindow* window = GetCurrentWindow();

        if (window->SkipItems) return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = CalcTextSize(label, NULL, true);

        ImVec2 pos = window->DC.CursorPos;

        ImVec2 size = CalcItemSize(size_arg, label_size.x, label_size.y);

        const ImRect bb(pos, pos + size);

        ItemSize(size, 0.f);
        if (!ItemAdd(bb, id)) return false;

        bool hovered, held, pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        auto it_anim = buttonanim.find(id);

        if (it_anim == buttonanim.end())
        {
            buttonanim.insert({ id, container() });
            it_anim = buttonanim.find(id);
        }

        it_anim->second.background = ImLerp(it_anim->second.background, IsItemActive() ? button::bg_active : hovered ? button::bg_hov : button::bg, g.IO.DeltaTime * 6.f);

        GetWindowDrawList()->AddRectFilled(bb.Min, bb.Max, GetColorU32(it_anim->second.background), button::rounding);

        RenderTextClipped(bb.Min, bb.Max, label, NULL, &label_size, ImVec2(0.5, 0.5), &bb);

        return pressed;
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
        bool active = false;
        bool hovered = false;
        float alpha = 0.f;
    };
    std::map<ImGuiID, key_state> keyanim;
    bool Keybind(const char* label, int* key, int* mode)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        ImGuiIO& io = g.IO;
        const ImGuiStyle& style = g.Style;

        const ImGuiID id = window->GetID(label);
        const float width = GetContentRegionMax().x - ImGui::GetStyle().WindowPadding.x;

        const ImRect rect(window->DC.CursorPos, window->DC.CursorPos + ImVec2(width, 22.f));

        ImGui::ItemSize(rect, style.FramePadding.y);
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

        ImRect clickable(ImVec2(rect.Max.x - 10 - label_size.x, rect.Min.y), rect.Max);
        bool hovered = ItemHoverable(clickable, id);


        window->DrawList->AddRectFilled(clickable.Min + ImVec2(0, 1), clickable.Max + ImVec2(0, 0), GetColorU32(keybind::bg), 2.f);
        window->DrawList->AddText(rect.Min - ImVec2(0, -1), GetColorU32(text::text), label);

        PushStyleColor(ImGuiCol_Text, text::text_active);
        RenderTextClipped(clickable.Min + ImVec2(0, 1), clickable.Max + ImVec2(0, 1), buf_display, NULL, &label_size, ImVec2(0.5f, 0.5f));
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
        auto it_anim = keyanim.find(id);

        if (it_anim == keyanim.end())
        {
            keyanim.insert({ id, key_state() });
            it_anim = keyanim.find(id);
        }

        if (hovered && g.IO.MouseClicked[1] || it_anim->second.active && (g.IO.MouseClicked[0] || g.IO.MouseClicked[1]) && !it_anim->second.hovered)
            it_anim->second.active = !it_anim->second.active;

        it_anim->second.alpha = ImClamp(it_anim->second.alpha + (8.f * g.IO.DeltaTime * (it_anim->second.active ? 1.f : -1.f)), 0.f, 1.f);

        SetNextWindowPos(ImVec2(clickable.GetCenter().x - 34, clickable.Max.y + 5));
        SetNextWindowSize(ImVec2(69, 74));
        PushStyleVar(ImGuiStyleVar_Alpha, it_anim->second.alpha);
        PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 8));
        PushStyleVar(ImGuiStyleVar_WindowRounding, 2.f);
        PushStyleColor(ImGuiCol_WindowBg, keybind::bg);
        PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.f);
        if (it_anim->second.alpha >= 0.01f)
        {
            Begin(label, NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
            {
                it_anim->second.hovered = IsWindowHovered();

                if (Selectable("Hold", *mode == 0))
                {
                    *mode = 0;
                    it_anim->second.active = false;
                }
                if (Selectable("Toggle", *mode == 1))
                {
                    *mode = 1;
                    it_anim->second.active = false;
                }
                if (Selectable("Always", *mode == 2))
                {
                    *mode = 2;
                    it_anim->second.active = false;
                }
            }
            End();
        }
        PopStyleColor(1);
        PopStyleVar(4);

        return value_changed;
    }

}