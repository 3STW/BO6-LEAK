#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <string>
#include <map>
#include <algorithm>
#include <vector>

inline ImVec4 accent_color = ImColor(94, 33, 237);
inline ImVec4 accent_alpha = ImColor(94, 33, 237, 0);
inline ImVec4 accent_color_low = ImColor(94 / 2, 33 / 2, 237 / 2);


namespace c {



    namespace other
    {
        inline ImVec4 white_color = ImColor(255, 255, 255, 255);
        inline ImVec4 low_color = ImColor(255, 255, 255, 0);
        inline ImVec4 accent_color = ImColor(255, 0, 76, 225);

        inline ImVec4 background_color = ImColor(100, 100, 100, 255);

        inline ImVec4 backgroud = ImColor(17, 16, 14, 105);
        inline ImVec4 line = ImColor(40, 40, 40, 255);
        inline ImVec4 line_tab = ImColor(6, 207, 169, 255);

        inline ImVec4 backgroud_color_0 = ImColor(38, 38, 38, 255);
        inline ImVec4 backgroud_color_1 = ImColor(20, 20, 20, 255);
        inline ImVec4 backgroud_tab = ImColor(33, 33, 35, 255);
        inline ImVec4 Icon = ImColor(0, 120, 231, 255);
        inline ImVec4 backgroud_rect = ImColor(255, 255, 255, 10);
    }

    namespace picker
    {
        inline ImVec4 background_inactive = ImColor(28, 33, 40, 240);
        inline float rounding = 2.f;
        inline ImVec4 i_bg = ImColor(12, 10, 9, 255);
    }
    namespace text
    {
        inline ImVec4 text_black = ImColor(0, 0, 0, 255);

        inline ImVec4 text_active = ImColor(255, 255, 255, 255);
        inline ImVec4 text_hov = ImColor(240, 240, 240, 255);
        inline ImVec4 text = ImColor(100, 100, 100, 255);

        inline ImVec4 text_hide = ImColor(255, 255, 255, 0);
    }

    namespace button
    {
        //[RED] - MORPHEUS
        //inline ImVec4 background = ImColor(245, 0, 76, 205);
        //inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);
        //[PURPLE] - PXRROT
        inline ImVec4 background = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        inline ImVec4 background_inactive = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        // [CYAN] - RAY

     /*    inline ImVec4 background = ImColor(0, 136, 204, 255);
         inline ImVec4 background_inactive = ImColor(0, 136, 204, 255);*/
        inline float rounding = 2.f;
    }
    namespace checkbox
    {
        ////[RED] - MORPHEUS
        //inline ImVec4 accent_color = ImColor(255, 0, 76, 225);
        //inline ImVec4 accent_color_inact = ImColor(255, 0, 76, 255);
        //inline ImVec4 circle_inactive = ImColor(255, 0, 76, 255);
        //inline ImVec4 circle_shadow_inactiv = ImColor(255, 0, 76, 255);
        //inline ImVec4 background_active = ImColor(245, 0, 76, 205);
        //[PURPLE] - PXRROT 
        inline ImVec4 accent_color = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        inline ImVec4 accent_color_inact = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        inline ImVec4 circle_inactive = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        inline ImVec4 circle_shadow_inactiv = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        inline ImVec4 background_active = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        //[CYAN] - RAY 
        //inline ImVec4 accent_color = ImColor(0, 136, 204, 255);
        //inline ImVec4 accent_color_inact =ImColor(0, 136, 204, 255);
        //inline ImVec4 circle_inactive = ImColor(0, 136, 204, 255);
        //inline ImVec4 circle_shadow_inactiv = ImColor(0, 136, 204, 255);
        //inline ImVec4 background_active = ImColor(0, 136, 204, 255);

        inline ImVec4 shadow = ImColor(5, 5, 5, 110);
        inline ImVec4 shadow_trans = ImColor(5, 5, 5, 0);
        inline ImVec4 background = ImColor(42, 41, 42);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);
        inline ImVec4 circle_active = ImColor(255, 255, 255, 255);
        inline ImVec4 circle_outline = ImColor(42, 45, 51, 255);
        inline ImVec4 circle_shadow_activ = ImColor(0, 255, 208, 255);
        inline float rounding = 4.f;

        inline ImVec4 bg = ImColor(17, 19, 21, 255);
        inline ImVec4 bg_hov = ImColor(27, 29, 31, 255);

        inline ImVec4 checkmark = ImColor(0, 0, 0, 255);

        //inline float rounding = 4.f;
    }

    namespace tab
    {
        inline ImVec4 image_inactive = ImColor(104, 114, 129, 255);
        inline ImVec4 line_inactive = ImColor(104, 114, 129, 0);
        inline ImVec4 circle_user = ImColor(114, 19, 42, 200);

        inline ImVec4 bg_active = ImColor(255, 255, 255, 10);

        inline ImVec4 bg_inactive = ImColor(255, 255, 255, 0);

        inline ImVec4 text_active = ImColor(200, 200, 200, 200);

        inline ImVec4 text_hov = ImColor(200, 200, 200, 200);

        inline ImVec4 text = ImColor(200, 200, 200, 200);

        inline ImVec4 ibg = ImColor(0, 120, 231, 255);

        inline ImVec4 i_bg = ImColor(203, 206, 207, 255);


        //[RED] - MORPHEUS
       //inline ImVec4 rect_active = ImColor(255, 0, 76, 255);
        //[PURPLE] - PXRROT
        inline ImVec4 rect_active = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        //[CYAN] - RAY     
        //inline ImVec4 rect_active = ImColor(0, 136, 204, 255);


        inline ImVec4 rect_inactive = ImColor(69, 69, 69, 255);
        inline ImVec4 rect_active1 = ImColor(0, 0, 0, 255);
        inline ImVec4 rect_inactive1 = ImColor(0, 0, 0, 0);
        inline ImVec4 rect_active2 = ImColor(69, 69, 69, 255);
        inline ImVec4 rect_inactive2 = ImColor(40, 40, 40, 255);
    }

    namespace subtab
    {
        inline ImVec4 accent_color = ImColor(142, 123, 255, 255);
        inline ImVec4 white_color = ImColor(69, 69, 69, 255);
        inline ImVec4 line_black = ImColor(0, 0, 0, 255);
        //[red] - MORPHEUS
       /* inline ImVec4 line_red = ImColor(255, 0, 76, 255);*/
        //[PURPLE] - PXRROT
        inline ImVec4 line_red = ImVec4(0.671f, 0.f, 0.99f, 1.00f);
        //[CYAN] - RAY
       //inline ImVec4 line_red = ImColor(0, 136, 204, 255);

        inline ImVec4 line_default = ImColor(69, 69, 69, 255);

    }

    namespace bg
    {
        inline ImVec4 background = ImColor(27, 28, 34, 140);
        inline ImVec2 size = ImVec2(60, 590);
        inline float rounding = 10.f;
    }

    namespace child
    {
        inline ImVec4 background = ImColor(27, 28, 34, 140);
        inline float rounding = 6.f;
    }

    namespace slider
    {
        inline ImVec4 background_active = ImColor(58, 63, 70, 80);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);
        inline ImVec4 rect = ImColor(16, 14, 20, 255);
        inline ImVec4 circle_active = ImColor(255, 255, 255, 255);
        inline ImVec4 bg = ImColor(17, 19, 21, 255);
        inline ImVec4 bg_hov = ImColor(27, 29, 31, 255);

        inline float rounding = 4.f;
    }

    namespace keybind
    {
        inline ImVec4 background_active = ImColor(255, 0, 76, 225);
        inline ImVec4 background_inactive = ImColor(58, 63, 70, 80);

        inline ImVec4 in_text = ImColor(100, 100, 100, 255);

        inline ImVec4 text = ImColor(255, 255, 255, 255);

        inline float rounding = 2.f;
    }
    namespace widget
    {
        inline ImVec4 background = ImColor(28, 28, 35, 255);
        inline ImVec4 selectable = ImColor(37, 37, 47, 255);
        inline ImVec4 popup = ImColor(21, 21, 22, 255);

        inline ImVec4 circle = ImColor(47, 55, 65, 255);
        inline float rounding = 4;
    }
    namespace combo
    {
        inline ImVec4 background_inactive = ImColor(10, 10, 11, 255);
        inline ImVec4 background_rect = ImColor(58, 63, 70, 80);
        inline float rounding = 2.f;
    }
    inline ImVec4 accent_color = ImColor(112, 109, 214);

    inline ImVec4 while_color = ImColor(255, 255, 255);
    inline ImVec4 black_color = ImColor(0, 0, 0);

    inline ImVec4 color_bg1 = ImColor(2, 2, 2);
    inline ImVec4 color_bg2 = ImColor(42, 42, 42);
}

namespace custom {
    extern bool checkbox(const char* label, bool* v);
    extern bool Switchbox(const char* label, bool* v);
    extern bool Tab(bool selected, const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags, ImFont* font);
    extern bool Subtab(const char* label, bool selectable, const ImVec2& size_arg);
    extern bool Slider(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
    extern bool SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    extern bool SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    extern bool Keybind(const char* label, int* key, bool show_label);
    extern void combosearch(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size, bool op);

}