#ifndef CUBE_HPP
#define CUBE_HPP

#include "drawable.hpp"
#include "shader.hpp"
#include "usings.hpp"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Cube : public Drawable {
public:
   Cube(); 

   void draw(Shader shader) const override;
   std::string get_shader_name() const override { return "terrain_mesh"; }

public:
    glm::mat4 model; 
    GLuint m_VAO, m_VBO;

    static float vertices[];
};

#endif /* CUBE_HPP */

