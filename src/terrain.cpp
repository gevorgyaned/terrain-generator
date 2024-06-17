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

void TerrainMesh::generate_buffers() 
{
    int vert_count = 0;
    double distance = 0.05;
    double z_beg = -0.90;

    for (int i = 0; i < m_width; ++i) {
        double x_beg = -0.90;

        for (int j = 0; j < m_height; ++j) {
            double height = (m_gen.get_value(i + rand() % 100 / m_scale, j + rand() % 100  / m_scale) / 2.0) + 0.5;

            m_vertices[vert_count++] = x_beg;
            m_vertices[vert_count++] = height - 0.5;
            m_vertices[vert_count++] = z_beg;
            x_beg += distance;
        }

        z_beg += distance;
    }

    std::cout << "vert_count: " << vert_count << std::endl;

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

    std::cout << "ind_count: " << ind_count << std::endl;
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

