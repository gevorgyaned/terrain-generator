#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad/glad.h>

#include "../events/event_manager.hpp"
#include "../events/mouse_event.hpp"
#include "../events/key_events.hpp"

#include "camera.hpp"
#include "window.hpp"

#include <iostream>

class Application {
public:
    Application(Window &&window, Camera const &camera);


private:
    void setup_context();

private:
    Window m_window;
    Camera m_camera;
};

#endif /* APPLICATION_HPP */
