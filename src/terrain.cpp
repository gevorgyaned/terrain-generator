#include <terrain.h>

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, double scale) 
    : m_gen { gen }
    , m_width { width }
    , m_height { height }
    , m_scale { scale }
{
	generate_chunks();
}

void TerrainMesh::generate_chunks() 
{
    const float d = m_tile_distance * static_cast<float>(CHUNK_SIDE);

    for (std::size_t i = 0; i < m_width; ++i) {
        for (std::size_t j = 0; j < m_height; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            m_chunks.push_back(Chunk( m_gen, pos, offset )); 
        }
    }
}

