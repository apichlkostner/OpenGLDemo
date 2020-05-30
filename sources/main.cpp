#include <GL/glew.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "GLBuffer.h"
#include "GLEnv.h"
#include "GLProgram.h"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void poll_gl_errors();

int main(int argc, char** argv) {
  GLEnv gl(640, 480, 1, "OpenGL test");
  gl.setKeyCallback(keyCallback);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Failed to init GLEW " << glewGetErrorString(err) << std::endl;
    glfwTerminate();

    return EXIT_FAILURE;
  }

  GLProgram program("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

  std::vector<float> vertices = {-0.6f, -0.4f, -1.0f, 1.0f, 0.0f, 0.0f,  0.6f, -0.4f, -1.0f,
                                 0.0f,  1.0f,  0.0f,  0.0f, 0.6f, -1.0f, 0.0f, 0.0f,  1.0f};

  GLBuffer vbPos{GL_ARRAY_BUFFER};
  vbPos.setData(vertices, 6);

  GLint mvpLocation = program.getUniformLocation("MVP");
  GLint posLocation = program.getAttribLocation("vPos");
  GLint colLocation = program.getAttribLocation("vColor");

  vbPos.connectVertexAttrib(posLocation, 3, 0);
  vbPos.connectVertexAttrib(colLocation, 3, 3);

  glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

  while (!gl.shouldClose()) {
    auto frameSize = gl.getFrameBufferSize();
    float aspect = float(frameSize[0]) / float(frameSize[1]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, frameSize[0], frameSize[1]);

    glm::mat4 p =
        glm::perspective(glm::radians<float>(90),  // The vertical Field of View, in radians: the amount of "zoom".
                         aspect,                   // Aspect Ratio.
                         0.01f,   // Near clipping plane. Keep as big as possible, or you'll get precision issues.
                         1000.0f  // Far clipping plane. Keep as little as possible.
        );

    glm::mat4 m = glm::rotate(glm::mat4(1.0f), float(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 mvp = p * m;

    program.use();
    program.setUniform(mvpLocation, mvp);

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