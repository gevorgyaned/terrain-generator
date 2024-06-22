#include "utility.h"

double util::interpolate(double a, double b, double t)
{
    double f = t * t * t * (t * (t * 6 - 15) + 10);
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

double util::fbm(NoiseGenerator& noise, float x, float y) {
    double val = 0.0;
    double frequency = 0.5;
    double amplitude = 3.0;

    for (int i = 0; i < 6; ++i) {
        val += noise.get_value(x * frequency, y * frequency) * amplitude;
        frequency *= 2.0;
        amplitude *= 0.5;
    }

    return val;
}
