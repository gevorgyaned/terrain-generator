#include "application.hpp"
#include "shader.hpp"

extern EventManager event_manager;

int main()
{
    Window main_window(800, 600, "terrain");

    Application main_app(Window(800, 600, "terrain"), Camera {});

    auto shader_res = Shader::create("shaders/vert.glsl", "shaders/frag.glsl");
    if (const auto *err_value = std::get_if<std::string>(&shader_res)) {
        exit(1);
    }

    auto& shader = std::get<Shader>(shader_res);

    constexpr glm::vec3 target_color(0.039f, 0.5f, 0.3f);



    while (main_window.should_close()) {
// process ()       
        const auto current = static_cast<float>(glfwGetTime());

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
        

		glfwSwapBuffers(main_window.get_window());
		glfwPollEvents();    
    }

    glfwTerminate();
}

