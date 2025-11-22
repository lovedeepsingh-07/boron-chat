#include "layout.hpp"

void pages::setup(PageEngine& page_e) {
    page_e.add_page("debug", pages::debug);
    page_e.add_page("login", pages::login);

    page_e.set_curr_page("debug");
}
