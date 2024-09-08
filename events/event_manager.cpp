#include "event_manager.hpp"

void subscribe(std::string const &event_name, UP<IEventHandlerWrapper> handler)
{
    event_manager.subscribe(event_name, std::move(handler));
}

void unsubscribe(std::string const &event_name, std::string const &handler_name)
{
    event_manager.unsubscribe(event_name, handler_name); 
}

void add_event(UP<Event> event) 
{
    event_manager.add_event(std::move(event));
}

void trigger(Event const &event)
{
    event_manager.trigger(event);
}

void EventManager::subscribe(std::string const &event_name, UP<IEventHandlerWrapper> handler)
{
    auto subscriber = _subscribers.find(event_name);
    if (subscriber != _subscribers.end()) {
        auto &handlers = subscriber->second;

        auto find = std::find_if(handlers.begin(), handlers.end(), [&handler](const auto& it)
            { return handler->get_type() != it->get_type(); });
        
        assert(find != handlers.end() && "cannot insert already registered handler");
        
        handlers.emplace_back(std::move(handler));
    } else {
        subscriber->second.emplace_back(std::move(handler));
    }
}

void EventManager::unsubscribe(std::string const &event_name, std::string const &handler_type)
{
    auto event = _subscribers.find(event_name);
    if (event != _subscribers.end()) {
        auto &handlers = event->second;
        handlers.erase(std::find_if(handlers.begin(), handlers.end(), [&handler_type](auto &it)
        { return handler_type == it->get_type(); }));
    }
}

void EventManager::add_event(UP<Event> event)
{
    _event_queue.emplace_back(std::move(event));
}

void EventManager::trigger(Event const &event)
{
    auto &handlers = _subscribers[event.get_name()];
    for (auto &it : handlers) {
        it->exec(event); 
    }
}

void EventManager::dispatch_events()
{
    while (!_event_queue.empty()) {
        auto &event = _event_queue.front();
        
        trigger(*event);

        _event_queue.pop_front();
    }
}

