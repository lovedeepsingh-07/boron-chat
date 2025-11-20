#include <common/layout_engine.hpp>

void layout_engine::LayoutEngine::setup() {
    this->add_theme(
        "light",
        Theme{ .colors = { { Color_ID::BACKGROUND, { 246, 230, 238, 255 } },
                           { Color_ID::FOREGROUND, { 91, 91, 91, 255 } },
                           { Color_ID::CARD, { 253, 237, 201, 255 } },
                           { Color_ID::CARD_FOREGROUND, { 91, 91, 91, 255 } },
                           { Color_ID::POPOVER, { 255, 255, 255, 255 } },
                           { Color_ID::POPOVER_FOREGROUND, { 91, 91, 91, 255 } },
                           { Color_ID::PRIMARY, { 208, 79, 153, 255 } },
                           { Color_ID::PRIMARY_FOREGROUND, { 255, 255, 255, 255 } },
                           { Color_ID::SECONDARY, { 138, 207, 209, 255 } },
                           { Color_ID::SECONDARY_FOREGROUND, { 51, 51, 51, 255 } },
                           { Color_ID::MUTED, { 178, 225, 235, 255 } },
                           { Color_ID::MUTED_FOREGROUND, { 122, 122, 122, 255 } },
                           { Color_ID::ACCENT, { 251, 226, 167, 255 } },
                           { Color_ID::ACCENT_FOREGROUND, { 51, 51, 51, 255 } },
                           { Color_ID::DESTRUCTIVE, { 249, 111, 112, 255 } },
                           { Color_ID::DESTRUCTIVE_FOREGROUND, { 255, 255, 255, 255 } },
                           { Color_ID::BORDER, { 208, 79, 153, 255 } },
                           { Color_ID::INPUT, { 228, 228, 228, 255 } },
                           { Color_ID::RING, { 230, 112, 171, 255 } },
                           { Color_ID::CHART_1, { 230, 112, 171, 255 } },
                           { Color_ID::CHART_2, { 132, 210, 226, 255 } },
                           { Color_ID::CHART_3, { 251, 226, 167, 255 } },
                           { Color_ID::CHART_4, { 243, 160, 202, 255 } },
                           { Color_ID::CHART_5, { 215, 72, 142, 255 } },
                           { Color_ID::SIDEBAR, { 248, 216, 234, 255 } },
                           { Color_ID::SIDEBAR_FOREGROUND, { 51, 51, 51, 255 } },
                           { Color_ID::SIDEBAR_PRIMARY, { 236, 72, 153, 255 } },
                           { Color_ID::SIDEBAR_PRIMARY_FOREGROUND, { 255, 255, 255, 255 } },
                           { Color_ID::SIDEBAR_ACCENT, { 249, 168, 212, 255 } },
                           { Color_ID::SIDEBAR_ACCENT_FOREGROUND, { 51, 51, 51, 255 } },
                           { Color_ID::SIDEBAR_BORDER, { 243, 232, 255, 255 } },
                           { Color_ID::SIDEBAR_RING, { 236, 72, 153, 255 } } },
               .radius = 0.4F }
    );

    this->add_theme(
        "dark",
        Theme{ .colors = { { Color_ID::BACKGROUND, { 18, 36, 46, 255 } },
                           { Color_ID::FOREGROUND, { 243, 227, 234, 255 } },
                           { Color_ID::CARD, { 28, 46, 56, 255 } },
                           { Color_ID::CARD_FOREGROUND, { 243, 227, 234, 255 } },
                           { Color_ID::POPOVER, { 28, 46, 56, 255 } },
                           { Color_ID::POPOVER_FOREGROUND, { 243, 227, 234, 255 } },
                           { Color_ID::PRIMARY, { 251, 226, 167, 255 } },
                           { Color_ID::PRIMARY_FOREGROUND, { 18, 36, 46, 255 } },
                           { Color_ID::SECONDARY, { 228, 162, 177, 255 } },
                           { Color_ID::SECONDARY_FOREGROUND, { 18, 36, 46, 255 } },
                           { Color_ID::MUTED, { 36, 39, 43, 255 } },
                           { Color_ID::MUTED_FOREGROUND, { 228, 162, 177, 255 } },
                           { Color_ID::ACCENT, { 198, 123, 150, 255 } },
                           { Color_ID::ACCENT_FOREGROUND, { 243, 227, 234, 255 } },
                           { Color_ID::DESTRUCTIVE, { 227, 94, 164, 255 } },
                           { Color_ID::DESTRUCTIVE_FOREGROUND, { 18, 36, 46, 255 } },
                           { Color_ID::BORDER, { 50, 72, 89, 255 } },
                           { Color_ID::INPUT, { 32, 51, 61, 255 } },
                           { Color_ID::RING, { 80, 175, 182, 255 } },
                           { Color_ID::CHART_1, { 80, 175, 182, 255 } },
                           { Color_ID::CHART_2, { 228, 162, 177, 255 } },
                           { Color_ID::CHART_3, { 198, 123, 150, 255 } },
                           { Color_ID::CHART_4, { 23, 92, 108, 255 } },
                           { Color_ID::CHART_5, { 36, 39, 43, 255 } },
                           { Color_ID::SIDEBAR, { 16, 31, 40, 255 } },
                           { Color_ID::SIDEBAR_FOREGROUND, { 243, 244, 246, 255 } },
                           { Color_ID::SIDEBAR_PRIMARY, { 236, 72, 153, 255 } },
                           { Color_ID::SIDEBAR_PRIMARY_FOREGROUND, { 255, 255, 255, 255 } },
                           { Color_ID::SIDEBAR_ACCENT, { 249, 168, 212, 255 } },
                           { Color_ID::SIDEBAR_ACCENT_FOREGROUND, { 31, 41, 55, 255 } },
                           { Color_ID::SIDEBAR_BORDER, { 55, 65, 81, 255 } },
                           { Color_ID::SIDEBAR_RING, { 236, 72, 153, 255 } } },
               .radius = 0.4F }
    );
}

void layout_engine::LayoutEngine::add_theme(const std::string& theme_id, Theme theme) {
    if (m_themes.find(theme_id) != m_themes.end()) {
        printf("WARN: theme with this ID already exists, doing "
               "nothing\n");
        return;
    }
    m_themes.emplace(theme_id, theme);
}
void layout_engine::LayoutEngine::set_theme(const std::string& theme_id) {
    if (m_curr_theme_id != theme_id) {
        m_curr_theme_id = theme_id;
    }
}
std::string layout_engine::LayoutEngine::get_curr_theme() {
    return m_curr_theme_id;
}
common::Color layout_engine::LayoutEngine::get_color(const Color_ID& color_id) {
    return m_themes.at(m_curr_theme_id).colors.at(color_id);
};
float layout_engine::LayoutEngine::get_radius() {
    return m_themes.at(m_curr_theme_id).radius;
}
