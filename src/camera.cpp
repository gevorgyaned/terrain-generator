#include "camera.hpp"

glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(m_camera_pos, m_camera_pos + m_front, m_up);
}

std::pair<float, float> Camera::process_mouse(float x, float y) 
{
    if (first_mouse) {
        xpos = x;
        ypos = y;
        first_mouse = false;
    }
    auto res = std::make_pair(x - xpos, ypos - y); 
    xpos = x;
    ypos = y;
    return res;
}

void Camera::on_mouse_move(Event &e)
{
    auto &move_event = static_cast<MouseMovedEvent&>(e);
    auto [x, y] = process_mouse(move_event.mouse_x, move_event.mouse_y);

    x *= m_sensitivity;
    y *= m_sensitivity;
    m_yaw   += x;
    m_pitch += y;

    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    else if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    update_vectors();
}

void Camera::on_key_pressed([[maybe_unused]]Event &e)
{
    delta_time = glfwGetTime();
}

void Camera::on_key_released(Event &e)
{
    auto &key_event = static_cast<KeyReleasedEvent&>(e);
    auto current = glfwGetTime();
    process_keyboard(key_event.key, current - delta_time);
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
    glm::vec3 tmp;
    tmp.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    tmp.y = sin(glm::radians(m_pitch));
    tmp.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(tmp);
    m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_up    = glm::normalize(glm::cross(m_right, m_front));   
}

glm::vec3 Camera::get_position() const { return m_camera_pos; }

