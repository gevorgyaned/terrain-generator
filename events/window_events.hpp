#ifndef WINDOW_EVENT_HPP
#define WINDOW_EVENT_HPP

#include "event.hpp"

class WindowEvent : public Event {
public:
    WindowEvent(size_t width_, size_t height_) :
        width(width_), height(height_) { }

    size_t width;
    size_t height;
};

class WindowResizeEvent : public WindowEvent {
public:
    WindowResizeEvent(size_t width, size_t height) : 
        WindowEvent(width, height),
        m_name(typeid(WindowResizeEvent).name()) { }
    
    EVENT_TYPE(WindowResizeEvent)

private:
    const std::string_view m_name;
};

class FramebufferResizeEvent : public WindowEvent {
public:
    FramebufferResizeEvent(size_t width, size_t height) : 
        WindowEvent(width, height),
        m_name(typeid(FramebufferResizeEvent).name()) { }

    EVENT_TYPE(FramebufferResizeEvent)

private:
    const std::string_view m_name;
};

#endif /* WINDOW_EVENT_HPP */

