#ifndef PERLIN_H
#define PERLIN_H

#include <random>
#include <algorithm>
#include <vector>

#include "noise_gen.h"
#include "vec2.h"
#include "utility.h"

class PerlinNoise : public NoiseGenerator {
public:
    PerlinNoise(std::size_t size = 256) 
        : m_size { size * 2 }
        , m_permutations ( m_size  )
    { fill_permutations(); }

    double get_value(double x, double y);

private:
    void fill_permutations();
    vec2 get_gradient_vec(int x, int y) const;
    std::size_t get_size() const;

private:
    const std::size_t m_size;
    std::vector<int> m_permutations;
};

#endif /* PERLIN_H */
