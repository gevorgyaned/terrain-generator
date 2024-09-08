#ifndef FBM_HPP
#define FBM_HPP

#include "noise.hpp"

#include <memory>

class FBM {
public:
    FBM(std::shared_ptr<NoiseGenerator> noise, float amplitude = 2.0f, float lacunarity = 2.0f, float gain = 0.5f, float frequency = 0.6f, int octaves = 6)
        : m_noise{noise}, m_amplitude{amplitude}, m_lacunarity{lacunarity}, m_gain{gain}, m_frequency{frequency}, m_octaves{octaves}
    { }

    float generate(float x, float y) const;

    void set_amplitude(float value) { m_amplitude = value; }
    void set_lacunarity(float value) { m_lacunarity = value; }
    void set_gain(float value) { m_gain = value; }
    void set_frequency(float value) { m_frequency = value; }
    void set_octaves(int value) { m_octaves = value; }

private:
    std::shared_ptr<NoiseGenerator> m_noise;

    float m_amplitude;
    float m_lacunarity;
    float m_gain;
    float m_frequency;
    int m_octaves;
};

#endif /* FBM_HPP */

