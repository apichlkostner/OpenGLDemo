#include "ParticleSystem.h"

#include "sprite_pixel.h"

ParticleSystem::ParticleSystem(uint32_t particleCount, const glm::vec3& center, float spreadRadius,
                               const glm::vec3& acceleration, float lifetime, float pointSize, const glm::vec3& color)
    : program("shaders/pointVertex.glsl", "shaders/pointFragment.glsl"),
      center(center),
      spreadRadius(spreadRadius),
      particles(),
      mvpLocation{0},
      posLocation{0},
      colLocation{0},
      texLocation{0},
      sprite(64, 64, 3, GL_LINEAR, GL_LINEAR),
      acceleration(acceleration),
      pointSize{pointSize},
      color(color),
      lifetime_(lifetime) {
  // setup shader
  mvpLocation = program.getUniformLocation("MVP");
  posLocation = program.getAttribLocation("vPos");
  colLocation = program.getAttribLocation("vColor");
  texLocation = program.getUniformLocation("sprite");

  // setup texture
  sprite.setData(spritePixel);

  for (uint32_t particleNr = 0; particleNr < particleCount; particleNr++) {
    Particle p(center, spreadRadius, 1., lifetime_, acceleration, color);
    particles.push_back(p);
  }
}

void ParticleSystem::render(const glm::mat4& v, const glm::mat4& p) {
  program.enable();
  program.setUniform(mvpLocation, p * v);
  program.setTexture(texLocation, sprite, 0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  glBlendEquation(GL_FUNC_ADD);

  glDisable(GL_CULL_FACE);

  glDepthMask(GL_FALSE);

  glPointSize(pointSize);

  std::vector<float> data;
  for (const Particle& p : particles) {
    std::vector<float> pData = p.getData();
    data.insert(data.end(), pData.begin(), pData.end());
  }

  GLBuffer vbPosColor(GL_ARRAY_BUFFER);
  vbPosColor.setData(data, 7);
  vbPosColor.connectVertexAttrib(posLocation, 3);
  vbPosColor.connectVertexAttrib(colLocation, 4, 3);

  glEnable(GL_POINT_SPRITE);

  glDrawArrays(GL_POINTS, 0, particles.size());

  glDisable(GL_POINT_SPRITE);
  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glDepthMask(GL_TRUE);
}

void ParticleSystem::update() {
  for (Particle& p : particles) {
    p.update(1. / 60.);
    if (p.lifetime() <= 0) {
      p = Particle(center, spreadRadius, 1., lifetime_, acceleration, color);
    }
  }
}