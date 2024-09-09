#ifndef TERRAIN_PARAMTER_EVENT_HPP
#define TERRAIN_PARAMTER_EVENT_HPP

#include "event.hpp"
#include "terrain_params.hpp"

class TerrainModEvent : public Event {
public:
    TerrainModEvent(TerrainParams const &params_) : 
        params(params_), 
        m_name(typeid(TerrainModEvent).name()) {}

    EVENT_TYPE(TerrainModEvent)

    TerrainParams params;

private:
    const std::string_view m_name;
};

#endif /* TERRAIN_PARAMTER_EVENT_HPP */

