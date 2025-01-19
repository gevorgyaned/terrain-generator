#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../events/event_manager.hpp"
#include "../events/mouse_event.hpp"
#include "../events/key_events.hpp"

#include "camera.hpp"
#include "window.hpp"
#include "shader.hpp" 
#include "terrain.hpp"
#include "drawable.hpp"
#include "usings.hpp"
#include "cube.hpp"
#include "perlin.hpp"

#include <cmath>
#include <iostream>
#include <set>

extern EventManager event_manager;

class Application {
public:
    Application(std::string_view name, size_t width, size_t height);

    void run();
    void update();
    void draw();

    void insert_shader(std::string const &shader_name, Shader shader);

private:
    void set_shaders();

public:
    Window m_window;

    UserInput input;

    Camera m_camera;

    std::unordered_map<std::string, Shader> m_shaders; 
    std::vector<UP<Drawable>> m_meshes;

    float last_time { 0.0f };
    float fps_hint { 60.0f };
};

void setup();
void enable_optimizations();
void set_context();

#endif /* APPLICATION_HPP */

