#include "app_utils.hpp"
#include "components.hpp"
#include "user_interface.hpp"

void user_interface::game::pause_menu(flecs::world& registry) {
    CLAY(Clay_ElementDeclaration{
        .id = CLAY_ID("pause_menu_body_container"),
        .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(16),
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_color_to_clay_color(ColorAlpha(BLACK, 0.45)),
        .floating = { .offset = { 0, 0 },
                      .zIndex = 80,
                      .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                      .attachTo = CLAY_ATTACH_TO_ROOT } }) {
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID_LOCAL("menu_container"),
            .layout = { .sizing = { CLAY_SIZING_FIT(0), CLAY_SIZING_FIT(0) },
                        .padding = CLAY_PADDING_ALL(16),
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            CLAY_TEXT(
                CLAY_STRING("Paused"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_color_to_clay_color(WHITE),
                    .fontId = 0,
                    .fontSize = 20,
                })
            );
            CLAY(Clay_ElementDeclaration{
                .id = CLAY_ID_LOCAL("resume_button"),
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(92), .height = CLAY_SIZING_FIT(20) },
                            .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_color_to_clay_color(RAYWHITE),
                .cornerRadius = CLAY_CORNER_RADIUS(8),
                .border = { .color = app_utils::raylib_color_to_clay_color(GRAY),
                            .width = { 1, 1, 1, 1, 0 } } }) {
                bool hovering = Clay_Hovered();
                if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    registry.remove<components::global_options::Paused>();
                }
                CLAY_TEXT(
                    CLAY_STRING("Resume"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_color_to_clay_color(BLACK),
                        .fontId = 0,
                        .fontSize = 20,
                    })
                );
            };
            CLAY(Clay_ElementDeclaration{
                .id = CLAY_ID_LOCAL("quit_button"),
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(92), .height = CLAY_SIZING_FIT(20) },
                            .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_color_to_clay_color(RAYWHITE),
                .cornerRadius = CLAY_CORNER_RADIUS(8),
                .border = { .color = app_utils::raylib_color_to_clay_color(GRAY),
                            .width = { 1, 1, 1, 1, 0 } } }) {
                bool hovering = Clay_Hovered();
                if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    registry.add<components::ActiveScene, components::scenes::MainMenu>();
                }
                CLAY_TEXT(
                    CLAY_STRING("Quit"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_color_to_clay_color(BLACK),
                        .fontId = 0,
                        .fontSize = 20,
                    })
                );
            };
        }
    }
}
