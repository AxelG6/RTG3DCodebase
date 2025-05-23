#version 450 core

// Diffuse texture - point light

// Texture sampler (for diffuse surface color)
layout(binding = 0) uniform sampler2D sampleTexture;

// Point light model
uniform vec3 POINTPos;     // Position of the point light
uniform vec3 POINTCol;     // Color/intensity of the point light
uniform vec3 POINTAmb;     // Ambient color/intensity of the point light
uniform vec3 POINTAtten;   // Attenuation factors (constant, linear, quadratic)

in SimplePacket {
    vec3 surfaceWorldPos; // Fragment position in world space
    vec3 surfaceNormal;   // Fragment normal in world space
    vec2 texCoord;        // Texture coordinates
} inputFragment;

layout (location=0) out vec4 fragColour;

void main(void) {
    // Normalize the surface normal
    vec3 N = normalize(inputFragment.surfaceNormal);

    // Calculate the direction to the point light
    vec3 lightDir = normalize(POINTPos - inputFragment.surfaceWorldPos);

    // Calculate the Lambertian (diffuse) term
    float l = max(dot(N, lightDir), 0.0);

    // Sample the surface color from the texture
    vec4 surfaceColour = texture(sampleTexture, inputFragment.texCoord);

    // Calculate diffuse color
    vec3 diffuseColour = surfaceColour.rgb * POINTCol * l;

    // Calculate the distance to the light and the attenuation factor
    float distance = length(POINTPos - inputFragment.surfaceWorldPos);
    float attenuation = 1.0 / (POINTAtten.x +
                               POINTAtten.y * distance +
                               POINTAtten.z * (distance * distance));

    // Combine the ambient and diffuse contributions, scaled by attenuation
    vec3 ambientColour = surfaceColour.rgb * POINTAmb * attenuation;
    vec3 finalColour = ambientColour + diffuseColour * attenuation;

    // Output the final fragment color
    fragColour = vec4(finalColour, 1.0);
}