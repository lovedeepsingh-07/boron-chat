#pragma once

#include <common/common.hpp>
#include <common/memory_arena.hpp>
#include <string>
#include <unordered_map>

namespace layout_engine {
    enum class Color_ID : uint8_t {
        BACKGROUND,
        FOREGROUND,
        CARD,
        CARD_FOREGROUND,
        POPOVER,
        POPOVER_FOREGROUND,
        PRIMARY,
        PRIMARY_FOREGROUND,
        SECONDARY,
        SECONDARY_FOREGROUND,
        MUTED,
        MUTED_FOREGROUND,
        ACCENT,
        ACCENT_FOREGROUND,
        DESTRUCTIVE,
        DESTRUCTIVE_FOREGROUND,
        BORDER,
        INPUT,
        RING,
        CHART_1,
        CHART_2,
        CHART_3,
        CHART_4,
        CHART_5,
        SIDEBAR,
        SIDEBAR_FOREGROUND,
        SIDEBAR_PRIMARY,
        SIDEBAR_PRIMARY_FOREGROUND,
        SIDEBAR_ACCENT,
        SIDEBAR_ACCENT_FOREGROUND,
        SIDEBAR_BORDER,
        SIDEBAR_RING
    };
    struct Color_ID_Hash {
        std::size_t operator()(const Color_ID& color_id) const noexcept {
            return static_cast<size_t>(color_id);
        }
    };
    struct Theme {
        std::unordered_map<Color_ID, common::Color, Color_ID_Hash> colors;
        float radius;
    };

    class LayoutEngine {
      private:
        std::unordered_map<std::string, Theme> m_themes;
        std::string m_curr_theme_id;

      public:
        MemoryArena frame_arena{ MemoryArena(10240) };
        LayoutEngine() = default;
        ~LayoutEngine() = default;

        // disable copying
        LayoutEngine(const LayoutEngine&) = delete;
        LayoutEngine& operator=(const LayoutEngine&) = delete;

        void setup();

        void add_theme(const std::string& theme_id, Theme theme);
        void set_theme(const std::string& theme_id);
        std::string get_curr_theme();
        common::Color get_color(const Color_ID& color_id);
        float get_radius();
    };
}
