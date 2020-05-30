#include "GLProgram.h"

#include <glm/gtc/type_ptr.hpp>

GLProgram::GLProgram(std::string const& vertex_shader_filename, std::string const& fragment_shader_filename) {
  // vertex shader
  std::ifstream vertex_shader_file(vertex_shader_filename);

  if (!vertex_shader_file) {
    throw std::runtime_error("Can't open vertex shader file");
  }
  std::string vertex_shader_string((std::istreambuf_iterator<char>(vertex_shader_file)),
                                   std::istreambuf_iterator<char>());
  const GLchar* vertex_shader_c = vertex_shader_string.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_shader_c, NULL);
  glCompileShader(vertexShader);
  check_shader_compile_errors(vertexShader);

  // fragment shader
  std::ifstream fragment_shader_file(fragment_shader_filename);
  if (!fragment_shader_file) {
    throw std::runtime_error("Can't open fragment shader file");
  }
  std::string fragment_shader_string((std::istreambuf_iterator<char>(fragment_shader_file)),
                                     std::istreambuf_iterator<char>());
  const GLchar* fragment_shader_c = fragment_shader_string.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragment_shader_c, NULL);
  glCompileShader(fragmentShader);
  check_shader_compile_errors(fragmentShader);
  // program
  program_ = glCreateProgram();
  glAttachShader(program_, vertexShader);
  glAttachShader(program_, fragmentShader);
  glLinkProgram(program_);

  // check program
  check_shader_link_errors();

  glDetachShader(program_, vertexShader);
  glDetachShader(program_, fragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  check_gl_errors();
}

GLint GLProgram::getUniformLocation(const std::string& name) { return glGetUniformLocation(program_, name.c_str()); }

GLint GLProgram::getAttribLocation(const std::string& name) { return glGetAttribLocation(program_, name.c_str()); }

void GLProgram::setUniform(GLint id, const glm::mat4& matrix) { glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix)); }

void GLProgram::setUniform(GLint id, const glm::vec3& vector) { glUniform3fv(id, 1, glm::value_ptr(vector)); }

void GLProgram::use() { glUseProgram(program_); }

void GLProgram::check_shader_compile_errors(GLuint shader) {
  GLint result = GL_FALSE;
  int info_log_length = 0;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    std::vector<char> ProgramErrorMessage(info_log_length + 1);
    glGetProgramInfoLog(program_, info_log_length, NULL, &ProgramErrorMessage[0]);
    std::cerr << (&ProgramErrorMessage[0]);
  }
}

void GLProgram::check_shader_link_errors() {
  GLint result = GL_FALSE;
  int info_log_length = 0;

  glGetProgramiv(program_, GL_LINK_STATUS, &result);
  glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &info_log_length);
  if (info_log_length > 0) {
    std::vector<char> ProgramErrorMessage(info_log_length + 1);
    glGetProgramInfoLog(program_, info_log_length, NULL, &ProgramErrorMessage[0]);
    std::cerr << (&ProgramErrorMessage[0]);
  }
}

void GLProgram::check_gl_errors() {
  GLenum e = glGetError();
  if (e != GL_NO_ERROR) {
    // throw std::runtime_error("GL error in GLProgram: " + std::to_string(e));
    std::cerr << "OpenGL error in program: " << std::to_string(e) << std::endl;
  }
}