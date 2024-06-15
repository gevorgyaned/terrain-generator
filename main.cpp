#include <iostream>
#include <fstream>
#include <vector>
#include "include/perlin.h"

// Utility function to save Perlin noise to a PGM image file
void save_pgm(const std::string& filename, const std::vector<std::vector<double>>& data, int width, int height) {
    std::ofstream ofs(filename, std::ios::out | std::ios::binary);
    ofs << "P5\n" << width << " " << height << "\n255\n";
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            if ( i < 0 || i >= width || j < 0 || j >= width)
                std::cout << "refgrewg" << std::endl;
            ofs << static_cast<unsigned char>(data[j][i] * 255);
        }
    }
    ofs.close();
}

int main() {
    const int width = 200;
    const int height = 200;
    const double scale = 0.1;

    try {
        PerlinNoise perlin;

        std::vector<std::vector<double>> noise(height, std::vector<double>(width));

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
            if ( i < 0 || i >= width || j < 0 || j >= width)
                std::cout << "refgrewg" << std::endl;
                double ni = i * scale;
                double nj = j * scale;
                noise[j][i] = (perlin.get_value(ni, nj) / 2.0) + 0.5;
            }
        }

        save_pgm("perlin_noise.pgm", noise, width, height);

        std::cout << "Perlin noise generated and saved to perlin_noise.pgm" << std::endl;
    } 
     catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}

