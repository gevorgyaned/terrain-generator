#ifndef TERRAIN_PARAMTER_EVENT_HPP
#define TERRAIN_PARAMTER_EVENT_HPP

#include "event.hpp"

class TerrainModEvent : public Event {
public:
    TerrainModEvent() : 
        m_name(typeid(TerrainModEvent).name()) {}

    EVENT_TYPE(TerrainModEvent)

private:
    const std::string_view m_name;
};

#endif /* TERRAIN_PARAMTER_EVENT_HPP */

