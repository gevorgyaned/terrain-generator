#include "terrain_renderer.hpp"

TerrainRenderer::TerrainRenderer(TerrainMesh& terrain)
    : m_terrain { terrain }
{ }

void TerrainRenderer::draw(Shader& shader) const 
{
	shader.use();

	for (const auto& chunk : m_terrain) {
		glBindVertexArray(chunk.VAO());
		glDrawElements(GL_TRIANGLES, chunk.indicies_size(), GL_UNSIGNED_INT, 0);
	}
}

