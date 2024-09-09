#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <cstddef>

#include "../events/event.hpp"
#include "../events/event_handler.hpp"

class Window {
public:
    Window(size_t height, size_t width)
        : m_height(height), m_width(width)
        , event_handler()
    { 
        subscribe(Event::get_name(), event_handler);
    }

    void onEvent(Event& e); 

private:
    size_t m_height;
    size_t m_width;

    EventHandlerWrapper<Event> event_handler;
};

#endif /* WINDOW_HPP */
