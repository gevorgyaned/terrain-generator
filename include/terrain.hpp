#ifndef TERRAIN_H
#define TERRAIN_H

#include "chunk.hpp"
#include "fbm.hpp"

#include "../events/terrain_parameter_event.hpp"
#include "../events/event_manager.hpp"


#include <vector>
#include <cstdlib>

class TerrainMesh {
public:
    TerrainMesh(FBM& fbm, size_t width, size_t height);

    ~TerrainMesh();

public:
    auto begin() { return m_chunks.begin(); }
    auto end() { return m_chunks.end(); }

    auto cbegin() { return m_chunks.cbegin(); }
    auto cend() { return m_chunks.cend(); }

private:
    void on_terrain_modify(Event &e); 

private:
    std::vector<Chunk> generate_chunks(size_t width, size_t height);
    
private:
    std::vector<Chunk> m_chunks;
    FBM& m_fbm;
};

#endif /* TERRAIN_H */

