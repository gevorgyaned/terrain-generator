#ifndef INPUT_HPP
#define INPUT_HPP

#include <utility>

#include "key.hpp"

class UserInput {
public:
    UserInput(GLFWwindow *window) : _window{window} {}

    bool is_key_pressed(Key key) {
        return glfwGetKey(_window, static_cast<GLenum>(key)) == GLFW_PRESS; 
    }

    bool is_key_released(Key key) {
        return !is_key_pressed(key); 
    }

    auto get_mouse_coords() 
    {
        double xpos, ypos;
        glfwGetCursorPos(_window, &xpos, &ypos);
        return std::make_pair(xpos, ypos);
    }

private:
    GLFWwindow *_window;
};

#endif /* INPUT_HPP */

