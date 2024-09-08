#include "perlin.h"

std::mt19937 PerlinNoise::random_engine (std::random_device{} ());

PerlinNoise::PerlinNoise(std::size_t size)
    : m_size(size)
    , m_gradients(generate_gradients())
{ 
    std::uniform_real_distribution<> dis(0.0, 100000.0);
    m_rand = dis(random_engine);
}

std::vector<glm::vec2> PerlinNoise::generate_gradients()
{
    std::uniform_real_distribution<> dis(0.0, 100.0);
    std::vector<glm::vec2> gradients;
    gradients.reserve(m_size);

    for (size_t i = 0; i < m_size; ++i) {
        m_gradients.emplace_back(sin(dis(random_engine)), cos(dis(random_engine)));
    }

    return gradients;
}

float PerlinNoise::get_value(float x, float y)
{
    const int ix = std::floor(x);
    const int iy = std::floor(y);

    const float dx = x - static_cast<float>(ix);
    const float dy = y - static_cast<float>(iy);
    
    const glm::vec2 top_left  = get_gradient_vec(ix, iy);
    const glm::vec2 top_right = get_gradient_vec(ix + 1, iy);
    const glm::vec2 bot_left  = get_gradient_vec(ix, iy + 1);
    const glm::vec2 bot_right = get_gradient_vec(ix + 1, iy + 1);

    float d1 = glm::dot(top_left, glm::vec2(dx, dy));
    float d2 = glm::dot(top_right, glm::vec2(dx - 1.0f, dy));
    const float r1 = interpolate(d1, d2, dx);

    d1 = glm::dot(bot_left, glm::vec2(dx, dy - 1.0f));
    d2 = glm::dot(bot_right, glm::vec2(dx - 1.0f, dy - 1.0f));
    const float r2 = interpolate(d1, d2, dx);

    return interpolate(r1, r2, dy);
}

float PerlinNoise::interpolate(float a, float b, float t)
{
    float f = t * t * t * (t * (t * 6 - 15) + 10);
    return a + f * (b - a);
}

glm::vec2 PerlinNoise::get_gradient_vec(int x, int y) const
{
    return m_gradients[static_cast<long>(m_rand * x + y) % m_size];
}   
