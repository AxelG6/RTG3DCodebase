#include "orthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <algorithm>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////
OrthographicCamera::OrthographicCamera()
    : m_left(-5.0f), m_right(5.0f), m_bottom(-5.0f), m_top(5.0f) {
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
    

    float width = m_right - m_left;
    float height = m_top - m_bottom;

    // Keep the height constant and adjust the width
    float newWidth = height * aspectRatio;
    float centerX = (m_left + m_right) / 2.0f; // Find the center of the bounds
    m_left = centerX - newWidth / 2.0f;
    m_right = centerX + newWidth / 2.0f;

    // Recalculate the projection matrix if necessary
    m_projectionMatrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_nearPlane, m_farPlane);
    
    m_viewMatrix = glm::lookAt(m_pos, m_lookAt, glm::vec3(0, 1, 0)); // Up vector is (0, 1, 0)
	calculateDerivedValues();
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
    m_pos += direction * _dt; 
    m_lookAt += direction * _dt; // Move the look-at point with the camera
	calculateDerivedValues();
	// Update the view matrix
}

void OrthographicCamera::Zoom(float scrollDelta) {
    float zoomSpeed = 0.1f; // Adjust this to control zoom sensitivity

    // Calculate the zoom scale
    float zoomScale = 1.0f - scrollDelta * zoomSpeed;

    // Prevent zoom from inverting the view or becoming too small
    zoomScale = glm::clamp(zoomScale, 0.1f, 2.0f);

    // Find the current bounds' center
    float centerX = (m_left + m_right) / 2.0f;
    float centerY = (m_bottom + m_top) / 2.0f;

    // Adjust the bounds based on the zoom scale
    float newWidth = (m_right - m_left) * zoomScale;
    float newHeight = (m_top - m_bottom) * zoomScale;

    m_left = centerX - newWidth / 2.0f;
    m_right = centerX + newWidth / 2.0f;
    m_bottom = centerY - newHeight / 2.0f;
    m_top = centerY + newHeight / 2.0f;

    // Recalculate the projection matrix
    calculateDerivedValues();
}