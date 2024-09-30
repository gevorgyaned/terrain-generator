#ifndef FBM_HPP
#define FBM_HPP

#include "noise.hpp"
#include "terrain_params.hpp"

class FBM {
public:
    FBM(NoiseGenerator &noise)
        : m_noise(noise)
    { 
    }

    float generate(float x, float y) const;

private:
    NoiseGenerator &m_noise;
    TerrainParams m_params;
};

#endif /* FBM_HPP */

