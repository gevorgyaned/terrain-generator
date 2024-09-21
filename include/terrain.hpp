#ifndef TERRAIN_H
#define TERRAIN_H

#include "chunk.hpp"
#include "fbm.hpp"
#include "shader.hpp"
#include "drawable.hpp"
#include "usings.hpp"

#include "../events/terrain_parameter_event.hpp"
#include "../events/event_manager.hpp"

#include <vector>
#include <cstdlib>

class TerrainMesh : public Drawable {
public:
    TerrainMesh(FBM &fbm, size_t width, size_t height);

    ~TerrainMesh();

public:
    void draw(Shader shader) const override;
    std::string get_shader_name() const override { return "terrain_mesh"; }

    void update();

private:
    void on_terrain_modify([[maybe_unused]]Event &e) { std::cout << "debug ----------\n"; m_is_modified = true; } 

private:
    std::vector<Chunk> generate_chunks(size_t width, size_t height);
    
private:
    FBM &m_fbm;
    std::vector<Chunk> m_chunks;

    bool m_is_modified { false };
};

#endif /* TERRAIN_H */

