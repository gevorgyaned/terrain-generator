#ifndef TERRAIN_H
#define TERRAIN_H

#include "../../external/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include <noise_gen.h>
#include <perlin.h>
#include <shader.h>
#include <cstdlib>
#include <unistd.h>
#include <tuple>
#include <type_traits>

template <typename T, typename = std::enable_if<std::is_floating_point_v<T>>>
struct Vertex {
    Vertex(T x, T y, T z) 
    {  
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vertex() = default;

    std::tuple<T, T, T> get_values() const {
        return { x, y, z };
    }

    template <typename U>
    friend Vertex<U> operator-(const Vertex<U>& a, const Vertex<U>& b);

    operator glm::vec3() {
        return glm::vec3(x, y, z);
    }

    T x;
    T y;
    T z;
};

class TerrainMesh {

public:
    TerrainMesh(NoiseGenerator& gen, std::size_t width = 100, std::size_t height = 100, double scale = 40.0);

public:
    int get_vertices_size() const;
    int get_indicies_size() const;

    std::size_t get_width() const;
    std::size_t get_height() const;

	// getters for buffers of vertex objects
    GLuint VAO() const {
		return m_vertices_VAO;
	}	

    GLuint VBO() const {
		return m_vertices_VBO;
	}	

	// getters for buffers of surface normals objects
    GLuint surf_VBO() const {
		return m_normal_VBO;
	}	

private:
    void generate_buffers();
    
private:
    NoiseGenerator& m_gen;

    std::size_t m_width;
    std::size_t m_height;

    double m_scale;
    const float m_tile_distance = 0.10;
    const float m_x_beg = 0.0;
    const float m_z_beg = 0.0;

    unsigned m_vertices_VBO, m_vertices_VAO;
	GLuint m_normal_VAO, m_normal_VBO;

    std::vector<Vertex<float>> m_vertices;
    std::vector<Vertex<float>> m_normals;
};

#endif /* TERRAIN_H */

