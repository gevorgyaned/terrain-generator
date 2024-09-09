#ifndef KEY_EVENT_HPP
#define KEY_EVENT_HPP

#include "event.hpp"
#include "key.hpp"

class KeyEvent : public Event {
public:
    KeyEvent(Key key_) : key(key_) { }

    Key key;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(Key key) : 
        KeyEvent(key), m_name(typeid(KeyPressedEvent).name()) { }

    EVENT_TYPE(KeyPressedEvent)

private:
    const std::string_view m_name;
};

class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(Key key) : 
        KeyEvent(key), m_name(typeid(KeyReleasedEvent).name()) { }

    EVENT_TYPE(KeyReleasedEvent)

private:
    const std::string_view m_name;
};


#endif /* KEY_EVENT_HPP */ 

