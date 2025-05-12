#pragma once

#include "core.h"
#include "Light.h"
#include <vector>
#include <string>

class PointLight : public Light
{
public:
    PointLight();
    ~PointLight();

    void Load(std::ifstream& _file) override;
    void SetRenderValues(unsigned int _prog, int index);

    // Static methods for managing multiple lights
    static void AddLight(const PointLight& light);
    static void RemoveLight(const std::string& name);
    static void SetAllRenderValues(unsigned int _prog);

private:
    glm::vec3 m_attenuation;

    static std::vector<PointLight> s_pointLights; // Container for all PointLight instances
};