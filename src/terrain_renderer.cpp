#include <terrain_renderer.h>

TerrainRenderer::TerrainRenderer(TerrainMesh& terrain_mesh)
    : m_terrain_mesh { terrain_mesh }
{ }

void TerrainRenderer::draw(Shader& shader) const 
{
	shader.use();

	const auto& chunks = m_terrain_mesh.get_chunks();

	for (int i = 0; i < chunks.size(); ++i) {
		glBindVertexArray(chunks[i].VAO());
		glDrawArrays(GL_TRIANGLES, 0, chunks[i].vertices_size());
	}
}

