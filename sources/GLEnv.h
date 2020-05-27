#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <iostream>
#include <string>

class GLException : public std::exception {
 public:
  GLException(const std::string& what) : what_(what) {}

  virtual const char* what() { return what_.c_str(); }

 private:
  std::string what_;
};

class GLEnv {
 public:
  GLEnv(uint32_t width, uint32_t height, uint32_t s, std::string title);
  virtual ~GLEnv();

  void setKeyCallback(GLFWkeyfun keyCallbackPtr);
  GLFWwindow* getWindow();
  void endOfFrame();
  bool shouldClose();
  glm::ivec2 getFrameBufferSize();

 private:
  static void errorCallback(int error, const char* description);

  GLFWwindow* window_;
};