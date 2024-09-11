#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../events/window_events.hpp"
#include "../events/mouse_event.hpp"
#include "../events/key_events.hpp"
#include "../events/event_manager.hpp"

#include <cstddef>
#include <cassert>

#include <GLFW/glfw3.h>

class Window {
public:
    Window(size_t width, size_t height, std::string_view window_name); 

    ~Window(); 

    void on_window_resize(Event &e); 
    void on_framebuffer_resize(Event &e);
    void on_key_pressed(Event &e);

    GLFWwindow *get_window() const { return m_window; }

    size_t width() const { return m_width; }
    size_t height() const { return m_height; }

    bool should_close() const;

    void create_window();
    void setup();

private:
    size_t m_width;
    size_t m_height;
    std::string_view m_name;

    GLFWwindow *m_window;
};

#endif /* WINDOW_HPP */

