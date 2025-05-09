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
    void ProcessKeyboardInput(int key, float deltaTime);

    // Handle mouse input
    void ProcessMouseMovement(float xOffset, float yOffset);

    // Handle mouse scroll
    void ProcessMouseScroll(float yOffset);

private:
    float speed; // Movement speed
    float sensitivity; // Mouse sensitivity
};