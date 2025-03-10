#include "CHalo3Context.h"

static bool show_context = false;
static const char* map_types[4] = {"", "Campaign", "Multiplayer", "MainMenu"};

namespace Halo3::Entry::Simulation {
    void ImGuiContext1();
    void ImGuiContext();
}

void CHalo3Context::context_global()  {
    if (ImGui::BeginMainMenuBar()) {
        ImGui::MenuItem("Global", nullptr, &show_context);
        ImGui::EndMainMenuBar();
    }

    if (!show_context) return;

    if (ImGui::Begin("Game Global", &show_context)) {
        char buffer[1024];
        auto p_time = Halo3::Native::game_time_globals();
        __int16 tick_per_second = 0;
        __int32 game_time = 0;
        float speed = 0;

        if (p_time == nullptr) return;

        ImGui::Text("Game Time: %d\nTick Per Second: %hd\nSpeed: %.2f", p_time->game_time, p_time->tick_per_second, p_time->speed);

        Halo3::Entry::Simulation::ImGuiContext1();

        Halo3::Entry::Simulation::ImGuiContext();

        auto map = Halo3::Native::game_globals();

        if (map == nullptr) return;

        {
            auto map_name = strrchr(map->map_info.name, '\\');

            if (map_name == nullptr) map_name = map->map_info.name;
            else map_name += 1;

            ImGui::Text("Map: %s (%s)", map_name, map_types[map->map_info.game_type]);
        }

        if (ImGui::BeginListBox("Skulls")) {
            for (int i = 0; i < sizeof(eSkullValue) / 4; ++i) {
                const char *skull_name = eSkullName[i];
                int skull_value = eSkullValue[i];

                bool status = map->get_skull((eSkull) skull_value);

                if (ImGui::Selectable(skull_name, status))
                    map->set_skull((eSkull) skull_value, !status);
            }

            ImGui::EndListBox();
        }

//        auto p_log = Halo3::Native::Log();
//        for (int i = 0; i < 0x20; ++i) {
//            auto log = p_log->log + i;
//            if (log->title[0] == 0) break;
//            ImGui::Text("%s %s", log->title, log->content);
//        }
    }
    ImGui::End();
}