#version 450 core

#define MAX_POINT_LIGHTS 10
// Directional light model
uniform vec3 DIRDir;       // Direction of the directional light
uniform vec3 DIRCol;       // Color/intensity of the directional light
uniform vec3 DIRAmb;       // Ambient color/intensity of the directional light

// Point light model
uniform vec3 POINTPos[MAX_POINT_LIGHTS];
uniform vec3 POINTCol[MAX_POINT_LIGHTS];
uniform vec3 POINTAmb[MAX_POINT_LIGHTS];
uniform vec3 POINTAtten[MAX_POINT_LIGHTS];
uniform int numPointLights;


// Sampler for the surface texture
uniform sampler2D sampleTexture;

in SimplePacket {
    vec3 surfaceWorldPos;  // Fragment position in world space
    vec3 surfaceNormal;    // Fragment normal in world space
    vec2 texCoord;         // Texture coordinates
} inputFragment;

layout (location=0) out vec4 fragColour;

void main(void) {
    // Normalize the surface normal
    vec3 N = normalize(inputFragment.surfaceNormal);

    // Sample the surface color from the texture
    vec4 surfaceColour = texture(sampleTexture, inputFragment.texCoord);

    // Accumulate contributions from all point lights
    vec3 finalColourPoint = vec3(0.0);
    for (int i = 0; i < numPointLights; ++i) {
        vec3 lightDirPoint = normalize(POINTPos[i] - inputFragment.surfaceWorldPos); // Direction to the point light
        float lPoint = max(dot(N, lightDirPoint), 0.0);                              // Lambertian term for point light
        vec3 diffuseColourPoint = surfaceColour.rgb * POINTCol[i] * lPoint;          // Diffuse contribution

        float distance = length(POINTPos[i] - inputFragment.surfaceWorldPos);        // Distance to the point light
        float attenuation = 1.0 / (POINTAtten[i].x +
                                   POINTAtten[i].y * distance +
                                   POINTAtten[i].z * (distance * distance));         // Attenuation factor

        vec3 ambientColourPoint = surfaceColour.rgb * POINTAmb[i] * attenuation;     // Ambient contribution
        finalColourPoint += ambientColourPoint + diffuseColourPoint * attenuation;  // Add to the total contribution
    }

    // --- Directional Light Calculations ---
    vec3 lightDirDirectional = normalize(DIRDir);                                  // Direction of the directional light
    float lDirectional = max(dot(N, lightDirDirectional), 0.0);                    // Lambertian term for directional light
    vec3 diffuseColourDirectional = surfaceColour.rgb * DIRCol * lDirectional;     // Diffuse contribution
    vec3 ambientColourDirectional = DIRAmb;                                        // Ambient contribution
    vec3 finalColourDirectional = ambientColourDirectional + diffuseColourDirectional;

    // Combine Point Light and Directional Light contributions
    vec3 finalColour = finalColourPoint + finalColourDirectional;

    // Output the final fragment color
    fragColour = vec4(finalColour, 1.0);
}