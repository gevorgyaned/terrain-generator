#ifndef FBM_H
#define FBM_H

#include "noise.h"

#include <memory>

class FBM {
public:
    FBM(std::shared_ptr<NoiseGenerator> noise, float amplitude = 2.0f, float lacunarity = 2.0f, float gain = 0.5f, float frequency = 0.6f, int octaves = 6)
        : _noise{noise}, _amplitude{amplitude}, _lacunarity{lacunarity}, _gain{gain}, _frequency{frequency}, _octaves{octaves}
    { }

    float generate(float x, float y) const;

    FBM& set_amplitude(float value) { _amplitude = value; return *this; }
    FBM& set_lacunarity(float value) { _lacunarity = value; return *this; }
    FBM& set_gain(float value) { _gain = value; return *this; }
    FBM& set_frequency(float value) { _frequency = value; return *this; }
    FBM& set_octaves(int value) { _octaves = value; return *this; }

private:
    std::shared_ptr<NoiseGenerator> _noise;

    float _amplitude;
    float _lacunarity;
    float _gain;
    float _frequency;
    int _octaves;
};

#endif /* FBM_H */

