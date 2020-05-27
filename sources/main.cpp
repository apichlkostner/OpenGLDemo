#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "GLEnv.h"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void poll_gl_errors();

int main(int argc, char** argv) {
  GLEnv gl(640, 480, 1, "Interactive Late Night Coding");
  gl.setKeyCallback(keyCallback);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Failed to init GLEW " << glewGetErrorString(err) << std::endl;
    glfwTerminate();

    return EXIT_FAILURE;
  }

  std::vector<float> vertices = {-0.6f, -0.4f, -1.0f, 1.0f, 0.0f, 0.0f,  0.6f, -0.4f, -1.0f,
                                 0.0f,  1.0f,  0.0f,  0.0f, 0.6f, -1.0f, 0.0f, 0.0f,  1.0f};

  GLuint vertexBuffer;

  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  std::ifstream vertex_shader_file("shaders/vertex_shader.glsl");
  std::string vertex_shader_string((std::istreambuf_iterator<char>(vertex_shader_file)),
                                   std::istreambuf_iterator<char>());
  const GLchar* vertex_shader_c = vertex_shader_string.c_str();

  glShaderSource(vertexShader, 1, &vertex_shader_c, NULL);
  glCompileShader(vertexShader);
  poll_gl_errors();

  std::ifstream fragment_shader_file("shaders/fragment_shader.glsl");
  std::string fragment_shader_string((std::istreambuf_iterator<char>(fragment_shader_file)),
                                     std::istreambuf_iterator<char>());
  const GLchar* fragment_shader_c = fragment_shader_string.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(fragmentShader, 1, &fragment_shader_c, NULL);
  glCompileShader(fragmentShader);
  poll_gl_errors();

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  poll_gl_errors();

  GLint mvpLocation = glGetUniformLocation(program, "MVP");
  GLint posLocation = glGetAttribLocation(program, "vPos");
  GLint colLocation = glGetAttribLocation(program, "vCol");

  glEnableVertexAttribArray(posLocation);
  glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
  glEnableVertexAttribArray(colLocation);
  glVertexAttribPointer(colLocation, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));

  while (!gl.shouldClose()) {
    auto frameSize = gl.getFrameBufferSize();
    float aspect = float(frameSize[0]) / float(frameSize[1]);
        
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, frameSize[0], frameSize[1]);
    
    glm::mat4 p =
        glm::perspective(glm::radians<float>(90),  // The vertical Field of View, in radians: the amount of "zoom".
                         aspect,                   // Aspect Ratio.
                         0.01f,   // Near clipping plane. Keep as big as possible, or you'll get precision issues.
                         1000.0f  // Far clipping plane. Keep as little as possible.
        );

    glm::mat4 mvp = glm::rotate(p, float(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

    glUseProgram(program);
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);

    gl.endOfFrame();

    poll_gl_errors();
  }

  return EXIT_SUCCESS;
}

static void poll_gl_errors() {
  GLenum e;
  while ((e = glGetError()) != GL_NO_ERROR) {
    std::cerr << "OpenGL error: " << e << std::endl;
  }
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}