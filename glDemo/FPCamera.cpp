#include "FPCamera.h"
#include <glm/gtx/string_cast.hpp>

FirstPersonCamera::FirstPersonCamera()
    : speed(0.5f), sensitivity(0.1f) {
    m_type = "FIRST_PERSON_CAMERA";

}

// Initialize the camera
void FirstPersonCamera::Init(float _w, float _h, Scene* _scene) 
{
    Camera::Init(_w, _h, _scene);
    rotateCamera(0.0f, 0.0f); // Initialize m_lookAt based on m_theta and m_phi
}

// Update the camera every frame
void FirstPersonCamera::Tick(float _dt, float aspectRatio) 
{
    Camera::Tick(_dt, aspectRatio);
}

// Handle keyboard input, somehow foward and left work but on the wrong axis
void FirstPersonCamera::ProcessKeyboardInput(const glm::vec3& direction, float _dt) 
{
    float velocity = speed * _dt;

    // Calculate the forward direction (normalized vector)
    glm::vec3 right = glm::normalize(m_lookAt - m_pos);

    // Calculate the right direction (normalized vector)
    glm::vec3 forward = glm::normalize(glm::cross(right, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (direction.z > 0.0f) { 
        m_pos -= forward * velocity * direction.z;
    }
    else if (direction.z < 0.0f) { 
        m_pos += forward * velocity * -direction.z;
    }

    if (direction.x > 0.0f) { 
        m_pos -= right * velocity * direction.x;
    }
    else if (direction.x < 0.0f) { 
        m_pos += right * velocity * -direction.x;
    }

    // Update the look-at point to move with the camera
    m_lookAt = m_pos + glm::normalize(m_lookAt - m_pos);
    m_pos.y=0.5f; // Keep the camera at a fixed height
    
    // Debug output for position and look-at
    //std::cout << "Camera::ProcessKeyboardInput: m_pos = " << glm::to_string(m_pos) << std::endl;
    //std::cout << "Camera::ProcessKeyboardInput: m_lookAt = " << glm::to_string(m_lookAt) << std::endl;

    // Recalculate derived values like view matrix
    calculateDerivedValues();
	rotateCamera(0.0f, 0.0f); // Update m_lookAt based on new position
}

// Handle mouse movement
void FirstPersonCamera::ProcessMouseMovement(float xOffset, float yOffset) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    // Update yaw (phi) and pitch (theta)
    m_phi += yOffset;
    m_theta -= xOffset;

    // Constrain pitch to avoid flipping
    if (m_theta > 89.0f)
        m_theta = 89.0f;
    if (m_theta < -89.0f)
        m_theta = -89.0f;

    // Update m_lookAt to reflect the new orientation
    rotateCamera(0.0f, 0.0f);
}

// Handle mouse scroll (optional zoom or other functionality)
void FirstPersonCamera::ProcessMouseScroll(float yOffset) {
    incrementRadius(yOffset);
}

// Calculate the camera's lookAt vector based on orientation and position
void FirstPersonCamera::rotateCamera(float xOffset, float yOffset) {
    // Convert spherical coordinates (theta, phi) to Cartesian coordinates
    glm::vec3 front;
    front.x = cos(glm::radians(m_theta)) * cos(glm::radians(m_phi));
    front.y = sin(glm::radians(m_theta));
    front.z = cos(glm::radians(m_theta)) * sin(glm::radians(m_phi));
    front = glm::normalize(front);

    // Calculate m_lookAt relative to m_pos
    m_lookAt = m_pos + front; // LookAt is always in front of the camera
}