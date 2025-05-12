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

void PointLight::Load(ifstream& _file)
{
    Light::Load(_file);
    
    StringHelp::Float3(_file, "ATTENUATION", m_attenuation.x, m_attenuation.y, m_attenuation.z);
}

void PointLight::SetRenderValues(unsigned int _prog)
{
    // Set the basic light data
    Light::SetRenderValues(_prog);

    GLint loc;
    string attenuationString = m_name + "Attenuation"; // Attenuation uniform name

    if (Helper::SetUniformLocation(_prog, attenuationString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_attenuation));
}
