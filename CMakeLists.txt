cmake_minimum_required(VERSION 3.15)
project(openGL_3dEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")


add_executable(openGL_3dEngine openGL_3dEngine.cpp Callbacks.cpp Callbacks.hpp src/Camera.h src/InitMethods.h src/Window.h src/Collisions.h src/Interaction.h include/model3DS.h include/model3DS.cpp include/textureBMP.cpp include/textureBMP.h include/textureTGA.cpp include/textureTGA.h model/Airplane.cpp model/Airplane.h model/Vector.cpp model/Vector.h model/Wind.cpp model/Wind.h)
target_link_libraries(openGL_3dEngine -lOpenGL32 -lfreeGLUT -lglu32)