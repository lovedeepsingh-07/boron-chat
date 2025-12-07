#include <chrono>
#include <common/common.hpp>
#include <common/constants.hpp>
#include <net.h>
#include <thread>

constexpr int delta_time = 1000 / constants::TARGET_FPS;
constexpr int port = 9090;

int main() {
    net::server::setup((uint16_t)port);
    common::info("Listening for incoming connections on :9090");
    while (true) {
        net::server::update(delta_time);
        net::server::send_packets();
        std::this_thread::sleep_for(std::chrono::milliseconds(delta_time));
    }
    return 0;
}
