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

#include <iostream>
#include <set>

extern EventManager event_manager;

class Application {
public:
    Application(Window &&window, Camera const &camera);

    void run();
    void update();
    void draw();

private:
    void set_shaders();

private:
    Window m_window;
    Camera m_camera;

    std::unordered_map<std::string, SP<Shader>> m_shaders; 
    std::set<UP<Drawable>> m_meshes;

    float last_time { 0.0f };
    float fps_hint { 60.0f };
};

void setup();
void enable_optimizations();
void set_context();

#endif /* APPLICATION_HPP */

