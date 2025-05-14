#version 450 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float time; // time variable for wave animation

layout(location = 0) in vec3 vertexPos;      // Vertex position
layout(location = 2) in vec2 vertexTexCoord; // Vertex texture coordinates
layout(location = 3) in vec3 vertexNormal; 

out SimplePacket {
    vec3 surfaceWorldPos;
    vec3 surfaceNormal;
    vec2 texCoord;
} outputVertex;

void main(void) {
    outputVertex.texCoord = vertexTexCoord;

    // Wave parameters
    float amplitude = 0.6;
    float frequency = 2.0;
    float speed = 2.0;

    // Deform vertex position with wave
    vec3 animatedPos = vertexPos;
    animatedPos.x += sin(vertexPos.x * frequency + time * speed) * amplitude;
    animatedPos.y += sin(vertexPos.x * frequency + time * speed) * amplitude;
    animatedPos.z += cos(vertexPos.x * frequency + time * speed) * amplitude;
    // Approximate the normal using partial derivatives
    vec3 tangentX = vec3(1.0, cos(vertexPos.x * frequency + time * speed) * amplitude * frequency, 0.0);
    vec3 tangentZ = vec3(0.0, cos(vertexPos.x * frequency + time * speed) * amplitude * frequency, 1.0);
    vec3 updatedNormal = normalize(cross(tangentZ, tangentX)); // Recalculate normal

    // Transform updated normal to world space
    outputVertex.surfaceNormal = (transpose(inverse(modelMatrix)) * vec4(updatedNormal, 0.0)).xyz;

    // Transform position to world space
    vec4 worldCoord = modelMatrix * vec4(animatedPos, 1.0);
    outputVertex.surfaceWorldPos = worldCoord.xyz;

    // Final position in clip space
    gl_Position = projMatrix * viewMatrix * worldCoord;
}