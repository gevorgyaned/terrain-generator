#ifndef CHUNK_H
#define CHUNK_H

#include "vertex.h"
#include "noise_gen.h"
#include "utility.h"
#include "perlin.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

constexpr std::size_t CHUNK_SIDE = 16;
constexpr std::size_t CHUNK_SIZE = CHUNK_SIDE * CHUNK_SIDE;

struct TerrainParams;

class Chunk {
public:
    Chunk(NoiseGenerator& gen, const glm::dvec2& coords, 
        const glm::vec2& begin, const TerrainParams& params);
    
    Chunk& operator=(Chunk&& rhs) noexcept;
    Chunk(Chunk&& other) = default;

    Chunk(const Chunk& rhs) = delete;
    Chunk& operator=(const Chunk& rhs) = delete;

public:
    [[nodiscard]] GLuint get_VAO() const { return VAO; }

	[[nodiscard]] size_t indicies_size() const { return indicies.size(); }
    [[nodiscard]] bool is_visible(const glm::vec3& camera_coords,
            const glm::vec3& euler_angles) const;
       
    void regenerate(const TerrainParams& params);

private:
    std::vector<Vertex> generate_vertices();
    std::vector<unsigned> generate_indicies();
    void set_normals();

public:
    NoiseGenerator& m_gen;

    TerrainParams m_params;

    glm::vec2 m_begin_coords;
    glm::dvec2 m_chunk_id;

    GLuint VAO, EBO, VBO;

    std::vector<unsigned> indicies;
    std::vector<Vertex> vertices;
};

#endif /* CHUNK_H */
