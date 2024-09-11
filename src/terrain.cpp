#include "terrain.hpp"

TerrainMesh::TerrainMesh(SP<FBM> fbm, size_t width, size_t height) : 
    m_chunks(generate_chunks(width, height)), m_fbm(fbm)
{
    subscribe(TerrainModEvent::get_type_s(), 
        std::make_unique<EventHandler<TerrainMesh>>(*this, &TerrainMesh::on_terrain_modify));
}

TerrainMesh::~TerrainMesh() {
    unsubscribe(TerrainModEvent::get_type_s(), EventHandler<TerrainMesh>::get_type_s()); 
}

void TerrainMesh::draw(Shader shader) const 
{
    for (auto const &chunk : m_chunks) {
        chunk->draw(shader); 
    }
}

std::vector<UP<Chunk>> TerrainMesh::generate_chunks(size_t width, size_t height) 
{
    std::vector<UP<Chunk>> chunks;
    chunks.reserve(width * height);

    const float d = 0.1f * chunk_side;

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            const auto pos = glm::dvec2(i, j);
            const auto offset = glm::vec2((float)i * d, (float)j * d);
            chunks.emplace_back(make_unique<Chunk>(m_fbm, pos, offset));
        }
    }

    return chunks;
}

void TerrainMesh::on_terrain_modify(Event &e) 
{
    m_is_modified = true;
}

void TerrainMesh::update()
{
    if (m_is_modified) {
        for (auto &chunk : m_chunks) {
            chunk->update();
        } 
    }
}

