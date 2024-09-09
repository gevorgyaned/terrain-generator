#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include "event.hpp"

class IEventHandler {
public:
    virtual void handle(Event &e) = 0;

    virtual std::string get_type() const = 0;

    virtual ~IEventHandler() = default;
};

template <typename Subscriber>
class EventHandler : public IEventHandler {
public:
    const std::string name;

    template <typename T>
    using CallbackFn = void(Subscriber::*)(Event &e);

    explicit EventHandler(Subscriber &subscriber, CallbackFn<Subscriber> callback)
        : m_subscriber(subscriber), m_callback(callback), m_name(typeid(Subscriber).name())
    { }

    static std::string get_type_s() {
        return typeid(Subscriber).name();
    }

    void handle(Event &e) override {
        (m_subscriber.*m_callback)(e);
    }

    std::string get_type() const override {
        return name;
    }

private:
    Subscriber& m_subscriber; 
    CallbackFn<Subscriber> m_callback;
};

#endif /* EVENT_HANDLER_HPP */

