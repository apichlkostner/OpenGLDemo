#version 330 core

uniform mat4 MVP;
in vec3 vPos;
in vec3 vColor;

out vec3 fragmentColor;

void main() {
  gl_Position = MVP * vec4(vPos, 1);
  fragmentColor = abs(vPos) / 2.0;
}