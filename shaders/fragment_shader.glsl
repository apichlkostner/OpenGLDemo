#version 330 core

in vec3 pos;
in vec3 normal;
in vec3 fragmentColor;
in vec2 textureCoord;

uniform vec3 vLightPos;

out vec4 color;

void main() {
  vec3 direction = normalize(vLightPos - pos);
  vec3 nnormal = normalize(normal); // normalize interpolated value

  float faktor = max(0, (dot(direction, nnormal)));
  vec3 color3 = abs(pow(faktor, 1) * fragmentColor);
  
  float tv = sin(20.0*3.1415*textureCoord.x)*cos(20.0*3.1415*textureCoord.y);
  color = vec4(tv, tv, tv, 1.0);
}