#include "terrain.hpp"

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, const TerrainParams& params)
    : m_params{params} 
    , m_chunks{generate_chunks(gen, width, height)}
{ }

std::vector<Chunk> TerrainMesh::generate_chunks(NoiseGenerator& m_gen, size_t width, size_t height) 
{
    std::vector<Chunk> chunks;
    chunks.reserve(width * height);

    const float d = 0.1f * static_cast<float>(CHUNK_SIDE);

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            chunks.emplace_back(m_gen, pos, offset, m_params);
        }
    }

    return chunks;
}

void TerrainMesh::reset(const TerrainParams& params)
{
    if (params != m_params) {
        m_params = params;

        for (auto& chunk : m_chunks) {
            chunk.regenerate(m_params);
        }
    }
}
