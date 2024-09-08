#ifndef PERLIN_H
#define PERLIN_H

#include <random>
#include <algorithm>
#include <vector>

#include "vec2.h"
#include "utility.h"
#include "noise_gen.h"

class PerlinNoise : public NoiseGenerator {
public:
    explicit PerlinNoise(const std::size_t size = 256)
        : m_size(size * 2)
        , m_permutations(m_size)
        , m_rand_grad(m_size)
    { 
        fill_permutations(); 

        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_real_distribution<> dis(0.0, 100.0);

        rand_a = dis(g);
        rand_b = dis(g);
    }

    float get_value(float x, float y) override;

private:
    void fill_permutations();
    vec2 get_gradient_vec(int x, int y) const;
    std::size_t get_size() const;

private:
    const std::size_t m_size;
    std::vector<int> m_permutations;
    std::vector<vec2> m_rand_grad;

    double rand_a, rand_b;
};

#endif /* PERLIN_H */

