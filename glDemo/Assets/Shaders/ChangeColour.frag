#version 450 core

#define MAX_POINT_LIGHTS 50
#define MAX_SPOT_LIGHTS 50

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

// Spot light model
uniform vec3 SPOTPos[MAX_SPOT_LIGHTS];
uniform vec3 SPOTDir[MAX_SPOT_LIGHTS];
uniform vec3 SPOTCol[MAX_SPOT_LIGHTS];
uniform vec3 SPOTAmb[MAX_SPOT_LIGHTS];
uniform vec3 SPOTAtten[MAX_SPOT_LIGHTS];
uniform float SPOTInnerCutoff[MAX_SPOT_LIGHTS];
uniform float SPOTOuterCutoff[MAX_SPOT_LIGHTS];
uniform int numSpotLights;

// Sampler for the surface texture
uniform sampler2D sampleTexture;
uniform float alphaValue;

// Alpha threshold for transparency (optional, can be adjusted)
uniform float alphaThreshold = 0.1;

// Uniform time variable passed from the application
uniform float time;

in SimplePacket {
    vec3 surfaceWorldPos;  // Fragment position in world space
    vec3 surfaceNormal;    // Fragment normal in world space
    vec2 texCoord;         // Texture coordinates
} inputFragment;

layout (location=0) out vec4 fragColour;

void main(void) {
    // Normalize the surface normal
    vec3 N = normalize(inputFragment.surfaceNormal);

    // Sample the surface color from the texture, including its alpha channel
    vec4 surfaceColour = texture(sampleTexture, inputFragment.texCoord);

    // Discard fragments with alpha below the threshold to avoid rendering them
    if (surfaceColour.a < alphaThreshold) {
        discard;
    }

    // --- Color Change Over Time ---
    // Use sin(time) to create a periodic oscillation for the color modifier
    float colorModifier = abs(sin(time)); // Oscillates between 0 and 1
    vec3 timeVaryingColor = vec3(colorModifier, 1.0 - colorModifier, 0.5 + 0.5 * sin(time * 0.5)); // R, G, B vary over time

    // --- Point Lights Contributions ---
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

    // --- Spot Lights Contributions ---
    vec3 finalColourSpot = vec3(0.0);
    for (int i = 0; i < numSpotLights; ++i) {
        vec3 lightDirSpot = normalize(SPOTPos[i] - inputFragment.surfaceWorldPos);  // Direction to the spotlight
        float lSpot = max(dot(N, lightDirSpot), 0.0);                               // Lambertian term for spotlight

        // Spotlight angle calculations
        float theta = dot(lightDirSpot, normalize(-SPOTDir[i]));                    // Angle between light direction and spotlight direction
        float epsilon = SPOTInnerCutoff[i] - SPOTOuterCutoff[i];
        float intensity = clamp((theta - SPOTOuterCutoff[i]) / epsilon, 0.0, 1.0);  // Spotlight intensity based on cutoff angles

        // Spotlight diffuse and ambient contributions
        vec3 diffuseColourSpot = surfaceColour.rgb * SPOTCol[i] * lSpot * intensity;

        float distance = length(SPOTPos[i] - inputFragment.surfaceWorldPos);        // Distance to the spotlight
        float attenuation = 1.0 / (SPOTAtten[i].x +
                                   SPOTAtten[i].y * distance +
                                   SPOTAtten[i].z * (distance * distance));         // Attenuation factor

        vec3 ambientColourSpot = surfaceColour.rgb * SPOTAmb[i] * attenuation * intensity;
        finalColourSpot += (ambientColourSpot + diffuseColourSpot) * attenuation;   // Add to the total contribution
    }

    // Combine all light contributions
    vec3 finalColour = finalColourPoint + finalColourDirectional + finalColourSpot;

    // Modulate the final fragment color with the time-varying color
    finalColour *= timeVaryingColor;

    // Output the final fragment color, preserving the alpha value from the texture
    fragColour = vec4(finalColour, alphaValue);
}