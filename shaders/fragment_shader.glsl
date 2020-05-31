#version 330 core

in vec3 pos;
in vec3 normal;
in vec3 fragmentColor;
in vec2 textureCoord;

uniform vec3 vLightPos;
uniform sampler2D textureSampler;
uniform mat4 invV;

out vec4 color;

void main() {
  vec3 direction = normalize(vLightPos - pos);
  vec3 nnormal = normalize(normal); // normalize interpolated value

  vec4 textureVal = texture(textureSampler, textureCoord);
  vec3 cameraPos = (invV * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
  vec3 cameraDirection = normalize(cameraPos - pos);

  // phong illumination
  float diffuse = max(0.0, dot(direction, nnormal));
  float ambient = 0.05;

  //vec3 r = normalize(2.0 * (-direction - dot(nnormal, -direction) * nnormal) + direction);
  vec3 r = reflect(-direction, nnormal);
  float specular = max(0.0, dot(cameraDirection, r));
  specular = pow(specular, 10.0);

  color = (diffuse + ambient) * textureVal + specular * vec4(1.0, 1.0, 1.0, 0.0);
}