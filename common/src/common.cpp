#include "common/common.hpp"
#include <algorithm>

std::string common::trim_whitespace(const std::string& input) {
    size_t start = 0;
    while (start < input.size()
           && (std::isspace(static_cast<unsigned char>(input[start])) != 0)) {
        ++start;
    }
    size_t end = input.size();
    while (end > start && (std::isspace(static_cast<unsigned char>(input[end - 1])) != 0)) {
        --end;
    }
    return input.substr(start, end - start);
}

common::Color common::set_color_alpha(common::Color color, float ratio) {
    ratio = std::clamp<float>(ratio, 0, 1);
    color.a = (uint8_t)(255 * ratio);
    return color;
}

Clay_Color common::to_clay_color(common::Color input_color) {
    Clay_Color clay_color;
    clay_color.r = input_color.r;
    clay_color.g = input_color.g;
    clay_color.b = input_color.b;
    clay_color.a = input_color.a;
    return clay_color;
}

void common::clay_error_handler(Clay_ErrorData error_data) {
    common::error(fmt::format("clay_error: {}", error_data.errorText.chars));
}

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
