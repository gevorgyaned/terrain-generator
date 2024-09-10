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
    TerrainMesh(SP<FBM> fbm, size_t width, size_t height);

    ~TerrainMesh();

public:
    auto begin() { return m_chunks.begin(); }
    auto end() { return m_chunks.end(); }

    auto cbegin() { return m_chunks.cbegin(); }
    auto cend() { return m_chunks.cend(); }

    void draw(SP<Shader> shader) const override;
    std::string get_shader_name() const override { return "terrain_mesh"; }

    void update();

private:
    void on_terrain_modify(Event &e); 

private:
    std::vector<UP<Chunk>> generate_chunks(size_t width, size_t height);
    
private:
    std::vector<UP<Chunk>> m_chunks;
    SP<FBM> m_fbm;
    SP<Shader> m_shader;

    bool m_is_modified { false };
};

#endif /* TERRAIN_H */

