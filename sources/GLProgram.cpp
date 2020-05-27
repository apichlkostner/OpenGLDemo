#include "GLProgram.h"

GLProgram::GLProgram(std::string const& vertex_shader_filename, std::string const& fragment_shader_filename) {
  // vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  std::ifstream vertex_shader_file(vertex_shader_filename);
  std::string vertex_shader_string((std::istreambuf_iterator<char>(vertex_shader_file)),
                                   std::istreambuf_iterator<char>());
  const GLchar* vertex_shader_c = vertex_shader_string.c_str();

  glShaderSource(vertexShader, 1, &vertex_shader_c, NULL);
  check_gl_errors();
  glCompileShader(vertexShader);
  check_gl_errors();

  // fragment shader
  std::ifstream fragment_shader_file(fragment_shader_filename);
  std::string fragment_shader_string((std::istreambuf_iterator<char>(fragment_shader_file)),
                                     std::istreambuf_iterator<char>());
  const GLchar* fragment_shader_c = fragment_shader_string.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragment_shader_c, NULL);
  check_gl_errors();
  glCompileShader(fragmentShader);
  check_gl_errors();

  // program
  program_ = glCreateProgram();
  glAttachShader(program_, vertexShader);
  check_gl_errors();
  glAttachShader(program_, fragmentShader);
  check_gl_errors();
  glLinkProgram(program_);
  check_gl_errors();
}

GLint GLProgram::getUniformLocation(const std::string& name) {
	return glGetUniformLocation(program_,name.c_str());
}

GLint GLProgram::getAttribLocation(const std::string& name) {
	return glGetAttribLocation(program_,name.c_str());
}

void GLProgram::use() {
	glUseProgram(program_);	
}

void GLProgram::check_gl_errors() {
  GLenum e = glGetError();
  if (e != GL_NO_ERROR) {
    throw std::runtime_error("GL error in GLProgram: " + std::to_string(e));
  }
}