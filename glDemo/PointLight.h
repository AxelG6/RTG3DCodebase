#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
    PointLight();
    virtual ~PointLight();

    // Load point light data from a file
    virtual void Load(ifstream& _file) override;

    // Set shader uniform values for the point light
    virtual void SetRenderValues(unsigned int _prog) override;

protected:

    vec3 m_attenuation;  // Attenuation factors (constant, linear, quadratic)
};