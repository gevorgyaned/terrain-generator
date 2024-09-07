#ifndef TERRAIN_H
#define TERRAIN_H

#include "chunk.h"
#include "perlin.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <vector>
#include <cstdlib>
#include <unistd.h>

class TerrainMesh {
public:
    TerrainMesh(FBM const &noise,
        size_t width, size_t height, const TerrainParams& params);

    TerrainMesh& operator=(const TerrainMesh&) = default;

public:
	std::vector<Chunk> const &chunks() const { return _chunks; }
    void reset(TerrainParams const &params);

private:
    std::vector<Chunk> generate_chunks(FBM const &noise, size_t width, size_t height);
    
public:
    TerrainParams _params;
    std::vector<Chunk> _chunks;
};

#endif /* TERRAIN_H */

