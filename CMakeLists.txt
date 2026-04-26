cmake_minimum_required(VERSION 3.16)
project(3d_course_work)
set(CMAKE_CXX_STANDARD 17)

add_library(glad glad.c)
target_include_directories(glad PUBLIC include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} Main.cpp)
target_link_libraries(${PROJECT_NAME} glad OpenGL::GL ${GLFW_LIBRARIES})
