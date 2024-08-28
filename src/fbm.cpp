#include "fbm.h"

float FBM::generate(float x, float y) const 
{
    float value = 0.f; 
    float freq = _frequency;
    float ampl = _amplitude;

    for (int i = 0; i < _octaves; ++i) {
        value += _noise->noise((x / 40.f) * freq, (y / 40.f) * freq) * ampl; 
        freq *= _lacunarity;
        ampl *= _gain;
    }

    return value;
}

