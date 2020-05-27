cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# add the executable
add_executable(opengltest main.cpp GLEnv.cpp GLProgram.cpp)

target_include_directories(opengltest PRIVATE ${PROJECT_SOURCE_DIR}/include
                                PUBLIC "${PROJECT_BINARY_DIR}"
                           )

#set(ENV{LD_PRELOAD} /usr/local/lib/libamdlibm.so)

target_link_libraries(opengltest pthread GLEW glfw OpenGL::GL glm)

# add the install targets
install(TARGETS opengltest DESTINATION bin)
