#include "camera.hpp"

#include <iostream>

glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(m_camera_pos, m_camera_pos + m_front, m_up);
}

void Camera::process_mouse(float x, float y) 
{
    x *= m_sensitivity;
    y *= m_sensitivity;

    m_yaw += x;
    m_pitch += y;

    if (m_pitch > 89.0f) {
        m_pitch = 89.0f;
    } else if (m_pitch < -89.0f) {
        m_pitch = -89.0f;
    }

    update_vectors();
}

void Camera::on_mouse_move(Event &e)
{
    auto &move_event = static_cast<MouseMovedEvent&>(e);
    if (first_mouse) {
        xpos = move_event.mouse_x;
        ypos = move_event.mouse_y;
        first_mouse = false;
    }
    auto xoffset = move_event.mouse_x - xpos;
    auto yoffset = ypos - move_event.mouse_y;
    
    xpos = move_event.mouse_x;
    ypos = move_event.mouse_y;

    process_mouse(xoffset, yoffset);
}

void Camera::on_key_pressed(Event &e)
{
    auto &key_event = static_cast<KeyPressedEvent&>(e);
    auto key = key_event.key;

    if (key == Key::W || key == Key::A || key == Key::S || key == Key::D)
        delta_time = glfwGetTime();
}

void Camera::on_key_released(Event &e)
{
    auto &key_event = static_cast<KeyReleasedEvent&>(e);
    auto current = glfwGetTime();
    process_keyboard(key_event.key, current - delta_time);
    delta_time = current;
}

void Camera::process_keyboard(Key key, float delta)
{
    float velocity = m_speed * delta;
    switch (key) {
    case Key::W:
        m_camera_pos += m_front * velocity;
        break;
    case Key::S:
        m_camera_pos -= m_front * velocity;
        break;
    case Key::D:
        m_camera_pos += m_right * velocity;
        break;
    case Key::A:
        m_camera_pos -= m_right * velocity;
        break;
    case Key::Q:
        m_camera_pos += m_up * velocity;
        break;
    case Key::E:
        m_camera_pos -= m_up * velocity;
        break;
    default:
        break;
    }
}

void Camera::update_vectors()
{
    std::cout << __func__ << std::endl;
    glm::vec3 tmp;
    tmp.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    tmp.y = sin(glm::radians(m_pitch));
    tmp.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(tmp);
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up    = glm::normalize(glm::cross(m_right, m_front));   

    std::cout << "m_front" << glm::to_string(m_front) << std::endl;
}

glm::vec3 Camera::get_position() const { return m_camera_pos; }

