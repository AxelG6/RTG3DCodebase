#include "core.h"
#include "PointLight.h"
#include "helper.h"
#include "stringHelp.h"

PointLight::PointLight()
{
    m_type = "POINT";
	m_pos = vec3(0.0, 0.0, 0.0);
    m_attenuation = vec3(1.0, 0.0, 0.0); // Default attenuation: constant, linear, quadratic
}

PointLight::~PointLight()
{
}

void PointLight::AddLight(const vec3& position, const vec3& attenuation) {
    PointLightData newLight = { position, attenuation };
    m_lights.push_back(newLight);
}

void PointLight::Load(ifstream& _file) {
    // Load multiple lights from the file if needed
    // Example: You can read the number of lights and their properties
    int numLights=2;
    for (int i = 0; i < numLights; ++i) {
        Light::Load(_file);
        vec3 attenuation;
        StringHelp::Float3(_file, "ATTENUATION", attenuation.x, attenuation.y, attenuation.z);
        AddLight(m_pos, attenuation);
        m_pos = glm::vec3(i * 1.0f, 0.0f, 1.0f);
    }
}


void PointLight::SetRenderValues(unsigned int _prog)
{
    // Set the basic light data
    for (size_t i = 0; i < m_lights.size(); ++i) {
        std::string lightName = "POINT" + std::to_string(i);

        GLint loc;

        // Set position uniform
        std::string positionString = lightName + "Pos";
        if (Helper::SetUniformLocation(_prog, positionString.c_str(), &loc))
            glUniform3fv(loc, 1, glm::value_ptr(m_lights[i].m_pos));

        // Set attenuation uniform
        std::string attenuationString = lightName + "Atten";
        if (Helper::SetUniformLocation(_prog, attenuationString.c_str(), &loc))
            glUniform3fv(loc, 1, glm::value_ptr(m_lights[i].m_attenuation));
    }
    
}
