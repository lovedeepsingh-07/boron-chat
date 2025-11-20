#pragma once

#include <clay/clay.h>
#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <string>

namespace common {
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    struct Vector2 {
        float x;
        float y;
    };

    Clay_Color to_clay_color(Color input_color);
    void clay_error_handler(Clay_ErrorData error_data);

    void debug(const std::string& input);
    void info(const std::string& input);
    void warn(const std::string& input);
    void error(const std::string& input);
};
