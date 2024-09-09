#include "utility.hpp"

float util::fbm(NoiseGenerator& noise, float x, float y, const TerrainParams& params) {
    float val = 0.0;
    float frequency = params.frequency;
    float amplitude = params.amplitude;

    for (int i = 0; i < 12; ++i) {
        val += noise.get_value((x / params.scale) * frequency, (y / params.scale) * frequency) * amplitude;
        frequency *= params.stride;
        amplitude *= params.elevage;
    }

    return val;
}
