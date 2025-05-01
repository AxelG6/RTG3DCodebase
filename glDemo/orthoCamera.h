#pragma once
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class OrthoCamera : public Camera
{
public:
    // Member variables
    glm::vec3 position;
    glm::vec3 rotation;
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    float left, right, bottom, top, nearView, farView;

    // Constructor
    OrthoCamera(float left, float right, float bottom, float top, float nearView, float farView);
    ~OrthoCamera();
    // Member functions
    void updateProjection();
    void updateView();

    void move(glm::vec3 translation);
    void rotate(glm::vec3 rotationDelta);

    void setPosition(glm::vec3 newPosition);
    void setRotation(glm::vec3 newRotation);

    glm::mat4 getViewProjectionMatrix();
};

