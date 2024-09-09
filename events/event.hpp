#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

class Event {
public:
    virtual ~Event() = default;

    virtual std::string get_type() const = 0;
};

#endif /* EVENT_HPP */

