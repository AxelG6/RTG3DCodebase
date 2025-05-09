#include "FPCamera.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

/////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////
FirstPersonCamera::FirstPersonCamera()
{
	m_type = "FPCAMERA";
}

/////////////////////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////////////////////
FirstPersonCamera::~FirstPersonCamera()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// MoveForward - Move the camera forward or backward along its forward vector
/////////////////////////////////////////////////////////////////////////////////////
void FirstPersonCamera::MoveForward(float distance)
{
    glm::vec3 forward = glm::normalize(m_lookAt - m_pos);
    m_pos += forward * distance;
    m_lookAt += forward * distance;
    calculateDerivedValues();
}

/////////////////////////////////////////////////////////////////////////////////////
// MoveRight - Move the camera to the right or left along its right vector
/////////////////////////////////////////////////////////////////////////////////////
void FirstPersonCamera::MoveRight(float distance)
{
    glm::vec3 forward = glm::normalize(m_lookAt - m_pos);
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_pos += right * distance;
    m_lookAt += right * distance;
    calculateDerivedValues();
}

/////////////////////////////////////////////////////////////////////////////////////
// MoveUp - Move the camera upwards or downwards along its up vector
/////////////////////////////////////////////////////////////////////////////////////
void FirstPersonCamera::MoveUp(float distance)
{
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    m_pos += up * distance;
    m_lookAt += up * distance;
    calculateDerivedValues();
}

/////////////////////////////////////////////////////////////////////////////////////
// Rotate - Rotate the camera based on horizontal and vertical delta inputs
/////////////////////////////////////////////////////////////////////////////////////
void FirstPersonCamera::Rotate(float deltaX, float deltaY)
{
    m_theta += deltaY * 0.1f;
    m_phi += deltaX * 0.1f;

    const float theta_ = glm::radians<float>(m_theta);
    const float phi_ = glm::radians<float>(m_phi);

    glm::vec3 direction;
    direction.x = sinf(phi_) * cosf(theta_);
    direction.y = sinf(theta_);
    direction.z = cosf(phi_) * cosf(theta_);

    m_lookAt = m_pos + direction;
    calculateDerivedValues();
}

/////////////////////////////////////////////////////////////////////////////////////
// calculateDerivedValues - Override to update view transform for first-person camera
/////////////////////////////////////////////////////////////////////////////////////
void FirstPersonCamera::calculateDerivedValues()
{
    m_viewMatrix = glm::lookAt(m_pos, m_lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    m_projectionMatrix = glm::perspective(glm::radians<float>(m_fovY), m_aspect, m_nearPlane, m_farPlane);
}