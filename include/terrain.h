#ifndef TERRAIN_H
#define TERRAIN_H

#include "noise_gen.h"

#include "../../external/glad/glad.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

class TerrainMesh {
public:
    TerrainMesh(NoiseGenerator& gen, std::size_t width = 100, std::size_t height = 100, 
            double scale = 40.0) 
        : m_gen { gen }
        , m_width { width + 1 }
        , m_height { height + 1 }
        , m_scale { scale }
        , m_vertices ( m_width * m_height * 3)
        , m_indicies ( width * height  * 6 )
    {
        generate_buffers();

        glGenVertexArrays(1, &m_VAO);

        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), 
                m_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(unsigned),
                m_indicies.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glBindVertexArray(0);
    }

public:
    int get_vertices_size() const;
    int get_indicies_size() const;

    std::size_t get_width() const;
    std::size_t get_height() const;

    GLuint VAO() const;
    GLuint EBO() const;
    GLuint VBO() const;
private:
    void generate_buffers();
    
private:
    NoiseGenerator& m_gen;

    std::size_t m_width;
    std::size_t m_height;

    double m_scale;

    unsigned m_VBO, m_VAO, m_EBO;
    std::vector<float> m_vertices;
    std::vector<unsigned> m_indicies;
};

#endif /* TERRAIN_H */
