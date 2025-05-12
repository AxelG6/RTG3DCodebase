#pragma once
#include "Light.h"
#include <vector>
class PointLight : public Light
{
public:
    

    PointLight();
    virtual ~PointLight();

    void AddLight(const vec3& position, const vec3& attenuation);

    // Load point light data from a file
    virtual void Load(ifstream& _file) override;

    // Set shader uniform values for the point light
    virtual void SetRenderValues(unsigned int _prog) override;

protected:
    struct PointLightData {
        vec3 m_pos;
        vec3 m_attenuation; // Default attenuation: constant, linear, quadratic
    };
	vec3 m_attenuation; // Attenuation factors (constant, linear, quadratic)
    
    std::vector<PointLightData> m_lights;
    
};