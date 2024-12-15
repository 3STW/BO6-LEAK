#include "includes.h"
#include "Vector.hpp"
#include <vector>



class dot
{
public:
    dot(SourceEngine::Vector p, SourceEngine::Vector v) {
        m_vel = v;
        m_pos = p;
    }

    void update();
    void draw();

    SourceEngine::Vector m_pos, m_vel;
};

std::vector<dot*> dots = { };

void dot::update() {
    auto opacity = 255.0f / 255.0f;

    m_pos += m_vel * (opacity);
}

void dot::draw() {

    int opacity = 255.0f * (255.0f / 255.0f);

    ImGui::GetWindowDrawList()->AddCircleFilled({ m_pos.x - 2.5f, m_pos.y - 2.5f }, 2, Settings::Colors::MenuColor, 30);

    auto t = std::find(dots.begin(), dots.end(), this);
    if (t == dots.end()) {
        return;
    }

    for (auto i = t; i != dots.end(); i++) {
        if ((*i) == this) continue;

        auto dist = (m_pos - (*i)->m_pos).Length2D();

        if (dist < 120) {
            int alpha = opacity * (dist / Settings::Aimbot::slider_dot);

            ImGui::GetWindowDrawList()->AddLine({ m_pos.x - 2, m_pos.y - 3 }, { (*i)->m_pos.x - 2, (*i)->m_pos.y - 3 }, Settings::Colors::MenuColor);

        }
    }
}

void dot_draw() {
    struct screen_size {
        int x, y;
    }; screen_size sc;


    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);

    sc.x = GetSystemMetrics(SM_CXSCREEN / 2);
    sc.y = GetSystemMetrics(SM_CYSCREEN / 2);

    int s = rand() % 1000 / Settings::Aimbot::slider_dot;

    if (s == 0) {
        dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, -16, 0), SourceEngine::Vector((rand() % 7) - 3, rand() % 3 + 1, 0)));
    }
    else if (s == 1) {
        dots.push_back(new dot(SourceEngine::Vector(rand() % (int)sc.x, (int)sc.y + 16, 0), SourceEngine::Vector((rand() % 7) - 3, -1 * (rand() % 3 + 1), 0)));
    }
    else if (s == 2) {
        dots.push_back(new dot(SourceEngine::Vector(-16, rand() % (int)sc.y, 0), SourceEngine::Vector(rand() % 3 + 1, (rand() % 7) - 3, 0)));
    }
    else if (s == 3) {
        dots.push_back(new dot(SourceEngine::Vector((int)sc.x + 16, rand() % (int)sc.y, 0), SourceEngine::Vector(-1 * (rand() % 3 + 1), (rand() % 7) - 3, 0)));
    }

    auto alph = 255.0f * (255.0f / 255.0f);
    auto a_int = (int)(alph);

    ImGui::GetWindowDrawList()->AddRectFilled({ 0, 0 }, { (float)sc.x, (float)sc.y }, ImColor(a_int, 0, 0, 0));

    for (auto i = dots.begin(); i < dots.end();) {
        if ((*i)->m_pos.y <= -20 || (*i)->m_pos.y > sc.y + 20 || (*i)->m_pos.x < -20 || (*i)->m_pos.x > sc.x + 20) {
            delete (*i);
            i = dots.erase(i);
        }
        else {
            (*i)->update();
            i++;
        }
    }
    for (auto i = dots.begin(); i < dots.end(); i++) {
        (*i)->draw();
    }
}

void dot_destroy() {
    for (auto i = dots.begin(); i < dots.end(); i++) {
        delete (*i);
    }

    dots.clear();
}
