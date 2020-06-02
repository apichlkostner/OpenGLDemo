#version 330 core

in vec3 pos;
in vec3 normal;
in vec3 tangent;
in vec2 textureCoord;

uniform vec3 vLightPos;
uniform sampler2D textureSampler;
uniform sampler2D normalSampler;
uniform mat4 invV;

out vec4 color;

void main() {
  vec3 direction = normalize(vLightPos - pos);
  vec3 nnormal = normalize(normal); // normalize interpolated value
  vec3 ntangent = normalize(tangent); // normalize interpolated value
  vec3 nbinorm = normalize(cross(nnormal, ntangent));
  //vec3 nbinorm = normalize(cross(ntangent, nnormal));

  // albedo and normal map
  vec4 textureVal = texture(textureSampler, textureCoord);
  vec3 normalVal = normalize(2.0 * (texture(normalSampler, textureCoord).xyz - 0.5));
  //normalVal = vec3(0,0,1);
  // calculate normal from normal map
  nnormal = normalize(mat3(ntangent, nbinorm, nnormal) * normalVal);
  
  // camera position and direction for specular part of illumination
  vec3 cameraPos = (invV * vec4(0.0, 0.0, 0.0, 1.0)).xyz + 0.001 * normalVal.xyz;
  vec3 cameraDirection = normalize(cameraPos - pos);

  // phong illumination
  float diffuse = max(0.0, dot(direction, nnormal));
  float ambient = 0.05;

  vec3 r = reflect(-direction, nnormal);
  float specular = max(0.0, dot(cameraDirection, r));
  specular = pow(specular, 20.0);

  color = (diffuse + ambient) * textureVal + specular * vec4(1.0, 1.0, 1.0, 0.0);
}