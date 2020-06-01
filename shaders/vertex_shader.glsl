#version 330 core

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 MInverseTranspose;
uniform vec3 vLightPos;

in vec3 vPos;
in vec3 vNormal;
in vec3 vTangent;
in vec2 vTextureCoord;

out vec3 pos;
out vec3 normal;
out vec3 tangent;
out vec2 textureCoord;

void main() {
  gl_Position = MVP * vec4(vPos, 1);

  pos = (M * vec4(vPos, 1)).xyz;  
  normal = (MInverseTranspose * vec4(vNormal, 0.0)).xyz;
  tangent = (MInverseTranspose * vec4(vTangent, 0.0)).xyz;

  textureCoord = vTextureCoord;
}