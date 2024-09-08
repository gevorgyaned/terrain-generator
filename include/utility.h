#ifndef UTIL_H
#define UTIL_H

#include <fstream>

#include "noise.h"

struct TerrainParams {
    float amplitude = 2.0f;
    float frequency = 0.5f;
    float scale = 40.f;
    float stride = 2.0f;
    float elevage = 0.5f;
    
    bool operator!= (const TerrainParams& rhs) const {
        return amplitude != rhs.amplitude ||
            frequency != rhs.frequency ||
            scale != rhs.scale ||
            stride != rhs.stride ||
            elevage != rhs.elevage; 
    }
};

enum Param { Amplitude, Frequency, Scale, Stride, Elevage, };

namespace util {
	std::string read_to_string(const char *filename); 

    float interpolate(float a, float b, float t);

    float fbm(NoiseGenerator&, float x, float y, const TerrainParams& params);
};

#endif /* UTIL_H */

