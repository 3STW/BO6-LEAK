
#include "imgui/imgui.h"
inline ImVec4 accent_color = ImColor(255, 7, 7);
inline ImVec4 accent_alpha = ImColor(255, 7, 7);
inline ImVec4 accent_color_low = ImColor(255, 7, 7);

namespace bg {

    inline ImVec4 bg = ImColor(8, 10, 12, 255);

    inline ImVec2 size = ImVec2(750, 600);
    inline float rounding = 7.f;
}

namespace child {

    inline ImVec4 bg = ImColor(18, 18, 18, 255);
    inline ImVec4 line = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    inline ImVec4 border = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);

    inline ImVec4 shadow = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);

    inline float rounding = 7.f;
}

namespace scrollbar {

    inline ImVec4 bg = ImColor(78, 78, 78);
    inline ImVec4 scroll = ImColor(78, 78, 78);
    inline float rounding = 2.f;
}

namespace input {

    inline ImVec4 bg = ImColor(18, 18, 18, 255);

    inline float rounding = 2.f;
}

namespace picker {

    inline ImVec4 bg = ImColor(28, 28, 28);


    inline float rounding = 2.f;
}

namespace combo {

    inline ImVec4 bg = ImColor(28, 28, 28);
    inline ImVec4 list = ImColor(27, 29, 31, 255);

    inline ImVec4 bg_shadow = ImColor(17, 19, 21, 0);

    inline float rounding = 2.f;
}

namespace checkbox {

    inline ImVec4 bg = ImColor(28, 28, 28);
    inline ImVec4 bg_hov = ImColor(27, 29, 31, 255);

    inline ImVec4 checkmark = ImColor(25, 25, 25);

    inline float rounding = 4.f;
}

namespace slider {

    inline ImVec4 bg = ImColor(28, 28, 28);
    inline ImVec4 bg_hov = ImColor(27, 29, 31, 255);

    inline float rounding = 4.f;
}

namespace text {

    inline ImVec4 text_hint = ImColor(75, 75, 75, 255);

    inline ImVec4 text_selected = ImColor(80, 80, 80, 80);

    inline ImVec4 text_active = ImColor(255, 255, 255, 255);
    inline ImVec4 text_hov = ImColor(180, 180, 180, 255);
    inline ImVec4 text = ImColor(120, 120, 120, 255);
}

namespace separator {

    inline ImVec4 bg = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);

}

namespace button {

    inline ImVec4 bg = ImColor(28, 28, 28);
    inline ImVec4 bg_hov = ImColor(27, 29, 31, 255);
    inline ImVec4 bg_active = ImColor(37, 39, 41, 255);

    inline float rounding = 4.f;
}

namespace keybind {

    inline ImVec4 bg = ImColor(28, 28, 28);
    inline ImVec4 bg_hov = ImColor(27, 29, 31, 255);
    inline ImVec4 bg_active = ImColor(37, 39, 41, 255);

    inline float rounding = 4.f;
}