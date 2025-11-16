#include <flecs.h>

namespace user_interface {
    void main_menu(flecs::world& registry);
    namespace game {
        void player_interface(flecs::world& registry);
        void pause_menu(flecs::world& registry);
    }
};
