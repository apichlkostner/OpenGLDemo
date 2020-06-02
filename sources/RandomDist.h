#pragma once

#include <glm/glm.hpp>
#include <random>

class RandomDist {
 public:
  static inline double random_double() {
    // thread_local to speed up, else the threads wait most of the time
    static thread_local std::mt19937 generator;  // slow
    // static thread_local std::ranlux48_base generator; // faster
    // fast random number generator
    // static thread_local std::minstd_rand generator;  // fastest
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
  }

  static inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
  }

  static inline glm::vec3 random_vec3() { return {random_double(), random_double(), random_double()}; }

  static inline glm::vec3 random_vec3(double min, double max) { return {random_double(min, max), random_double(min, max), random_double(min, max)}; }
};