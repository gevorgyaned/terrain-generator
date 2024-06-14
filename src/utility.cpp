#include "../include/utility.h"

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
    return (a - b) * ((t * (t * 6.0 - 15.0) + 10.0) * t * t * t) + a;
}
