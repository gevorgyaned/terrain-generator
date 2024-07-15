#include <terrain.h>

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, double scale) 
    : m_gen { gen }
    , m_width { width + 1 }
    , m_height { height + 1 }
    , m_scale { scale }
{
	generate_chunks();
}

void TerrainMesh::generate_chunks() 
{
    const float d = m_tile_distance * static_cast<float>(CHUNK_SIDE);

    for (std::size_t i = 0; i < m_width - 1; ++i) {
        for (std::size_t j = 0; j < m_height - 1; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            m_chunks.push_back(Chunk( m_gen, pos, offset )); 
        }
    }
}

