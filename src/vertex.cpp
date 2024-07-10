#include <vertex.h>

struct Vertex {
    Vertex(float x, float y, float z) 
    {  
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vertex() = default;

    std::tuple<float, float, float> get_values() const {
        return { x, y, z };
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};
