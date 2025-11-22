#include "layout.hpp"

void pages::login(PageEngine& page_e, Context& ctx) {
    CLAY(Clay_ElementDeclaration{
        .id = CLAY_ID("main_container"),
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(16),
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor =
            common::to_clay_color(ctx.theme_e.get_color(Color_ID::BACKGROUND)) }) {
        CLAY_TEXT(
            CLAY_STRING("Login"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = common::to_clay_color(ctx.theme_e.get_color(Color_ID::FOREGROUND)),
                .fontId = 0,
                .fontSize = 28,
            })
        );
    }
}
