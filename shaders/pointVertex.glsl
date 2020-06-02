#version 330 core

in vec3 vPos;
in vec4 vColor;

uniform mat4 MVP;

out vec4 color;

void main() {
	gl_Position = MVP * vec4(vPos, 1.0);
    color = vColor;
}
