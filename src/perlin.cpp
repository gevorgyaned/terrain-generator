#include "perlin.h"

void PerlinNoise::fill_permutations()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    for (size_t i = 0; i < m_size; ++i) {
        m_rand_grad[i] = glm::vec2(sin(dis(g)), cos(dis(g)));
        m_permutations[i] = i + 1;
    }

    std::shuffle(m_permutations.begin(), m_permutations.end(), g);
    m_permutations.insert(m_permutations.end(), m_permutations.begin(), 
            m_permutations.end());
}

float lerp(float a, float b, float t)
{
    float f = t * t * t * (t * (t * 6 - 15) + 10);
    return a + f * (b - a);
}

float PerlinNoise::noise(float x, float y) const
{
    const int ix = std::floor(x);
    const int iy = std::floor(y);

    const float dx = x - static_cast<float>(ix);
    const float dy = y - static_cast<float>(iy);
    
    const auto top_left  = get_gradient_vec(ix, iy);
    const auto top_right = get_gradient_vec(ix + 1, iy);
    const auto bot_left  = get_gradient_vec(ix, iy + 1);
    const auto bot_right = get_gradient_vec(ix + 1, iy + 1);

    float d1 = glm::dot(top_left, glm::vec2(dx, dy));
    float d2 = glm::dot(top_right, glm::vec2(dx - 1.0f, dy));
    const float r1 = lerp(d1, d2, dx);

    d1 = glm::dot(bot_left, glm::vec2(dx, dy - 1.0f));
    d2 = glm::dot(bot_right, glm::vec2(dx - 1.0f, dy - 1.0f));
    const float r2 = lerp(d1, d2, dx);

    return lerp(r1, r2, dy);
}

glm::vec2 PerlinNoise::get_gradient_vec(int x, int y) const
{
    return m_rand_grad[(m_permutations[x % m_size] + y % m_size) % m_size];
}   
