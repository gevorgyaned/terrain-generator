#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include "event.hpp"
#include "key.hpp"

class KeyPressEvent : public Event {
public:
    KeyPressEvent(Key key) : _key{key}
    { }

    std::string to_string() const override 
    {
        return "key pressed event: " + std::to_string(static_cast<int>(_key));
    }
    
    EventType get_type() const override { return EventType::KeyPressed; }

    Key get_key() const { return _key; }

private:
    Key _key;
};


class KeyReleaseEvent : public Event {
public:
    KeyReleaseEvent(Key key) : _key{key}
    { }

    std::string to_string() const override 
    {
        return "key pressed event: " + std::to_string(static_cast<int>(_key));
    }
    
    EventType get_type() const override { return EventType::KeyPressed; }

    Key get_key() const { return _key; }

private:
    Key _key;
};

#endif /* KEYBOARD_EVENT_HPP */

