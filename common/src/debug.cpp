#include "common/common.hpp"

void common::debug(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[DEBUG]", fmt::fg(fmt::color::white)), input);
}
void common::info(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[INFO]", fmt::fg(fmt::color::cyan)), input);
}
void common::warn(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[WARN]", fmt::fg(fmt::color::yellow)), input);
}
void common::error(const std::string& input) {
    fmt::println("{} {}", fmt::styled("[ERROR]", fmt::fg(fmt::color::red)), input);
}
