#version 330 core

in vec3 pos;
in vec3 normal;
in vec3 fragmentColor;
in vec2 textureCoord;

uniform vec3 vLightPos;
uniform sampler2D textureSampler;

out vec4 color;

void main() {
  vec3 direction = normalize(vLightPos - pos);
  vec3 nnormal = normalize(normal); // normalize interpolated value

  vec4 textureVal = texture(textureSampler, textureCoord);

  // phong illumination
  float diffuse = max(0.0, dot(direction, nnormal));
  float ambient = 0.05;
  //float specular = dot(pos, reflect(-vLightPos, nnormal));
  float specular = max(0.0, dot(pos, 2.0 * (direction - dot(nnormal, direction) * nnormal) + direction));
  specular =  pow(specular, 20);

  color = (diffuse + ambient) * textureVal + specular * vec4(1.0, 1.0, 1.0, 0.0);
}