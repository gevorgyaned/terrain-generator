#include "event_manager.hpp"

#include <iostream>

void subscribe(std::string_view const &event_name, UP<IEventHandler> handler)
{
    event_manager.subscribe(event_name, std::move(handler));
}

void unsubscribe(std::string_view const &event_name, std::string_view const &handler_name)
{
    event_manager.unsubscribe(event_name, handler_name); 
}

void add_event(UP<Event> event) 
{
    event_manager.add_event(std::move(event));
}

void EventManager::subscribe(std::string_view const &event_name, UP<IEventHandler> handler)
{
    auto subscriber = _subscribers.find(event_name);
    if (subscriber != _subscribers.end()) {
        auto &handlers = subscriber->second;
        handlers.emplace_back(std::move(handler));
    } else {
        _subscribers[event_name].emplace_back(std::move(handler));
    }
}

void EventManager::unsubscribe(std::string_view const &event_name, std::string_view const &handler_type)
{
    auto event = _subscribers.find(event_name);
    if (event != _subscribers.end()) {
        auto &handlers = event->second;
        handlers.erase(rng::find_if(handlers, [&handler_type](auto &it)
        { return handler_type == it->get_type(); }));
    }
}

void EventManager::add_event(UP<Event> event)
{
    _event_queue.emplace_back(std::move(event));
}

void EventManager::trigger(Event &event)
{
    auto &handlers = _subscribers[event.get_type()];
    for (auto &it : handlers) {
        if (it->is_handled) {
            continue; 
        }

        it->handle(event); 
    }
}

void EventManager::dispatch_events()
{
    for (auto &event : _event_queue) {
        trigger(*event);
    }
    
    _event_queue.clear();
}

