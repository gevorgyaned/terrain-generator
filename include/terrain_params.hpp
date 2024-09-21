#ifndef TERRAIN_PARAMS_HPP
#define TERRAIN_PARAMS_HPP

#include "../events/key_events.hpp"
#include "../events/terrain_mod_event.hpp"
#include "../events/event_manager.hpp"

class TerrainParams {
public:
    TerrainParams()
    { 
        subscribe(KeyPressedEvent::get_type_s(), 
            std::make_unique<EventHandler<TerrainParams>>(*this, &TerrainParams::on_key_pressed));
    }

    void on_key_pressed(Event &e)
    {
        auto &key_event = static_cast<KeyPressedEvent&>(e);
        process(key_event.key);
    }

    void process(Key key)
    {
        switch (key) {
        case Key::K:
            modify_param(-1);
            add_event(std::make_unique<TerrainModEvent>());
            break;
        case Key::J:
            modify_param(1);
            add_event(std::make_unique<TerrainModEvent>());
            break;
        case Key::Key1:
            current = ampl;
            break;
        case Key::Key2:
            current = freq;
            break;
        case Key::Key3:
            current = gain;
            break;
        case Key::Key4:
            current = lacun;
            break;
        case Key::Key5:
            current = octaves;
            break;
        default: 
            break;
        }
    }

private:
    void modify_param(float sign) {
        switch (current) {
        case ampl:
            m_amplitude += 0.1f * sign;
            break;
        case freq:
            m_frequency += 0.1f * sign;
            break;
        case lacun:
            m_lacunarity += 0.1f * sign;
            break;
        case gain:
            m_gain += 0.1f * sign;
            break;
        case octaves:
            m_octaves += (int)sign;
            break;
        }
    }

private:
    enum Param { ampl, freq, lacun, gain, octaves } current = ampl;

public:
    float m_amplitude { 2.0f };
    float m_lacunarity { 2.2f };
    float m_gain { 0.5f };
    float m_frequency { 0.5f };
    int m_octaves { 12 };
};

#endif /* TERRAIN_PARAMS_HPP */

