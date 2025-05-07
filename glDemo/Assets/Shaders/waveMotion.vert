#version 450 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float time; // new: time variable for wave animation

layout (location=0) in vec3 vertexPos;
layout (location=2) in vec3 vertexTexCoord;
layout (location=3) in vec3 vertexNormal;

out SimplePacket {
  vec3 surfaceWorldPos;
  vec3 surfaceNormal;
  vec2 texCoord;
} outputVertex;

void main(void) {

  outputVertex.texCoord = vertexTexCoord.st;

  // Parameters for wave
  float amplitude = 0.2;     // height of the wave
  float frequency = 2.0;     // number of waves
  float speed = 2.0;         // how fast the wave moves

  // Apply wave to Y-axis based on X and time
  vec3 animatedPos = vertexPos;
  animatedPos.y += sin(vertexPos.x * frequency + time * speed) * amplitude;

  // Transform normal with the inverse-transpose of the model matrix
  outputVertex.surfaceNormal = (transpose(inverse(modelMatrix)) * vec4(vertexNormal, 0.0)).xyz;

  // Convert to world coordinates
  vec4 worldCoord = modelMatrix * vec4(animatedPos, 1.0);
  outputVertex.surfaceWorldPos = worldCoord.xyz;

  // Final position in clip space
  gl_Position = projMatrix * viewMatrix * worldCoord;
}
