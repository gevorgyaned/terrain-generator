#include "application.hpp"
#include "event_manager.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Application::Application(std::string_view name, size_t width, size_t height) :
    m_window(width, height, name)
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
    input = UserInput(m_window.get_window());
    glEnable(GL_DEPTH_TEST);
}

void Application::set_shaders()
{
    //for (auto &&[_name, shader] : m_shaders) {
    //    shader.use();
    //    shader.set_matrix4(m_camera.get_view_matrix(), "view");
    //    shader.set_matrix4(glm::perspective(glm::radians(45.0f), 
    //        m_window.width() / (float)m_window.height(), 0.1f, 100.f), "proj");
    //    shader.set_float3(m_camera.get_position(), "u_camera_location");
    //    shader.set_float3(m_camera.get_position(), "u_light_location");
    //    shader.set_float3({1.f, 1.f, 1.f}, "u_light_color");
    //}
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
    Camera camera;
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

    PerlinNoise noise;
    auto fbm = std::make_shared<FBM>(noise);

    TerrainMesh mesh(fbm, 4, 4);

    float last_time {};
    float current {};

    while (!m_window.should_close()) {
        glClearColor(.0f, 0.5f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        current = glfwGetTime();
        float delta_time = current - last_time;
        last_time = current;

        shader.use();

        shader.set_matrix4(camera.get_view_matrix(), "view");
        shader.set_float3(camera.get_position(), "u_camera_location");
        shader.set_float3(camera.get_position(), "u_light_location");
        shader.set_float3({1.f, 1.f, 1.f}, "u_light_color");
        shader.set_float3({1.0f, 0.0f, 0.0f}, "u_target_color");
        glm::mat4 model(1.0f);

        event_manager.dispatch_events();

        mesh.update();

        shader.set_matrix4(model, "model");
        cube.draw(shader);

        shader.use();
        shader.set_float3({0.0f, 0.31f, 0.42f}, "u_target_color");
        mesh.draw(shader);

        camera.process_keyboard(input, delta_time);

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
    //auto &shader = m_shaders.at("terrain_mesh");
    //shader.use();
    //shader.set_matrix4(m_camera.get_view_matrix(), "view");
    //shader.set_matrix4(glm::perspective(glm::radians(45.0f), 
    //    m_window.width() / (float)m_window.height(), 0.1f, 100.f), "proj");
    //shader.set_float3(m_camera.get_position(), "u_camera_location");
    //shader.set_float3(m_camera.get_position(), "u_light_location");
    //shader.set_float3({1.f, 1.f, 1.f}, "u_light_color");

    //shader.set_float3({1.0f, 0.0f, 0.0f}, "u_target_color");
    //auto *ptr = m_meshes[0].get();

    //shader.set_matrix4(static_cast<Cube *>(ptr)->model, "model");
}

