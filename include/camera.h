#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class MoveDirection {
    Forward,
    Backward,
    Right,
    Left,
    Up,
    Down
};

class Camera {
public:
	explicit Camera(glm::vec3 camera_pos = glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), float yaw = -90.f, float pitch = 0.0f)
		: m_camera_pos { camera_pos }
        , m_front { front }
        , m_yaw { yaw }
        , m_pitch { pitch }
        , m_sensitivity { 0.1f }
        , m_speed { 3.0f }
	{  update_vectors(); }

    [[nodiscard]] glm::mat4 get_view_matrix() const;

    [[nodiscard]] glm::vec3 get_position() const;
    void process_mouse(float x, float y);
    void process_keyboard(MoveDirection dir, float delta_time);

private:
    void update_vectors();

private:
	glm::vec3 m_camera_pos;
	glm::vec3 m_up;
	glm::vec3 m_front;
    glm::vec3 m_right;

    float m_yaw;
    float m_pitch;
    float m_sensitivity;
    float m_speed;
};

#endif /* CAMERA_H */
