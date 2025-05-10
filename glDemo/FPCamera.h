#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class FirstPersonCamera : public Camera {
public:
    FirstPersonCamera();

    // Override Init to set default values
    void Init(float _w, float _h, Scene* _scene) override;

    // Override Tick to handle movement and rotation
    void Tick(float _dt, float aspectRatio) override;

    // Handle keyboard input
    void ProcessKeyboardInput(const glm::vec3& direction, float _dt);

    // Handle mouse input
    void ProcessMouseMovement(float xOffset, float yOffset);

    // Handle mouse scroll
    void ProcessMouseScroll(float yOffset);
    void rotateCamera(float xOffset, float yOffset);
private:
    float speed; // Movement speed
    float sensitivity; // Mouse sensitivity
};