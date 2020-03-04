cmake_minimum_required(VERSION 3.15)
project(openGL_3dEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(openGL_3dEngine HelloGLUT.c Callbacks.c Callbacks.h)
target_link_libraries(openGL_3dEngine -lOpenGL32 -lfreeGLUT)