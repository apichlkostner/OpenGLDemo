#pragma once

#include <glm/glm.hpp>
#include <vector>

class Tesselation {
 public:
  static Tesselation genSphere(const glm::vec3& center, const float radius, const uint32_t sectorCount,
                               const uint32_t stackCount);

  const std::vector<float>& getVertices() const { return vertices; }
  const std::vector<float>& getNormals() const { return normals; }
  const std::vector<float>& getTangents() const { return tangents; }
  const std::vector<float>& getTexCoords() const { return texCoords; }
  const std::vector<uint32_t>& getIndices() const { return indices; }

 private:
  Tesselation() {}

  std::vector<float> vertices;
  std::vector<float> normals;
  std::vector<float> tangents;
  std::vector<float> texCoords;
  std::vector<uint32_t> indices;
};