#ifndef VEC2_H
#define VEC2_H

struct vec2 {
public:
    vec2(float _x = 0.0, float _y = 0.0)
        : x { _x }
        , y { _y }
    { }

    float dot(const vec2& oth) const;

    float x;
    float y;
};

#endif /* VEC2_H */
