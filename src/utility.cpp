#include "utility.h"

float util::interpolate(float a, float b, float t)
{
    float f = t * t * t * (t * (t * 6 - 15) + 10);
    return a + f * (b - a);
}

std::string util::read_to_string(const char *filename)
{
    std::ifstream stream(filename);

    std::string result;
    std::string line;
    while (std::getline(stream, line)) {
        result += line;
        result.push_back('\n');
    }
    
    stream.close();
    return result;
}

float util::fbm(NoiseGenerator& noise, float x, float y) {
    float val = 0.0;
    float frequency = 0.5;
    float amplitude = 3.0;

    for (int i = 0; i < 6; ++i) {
        val += noise.get_value(x * frequency, y * frequency) * amplitude;
        frequency *= 2.0;
        amplitude *= 0.5;
    }

    return val;
}
