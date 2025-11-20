#include <common/common.hpp>

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
