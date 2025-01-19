#include "terrain.hpp"

TerrainMesh::TerrainMesh(std::shared_ptr<FBM> fbm, size_t width, size_t height) : 
     m_fbm(fbm), m_chunks(generate_chunks(width, height))
{
    subscribe(KeyPressedEvent::get_type_s(),
        std::make_unique<EventHandler<TerrainMesh>>(*this, &TerrainMesh::on_terrain_modify));
}

TerrainMesh::~TerrainMesh() {
    unsubscribe(KeyPressedEvent::get_type_s(), EventHandler<TerrainMesh>::get_type_s());
}

void TerrainMesh::draw(Shader shader) const 
{
    for (auto const &chunk : m_chunks) {
        chunk.draw(shader); 
    }
}

std::vector<Chunk> TerrainMesh::generate_chunks(size_t width, size_t height) 
{
    std::vector<Chunk> chunks;
    chunks.reserve(width * height);

    const float d = 0.1f * chunk_side;

    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            auto pos = glm::dvec2(i, j);
            auto offset = glm::vec2((float)i * d, (float)j * d);
            chunks.emplace_back(m_fbm, pos, offset);
        }
    }

    return chunks;
}

void TerrainMesh::update()
{
    if (m_is_modified) {
        for (auto &chunk : m_chunks) {
            chunk.update();
        } 
    }

    m_is_modified = false;
}

