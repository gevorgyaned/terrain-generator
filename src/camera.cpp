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

void Camera::process_keyboard(UserInput input, float delta)
{
    float velocity = m_speed * delta;
    if (input.is_key_pressed(Key::W)) {
        m_camera_pos += m_front * velocity;
    } 
    if (input.is_key_pressed(Key::S)) {
        m_camera_pos -= m_front * velocity;
    }
    if (input.is_key_pressed(Key::D)) {
        m_camera_pos += m_right * velocity;
    }
    if (input.is_key_pressed(Key::A)) {
        m_camera_pos -= m_right * velocity;
    }
    if (input.is_key_pressed(Key::Q)) {
        m_camera_pos += m_up * velocity;
    }
    if (input.is_key_pressed(Key::E)) {
        m_camera_pos -= m_up * velocity;
    }
}

void Camera::update_vectors()
{
    glm::vec3 tmp;
    tmp.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    tmp.y = sin(glm::radians(m_pitch));
    tmp.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(tmp);
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up    = glm::normalize(glm::cross(m_right, m_front));   
}

glm::vec3 Camera::get_position() const { return m_camera_pos; }

