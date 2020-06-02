#include "Particle.h"

#include "RandomDist.h"

Particle::Particle(glm::vec3 spawnPos, float spawnRadius, float velocity, float lifetime, glm::vec3 acceleration,
                   glm::vec3 color)
    : acc_(acceleration), color_(color), lifetime_(lifetime) {
  pos_ = spawnPos + spawnRadius * RandomDist::random_vec3(-1., 1.);
  vel_ = velocity * RandomDist::random_vec3();
  lifetime_ *= RandomDist::random_double();
  color_ *= RandomDist::random_vec3();
}

std::vector<float> Particle::getData() const {
  return {pos_[0], pos_[1], pos_[2], color_[0], color_[1], color_[2], 0.5};
}

void Particle::update(float dt) {
  vel_ += acc_ * dt;
  pos_ += vel_ * dt;
  lifetime_ -= dt;
}