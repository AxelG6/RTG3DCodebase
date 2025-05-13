#pragma once
#include "Light.h"
#include "core.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

class SpotLight : public Light
{
public:
    SpotLight();
    ~SpotLight();

    void Load(std::ifstream& _file) override;
    void SetRenderValues(unsigned int _prog, int index);

    // Static methods for managing spotlights
    static void AddLight(const SpotLight& light);
    static void RemoveLight(const std::string& name);
    static void SetAllRenderValues(unsigned int _prog);

private:
    glm::vec3 m_direction;
    glm::vec3 m_attenuation;
    float m_innerCutoff;
    float m_outerCutoff;

    static std::vector<SpotLight> s_spotLights;
};