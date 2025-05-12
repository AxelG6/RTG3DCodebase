#pragma once
#include "Camera.h"

class OrthographicCamera : public Camera {
public:
    // Constructor and Destructor
    OrthographicCamera();
    virtual ~OrthographicCamera();

    // Initialize the orthographic camera
    void InitOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

    // Update the orthographic projection matrix
    virtual void Tick(float _dt, float aspectRatio) override;

    // Modify orthographic bounds
    void setBounds(float left, float right, float bottom, float top);
    void getBounds(float& left, float& right, float& bottom, float& top) const;

    // Movement controls
    void move(const glm::vec3& direction, float speed); // Move the camera in a specific direction
    void Zoom(float scrollDelta);

protected:
    // Orthographic bounds
    float m_left, m_right, m_bottom, m_top,c_speed;

    // Recalculate the projection matrix for orthographic camera
    virtual void calculateDerivedValues() override;
};