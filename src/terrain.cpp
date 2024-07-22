#include "terrain.h"

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, float sc, float ampl, float fr)
    : m_scale{sc}
    , m_amplitude{ampl}
    , m_freq {fr}
    , m_chunks{generate_chunks(gen, width, height)}
{ }

std::vector<Chunk> TerrainMesh::generate_chunks(NoiseGenerator& m_gen, size_t width, size_t height) 
{
    std::vector<Chunk> chunks;
    const float d = 0.1f * static_cast<float>(CHUNK_SIDE);

    for (std::size_t i = 0; i < width; ++i) {
        for (std::size_t j = 0; j < height; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            chunks.emplace_back(m_gen, pos, offset, m_scale, m_amplitude, m_freq);
        }
    }

    return chunks;
}

void TerrainMesh::reset(float scale, float amplitude, float frequency)
{
    if (scale != m_scale || amplitude != m_amplitude || frequency != m_freq) {
        m_scale = scale;
        m_amplitude = amplitude;
        m_freq = frequency;

        for (auto& chunk : m_chunks) {
            chunk.regenerate(scale, amplitude, frequency);
        }
    }
}
