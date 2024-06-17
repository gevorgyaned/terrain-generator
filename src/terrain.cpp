#include "../include/terrain.h"
#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../external/glm/glm/gtc/type_ptr.hpp"
#include "../include/perlin.h"
#include "../include/shader.h"
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
    double distance = 0.10;
    double z_beg = -0.5;

    for (int i = 0; i < m_width; ++i) {
        double x_beg = -0.5;

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


// Delte after testing

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
 
const char *vertex_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 view;\n"
    "uniform mat4 proj;\n"
    "uniform mat4 model;\n"
    "out vec3 color;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = proj * view * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   color = aPos;\n"
    "}\0";

const char *fragment_source = "#version 330 core\n"
    "in vec3 color;\n"
    "void main()\n"
    "{\n"
    "   gl_FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\0";

void process(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
   } 
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    atexit(glfwTerminate);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "transform", NULL, NULL);
    if (window == NULL) {
        std::cerr << "glfwCreateWindow" << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }   

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    auto shader = Shader (std::string(vertex_source), std::string(fragment_source));

    PerlinNoise noise;

    TerrainMesh mesh(noise, 10, 10);

    mesh.debug();

    while (!glfwWindowShouldClose(window)) {
        process(window);

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model(1.f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));

        glm::mat4 view = glm::mat4(1.f);
        view = glm::translate(view, glm::vec3(0.f, 0.f, -2.0f));

        glm::mat4 proj = glm::perspective(glm::radians(45.0f),  SCR_WIDTH / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);

        shader.set_matrix(view, "view");
        shader.set_matrix(proj, "proj");
        shader.set_matrix(model, "model");

        glBindVertexArray(mesh.VAO());           
        glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, mesh.get_indicies_size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
}
