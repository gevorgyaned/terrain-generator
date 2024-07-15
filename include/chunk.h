#ifndef CHUNK_H
#define CHUNK_H

#include <vertex.h>
#include <noise_gen.h>
#include <utility.h>

#include <glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <utility>

constexpr std::size_t CHUNK_SIDE = 16;
constexpr std::size_t CHUNK_SIZE = CHUNK_SIDE * CHUNK_SIDE;

class Chunk {
public:
    Chunk(NoiseGenerator& gen, const glm::dvec2& coords, 
        const glm::vec2& begin = glm::vec2(0.0f), float scale = 40.0f);
    
    Chunk& operator=(Chunk&& rhs);
    Chunk(const Chunk& rhs) = default;

public:
    GLuint VAO() const { return m_VAO; }

	size_t vertices_size() const { return m_vertices.size(); }
    bool is_visible(const glm::vec3& camera_coords, 
            const glm::vec3& euler_angles) const;
       
private:
    void generate_vertices(NoiseGenerator& gen);
    void generate_normals();
    std::vector<Vertex<float>> create_heightmap(NoiseGenerator& gen);

public:
    std::vector<Vertex<float>> m_vertices { CHUNK_SIZE * 6 }; 
    std::vector<Vertex<float>> m_normals { CHUNK_SIZE * 6 };
    
    float m_scale = 40.0f;

    glm::vec2 m_begin_coords;
    glm::dvec2 m_chunk_id;

    GLuint m_VAO, mesh_VBO;
    GLuint normals_VBO;
};

#endif /* CHUNK_H */
