#pragma once
#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "GLTexture2D.h"

class GLProgram {
 public:
  GLProgram(std::string const& vertex_shader_filename, std::string const& fragment_shader_filename);
  GLint getUniformLocation(const std::string& name);
  GLint getAttribLocation(const std::string& name);
  void setUniform(GLint id, const glm::mat4& matrix);
  void setUniform(GLint id, const glm::vec3& vector);
  void setTexture(GLint id, const GLTexture2D& texture, GLuint unit);
  void enable();
  void disable();

 private:
  void check_shader_compile_errors(GLuint shader);
  void check_shader_link_errors();
  void check_gl_errors();
  GLuint program_;
};