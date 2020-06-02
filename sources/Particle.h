#pragma once

#include <glm/glm.hpp>
#include <vector>

class Particle {
 public:
  Particle(glm::vec3 spawnPos, float spawnRadius, float velocity, float lifetime, glm::vec3 acceleration,
           glm::vec3 color);
  std::vector<float> getData() const;
  void update(float dt);
  float lifetime() { return lifetime_; }

 private:
  glm::vec3 pos_;
  glm::vec3 vel_;
  glm::vec3 acc_;
  glm::vec3 color_;
  float lifetime_;
};