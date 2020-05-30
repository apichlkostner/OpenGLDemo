#version 430 core

uniform mat4 MVP;
in vec3 vPos;
in vec3 vColor;

out vec3 fragmentColor;

void main() {
  gl_Position = MVP * vec4(vPos, 1);
  fragmentColor = abs((MVP * vec4(vPos, 1))).xyz / 2.0; //vColor;
}