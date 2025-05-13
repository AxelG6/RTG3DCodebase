#include "SpotLight.h"
#include "helper.h"
#include "stringHelp.h"

std::vector<SpotLight> SpotLight::s_spotLights;

SpotLight::SpotLight()
{
    m_type = "SPOT";
}

SpotLight::~SpotLight()
{
}

void SpotLight::Load(std::ifstream& _file)
{
    Light::Load(_file);
    StringHelp::Float3(_file, "DIRECTION", m_direction.x, m_direction.y, m_direction.z);
    StringHelp::Float(_file, "INNER_C", m_innerCutoff);
    StringHelp::Float(_file, "OUTER_C", m_outerCutoff);
    StringHelp::Float3(_file, "ATTENUATION", m_attenuation.x, m_attenuation.y, m_attenuation.z);
    AddLight(*this);
}

void SpotLight::SetRenderValues(unsigned int _prog, int index)
{
    // Set the basic light data
    Light::SetRenderValues(_prog);

    GLint loc;

    // Set position uniform
    std::string positionString = "SPOTPos[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, positionString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_pos));

    // Set direction uniform
    std::string directionString = "SPOTDir[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, directionString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_direction));

    // Set color uniform
    std::string colorString = "SPOTCol[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, colorString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_col));

    // Set ambient uniform
    std::string ambString = "SPOTAmb[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, ambString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_amb));

    // Set attenuation uniform
    std::string attenuationString = "SPOTAtten[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, attenuationString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_attenuation));

    // Set inner cutoff uniform
    std::string innerCutoffString = "SPOTInnerCutoff[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, innerCutoffString.c_str(), &loc))
        glUniform1f(loc, m_innerCutoff);

    // Set outer cutoff uniform
    std::string outerCutoffString = "SPOTOuterCutoff[" + std::to_string(index) + "]";
    if (Helper::SetUniformLocation(_prog, outerCutoffString.c_str(), &loc))
        glUniform1f(loc, m_outerCutoff);
}

// Static methods
void SpotLight::AddLight(const SpotLight& light)
{
    s_spotLights.push_back(light);
}

void SpotLight::RemoveLight(const std::string& name)
{
    s_spotLights.erase(std::remove_if(s_spotLights.begin(), s_spotLights.end(),
        [&name](const SpotLight& light) { return light.m_name == name; }),
        s_spotLights.end());
}

void SpotLight::SetAllRenderValues(unsigned int _prog)
{
    // Set the number of active lights
    GLint numLightsLoc = glGetUniformLocation(_prog, "numSpotLights");
    glUniform1i(numLightsLoc, static_cast<int>(s_spotLights.size()));
    int i = 0;
    // Set uniforms for all lights
    for (i; i < s_spotLights.size(); ++i)
    {
        s_spotLights[i].SetRenderValues(_prog, i);
    }
}