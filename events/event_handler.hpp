#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "event.hpp"

#include <iostream>
#include <functional>

template <typename EventType>
using EventHandler = std::function<void(const EventType&)>;

class IEventHandlerWrapper {
public:
    void exec(const Event& event) 
    {
        call(event);
    }

    virtual std::string get_type() const = 0;

private:
    virtual void call(const Event& event) = 0;
}; 

template <typename EventType>
class EventHandlerWrapper : public IEventHandlerWrapper {
public:
    EventHandlerWrapper(const EventHandler<EventType>& handler) 
        : _handler(handler)
        , _name(_handler.target_type().name()) 
    { }

private:
    void call(const Event& event) override 
    {
        if (event.get_name() == std::declval<EventType>().get_type()) {
            std::cout << event.get_name() << ", " << std::declval<EventType>().get_type() << std::endl; 
            _handler(event);        
        }
    }

    std::string get_type() const override { return _name; }

private:
    EventHandler<EventType> _handler;
    const std::string _name;
};

#endif /* EVENT_HANDLER_HPP */

