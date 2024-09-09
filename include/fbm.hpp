#ifndef FBM_HPP
#define FBM_HPP

#include "noise.hpp"
#include "terrain_params.hpp"

#include <memory>

class FBM {
public:
    FBM(std::shared_ptr<NoiseGenerator> noise, std::shared_ptr<TerrainParams> params)
        : m_noise(noise), m_params(params)
    { }

    float generate(float x, float y) const;

private:
    std::shared_ptr<NoiseGenerator> m_noise;
    std::shared_ptr<TerrainParams> m_params;
};

#endif /* FBM_HPP */

