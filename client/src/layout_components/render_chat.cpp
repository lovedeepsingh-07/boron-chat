#include "debug.hpp"
#include "layout.hpp"
#include <client_runtime.h>
#include <generated/packet_.h>

void layout::components::render_chat(
    Document& doc, Context& ctx, const std::vector<std::vector<uint8_t>>& packets
) {
    for (auto curr_packet : packets) {
        const auto* packet = packet::GetPacket(curr_packet.data());
        auto packet_type = packet->data_type();
        switch (packet_type) {
            case (packet::Packet_Data_Message): {
                const auto* message = packet->data_as_Message();
                std::string message_username = std::string(message->username()->c_str());
                std::string message_body = std::string(message->body()->c_str());

                auto client_username = rt::get_client_username();
                bool outgoing_message = message_username
                    == std::string(client_username.begin(), client_username.end());

                layout::components::chat_bubble(doc, ctx, message_username, message_body, outgoing_message);
                break;
            }
            case (packet::Packet_Data_JoinEvent): {
                const auto* join_event = packet->data_as_JoinEvent();
                std::string username = std::string(join_event->username()->c_str());

                auto client_username = rt::get_client_username();
                if (username
                    != std::string(client_username.begin(), client_username.end())) {
                    layout::components::chat_event(doc, ctx, fmt::format("{} joined the server", username));
                }
                break;
            }
            case (packet::Packet_Data_LeaveEvent): {
                const auto* leave_event = packet->data_as_LeaveEvent();
                std::string username = std::string(leave_event->username()->c_str());

                auto client_username = rt::get_client_username();
                if (username
                    != std::string(client_username.begin(), client_username.end())) {
                    layout::components::chat_event(doc, ctx, fmt::format("{} left the server", username));
                }
                break;
            }
            default: {
            }
        }
    }
}
