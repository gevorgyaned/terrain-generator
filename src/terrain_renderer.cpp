#include "terrain_renderer.h"

TerrainRenderer::TerrainRenderer(TerrainMesh& terrain_mesh)
    : m_terrain_mesh { terrain_mesh }
{ }

void TerrainRenderer::draw(Shader& shader) const 
{
	shader.use();

	const auto& chunks = m_terrain_mesh.get_chunks();

	for (int i = 0; i < chunks.size(); ++i) {
		glBindVertexArray(chunks[i].get_VAO());
		glDrawElements(GL_TRIANGLES, chunks[i].indicies.size(), GL_UNSIGNED_INT, 0);
	}
}

