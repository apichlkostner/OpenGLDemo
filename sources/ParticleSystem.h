#pragma once

#include "GLBuffer.h"
#include "GLEnv.h"
#include "GLProgram.h"
#include "GLTexture2D.h"
#include "Particle.h"

class ParticleSystem {
 public:
  ParticleSystem(uint32_t particleCount, const glm::vec3& center, float spreadRadius, const glm::vec3& acceleration,
                 float lifetime, float pointSize, const glm::vec3& color);

  void render(const glm::mat4& v, const glm::mat4& p);
  void update();

 private:
  GLProgram program;
  glm::vec3 center;
  float spreadRadius;
  std::vector<Particle> particles;

  GLint mvpLocation;
  GLint posLocation;
  GLint colLocation;
  GLint texLocation;

  GLTexture2D sprite;

  glm::vec3 acceleration;

  float pointSize;
  glm::vec3 color;
  float lifetime_;
};