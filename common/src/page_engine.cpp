#include <common/context.hpp>

void PageEngine::add_page(
    const std::string& page_id,
    const std::function<void(PageEngine& page_e, Context& ctx)>& page_func
) {
    if (this->m_pages.find(page_id) != this->m_pages.end()) {
        common::warn("(PageEngine::add_page) page with this ID already "
                     "exists, doing nothing");
        return;
    }

    this->m_pages.emplace(page_id, page_func);
}

void PageEngine::set_curr_page(const std::string& page_id) {
    if (this->m_pages.find(page_id) == this->m_pages.end()) {
        common::warn("(PageEngine::set_curr_page) page with this ID does not "
                     "exist, doing nothing");
        return;
    }
    if (this->m_curr_page_id != page_id) {
        this->m_curr_page_id = page_id;
    }
}

const std::string& PageEngine::get_curr_page() {
    return this->m_curr_page_id;
}

void PageEngine::render_curr_page(PageEngine& page_e, Context& ctx) {
    auto iter = this->m_pages.find(this->m_curr_page_id);
    if (iter == this->m_pages.end()) {
        common::error("(PageEngine::render_curr_page) page with this ID does "
                      "not exist, doing nothing");
        return;
    }
    iter->second(page_e, ctx);
}
