#ifndef VERTEX_H
#define VERTEX_H

#include <tuple>

#include <glm/vec3.hpp>

template <typename T>
struct Vertex {
    Vertex(T x, T y, T z) 
    {  
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vertex() = default;

    std::tuple<T, T, T> get_values() const {
        return { x, y, z };
    }

    template <typename U>
    friend Vertex<U> operator-(const Vertex<U>& a, const Vertex<U>& b);

    operator glm::vec3() {
        return glm::vec3(x, y, z);
    }

    T x;
    T y;
    T z;
};

template <typename T>
Vertex<T> operator-(const Vertex<T>& a, const Vertex<T>& b)
{
    return Vertex(b.x - a.x, b.y - a.y, b.z - a.z);
}


#endif /* VERTEX_H */
