#ifndef NOISE_GEN_H
#define NOISE_GEN_H

class NoiseGenerator {
public:
    virtual double get_value(double x, double y) = 0;
};

#endif /* NOISE_GEN_H */
