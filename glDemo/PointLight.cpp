#include "PointLight.h"
#include "helper.h"
#include "stringHelp.h"

std::vector<PointLight> PointLight::s_pointLights;

PointLight::PointLight()
{
    m_type = "POINT";
}

PointLight::~PointLight()
{
}

void PointLight::Load(std::ifstream& _file)
{
    Light::Load(_file);
    StringHelp::Float3(_file, "ATTENUATION", m_attenuation.x, m_attenuation.y, m_attenuation.z);
    AddLight(*this);
}

void PointLight::SetRenderValues(unsigned int _prog, int index)
{
    // Set the basic light data
    Light::SetRenderValues(_prog);

    GLint loc;

    // Set position uniform
    std::string positionString = "POINTPos[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, positionString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_pos));

    // Set color uniform
    std::string colorString = "POINTCol[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, colorString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_col));

    std::string ambString = "POINTAmb[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, ambString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_amb));
    // Set attenuation uniform
    std::string attenuationString = "POINTAtten[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, attenuationString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_attenuation));
}

// Static methods
void PointLight::AddLight(const PointLight& light)
{
    s_pointLights.push_back(light);
}

void PointLight::RemoveLight(const std::string& name)
{
    s_pointLights.erase(std::remove_if(s_pointLights.begin(), s_pointLights.end(),
        [&name](const PointLight& light) { return light.m_name == name; }),
        s_pointLights.end());
}

void PointLight::SetAllRenderValues(unsigned int _prog)
{
    // Set the number of active lights
    GLint numLightsLoc = glGetUniformLocation(_prog, "numPointLights");
    glUniform1i(numLightsLoc, static_cast<int>(s_pointLights.size()));
    int i = 0;
    // Set uniforms for all lights
    for ( i; i < s_pointLights.size(); ++i)
    {
        s_pointLights[i].SetRenderValues(_prog, i);
    }
}