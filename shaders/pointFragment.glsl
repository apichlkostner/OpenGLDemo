#version 330 core

uniform sampler2D sprite;

in vec4 color;
out vec4 fcolor;

void main() {
    vec4 texValue = texture2D(sprite, gl_PointCoord).rgbr;
    fcolor = vec4(color * texValue);
}
