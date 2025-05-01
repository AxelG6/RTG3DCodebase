#include "orthoCamera.h"

// Constructor
OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float nearView, float farView)
    : left(left), right(right), bottom(bottom), top(top), nearView(nearView), farView(farView) {
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    updateProjection();
    updateView();
}

// Update the projection matrix
void OrthoCamera::updateProjection() {
    projectionMatrix = glm::ortho(left, right, bottom, top, nearView, farView);
}

// Update the view matrix
void OrthoCamera::updateView() {
    viewMatrix = glm::translate(glm::mat4(1.0f), -position); // Translate by -position
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate on X axis
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate on Y axis
    viewMatrix = glm::rotate(viewMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate on Z axis
}

// Move the camera by a certain amount
void OrthoCamera::move(glm::vec3 translation) {
    position += translation;
    updateView();
}

// Rotate the camera by a certain amount
void OrthoCamera::rotate(glm::vec3 rotationDelta) {
    rotation += rotationDelta;
    updateView();
}

// Set the camera's position directly
void OrthoCamera::setPosition(glm::vec3 newPosition) {
    position = newPosition;
    updateView();
}

// Set the camera's rotation directly
void OrthoCamera::setRotation(glm::vec3 newRotation) {
    rotation = newRotation;
    updateView();
}

// Get the view-projection matrix
glm::mat4 OrthoCamera::getViewProjectionMatrix() {
    return projectionMatrix * viewMatrix;
}
