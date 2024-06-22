#ifndef VEC2_H
#define VEC2_H

struct vec2 {
public:
    vec2(double _x = 0.0, double _y = 0.0) 
        : x { _x }
        , y { _y }
    { }

    double dot(const vec2& oth) const;

    double x;
    double y;
};

#endif /* VEC2_H */
