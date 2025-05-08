#include "FPCamera.h"
#include <glm/gtx/rotate_vector.hpp>

FirstPersonCamera::FirstPersonCamera()
    : m_speed(5.0f), m_sensitivity(0.1f)
{
    m_type = "FPCAMERA";
    m_theta = 0.0f;
    m_phi = 0.0f;
    calculateDerivedValues();
}

FirstPersonCamera::~FirstPersonCamera() {}

void FirstPersonCamera::move(const glm::vec3& direction, float _dt) {

    //float speed = c_speed * _dt; // Calculate speed based on delta time
    m_pos += direction * _dt;
    m_lookAt += direction * _dt; // Move the look-at point with the camera
    calculateDerivedValues();
    
    // Update the view matrix
}

void FirstPersonCamera::Rotate(float deltaX, float deltaY)
{
    // Adjust rotation angles by mouse sensitivity
    m_phi += deltaX * m_sensitivity;
    m_theta -= deltaY * m_sensitivity;

    // Clamp theta to avoid flipping the camera
    m_theta = glm::clamp(m_theta, -89.0f, 89.0f);

    const float theta_ = glm::radians(m_theta);
    const float phi_ = glm::radians(m_phi);

    glm::vec3 direction;
    direction.x = cosf(theta_) * sinf(phi_);
    direction.y = sinf(theta_);
    direction.z = cosf(theta_) * cosf(phi_);
    m_lookAt = m_pos + glm::normalize(direction);

    calculateDerivedValues();
}
