#include "utility.hpp"

float util::interpolate(float a, float b, float t)
{
   
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
