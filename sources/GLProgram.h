#pragma once
#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

class GLProgram {
 public:
  GLProgram(std::string const& vertex_shader_filename, std::string const& fragment_shader_filename);
  GLint getUniformLocation(const std::string& name);
  GLint getAttribLocation(const std::string& name);
  void use();

 private:
  void check_gl_errors();
  GLuint program_;
};