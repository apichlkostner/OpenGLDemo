#version 330 core

uniform mat4 MVP;
uniform mat4 M;
uniform vec3 vLightPos;
in vec3 vPos;
in vec3 vColor;
in vec3 vNormal;
in vec2 vTextureCoord;

out vec3 fragmentColor;
out vec3 pos;
out vec3 normal;
out vec2 textureCoord;

void main() {
  gl_Position = MVP * vec4(vPos, 1);

  pos = (M * vec4(vPos, 1)).xyz;  
  normal = (M * vec4(vNormal, 1.0)).xyz;

  textureCoord = vTextureCoord;
  fragmentColor = vec3(1.0, 0.3, 0.3);
}