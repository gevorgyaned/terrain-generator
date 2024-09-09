#include "terrain.hpp"

TerrainMesh::TerrainMesh(FBM& fbm, size_t width, size_t height) : 
    m_chunks(generate_chunks(width, height)), m_fbm(fbm)
{
    subscribe(TerrainModEvent::get_type_s(), 
        std::make_unique<EventHandler<TerrainMesh>>(*this, &TerrainMesh::on_terrain_modify));
}

TerrainMesh::~TerrainMesh() {
    unsubscribe(TerrainModEvent::get_type_s(), EventHandler<TerrainMesh>::get_type_s()); 
}

std::vector<Chunk> TerrainMesh::generate_chunks(size_t width, size_t height) 
{
    std::vector<Chunk> chunks;
    chunks.reserve(width * height);

    const float d = 0.1f * chunk_side;

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            chunks.emplace_back(m_fbm, pos, offset);
        }
    }

    return chunks;
}

void TerrainMesh::on_terrain_modify(Event &e) 
{
    if (e.get_type() == TerrainModEvent::get_type_s()) {
        for (auto &chunk : m_chunks) {
            chunk.update();
        }
    }
}

