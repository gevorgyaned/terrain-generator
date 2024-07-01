#include "../../external/glad/glad.h"
#include <glm/glm.hpp>


class Grass {
public:
    Grass(glm::vec3 base_color = glm::vec3(0.2f, 1.0f, 0.0f));

private:
    void generate_buffers();

    static float cubic_bezier(float t);
private:
    GLuint m_VAO, m_VBO, m_EBO;
    glm::vec3 m_base_color;
};

Grass::Grass(glm::vec3 base_color)
    : m_base_color { base_color }
{


}

float Grass::cubic_bezier(float t)
{
    static std::array<float, 8> key_points = { 0.0f, 0.0f, 0.0f, 0.2f, 0.1f, 0.3f, 0.15f, 0.3f };

    static float width = 0.3f;

    return (;
}

void Grass::generate_buffers()
{
    
}
