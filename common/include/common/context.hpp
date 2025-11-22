#pragma once

#include <common/memory_arena.hpp>
#include <common/theme_engine.hpp>
#include <functional>

class Context {
  public:
    MemoryArena frame_arena{ MemoryArena(10240) };
    ThemeEngine theme_e;

    Context() = default;
    ~Context() = default;

    // disable copying and moving
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;

    void setup();
};

class PageEngine {
  private:
    std::unordered_map<std::string, std::function<void(PageEngine& page_e, Context& ctx)>> m_pages;
    std::string m_curr_page_id;

  public:
    PageEngine() = default;
    ~PageEngine() = default;

    // disable copying and moving
    PageEngine(const PageEngine&) = delete;
    PageEngine& operator=(const PageEngine&) = delete;
    PageEngine(PageEngine&&) = delete;
    PageEngine& operator=(PageEngine&&) = delete;

    void add_page(
        const std::string& page_id,
        const std::function<void(PageEngine& page_e, Context& ctx)>& page_func
    );
    void set_curr_page(const std::string& page_id);
    const std::string& get_curr_page();
    void render_curr_page(PageEngine& page_e, Context& ctx);
};
