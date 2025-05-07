#version 450 core

// Inputs from vertex shader
in SimplePacket {
    vec3 surfaceWorldPos;
    vec3 surfaceNormal;
    vec2 texCoord;
} inputFragment;

// Output color
out vec4 fragColor;

// Uniforms (optional)
uniform vec3 lightDir = normalize(vec3(-1.0, -1.0, -1.0)); // simple directional light
uniform vec3 baseColor = vec3(0.2, 0.6, 1.0);              // object base color
// uniform sampler2D diffuseMap; // Uncomment if using texture

void main() {
    // Normalize interpolated normal
    vec3 normal = normalize(inputFragment.surfaceNormal);

    // Simple Lambertian diffuse lighting
    float diff = max(dot(normal, -lightDir), 0.0);

    // Final color with ambient + diffuse
    vec3 ambient = 0.1 * baseColor;
    vec3 diffuse = diff * baseColor;

    // Optional: use texture instead of base color
    // vec3 texColor = texture(diffuseMap, inputFragment.texCoord).rgb;
    // vec3 finalColor = ambient + diff * texColor;

    vec3 finalColor = ambient + diffuse;
    fragColor = vec4(finalColor, 1.0);
}
