#include "terrain.h"

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, float sc, float ampl, float fr)
    : m_width { width }
    , m_height { height }
    , freq { fr }
    , amplitude{ ampl }
    , scale{sc}
{
	generate_chunks(gen);
}

void TerrainMesh::generate_chunks(NoiseGenerator& m_gen) 
{
    const float d = 0.1f * static_cast<float>(CHUNK_SIDE);

    for (std::size_t i = 0; i < m_width; ++i) {
        for (std::size_t j = 0; j < m_height; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            m_chunks.emplace_back(m_gen, pos, offset, scale, amplitude, freq);
        }
    }
}

void TerrainMesh::reset(float scale, float amplitude, float frequency)
{
    if (scale != this->scale || amplitude != this->amplitude || frequency != this->freq) {
        this->scale = scale;
        this->amplitude = amplitude;
        this->freq = frequency;

        for (auto& chunk : m_chunks) {
            chunk.regenerate(scale, amplitude, frequency);
        }

    }
}
