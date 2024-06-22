#include <camera.h>

glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(m_camera_pos, m_camera_pos + m_front, m_up);
}

void Camera::process_mouse(float x, float y)
{
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

void Camera::process_keyboard(MoveDirection dir, float delta)
{
    float velocity = m_speed * delta;
    switch (dir) {
    case MoveDirection::Forward:
        m_camera_pos += m_front * velocity;
        break;
    case MoveDirection::Backward:
        m_camera_pos -= m_front * velocity;
        break;
    case MoveDirection::Right:
        m_camera_pos += m_right * velocity;
        break;
    case MoveDirection::Left:
        m_camera_pos -= m_right * velocity;
        break;
    case MoveDirection::Up:
        m_camera_pos += m_up * velocity;
        break;
    case MoveDirection::Down:
        m_camera_pos -= m_up * velocity;
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
