#ifndef TERRAIN_H
#define TERRAIN_H

#include "vertex.h"
#include "chunk.h"
#include "perlin.h"
#include "shader.h"
#include "noise_gen.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>


class TerrainMesh {
public:
    explicit TerrainMesh(NoiseGenerator& gen,
        size_t width, size_t height, float sc, float ampl, float fr);

    TerrainMesh& operator=(const TerrainMesh&) = default;

public:
	[[nodiscard]] const std::vector<Chunk>& get_chunks() const { return m_chunks; }

    void reset(float scale, float amplitude, float frequency);


private:
    std::vector<Chunk> generate_chunks(NoiseGenerator& gen, size_t width, size_t height);
    
public:
    float m_scale;
    float m_amplitude;
    float m_freq;

    std::vector<Chunk> m_chunks;
};

#endif /* TERRAIN_H */

