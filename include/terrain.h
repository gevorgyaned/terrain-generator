#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <noise_gen.h>
#include <perlin.h>
#include <shader.h>
#include <cstdlib>
#include <unistd.h>
#include <vertex.h>
#include <chunk.h>

class TerrainMesh {

public:
    TerrainMesh(NoiseGenerator& gen, 
        std::size_t width = 100, std::size_t height = 100, double scale = 40.0);

public:
    std::size_t get_chunks_width() const;
    std::size_t get_chunks_height() const;

	const std::vector<Chunk>& get_chunks() const { return m_chunks; }

private:
    void generate_chunks();
    
public:
    NoiseGenerator& m_gen;

    std::size_t m_width;
    std::size_t m_height;

    double m_scale;
    const float m_tile_distance = 0.10;
    const float m_x_beg = 0.0;
    const float m_z_beg = 0.0;

    std::vector<Chunk> m_chunks;
};

#endif /* TERRAIN_H */

