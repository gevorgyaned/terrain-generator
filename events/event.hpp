#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

enum class EventType {
    None, 
    WindowClose, WindowResize,
    KeyPressed, KeyReleased,
    MouseScrol, MouseHover, MouseClicked, MouseReleased
};

class Event {
public:
    virtual std::string to_string() const;

    virtual EventType get_type() const;

    virtual ~Event() = default;
};

#endif /* EVENT_HPP */

