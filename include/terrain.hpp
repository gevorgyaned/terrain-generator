#ifndef TERRAIN_H
#define TERRAIN_H

#include "vertex.hpp"
#include "chunk.hpp"
#include "perlin.hpp"
#include "shader.hpp"
#include "noise.hpp"
#include "utility.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>


class TerrainMesh {
public:
    explicit TerrainMesh(NoiseGenerator& gen,
        size_t width, size_t height, const TerrainParams& params);

    TerrainMesh& operator=(const TerrainMesh&) = default;

public:
	[[nodiscard]] const std::vector<Chunk>& get_chunks() const { return m_chunks; }

    void reset(const TerrainParams& params);


private:
    std::vector<Chunk> generate_chunks(NoiseGenerator& gen, size_t width, size_t height);
    
public:
    TerrainParams m_params;
    std::vector<Chunk> m_chunks;
};

#endif /* TERRAIN_H */

