#include "application.hpp"

#include <cmath>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Application::Application(std::string_view name, size_t width, size_t height, Camera const &camera) :
    m_window(width, height, name), m_camera(camera)
{ 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif /* __APPLE__ */

    m_window.create_window();
    glfwMakeContextCurrent(m_window.get_window());

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    m_window.setup();

    glEnable(GL_DEPTH_TEST);
    //enable_optimizations();
}

void Application::set_shaders()
{
    for (auto &&[_name, shader] : m_shaders) {
        shader.use();
        shader.set_matrix4(m_camera.get_view_matrix(), "view");
        shader.set_matrix4(glm::perspective(glm::radians(45.0f), 
            m_window.width() / (float)m_window.height(), 0.1f, 100.f), "proj");
        shader.set_float3(m_camera.get_position(), "u_camera_location");
        shader.set_float3(m_camera.get_position(), "u_light_location");
        shader.set_float3({1.f, 1.f, 1.f}, "u_light_color");
    }
}

void enable_optimizations()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glDepthFunc(GL_LESS);
}

void Application::run()
{
    Cube cube;

    auto shader_res = Shader::create("shaders/vert.glsl", "shaders/frag.glsl");
    if (auto err_value = std::get_if<std::string>(&shader_res)) {
        std::cerr << *err_value << std::endl;
        exit(1);
    }

    auto shader = std::get<Shader>(shader_res);
    shader.use();

    shader.set_matrix4(glm::perspective(glm::radians(45.0f), 
        m_window.width() / (float)m_window.height(), 0.1f, 100.f), "proj");

    while (!m_window.should_close()) {
        glClearColor(.0f, 0.5f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        shader.set_matrix4(m_camera.get_view_matrix(), "view");
        std::cout << glm::to_string(m_camera.get_view_matrix()) << std::endl;
        shader.set_float3(m_camera.get_position(), "u_camera_location");
        shader.set_float3(m_camera.get_position(), "u_light_location");
        shader.set_float3({1.f, 1.f, 1.f}, "u_light_color");
        shader.set_float3({1.0f, 0.0f, 0.0f}, "u_target_color");
        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f * -abs(cos(glfwGetTime()))));
        shader.set_matrix4(model, "model");

        event_manager.dispatch_events();

        cube.draw(shader);
        glfwSwapBuffers(m_window.get_window());
        glfwPollEvents();
    } 
}

void Application::draw()
{
    m_meshes[0]->draw(m_shaders.at("terrain_mesh"));
    return;

    for (auto &entity : m_meshes) {
        entity->draw(m_shaders[entity->get_shader_name()]);
    }
}

void Application::update()
{
    auto &shader = m_shaders.at("terrain_mesh");
    shader.use();
    shader.set_matrix4(m_camera.get_view_matrix(), "view");
    shader.set_matrix4(glm::perspective(glm::radians(45.0f), 
        m_window.width() / (float)m_window.height(), 0.1f, 100.f), "proj");
    shader.set_float3(m_camera.get_position(), "u_camera_location");
    shader.set_float3(m_camera.get_position(), "u_light_location");
    shader.set_float3({1.f, 1.f, 1.f}, "u_light_color");

    shader.set_float3({1.0f, 0.0f, 0.0f}, "u_target_color");
    auto *ptr = m_meshes[0].get();

    shader.set_matrix4(static_cast<Cube *>(ptr)->model, "model");
}

