#include "debug.hpp"

void debug::debug(const std::string& input) {
    auto flag_str = "\x1b[90m[DEBUG]\x1b[0m";
    fmt::println("{} {}", flag_str, input);
}
void debug::info(const std::string& input) {
    auto flag_str = "\x1b[94m[INFO]\x1b[0m";
    fmt::println("{} {}", flag_str, input);
}
void debug::warn(const std::string& input) {
    auto flag_str = "\x1b[93m[WARN]\x1b[0m";
    fmt::println("{} {}", flag_str, input);
}
void debug::error(const std::string& input) {
    auto flag_str = "\x1b[91m[ERROR]\x1b[0m";
    fmt::println("{} {}", flag_str, input);
}
