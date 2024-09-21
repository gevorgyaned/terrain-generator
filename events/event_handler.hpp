#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "event.hpp"
#include "usings.hpp"

class IEventHandler {
public:
    virtual ~IEventHandler() = default;

    virtual std::string_view get_type() const = 0;

    virtual void handle(Event &e) = 0;

    bool is_handled { false };
};

template <typename Subscriber>
class EventHandler : public IEventHandler {
public:
    using CallbackFn = void(Subscriber::*)(Event &e);

    EventHandler(Subscriber &subscriber, CallbackFn callback) :  
        name(typeid(Subscriber).name()), 
        m_subscriber(subscriber), m_callback(callback)
    { }

    static std::string_view get_type_s() {
        return typeid(Subscriber).name();
    }

    void handle(Event &e) override {
        (m_subscriber.*m_callback)(e);
    }

    std::string_view get_type() const override {
        return name;
    }

    const std::string_view name;

private:
    Subscriber& m_subscriber; 
    CallbackFn m_callback;
};

#endif /* EVENT_HANDLER_HPP */

