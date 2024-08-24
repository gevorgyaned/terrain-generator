#include "perlin.h"

void PerlinNoise::fill_permutations()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);

    for (size_t i = 0; i < m_size; ++i) {
        m_rand_grad[i] = vec2(sin(dis(g)), cos(dis(g)));
        m_permutations[i] = i + 1;
    }

    std::shuffle(m_permutations.begin(), m_permutations.end(), g);
    m_permutations.insert(m_permutations.end(), m_permutations.begin(), 
            m_permutations.end());
}

float PerlinNoise::get_value(float x, float y)
{
    const int ix = std::floor(x);
    const int iy = std::floor(y);

    const float dx = x - static_cast<float>(ix);
    const float dy = y - static_cast<float>(iy);
    
    const vec2 top_left  = get_gradient_vec(ix, iy);
    const vec2 top_right = get_gradient_vec(ix + 1, iy);
    const vec2 bot_left  = get_gradient_vec(ix, iy + 1);
    const vec2 bot_right = get_gradient_vec(ix + 1, iy + 1);

    float d1 = top_left.dot(vec2(dx, dy));
    float d2 = top_right.dot(vec2(dx - 1.0f, dy));
    const float r1 = util::interpolate(d1, d2, dx);

    d1 = bot_left.dot(vec2(dx, dy - 1.0f));
    d2 = bot_right.dot(vec2(dx - 1.0f, dy - 1.0f));
    const float r2 = util::interpolate(d1, d2, dx);

    return util::interpolate(r1, r2, dy);
}

vec2 PerlinNoise::get_gradient_vec(int x, int y) const
{
    return m_rand_grad[(m_permutations[x % m_size] + y % m_size) % m_size];
}   
