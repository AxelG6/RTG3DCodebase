#pragma once

#include "Camera.h"
#include <glm/glm.hpp>

class FirstPersonCamera : public Camera
{
public:
    // Constructor
    FirstPersonCamera();

    // Destructor
    ~FirstPersonCamera();

    // Move the camera forward or backward
    void MoveForward(float distance);

    // Move the camera to the right or left
    void MoveRight(float distance);

    // Move the camera upwards or downwards
    void MoveUp(float distance);

    // Rotate the camera based on horizontal and vertical deltas
    void Rotate(float deltaX, float deltaY);

private:
    void calculateDerivedValues() override;
};