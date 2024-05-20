#include "home_page.h"

#include "hook/mcc/setting/setting.h"
#include "core/String.h"

#define InputInt(name, value, v_min, v_max) int _input_int_##name##_tmp_value = *value; \
if (ImGui::InputInt(#name, &_input_int_##name##_tmp_value, v_min, v_max)) \
    *value = _input_int_##name##_tmp_value;

static struct Tab {
    const char* name;
    void (*render)();
} tabs[] = {
    { "Input", [] {
        auto p_setting = InputSetting();

        ImGui::Checkbox("Override Input", &p_setting->override_input);

        if (!p_setting->override_input) return;

        ImGui::Checkbox("Enable K/M", &p_setting->enable_km);
        for (int i = 0; i < 4; ++i) {
            if (i || !p_setting->enable_km) {
                const char* items[] = { "Controller 0", "Controller 1", "Controller 2", "Controller 3", "NONE" };
                ImGui::Text("Player %d", i + 1);
                ImGui::PushID(i);
                ImGui::Combo("", &p_setting->controller_map[i], items, IM_ARRAYSIZE(items));
                ImGui::PopID();
            }
        }
    } },
    { "Coop", [] {
        char buffer[MAX_NAME_LENGTH];
        auto p_setting = ProfileSetting();

        ImGui::Checkbox("Override Profile", &p_setting->b_override);

        if (!p_setting->b_override) return;

        InputInt(PlayerCount, &p_setting->player_count, 1, 4);

        for (int i = 0; i < p_setting->player_count; ++i) {
            ImGui::Text("Player %d", i + 1);
            ImGui::PushID(i);
            String::strcpy(buffer, p_setting->profiles[i].name, MAX_NAME_LENGTH);
            if (ImGui::InputText("Name", buffer, MAX_NAME_LENGTH)) {
                String::wstrcpy(p_setting->profiles[i].name, buffer, MAX_NAME_LENGTH);
            }
            ImGui::PopID();
        }
    } },
};

void ImGui::CustomWidget::HomePage::render() {
    ImGui::BeginTabBar("mcc_tab");
    for (auto tab : tabs) {
        if (!ImGui::BeginTabItem(tab.name)) continue;
        tab.render();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}
