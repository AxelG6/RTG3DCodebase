#version 450 core

// Uniforms for transformation matrices
uniform mat4 modelMatrix; 
uniform mat4 viewMatrix;  
uniform mat4 projMatrix;  

layout(location = 0) in vec3 vertexPos;      // Vertex position
layout(location = 2) in vec2 vertexTexCoord; // Vertex texture coordinates
layout(location = 3) in vec3 vertexNormal;  

// Output to the fragment shader
out SimplePacket {
    vec3 surfaceWorldPos;  // Surface position in world space
    vec3 surfaceNormal;    // Surface normal in world space
    vec2 texCoord;         // Texture coordinates
} outputVertex;

void main(void) {
  // Pass the texture coordinates to the fragment shader
outputVertex.texCoord = vertexTexCoord;

// Transform the normal vector by the inverse-transpose of the model matrix
outputVertex.surfaceNormal = normalize((transpose(inverse(modelMatrix)) * vec4(vertexNormal, 0.0)).xyz);

// Transform vertex position into world coordinates and pass to the fragment shader
vec4 worldCoord = modelMatrix * vec4(vertexPos, 1.0);
outputVertex.surfaceWorldPos = worldCoord.xyz;

// Transform vertex position into clip coordinates and set it to gl_Position
gl_Position = projMatrix * viewMatrix * worldCoord;
}