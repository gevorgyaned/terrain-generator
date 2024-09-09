#ifndef TERRAIN_PARAMS_HPP
#define TERRAIN_PARAMS_HPP

#include "../events/key_events.hpp"
#include "../events/event_manager.hpp"

class TerrainParams {
public:
    TerrainParams(float amplitude, float lacunarity, float gain, float frequency, int octaves) : 
        m_amplitude(amplitude), m_lacunarity(lacunarity), m_gain(gain),
        m_frequency(frequency), m_octaves(octaves)
    { 
        subscribe(KeyPressedEvent::get_type_s(), 
            std::make_unique<EventHandler<TerrainParams>>(*this, &TerrainParams::on_key_pressed));
    }

    void on_key_pressed(Event &e)
    {
        if (e.get_type() == KeyPressedEvent::get_type_s()) {
            auto &key_event = static_cast<KeyPressedEvent&>(e);
            process(key_event.key);
        }
    }

    void process(Key key)
    {
        switch (key) {
            case Key::J: 
                modify_param(-1); 
                break; 
            case Key::K: 
                modify_param(1); 
                break;
            case Key::Key1: 
                current = ampl; 
                break;
            case Key::Key2: 
                current = freq; 
                break;
            case Key::Key3: 
                current = lacun; 
                break;
            case Key::Key4: 
                current = gain; 
                break;
            case Key::Key5: 
                current = octaves; 
                break;
            default: break;
        };
    }

private:
    enum Param { ampl, freq, lacun, gain, octaves } current;

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
            m_octaves += sign;
            break;
        }
    }

private:
    float m_amplitude;
    float m_lacunarity;
    float m_gain;
    float m_frequency;
    int m_octaves;
};

#endif /* TERRAIN_PARAMS_HPP */

