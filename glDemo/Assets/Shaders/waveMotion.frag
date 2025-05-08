#version 450 core

// Texture sampler (for diffuse surface color)
layout(binding = 0) uniform sampler2D texSampler;

// Directional light attributes
uniform vec3 DIRDir; // Light direction
uniform vec3 DIRCol; // Light color
uniform vec3 DIRAmb; // Ambient light color

in SimplePacket {
  vec3 surfaceWorldPos;
  vec3 surfaceNormal;
  vec2 texCoord;
} inputFragment;

layout (location=0) out vec4 fragColour;

void main(void) {
  // Normalize the surface normal
  vec3 N = normalize(inputFragment.surfaceNormal);
  
  // Normalize the light direction
  vec3 L = normalize(DIRDir);
  
  // Calculate Lambertian (diffuse lighting)
  float l = max(dot(N, L), 0.0); // Ensure non-negative lighting
  
  // Sample texture color
  vec4 surfaceColour = texture(texSampler, inputFragment.texCoord);
  
  // Calculate diffuse color
  vec3 diffuseColour = surfaceColour.rgb * DIRCol * l;
  
  // Combine ambient and diffuse components for final color
  vec3 finalColor = DIRAmb + diffuseColour;
  
  fragColour = vec4(finalColor, surfaceColour.a); // Use alpha from the texture
}