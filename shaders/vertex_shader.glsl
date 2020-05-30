#version 330 core

uniform mat4 MVP;
uniform mat4 M;
uniform vec3 vLightPos;
in vec3 vPos;
in vec3 vColor;
in vec3 vNormal;

out vec3 fragmentColor;
out vec3 pos;
out vec3 normal;

void main() {
  gl_Position = MVP * vec4(vPos, 1);

  pos = (M * vec4(vPos, 1)).xyz;  
  normal = (M * vec4(vNormal, 1.0)).xyz;
  
  fragmentColor = vec3(1.0, 0.3, 0.3);
}