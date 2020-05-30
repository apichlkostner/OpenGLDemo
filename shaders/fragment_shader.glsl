#version 330 core

in vec3 pos;
in vec3 normal;
in vec3 fragmentColor;

uniform vec3 vLightPos;

out vec4 color;

void main() {
  //vec3 light = vLightPos;
  vec3 direction = normalize(vLightPos - pos);
  vec3 nnormal = normalize(normal); // normalize interpolated value

  float faktor = max(0, (dot(direction, nnormal)));
  vec3 color3 = abs(pow(faktor, 1) * fragmentColor);
  //color3 = fragmentColor + vec3(0.1,0.1,0.1);
  color = vec4(color3, 1.0);
}