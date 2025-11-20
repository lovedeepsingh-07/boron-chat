#include <array>
#include <clay_raylib.hpp>
#include <common/common.hpp>
#include <common/layout_engine.hpp>

int main() {
    Clay_Raylib_Initialize(1280, 720, "game", FLAG_WINDOW_RESIZABLE);

    // clay setup
    uint64_t clay_required_memory = Clay_MinMemorySize();
    Clay_Arena clay_memory =
        Clay_CreateArenaWithCapacityAndMemory(clay_required_memory, malloc(clay_required_memory));
    Clay_Initialize(
        clay_memory,
        (Clay_Dimensions){ .width = (float)GetScreenWidth(),
                           .height = (float)GetScreenHeight() },
        (Clay_ErrorHandler){ common::clay_error_handler }
    );

    // font setup
    std::array<Font, 1> font_list;
    font_list[0] = LoadFontEx("./assets/Poppins-Regular.ttf", 48, NULL, 400);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, font_list.data());

    // layout engine
    layout_engine::LayoutEngine layout_engine{};
    layout_engine.setup();
    layout_engine.set_theme("dark");

    while (!WindowShouldClose()) {
        // clear the frame memory arena at the starting of every frame
        layout_engine.frame_arena.clear();

        // window state
        Vector2 mouse_pos = GetMousePosition();
        Vector2 scroll_delta =
            Vector2Scale(GetMouseWheelMoveV(), 2); // scroll delta scaled 2 times
        float delta_time = GetFrameTime();

        // update clay state
        Clay_SetLayoutDimensions((Clay_Dimensions){ (float)GetScreenWidth(),
                                                    (float)GetScreenHeight() });
        Clay_SetPointerState((Clay_Vector2){ mouse_pos.x, mouse_pos.y }, IsMouseButtonDown(0));
        Clay_UpdateScrollContainers(
            true, (Clay_Vector2){ scroll_delta.x, scroll_delta.y }, delta_time
        );

        Clay_BeginLayout();

        // ------ theme button ------
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("theme_button"),
            .layout = { .sizing = { .width = CLAY_SIZING_FIT(92), .height = CLAY_SIZING_FIT(20) },
                        .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM },
            .backgroundColor =
                common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::PRIMARY)),
            .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
            .floating = { .attachPoints = { .element = CLAY_ATTACH_POINT_RIGHT_TOP,
                                            .parent = CLAY_ATTACH_POINT_RIGHT_TOP },
                          .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                          .attachTo = CLAY_ATTACH_TO_ROOT },
            .border = { .color = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::BORDER)),
                        .width = { 1, 1, 1, 1, 0 } } }) {
            if (Clay_Hovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (layout_engine.get_curr_theme() == "dark") {
                    layout_engine.set_theme("light");
                } else {
                    layout_engine.set_theme("dark");
                }
            }
            CLAY_TEXT(
                CLAY_STRING("theme"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::PRIMARY_FOREGROUND)),
                    .fontId = 0,
                    .fontSize = 20,
                })
            );
        };

        // ------ main container ------
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("main_container"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                        .padding = CLAY_PADDING_ALL(16),
                        .layoutDirection = CLAY_TOP_TO_BOTTOM },
            .backgroundColor = common::to_clay_color(
                layout_engine.get_color(layout_engine::Color_ID::BACKGROUND)
            ) }) {
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0) },
                            .childGap = 20,
                            .layoutDirection = CLAY_LEFT_TO_RIGHT } }) {
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::CARD)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::POPOVER)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::PRIMARY)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::SECONDARY)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::MUTED)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::ACCENT)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::DESTRUCTIVE)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::SIDEBAR)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::SIDEBAR_PRIMARY)) }) {}
                CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(80), .height = CLAY_SIZING_FIT(30) },
                            },.backgroundColor = common::to_clay_color(layout_engine.get_color(layout_engine::Color_ID::SIDEBAR_ACCENT)) }) {}
            }
        }
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        Clay_Raylib_Render(renderCommands, font_list.data());
        EndDrawing();
    }

    // unload the fonts once the game loop exits
    for (auto& curr_font : font_list) {
        UnloadFont(curr_font);
    }
    return 0;
}
