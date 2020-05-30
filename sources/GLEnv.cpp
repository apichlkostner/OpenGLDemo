#include "GLEnv.h"

GLEnv::GLEnv(uint32_t width, uint32_t height, uint32_t s, std::string title) {
  if (!glfwInit()) {
    throw(std::runtime_error("glfwInit() didn't work"));
  }

  glfwWindowHint(GLFW_SAMPLES, 4);

  window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window_ == nullptr) {
    std::cerr << "Failed to open GLFW window." << std::endl;
    glfwTerminate();
    throw(std::runtime_error("glfwCreateWindow() didn't work"));
  }

  glfwMakeContextCurrent(window_);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error((const char*)glewGetErrorString(err));
  }

  glfwSetErrorCallback(errorCallback);
}

GLEnv::~GLEnv() { glfwTerminate(); }

void GLEnv::endOfFrame() {
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

bool GLEnv::shouldClose() { return glfwWindowShouldClose(window_); }

glm::ivec2 GLEnv::getFrameBufferSize() {
  glm::ivec2 box;

  glfwGetFramebufferSize(window_, &box[0], &box[1]);

  return box;
}

void GLEnv::setKeyCallback(GLFWkeyfun keyCallbackPtr) { glfwSetKeyCallback(window_, keyCallbackPtr); }

GLFWwindow* GLEnv::getWindow() { return window_; }

void GLEnv::errorCallback(int error, const char* description) {
  std::cerr << "Fatal error: " << description << " (" << error << ")" << std::endl;
}
