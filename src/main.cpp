#include "terrain.h" 
#include "perlin.h" 
#include "shader.h" 
#include "camera.h" 
#include "terrain_renderer.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

constexpr int SCR_WIDTH = 800;
constexpr int SCR_HEIGHT = 800;

Camera camera; 

float delta_time = 0.0f; 
float last_frame = 0.0f; 
bool first_mouse = true;

float lastX = static_cast<float>(SCR_WIDTH) / 2.0f;
float lastY = static_cast<float>(SCR_HEIGHT) / 2.0f;

void process(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xPos, double yPos);

float amplitude = 2.0f;
float frequency = 0.5f;
float scale = 40.f;

float *current = &amplitude;

bool is_changed = false;

GLenum cursor_mode = GLFW_CURSOR_DISABLED;

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    auto shader_res = Shader::create("../shaders/vert.glsl", "../shaders/frag.glsl");
    if (const auto *err_value = std::get_if<std::string>(&shader_res)) {
        std::cerr << *err_value << std::endl;
        exit(1);
    }

    auto& shader = std::get<Shader>(shader_res);

    constexpr glm::vec3 target_color(0.039f, 0.5f, 0.3f);
    constexpr glm::vec3 light_position(0.0f, 4.0f, 0.0f);
	glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, cursor_mode);

    int frames = 0;
    auto last = static_cast<float>(glfwGetTime());

    PerlinNoise noise;
    TerrainMesh mesh(noise, 3, 2, scale, amplitude, frequency);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        process(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Configuration");
        ImGui::SliderFloat("amplitude: ", &amplitude, 0.1f, 10.0f);
        ImGui::SliderFloat("frequency: ", &frequency, 0.1f, 10.0f);
        ImGui::SliderFloat("scale: ", &scale, 0.1f, 120.f);
        ImGui::End();

        ImGui::Render();
        
        mesh.reset(scale, amplitude, frequency);

        const auto current = static_cast<float>(glfwGetTime());
        delta_time = current - last_frame;
        last_frame = current;

        frames++;
        if (current - last >= 1.0f) {
            printf("%lf ms\n", 1000.0 / static_cast<double>(frames));
            printf("%d fps\n",  frames );
            frames = 0;
            last += 1.0f;
        }

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // for rendering in polygon mode
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // rendering 
        glm::mat4 model(1.f);
        glm::mat4 view = camera.get_view_matrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f),  SCR_WIDTH / static_cast<float>(SCR_HEIGHT), 0.1f, 100.f);

        shader.use();

        shader.set_matrix4(model, "model")
            .set_matrix4(view, "view")
            .set_matrix4(proj, "proj")
            .set_float3(target_color, "u_target_color")
            .set_float3(camera.get_position(), "u_camera_location")
            .set_float3(camera.get_position(), "u_light_location")
            .set_float3(glm::vec3(1.0f, 1.0f, 1.0f), "u_light_color");

        for (int i = 0; i < mesh.m_chunks.size(); ++i) {
            glBindVertexArray(mesh.m_chunks[i].VAO);
            glDrawElements(GL_TRIANGLES, mesh.m_chunks[i].indicies.size(), GL_UNSIGNED_INT, 0);
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();    
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
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
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) 
        current = &amplitude;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) 
        current = &frequency;
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) 
        current = &scale; 
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
        is_changed = true;
        *current += 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS) {
        is_changed = true;
        *current -= 0.1;
    }
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
