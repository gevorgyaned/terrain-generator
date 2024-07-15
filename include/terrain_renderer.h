#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include <shader.h>
#include <terrain.h>
#include <glad.h>

class TerrainRenderer {
public:
    TerrainRenderer(TerrainMesh& terrain_mesh);

public:
    void draw(Shader& program) const;
    void set_polygon_mode(GLenum mode) const { glPolygonMode(GL_FRONT_AND_BACK, mode); } 
    
private:
    TerrainMesh& m_terrain_mesh;
};

#endif /* TERRAIN_RENDERER_H */

