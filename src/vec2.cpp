#include "vec2.h"

float vec2::dot(const vec2& oth) const
{
    return x * oth.x + y * oth.y;
}
