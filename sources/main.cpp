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
#include "GLTexture2D.h"
#include "Image.h"
#include "Tesselation.h"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void poll_gl_errors();

int main(int argc, char** argv) {
  GLEnv gl(640, 480, 1, "OpenGL test");

  // callback
  gl.setKeyCallback(keyCallback);

  // load shaders
  GLProgram program("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

  // graphic
  Tesselation sphere(Tesselation::genSphere({0, 0, 0}, 1, 100, 100));

  GLBuffer vbPos(GL_ARRAY_BUFFER);
  vbPos.setData(sphere.getVertices(), 3);

  GLBuffer vTextureCoord(GL_ARRAY_BUFFER);
  vTextureCoord.setData(sphere.getTexCoords(), 2);

  GLBuffer vNormals(GL_ARRAY_BUFFER);
  vNormals.setData(sphere.getNormals(), 3);

  GLBuffer vTangents(GL_ARRAY_BUFFER);
  vTangents.setData(sphere.getTangents(), 3);

  GLBuffer ib(GL_ELEMENT_ARRAY_BUFFER);
  ib.setData(sphere.getIndices());

  Image image_albedo;
  //image_albedo.loadPng("assets/albedo.png");
  image_albedo.loadBmp("assets/albedo.bmp");

  GLTexture2D textureAlbedo(image_albedo.width(), image_albedo.height(), image_albedo.bits_per_pixel() / 8, GL_LINEAR,
                            GL_LINEAR);
  textureAlbedo.setData(image_albedo.data());

  Image image_normal;
  //image_normal.loadPng("assets/normal.png");
  image_normal.loadBmp("assets/normal.bmp");

  GLTexture2D textureNormal(image_normal.width(), image_normal.height(), image_normal.bits_per_pixel() / 8, GL_LINEAR,
                            GL_LINEAR);
  textureNormal.setData(image_normal.data());

  GLint mvpLocation = program.getUniformLocation("MVP");
  GLint mLocation = program.getUniformLocation("M");
  GLint MInverseTransposeLocation = program.getUniformLocation("MInverseTranspose");
  GLint lighLocation = program.getUniformLocation("vLightPos");
  GLint textureSamplerLocation = program.getUniformLocation("textureSampler");
  GLint normalSamplerLocation = program.getUniformLocation("normalSampler");
  GLint invVLocation = program.getUniformLocation("invV");

  GLint posLocation = program.getAttribLocation("vPos");
  GLint normalLocation = program.getAttribLocation("vNormal");
  GLint tangentLocation = program.getAttribLocation("vTangent");
  GLint vTextureCoordLocation = program.getAttribLocation("vTextureCoord");

  vbPos.connectVertexAttrib(posLocation, 3);
  vNormals.connectVertexAttrib(normalLocation, 3);
  vTangents.connectVertexAttrib(tangentLocation, 3);
  vTextureCoord.connectVertexAttrib(vTextureCoordLocation, 2);

  glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
  glClearDepth(1.0f);

  poll_gl_errors();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);  

  glm::vec3 lightPos(1., 1., 2);

  // std::cout << "indices: " << sphere.getIndices().size() << " vertices: " << sphere.getVertices().size() <<
  // std::endl;

  while (!gl.shouldClose()) {
    auto frameSize = gl.getFrameBufferSize();
    float aspect = float(frameSize[0]) / float(frameSize[1]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, frameSize[0], frameSize[1]);
    program.use();

    glm::mat4 p =
        glm::perspective(glm::radians<float>(90),  // The vertical Field of View, in radians: the amount of "zoom".
                         aspect,                   // Aspect Ratio.
                         0.01f,   // Near clipping plane. Keep as big as possible, or you'll get precision issues.
                         1000.0f  // Far clipping plane. Keep as little as possible.
        );

    glm::mat4 v = glm::lookAt(glm::vec3{0., 0., 2.}, glm::vec3{0., 0., 0.}, glm::vec3{0., 1., 0.});

    glm::mat4 m = glm::rotate(glm::mat4(1.0f), float(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
    m = glm::rotate(m, float(glm::radians(90.0)), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 mvp = p * v * m;

    program.setUniform(mvpLocation, mvp);
    program.setUniform(mLocation, m);
    program.setUniform(MInverseTransposeLocation, glm::transpose(glm::inverse(m)));
    program.setUniform(invVLocation, glm::inverse(v));
    program.setUniform(lighLocation, lightPos);
    program.setTexture(textureSamplerLocation, textureAlbedo, 0);
    program.setTexture(normalSamplerLocation, textureNormal, 1);

    glDrawElements(GL_TRIANGLES, sphere.getIndices().size(), GL_UNSIGNED_INT, (void*)0);

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