#include "../external/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "shader.h"
#include "utility.h"

int main(int argc, char *argv[])
{
    if (glfwInit() != 0) {
        std::cerr << "glfwInit" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEX_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEX_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    atexit(glfwTerminate);

    GLFWwindow *window = glfwCreateWindow(800, 600, "terrain generator", NULL, NULL);
    if (window == NULL) {
        std::cerr << "glfwCreateWindow" << std::endl;
        exit(1);
    }

    glfwSetContextCurrent(window);

    
    




}
