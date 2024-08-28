#ifndef NOISE_H
#define NOISE_H

class NoiseGenerator {
public:
    virtual float noise(float x, float y) const = 0;

    virtual ~NoiseGenerator() = default;
};

#endif /* NOISE_H */
