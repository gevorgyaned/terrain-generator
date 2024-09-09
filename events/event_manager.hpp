#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include "event_handler.hpp"

#include <unordered_map>
#include <deque>
#include <memory>
#include <cassert>
#include <algorithm>
#include <ranges>

namespace rng = std::ranges;

template <typename T>
using UP = std::unique_ptr<T>;

class EventManager {
public:
    void subscribe(std::string const &event_name, UP<IEventHandler> handler);
    void unsubscribe(std::string const &event_name, std::string const &hanler_name);

    void add_event(UP<Event> event);
    void trigger(Event &event);
    void dispatch_events();

private:
    std::deque<UP<Event>> _event_queue;
    std::unordered_map<std::string, std::vector<UP<IEventHandler>>> _subscribers;
};

extern EventManager event_manager;

/* function for gloabal EventManager entity */
void subscribe(std::string const &event_name, UP<IEventHandler> handler);
void unsubscribe(std::string const &event_name, std::string const &handler_name);
void add_event(UP<Event> event) ;
void trigger(Event &e);

#endif /* EVENT_MANAGER_HPP */

