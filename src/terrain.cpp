#include <terrain.h>
#include <perlin.h>
#include <shader.h>
#include <cstdlib>
#include <unistd.h>

int TerrainMesh::get_vertices_size() const {
    return m_vertices.size() * sizeof(float);
}

int TerrainMesh::get_indicies_size() const {
    return m_indicies.size();
}

double fbm(NoiseGenerator& noise, float x, float y) {
    double val = 0.0;
    double frequency = 0.5;
    double amplitude = 4.0;

    for (int i = 0; i < 6; ++i) {
        val += noise.get_value(x * frequency, y * frequency) * amplitude;
        frequency *= 2.0;
        amplitude *= 0.5;
    }

    return val;
}

void TerrainMesh::generate_buffers() 
{
    int vert_count = 0;
    double distance = 0.10;
    double z_beg = -0.90;

    double big = 0.0;
    double small = std::numeric_limits<float>::infinity();
    for (int i = 0; i < m_width; ++i) {
        double x_beg = -0.90;

        for (int j = 0; j < m_height; ++j) {
            double height = fbm(m_gen, static_cast<double>(i) / m_scale, static_cast<double>(j) / m_scale);
           // double height = m_gen.get_value(static_cast<float>(i) / m_scale, static_cast<float>(j) / m_scale);
            big = std::max(big, height);
            small = std::min(small, height);
            m_vertices[vert_count++] = x_beg;
            m_vertices[vert_count++] = height;
            m_vertices[vert_count++] = z_beg;
            x_beg += distance;
        }

        z_beg += distance;
    }

    int ind_count = 0;
    for (int i = 0; i < m_width - 1; ++i) {
        for (int j = 0; j < m_height - 1; ++j) {
            m_indicies[ind_count++] = i * m_width + j;
            m_indicies[ind_count++] = i * m_width + j + m_width;
            m_indicies[ind_count++] = i * m_width + j + m_width + 1;

            m_indicies[ind_count++] = i * m_width + j;
            m_indicies[ind_count++] = i * m_width + j + 1;
            m_indicies[ind_count++] = i * m_width + j + m_width + 1;
        }
    }
}

GLuint TerrainMesh::EBO() const {
    return m_EBO;
}

GLuint TerrainMesh::VBO() const {
    return m_VBO;
}

GLuint TerrainMesh::VAO() const {
    return m_VAO;
}

