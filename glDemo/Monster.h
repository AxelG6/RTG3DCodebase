#pragma once

#include "ExampleGO.h"
#include <glm/glm.hpp>
#include <string>

class Monster : public ExampleGO {
public:
    Monster();

    void Load(std::ifstream& _file) override;
    void Tick(float _dt) override;
    void Init(Scene* _scene) override;

private:
    void Wander(float _dt); // Wandering behavior

    glm::vec3 m_Direction;  // Direction of movement
    float m_Speed;          // Speed of the monster
    float m_WanderRadius;   // Radius within which the monster can wander
    float m_Timer;          // Timer for changing direction
    float m_ChangeInterval; // Time interval to change direction

};