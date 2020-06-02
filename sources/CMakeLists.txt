cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(png++)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# add the executable
add_executable(opengltest main.cpp GLEnv.cpp GLProgram.cpp GLBuffer.cpp Tesselation.cpp GLTexture2D.cpp Particle.cpp ParticleSystem.cpp)

target_include_directories(opengltest PRIVATE ${PROJECT_SOURCE_DIR}/include
                                PUBLIC "${PROJECT_BINARY_DIR}"
                           )

#set(ENV{LD_PRELOAD} /usr/local/lib/libamdlibm.so)

if (png++_FOUND)
     add_definitions(-DUSE_PNG)
     target_link_libraries(opengltest ${png++_LIBRARIES})
     message(INFO " Using png++")
else()
     message(INFO " png++ not available")
endif()

target_link_libraries(opengltest pthread GLEW glfw OpenGL::GL glm)

# add the install targets
install(TARGETS opengltest DESTINATION bin)
