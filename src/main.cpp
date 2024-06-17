#include <terrain.h>
#include <perlin.h>
#include <shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
 
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

    auto shader_res = Shader::create("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    if (const auto *err_value = std::get_if<std::string>(&shader_res)) {
        std::cerr << err_value << std::endl;
        exit(1);
    }

    auto shader = std::get<Shader>(shader_res);

    PerlinNoise noise;
    TerrainMesh mesh(noise, 50, 50);

    while (!glfwWindowShouldClose(window)) {
        process(window);

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model(1.f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));

        glm::mat4 view = glm::mat4(1.f);
        view = glm::translate(view, glm::vec3(0.f, 2 * -abs(sin(glfwGetTime())), -2.0f));
        view = glm::rotate(view, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));

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
