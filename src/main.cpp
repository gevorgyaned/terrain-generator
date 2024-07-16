#include <terrain.h> 
#include <perlin.h> 
#include <shader.h> 
#include <camera.h> 
#include <terrain_renderer.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

const int SCR_WIDTH = 800; const int SCR_HEIGHT = 800;

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

    auto shader_res = Shader::create("../shaders/vert.glsl", "../shaders/frag.glsl");
    if (const auto *err_value = std::get_if<std::string>(&shader_res)) {
        std::cerr << *err_value << std::endl;
        exit(1);
    }

    auto& shader = std::get<Shader>(shader_res);

    PerlinNoise noise;
    TerrainMesh mesh(noise, 4, 4);

	TerrainRenderer renderer(mesh);

    const glm::vec3 target_color(0.0f, 0.39f, 0.1f);
    const glm::vec3 light_position(0.0f, 4.0f, 0.0f);
	glfwSwapInterval(0);

    int frames = 0;
    float last = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        process(window);

        float current = static_cast<float>(glfwGetTime());
        delta_time = current - last_frame;
        last_frame = current;

        frames++;
        if (current - last >= 1.0f) {
            printf("%lf ms\n", 1000.0 / double( frames) );
            printf("%d fps\n",  frames );
            frames = 0;
            last += 1.0f;
        }

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // for rendering in polygon mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
            .set_float3(light_position, "u_light_location")
            .set_float3(glm::vec3(1.0f, 1.0f, 1.0f), "u_light_color");

		renderer.draw(shader);

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

void mouse_callback(GLFWwindow *, double xPos, double yPos)
{
    float xpos = static_cast<float>(xPos);
    float ypos = static_cast<float>(yPos);

    if (first_mouse) {
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

