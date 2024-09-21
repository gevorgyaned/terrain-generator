#include "window.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

Window::Window(size_t width, size_t height, std::string_view window_name) : 
    m_width(width), m_height(height), m_name(window_name)
{ 
    subscribe(WindowResizeEvent::get_type_s(),
        std::make_unique<EventHandler<Window>>(*this, &Window::on_window_resize)); 
    
    subscribe(KeyPressedEvent::get_type_s(),
        std::make_unique<EventHandler<Window>>(*this, &Window::on_key_pressed)); 
}

Window::~Window() {
    unsubscribe(WindowResizeEvent::get_type_s(), 
        EventHandler<Window>::get_type_s());

    unsubscribe(KeyPressedEvent::get_type_s(), 
        EventHandler<Window>::get_type_s());

    glfwDestroyWindow(m_window);
}

bool Window::should_close() const {
    return glfwWindowShouldClose(m_window);
}

void Window::create_window()
{
    m_window = glfwCreateWindow(m_width, m_height, m_name.data(), NULL, NULL);
}

void Window::setup()
{
    glfwSetFramebufferSizeCallback(m_window, 
    []([[maybe_unused]] GLFWwindow *window, int height, int width) { 
        add_event(std::make_unique<FramebufferResizeEvent>(width, height));
    });
    
    glfwSetCursorPosCallback(m_window, 
    []([[maybe_unused]]GLFWwindow *window, double x, double y) {
        add_event(std::make_unique<MouseMovedEvent>(x, y));
    });    

    glfwSetKeyCallback(m_window, 
    []([[maybe_unused]]GLFWwindow *window, int keycode, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mode) {
        if (action == GLFW_PRESS) {
            add_event(std::make_unique<KeyPressedEvent>(static_cast<Key>(keycode)));
        } else if (action == GLFW_RELEASE) {
            add_event(std::make_unique<KeyReleasedEvent>(static_cast<Key>(keycode)));
        } 
    });    

	glfwSwapInterval(1);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::on_window_resize(Event &e) {
    auto &resize_event = static_cast<WindowResizeEvent&>(e);

    m_width = resize_event.width;
    m_height = resize_event.height;

    glfwSetWindowSize(m_window, m_width, m_height);
}

void Window::on_key_pressed(Event &e)
{
    auto &key_event = static_cast<KeyPressedEvent&>(e);

    if (key_event.key == Key::X) {
        glfwSetWindowShouldClose(m_window, true);
    }
}

void Window::on_framebuffer_resize(Event &e) {
    auto &resize_event = static_cast<WindowResizeEvent&>(e);

    m_width = resize_event.width;
    m_height = resize_event.height;

    glfwSetWindowSize(m_window, m_width, m_height);
}

