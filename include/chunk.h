#ifndef CHUNK_H
#define CHUNK_H

#define GLM_ENABLE_EXPERIMENTAL

#include "vertex.h"
#include "utility.h"
#include "camera.h"
#include "fbm.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <algorithm>

constexpr size_t CHUNK_SIDE = 16;
constexpr size_t CHUNK_SIZE = CHUNK_SIDE * CHUNK_SIDE;

struct TerrainParams;

class Chunk {
public:
    Chunk(FBM const &noise, const glm::dvec2 &coords, 
        const glm::vec2 &begin, TerrainParams &params);
    
    Chunk& operator=(Chunk &&rhs) noexcept = default;
    Chunk(Chunk &&other) noexcept = default;

    Chunk(Chunk const &rhs) = delete;
    Chunk& operator=(Chunk const &rhs) = delete;

public:
    GLuint VAO() const { return _VAO; }

	size_t indicies_size() const { return _indicies.size(); }
    bool is_visible(Camera const &camera) const;
       
    void regenerate(TerrainParams const &params);

private:
    std::vector<Vertex> generate_vertices(size_t chunk_side);
    std::vector<int> generate_indicies(size_t chunk_side);
    void set_normals(std::vector<Vertex> &vertices, std::vector<int> const &indicies);

    void normalize_vertex_normals(std::vector<Vertex>& vertices);
    void add_vertex_normals(std::vector<Vertex> &vertices, std::vector<int> const &indicies);

public:
    FBM _noise;

    TerrainParams _params;

    float _x_beg;
    float _z_beg;
    glm::dvec2 _chunk_id;

    GLuint _VAO, _EBO, _VBO;

    std::vector<int> _indicies;
    std::vector<Vertex> _vertices;
};

#endif /* CHUNK_H */
