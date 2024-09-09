#ifndef EVENT_HPP
#define EVENT_HPP

#include <string_view>

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
};

#endif /* EVENT_HPP */

