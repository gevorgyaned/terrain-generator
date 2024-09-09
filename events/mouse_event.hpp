#ifndef MOUSE_EVENT_HPP
#define MOUSE_EVENT_HPP

#include "event.hpp"

class MouseEvent : public Event {
public:
    MouseEvent(float mouse_x_, float mouse_y_) : 
        mouse_x(mouse_x_), mouse_y(mouse_y_) { }

    float mouse_x;
    float mouse_y;
};

class MouseClickedEvent : public MouseEvent {
public:
    MouseClickedEvent(float mouse_x, float mouse_y) :
        MouseEvent(mouse_x, mouse_y), 
        m_name(typeid(MouseClickedEvent).name()) { }
    
    EVENT_TYPE(MouseClickedEvent)

private:
    const std::string_view m_name;
};

class MouseMovedEvent : public MouseEvent {
public:
    MouseMovedEvent(float mouse_x, float mouse_y) :
        MouseEvent(mouse_x, mouse_y),
        m_name(typeid(MouseMovedEvent).name()) { }

    EVENT_TYPE(MouseMovedEvent)

private:
    const std::string_view m_name;
};

#endif /* MOUSE_EVENT_HPP */
