#include "FPCamera.h"

FirstPersonCamera::FirstPersonCamera()
    : speed(2.5f), sensitivity(0.1f) {
    m_type = "FIRST_PERSON_CAMERA";
}

void FirstPersonCamera::Init(float _w, float _h, Scene* _scene) {
    Camera::Init(_w, _h, _scene);
}

void FirstPersonCamera::Tick(float _dt, float aspectRatio) {
    Camera::Tick(_dt, aspectRatio);
	
}

void FirstPersonCamera::ProcessKeyboardInput(int key, float deltaTime)
{
    float velocity = speed * deltaTime;
    glm::vec3 forward = glm::normalize(m_lookAt - m_pos);
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (key == GLFW_KEY_W) // Move forward
        m_pos += forward * velocity;
    if (key == GLFW_KEY_S) // Move backward
        m_pos -= forward * velocity;
    if (key == GLFW_KEY_A) // Move left
        m_pos -= right * velocity;
    if (key == GLFW_KEY_D) // Move right
        m_pos += right * velocity;

    m_lookAt = m_pos + forward; // Update lookAt position
}

void FirstPersonCamera::ProcessMouseMovement(float xOffset, float yOffset) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    m_phi += xOffset;
    m_theta -= yOffset;

    // Constrain pitch
    if (m_theta > 89.0f)
        m_theta = 89.0f;
    if (m_theta < -89.0f)
        m_theta = -89.0f;

    rotateCamera(0.0f, 0.0f); // Recalculate lookAt based on theta and phi
}

void FirstPersonCamera::ProcessMouseScroll(float yOffset) {
    incrementRadius(yOffset);
}