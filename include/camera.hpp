#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include "../events/event_manager.hpp"
#include "../events/mouse_event.hpp"
#include "../events/key_events.hpp"

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
	Camera(glm::vec3 camera_pos = glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), float yaw = -90.f, float pitch = 0.0f) :
        m_camera_pos (camera_pos), m_front (front), m_yaw (yaw), 
        m_pitch (pitch), m_sensitivity (0.1f), m_speed (3.0f)
	{  
        subscribe(MouseMovedEvent::get_type_s(), std::make_unique<EventHandler<Camera>>(*this, &Camera::on_mouse_move));
        subscribe(KeyPressedEvent::get_type_s(), std::make_unique<EventHandler<Camera>>(*this, &Camera::on_key_pressed));
        subscribe(KeyReleasedEvent::get_type_s(), std::make_unique<EventHandler<Camera>>(*this, &Camera::on_key_released));
        update_vectors(); 
    }

    void on_mouse_move(Event &e);
    void on_key_pressed(Event &e);
    void on_key_released(Event &e);

    glm::mat4 get_view_matrix() const;

    glm::vec3 get_position() const;
    void process_mouse(float x, float y);
    void process_keyboard(Key key, float delta_time);

private:
    void update_vectors();

private:
	glm::vec3 m_camera_pos;
	glm::vec3 m_up;
	glm::vec3 m_front;
    glm::vec3 m_right;

    float m_yaw { -90.f };
    float m_pitch { 0.0f };
    float m_sensitivity { 0.1f };
    float m_speed { 0.05f };

    float xpos { 400.f };
    float ypos { 300.f };
    
    float delta_time { 0.0f };

    bool first_mouse { true };
};

#endif /* CAMERA_H */

