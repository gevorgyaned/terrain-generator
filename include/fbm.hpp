#ifndef FBM_HPP
#define FBM_HPP

#include "noise.hpp"
#include "terrain_params.hpp"

class FBM {
public:
    FBM(std::shared_ptr<NoiseGenerator> noise)
        : m_noise(noise)
    { 
    }

    float generate(float x, float y) const;

private:
    std::shared_ptr<NoiseGenerator> m_noise;
    TerrainParams m_params;
};

#endif /* FBM_HPP */

