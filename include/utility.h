#ifndef UTIL_H
#define UTIL_H

#include <fstream>

#include "perlin.h"

struct TerrainParams {
    
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

    float fbm(PerlinNoise&, float x, float y, const TerrainParams& params);
};

#endif /* UTIL_H */

