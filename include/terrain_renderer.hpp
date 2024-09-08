#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "shader.hpp"
#include "terrain.hpp"

#include <glad/glad.h>

class TerrainRenderer {
public:
    explicit TerrainRenderer(TerrainMesh& terrain_mesh);

public:
    void draw(Shader& program) const;

    static void set_polygon_mode(GLenum mode)
    { glPolygonMode(GL_FRONT_AND_BACK, mode); }
    
private:
    TerrainMesh& m_terrain_mesh;
};

#endif /* TERRAIN_RENDERER_H */

