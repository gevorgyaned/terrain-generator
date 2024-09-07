#ifndef UTIL_H
#define UTIL_H

struct TerrainParams {
    float amplitude;
    float frequency;
    float gain;
    float lucarity;
    int octaves;
    
    bool operator!=(const TerrainParams& rhs) const;
};

#endif /* UTIL_H */

