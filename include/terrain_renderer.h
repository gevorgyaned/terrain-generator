#ifndef TERRAIN_RENDERER_H
#define TERRAIN_RENDERER_H

#include "shader.h"
#include "terrain.h"

class TerrainRenderer {
public:
    TerrainRenderer()

public:
    void render_terrain() const;
    void set_polygon_mode(GLenum mode) const;
    
private:
    TerrainMesh& m_terrain;
    Shader m_program;
};

#endif /* TERRAIN_RENDERER_H */

