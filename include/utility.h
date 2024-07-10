#ifndef UTIL_H
#define UTIL_H

#include <fstream>

#include "noise_gen.h"

namespace util {
	std::string read_to_string(const char *filename); 

    float interpolate(float a, float b, float t);

    float fbm(NoiseGenerator& noise, float x, float y);
};


#endif /* UTIL_H */
