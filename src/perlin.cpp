#include "../include/perlin.h"

void PerlinNoise::fill_permutations()
{
    std::cout << m_permutations.size() << std::endl;
    for (int i = 0; i < m_size; ++i) {
        m_permutations[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(m_permutations.begin(), m_permutations.end(), g);

    m_permutations.insert(m_permutations.end(), m_permutations.begin(), 
            m_permutations.end());
}

double PerlinNoise::get_value(double x, double y) 
{
    uint32_t ix = std::floor(x);
    uint32_t iy = std::floor(y);

    double dx = x - ix;
    double dy = y - iy;
    
    vec2 top_left  = get_gradient_vec(ix, iy);
    vec2 top_right = get_gradient_vec(ix + 1, iy);
    vec2 bot_left  = get_gradient_vec(ix, iy + 1);
    vec2 bot_right = get_gradient_vec(ix + 1, iy + 1);

    double d1, d2;
    d1 = top_left.dot(vec2(dx, dy)); 
    d2 = top_right.dot(vec2(dx - 1.0, dy)); 
    double r1 = util::interpolate(d1, d2, dx); 

    d1 = bot_left.dot(vec2(dx, dy - 1.0)); 
    d2 = bot_right.dot(vec2(dx - 1.0, dy - 1.0)); 
    double r2 = util::interpolate(d1, d2, dx);

    return util::interpolate(r1, r2, dy);
}

vec2 PerlinNoise::get_gradient_vec(int x, int y) const
{
    int index = m_permutations[(m_permutations[x] + y) % m_size];
    return util::get_random_gradient(index);
}   
