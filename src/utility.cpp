#include "../include/utility.h"
#include <fstream>

vec2 util::get_random_gradient(int x)
{
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; 
    unsigned a = x, b = x;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    double random = a * (3.14159265);
    return vec2(cos(random), sin(random));
}

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
    }
    
    stream.close();
    return result;
}
