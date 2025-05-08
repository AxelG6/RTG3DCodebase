#include "orthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////
OrthographicCamera::OrthographicCamera()
    : m_left(-1.0f), m_right(1.0f), m_bottom(-1.0f), m_top(1.0f) {
    m_type = "ORTHOGRAPHIC_CAMERA";
}

/////////////////////////////////////////////////////////////////////////////////////
// Destructor
/////////////////////////////////////////////////////////////////////////////////////
OrthographicCamera::~OrthographicCamera() {
    // Nothing to clean up for now
}

/////////////////////////////////////////////////////////////////////////////////////
// InitOrthographic() - Initialize the orthographic camera
/////////////////////////////////////////////////////////////////////////////////////
void OrthographicCamera::InitOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    m_left = left;
    m_right = right;
    m_bottom = bottom;
    m_top = top;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
	float c_speed = 0.1f; // Speed of camera movement
    // Set the projection matrix using glm::ortho
    m_projectionMatrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_nearPlane, m_farPlane);
}

/////////////////////////////////////////////////////////////////////////////////////
// Tick() - Update the projection and view matrices
/////////////////////////////////////////////////////////////////////////////////////
void OrthographicCamera::Tick(float _dt, float aspectRatio) {
    // Recalculate the projection matrix if necessary
    m_projectionMatrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_nearPlane, m_farPlane);

    // Update the view matrix
    m_viewMatrix = glm::lookAt(m_pos, m_lookAt, glm::vec3(0, 1, 0)); // Up vector is (0, 1, 0)
}

/////////////////////////////////////////////////////////////////////////////////////
// setBounds() - Modify the orthographic bounds
/////////////////////////////////////////////////////////////////////////////////////
void OrthographicCamera::setBounds(float left, float right, float bottom, float top) {
    m_left = left;
    m_right = right;
    m_bottom = bottom;
    m_top = top;

    // Recalculate the projection matrix
    calculateDerivedValues();
}

/////////////////////////////////////////////////////////////////////////////////////
// getBounds() - Retrieve the current orthographic bounds
/////////////////////////////////////////////////////////////////////////////////////
void OrthographicCamera::getBounds(float& left, float& right, float& bottom, float& top) const {
    left = m_left;
    right = m_right;
    bottom = m_bottom;
    top = m_top;
}

/////////////////////////////////////////////////////////////////////////////////////
// calculateDerivedValues() - Recalculate the projection matrix
/////////////////////////////////////////////////////////////////////////////////////
void OrthographicCamera::calculateDerivedValues() {
    // Update the orthographic projection matrix
    m_projectionMatrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_nearPlane, m_farPlane);
}

/////////////////////////////////////////////////////////////////////////////////////
// Movement Functions
/////////////////////////////////////////////////////////////////////////////////////
void OrthographicCamera::move(const glm::vec3& direction, float _dt) {
    
	//float speed = c_speed * _dt; // Calculate speed based on delta time
    m_pos += direction * _dt; // Move the camera in the given direction
    m_lookAt += direction * _dt; // Move the look-at point with the camera
}