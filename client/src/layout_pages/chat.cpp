#include "layout.hpp"
#include <common/theme_engine.hpp>
#include <net.h>
#include <raylib.h>

std::vector<std::string> messages;

void layout::pages::chat(Document& doc, Context& ctx) {
    // update client
    net::client::update((uint64_t)GetFrameTime());
    // poll messages
    for (auto msg : net::client::poll_messages()) {
        messages.emplace_back(std::string(msg.begin(), msg.end()));
    };

    CLAY(Clay_ElementDeclaration{
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    // .padding = { .top = 160 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_TOP },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            for (auto msg : messages) {
                Clay_String msg_cs = ctx.frame_arena.alloc_clay_string(msg);
                CLAY_TEXT(
                    msg_cs,
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = common::to_clay_color(ctx.theme_e.get_color(Color_ID::FOREGROUND)),
                        .fontId = 0,
                        .fontSize = 24,
                    })
                );
            }
        }
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                        .childGap = 12,
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_LEFT_TO_RIGHT } }) {
            layout::components::message_input(doc, ctx, "message_input", "Enter Message");
            if (layout::components::send_button(doc, ctx, "send_button", "Send")) {
                auto* message_element =
                    doc.get_element<elements::Input>("message_input");
                if (message_element != nullptr) {
                    std::string message_input =
                        common::trim_whitespace(message_element->value);
                    if (message_input.size() != 0) {
                        net::client::send_message(message_input);
                        message_element->value = "";
                    }
                }
            };
        }
    }

    // sync to server
    net::client::send_packets();
}
