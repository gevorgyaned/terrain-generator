#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "event.hpp"

#include <functional>
#include <memory>

class EventHandler {
public:
    using CallBackFn = std::function<void(Event&)>;

    EventHandler(std::shared_ptr<Event> event, CallBackFn callback)
        : _event{std::move(event)}
        , _callback{callback}
    { }

    void handle()
    {
        _callback(*_event);
    }

public:
    std::shared_ptr<Event> _event; 
    CallBackFn _callback;
};

#endif /* EVENT_HANDLER_HPP */

