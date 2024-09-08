#ifndef VERTEX_H
#define VERTEX_H

#include <tuple>
#include <ostream>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex {
    Vertex(const glm::vec3& pos, const glm::vec3& norm)
        : position{pos}
        , normal{norm}
    {  }

    Vertex() = default;

    Vertex& operator=(const Vertex& other) = default;

    [[nodiscard]] inline std::tuple<float, float, float> get_position() const;

    friend std::ostream& operator<<(std::ostream& stream, Vertex& vert);

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
};

inline std::tuple<float, float, float> Vertex::get_position() const
{
    return { position[0], position[1], position[2] };
}

#endif /* VERTEX_H */

