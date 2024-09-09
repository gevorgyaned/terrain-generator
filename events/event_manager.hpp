#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "event_handler.hpp"

#include <unordered_map>
#include <deque>
#include <cassert>
#include <algorithm>
#include <ranges>

namespace rng = std::ranges;

class EventManager {
public:
    void subscribe(std::string_view const &event_name, UP<IEventHandler> handler);
    void unsubscribe(std::string_view const &event_name, std::string_view const &hanler_name);

    void add_event(UP<Event> event);
    void dispatch_events();

private:
    void trigger(Event &event);

private:
    std::deque<UP<Event>> _event_queue;
    std::unordered_map<std::string_view, std::vector<UP<IEventHandler>>> _subscribers;
};

extern EventManager event_manager;

/* function for gloabal EventManager entity */
void subscribe(std::string_view const &event_name, UP<IEventHandler> handler);
void unsubscribe(std::string_view const &event_name, std::string_view const &handler_name);
void add_event(UP<Event> event) ;

#endif /* EVENT_MANAGER_HPP */

