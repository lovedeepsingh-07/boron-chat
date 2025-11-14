#include "common/common.hpp"

void debug::debug(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[DEBUG]", fmt::fg(fmt::color::white)), input);
}
void debug::info(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[INFO]", fmt::fg(fmt::color::cyan)), input);
}
void debug::warn(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[WARN]", fmt::fg(fmt::color::yellow)), input);
}
void debug::error(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[ERROR]", fmt::fg(fmt::color::red)), input);
}
