#include "fbm.h"

float FBM::generate(float x, float y) const 
{
    float value = 0.f; 
    float freq = m_frequency;
    float ampl = m_amplitude;

    for (int i = 0; i < m_octaves; ++i) {
        value += m_noise->get_value((x / 40.f) * freq, (y / 40.f) * freq) * ampl; 
        freq *= m_lacunarity;
        ampl *= m_gain;
    }

    return value;
}

