#include "components.hpp"
#include "systems.hpp"
#include <clay/clay.h>

void systems::global_events(flecs::world& registry) {
    registry.system()
        .kind<components::phases::OnUpdate>()
        .run([](flecs::iter& iter) {
            flecs::world registry = iter.world();
            if (WindowShouldClose()) {
                registry.add<components::events::GameQuitEvent>();
            }
            if (IsKeyPressed(KEY_F9)) {
                Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
            }
            if (IsKeyPressed(KEY_ESCAPE)
                && registry.has<components::ActiveScene, components::scenes::Game>()) {
                if (registry.has<components::global_options::Paused>()) {
                    registry.remove<components::global_options::Paused>();
                } else {
                    registry.add<components::global_options::Paused>();
                }
            }
        })
        .add<components::scenes::Common>();
}
