#include <terrain.h>
#include <perlin.h>
#include <shader.h>
#include <camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;

Camera camera;
float delta_time = 0.0f;	
float last_frame = 0.0f;
bool first_mouse = true;

float lastX = static_cast<float>(SCR_WIDTH) / 2.0f;
float lastY = static_cast<float>(SCR_HEIGHT) / 2.0f;

void process(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif 

    atexit(glfwTerminate);
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "transform", NULL, NULL);
    if (window == NULL) {
        std::cerr << "glfwCreateWindow" << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }   

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    auto shader_res = Shader::create("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    if (const auto *err_value = std::get_if<std::string>(&shader_res)) {
        std::cerr << err_value << std::endl;
        exit(1);
    }

    auto shader = std::get<Shader>(shader_res);
    PerlinNoise noise;
    TerrainMesh mesh(noise, 100, 100);

    while (!glfwWindowShouldClose(window)) {
        process(window);

        float current = static_cast<float>(glfwGetTime());
        delta_time = current - last_frame;
        last_frame = current;

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model(1.f);
        glm::mat4 view = camera.get_view_matrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f),  SCR_WIDTH / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);

        shader.use();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        shader.set_matrix(view, "view");
        shader.set_matrix(proj, "proj");
        shader.set_matrix(model, "model");
        shader.set_float({0.0f, 0.f, 1.f}, "col");

        glBindVertexArray(mesh.VAO());
        glEnableVertexAttribArray(0);
        glDrawElements(GL_TRIANGLES, mesh.get_indicies_size(), GL_UNSIGNED_INT, 0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_POLYGON_OFFSET_LINE);
        glPolygonOffset(-1.0f, -1.0f); 
        shader.set_float({1.0f, 0.34f, 0.48f}, "col"); 
        
        glDrawElements(GL_TRIANGLES, mesh.get_indicies_size(), GL_UNSIGNED_INT, 0);
        glDisable(GL_POLYGON_OFFSET_LINE);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
}

void process(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true); 

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        camera.process_keyboard(MoveDirection::Forward, delta_time); 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        camera.process_keyboard(MoveDirection::Backward, delta_time); 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.process_keyboard(MoveDirection::Left, delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.process_keyboard(MoveDirection::Right, delta_time);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.process_keyboard(MoveDirection::Up, delta_time);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.process_keyboard(MoveDirection::Down, delta_time);
}


void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
    float xpos = static_cast<float>(xPos);
    float ypos = static_cast<float>(yPos);

    if (first_mouse)
    {
        lastX = xpos;
        lastY = ypos;
        first_mouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.process_mouse(xoffset, yoffset);
}
