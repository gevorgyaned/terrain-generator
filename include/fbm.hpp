#ifndef FBM_HPP
#define FBM_HPP

#include "noise.hpp"
#include "terrain_params.hpp"

class FBM {
public:
    FBM(NoiseGenerator &noise, TerrainParams const &params)
        : m_noise(noise), m_params(params)
    { 
    }

    float generate(float x, float y) const;

private:
    NoiseGenerator &m_noise;
    TerrainParams m_params;
};

#endif /* FBM_HPP */

