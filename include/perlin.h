#ifndef PERLIN_H
#define PERLIN_H

#include <random>
#include <algorithm>
#include <vector>

#include <glm/glm/vec2.hpp>
#include <glm/ext/quaternion_geometric.hpp>

#include "noise.h"

class PerlinNoise : public NoiseGenerator {
public:
    explicit PerlinNoise(size_t size = 256)
        : m_size(size * 2)
        , m_permutations(m_size)
        , m_rand_grad(m_size)
    { fill_permutations(); }

    float noise(float x, float y) const override;

private:
    void fill_permutations();
    glm::vec2 get_gradient_vec(int x, int y) const;
    std::size_t get_size() const;

    static float lerp(float a, float b, float t);

private:
    std::size_t m_size;
    std::vector<int> m_permutations;
    std::vector<glm::vec2> m_rand_grad;
};

#endif /* PERLIN_H */
 
