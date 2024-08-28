#include "terrain_renderer.h"

TerrainRenderer::TerrainRenderer(TerrainMesh& terrain_mesh)
    : m_terrain_mesh { terrain_mesh }
{ }

void TerrainRenderer::draw(Shader& shader) const 
{
	shader.use();

	for (const auto& chunk : m_terrain_mesh.chunks()) {
		glBindVertexArray(chunk.VAO());
		glDrawElements(GL_TRIANGLES, chunk.indicies_size(), GL_UNSIGNED_INT, 0);
	}
}

