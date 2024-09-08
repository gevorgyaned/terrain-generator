#include "terrain_renderer.hpp"

TerrainRenderer::TerrainRenderer(TerrainMesh& terrain_mesh)
    : m_terrain_mesh { terrain_mesh }
{ }

void TerrainRenderer::draw(Shader& shader) const 
{
	shader.use();

	const auto& chunks = m_terrain_mesh.get_chunks();

	for (const auto& chunk : chunks) {
		glBindVertexArray(chunk.get_VAO());
		glDrawElements(GL_TRIANGLES, chunk.indicies_size(), GL_UNSIGNED_INT, 0);
	}
}

