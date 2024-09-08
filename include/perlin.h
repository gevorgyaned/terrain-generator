#ifndef PERLIN_H
#define PERLIN_H

#include "utility.h"
#include "noise.h"

#include <random>
#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

class PerlinNoise : public NoiseGenerator {
public:
    explicit PerlinNoise(const std::size_t size = 512);

    float get_value(float x, float y) override;

    float get_value(float x, float y, float z) override
    { (void)x; (void)y; (void)z; assert(false && "Not implemented"); }

private:
    std::vector<glm::vec2> generate_gradients();
    glm::vec2 get_gradient_vec(int x, int y) const;
    std::size_t get_size() const;

    static float interpolate(float a, float b, float t);

    static std::mt19937 random_engine;

private:
    const std::size_t m_size;
    std::vector<glm::vec2> m_gradients;
    double m_rand;

};

#endif /* PERLIN_H */

