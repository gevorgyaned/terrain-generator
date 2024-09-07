#include "event_manager.hpp"

EventManager::EventManager(std::initializer_list<EventHandler> ilist) 
{
    _registered_events.assign(ilist.begin(), ilist.end());
}

void EventManager::register_event(EventHandler event) 
{
    _registered_events.push_back(event);
}

void EventManager::process_events() 
{
    for (auto& handler : _registered_events) {
        handler.handle();
    }
}
