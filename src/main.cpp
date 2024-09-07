#include "terrain.h" 
#include "perlin.h" 
#include "shader.h" 
#include "camera.h" 
#include "terrain_renderer.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 

#include <memory>

constexpr int SCR_WIDTH = 800;
constexpr int SCR_HEIGHT = 800;

Camera camera; 

float delta_time = 0.0f; 
float last_frame = 0.0f; 
bool first_mouse = true;

float lastX = static_cast<float>(SCR_WIDTH) / 2.0f;
float lastY = static_cast<float>(SCR_HEIGHT) / 2.0f;

void process(GLFWwindow *window, TerrainParams& params);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);

Param current = Param::Amplitude;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    GLFWwindow *window = glfwCreateWindow(800, 600, "transform", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "glfwCreateWindow" << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);    

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }   

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    auto shader_res = Shader::create("../shaders/vert.glsl", "../shaders/frag.glsl");
    if (const auto *err_value = std::get_if<std::string>(&shader_res)) {
        std::cerr << *err_value << std::endl;
        exit(1);
    }

    auto& shader = std::get<Shader>(shader_res);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f),  SCR_WIDTH / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);
    glm::vec3 target_color(0.039f, 0.5f, 0.3f);

    shader.use();
    shader.set_matrix4(proj, "proj")
        .set_float3({0.054, 0.5f, 0.14f}, "u_target_color")
        .set_float3(camera.get_position(), "u_light_location")
        .set_float3(target_color, "u_light_color");

    TerrainParams params;

    FBM fbm(std::make_shared<PerlinNoise>());
    TerrainMesh mesh(fbm, 4, 4, params);

    TerrainRenderer renderer(mesh);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        process(window, params);
        
        mesh.reset(params);

        const auto current = static_cast<float>(glfwGetTime());
        delta_time = current - last_frame;
        last_frame = current;

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // renderering 
        glm::mat4 model(1.f);
        glm::mat4 view = camera.get_view_matrix();

        shader.use();

        shader.set_matrix4(model, "model")
            .set_matrix4(view, "view")
            .set_float3(camera.get_position(), "u_camera_location");
        
        renderer.draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();    
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void process(GLFWwindow *window, TerrainParams& params) {
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

void mouse_callback(GLFWwindow *, const double xPos, const double yPos)
{
    const auto xpos = static_cast<float>(xPos);
    const auto ypos = static_cast<float>(yPos);

    if (first_mouse) {
        lastX = xpos;
        lastY = ypos;
        first_mouse = false;
    }

    const float xoffset = xpos - lastX;
    const float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.process_mouse(xoffset, yoffset);
}
