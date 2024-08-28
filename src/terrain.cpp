#include "terrain.h"

TerrainMesh::TerrainMesh(FBM const &noise, std::size_t width, std::size_t height, const TerrainParams& params)
    : _params{params} 
    , _chunks{generate_chunks(noise, width, height)}
{ }

std::vector<Chunk> TerrainMesh::generate_chunks(FBM const &noise, size_t width, size_t height) 
{
    std::vector<Chunk> chunks;

    chunks.reserve(width * height);

    const float d = 0.1f * static_cast<float>(CHUNK_SIDE);

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            auto pos = glm::dvec2(i, j);
            auto offset = glm::vec2((float)i * d, (float)j * d);
            chunks.emplace_back(noise, pos, offset, _params);
        }
    }

    return chunks;
}

void TerrainMesh::reset(const TerrainParams& params)
{
    if (params != _params) {
        _params = params;

        for (auto& chunk : _chunks) {
            chunk.regenerate(_params);
        }
    }
}

