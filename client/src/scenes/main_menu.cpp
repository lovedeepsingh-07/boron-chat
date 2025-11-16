#include "scenes.hpp"
#include <common/common.hpp>

void scenes::main_menu::on_enter(flecs::iter& iter, size_t, components::ActiveScene) {
    debug::debug("main_menu::on_enter");
    flecs::world registry = iter.world();

    registry.defer_begin();
    registry.delete_with(flecs::ChildOf, registry.lookup("scene_root"));
    registry.defer_end();

    registry.set_pipeline(registry.get<components::pipelines::MainMenu>().pipeline);
}

void scenes::main_menu::on_exit(flecs::iter& iter, size_t, components::ActiveScene) {
    debug::debug("main_menu::on_exit");
}
