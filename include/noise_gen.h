#ifndef NOISE_GEN_H
#define NOISE_GEN_H

class NoiseGenerator {
public:
    virtual ~NoiseGenerator() = default;

    virtual float get_value(float x, float y) = 0;
};

#endif /* NOISE_GEN_H */
