#include "../include/vec2.h"

double vec2::dot(const vec2& oth) const 
{
    return x * oth.x + y * oth.y;
}
