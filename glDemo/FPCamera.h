#pragma once
#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
    FirstPersonCamera();
    ~FirstPersonCamera();

    // Handle keyboard input for movement
	void move(const glm::vec3& direction, float _dt);

    // Handle mouse input for rotation
    void Rotate(float deltaX, float deltaY);

    // Update the camera matrices based on movement and rotation
    void Update(float deltaTime);

private:
    float m_speed;         // Movement speed
    float m_sensitivity;   // Mouse sensitivity
};