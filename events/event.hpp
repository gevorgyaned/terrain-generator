#ifndef EVENT_HPP
#define EVENT_HPP

#include <typeinfo>
#include <string_view>
#include <string>

#define EVENT_TYPE(type)\
    std::string_view get_type() const override {\
        return m_name;\
    }\
\
    static std::string_view get_type_s() {\
        return typeid(type).name();\
    }\

class Event {
public:
    virtual ~Event() = default;

    virtual std::string_view get_type() const = 0;

    virtual std::string print() { return "base event"; }
};

#endif /* EVENT_HPP */

