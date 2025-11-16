#include "app_utils.hpp"
#include "user_interface.hpp"

void user_interface::game::player_interface(flecs::world& registry) {
    CLAY(Clay_ElementDeclaration{
        .id = CLAY_ID("player_interface_body_container"),
        .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(16),
                    .childAlignment = { .x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_TOP },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID_LOCAL("menu_container"),
            .layout = { .sizing = { CLAY_SIZING_FIT(0), CLAY_SIZING_FIT(0) },
                        .padding = CLAY_PADDING_ALL(16),
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            CLAY_TEXT(
                CLAY_STRING("Player Interface"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_color_to_clay_color(WHITE),
                    .fontId = 0,
                    .fontSize = 20,
                })
            );
            CLAY_TEXT(
                CLAY_STRING("Some Other GUI"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_color_to_clay_color(WHITE),
                    .fontId = 0,
                    .fontSize = 20,
                })
            );
        }
    }
}
