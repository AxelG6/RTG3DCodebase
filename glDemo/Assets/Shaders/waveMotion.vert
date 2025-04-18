#version 450 core

layout(location = 0) in vec3 aPos;   // Vertex position
layout(location = 1) in vec2 aTexCoord;

uniform float uTime;                 // Time uniform to animate the wave
uniform float uWaveStrength = 0.1;   // Controls wave height
uniform float uWaveFrequency = 2.0;  // Controls how many waves
uniform float uWaveSpeed = 1.0;      // Controls wave speed

out vec2 vTexCoord;

void main()
{
    vec3 pos = aPos;
    uTime= glfwGetTime();
    // Displace the y-position using a sine wave
    pos.y += sin(pos.x * uWaveFrequency + uTime * uWaveSpeed) * uWaveStrength;

    gl_Position = vec4(pos, 1.0);
    vTexCoord = aTexCoord;
}