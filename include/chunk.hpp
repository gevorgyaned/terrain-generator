#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>

#include "vertex.hpp"
#include "fbm.hpp"
#include "drawable.hpp"
#include "camera.hpp"
#include "usings.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>

#include <cstddef>
#include <vector>
#include <algorithm>
#include <ranges>

namespace rng = std::ranges;

constexpr size_t chunk_side = 16;

class Chunk : public Drawable {
public:
    Chunk(SP<FBM> fbm, const glm::dvec2& coords, const glm::vec2& begin);
    
    Chunk(Chunk&& other) = default;

public:
    GLuint VAO() const { return m_VAO; }

	size_t indicies_size() const { return m_indicies.size(); }
    bool is_visible(Camera const &camera) const;
       
    void update();
    void draw(SP<Shader> shader) const override;
    std::string get_shader_name() const override { return "default"; }

private:
    std::vector<Vertex> generate_vertices();
    std::vector<unsigned> generate_indicies();
    void normalize_vertex_normals(std::vector<Vertex>& vertices);
    void accumulate_vertex_normals(std::vector<Vertex> &vertices, std::vector<uint> const &indicies);
    void set_normals(std::vector<Vertex> &vertices, std::vector<uint> const &indicies);

public:
    SP<FBM> m_fbm;

    glm::vec2 m_begin_coords;
    glm::dvec2 m_position;

    GLuint m_VAO, m_EBO, m_VBO;

    std::vector<uint> m_indicies;
    std::vector<Vertex> m_vertices;
};

#endif /* CHUNK_H */

