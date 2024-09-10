#include "application.hpp"

Application::Application(Window &&window, Camera const &camera) :
    m_window(std::move(window)), m_camera(camera)
{ 
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }  
}

void setup()
{
    set_context();
    enable_optimizations();
}

void Application::set_shaders()
{
    for (auto &&[_name, shader] : m_shaders) {
        shader->set_matrix4(m_camera.get_view_matrix(), "view");
        shader->set_matrix4(glm::perspective(glm::radians(45.0f), 
            m_window.width() / (float)m_window.height(), 0.1f, 100.f), "proj");
        shader->set_float3(m_camera.get_position(), "u_camera_location");
        shader->set_float3(m_camera.get_position(), "u_light_location");
    }
}

void enable_optimizations()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void set_context()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif /* __APPLE__ */
}

void Application::run()
{
    while (!m_window.should_close()) {

        float current = glfwGetTime();
        if (last_time - current > 1.0f / fps_hint) {
            last_time = current;
            event_manager.dispatch_events();
            update(); 
            draw();
        }

        glfwPollEvents();
    } 
}

void Application::draw()
{
    for (auto &entity : m_meshes) {
        entity->draw(m_shaders[entity->get_shader_name()]);
    }
}

void Application::update()
{
    set_shaders();
}
