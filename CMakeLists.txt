cmake_minimum_required(VERSION 3.8)
project(hw5)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Objects/Sphere.cpp Objects/Sphere.h Vector3.cpp Vector3.h Ray.cpp Ray.h Scene.cpp Scene.h PixelBuffer.cpp PixelBuffer.h Camera.cpp Camera.h Intersection.cpp Intersection.h Color.cpp Color.h Light.cpp Light.h Objects/Plane.cpp Objects/Plane.h Objects/Object.cpp Objects/Object.h)
add_executable(hw5 ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

target_link_libraries(hw5 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})