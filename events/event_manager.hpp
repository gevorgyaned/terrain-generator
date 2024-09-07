#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "event_handler.hpp"

#include <vector>
#include <initializer_list>

class EventManager {
public:
    EventManager() = default;
    
    EventManager(std::initializer_list<EventHandler> ilist);

    void register_event(EventHandler event);

    void process_events();

private:
    std::vector<EventHandler> _registered_events;
};

#endif /* EVENT_MANAGER_HPP */

