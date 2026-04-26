cmake_minimum_required(VERSION 3.16)
project(3d_course_work)
set(CMAKE_CXX_STANDARD 17)

# GLAD
add_library(glad glad.c)
target_include_directories(glad PUBLIC include)

# GLFW и OpenGL
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)

# glm
find_path(GLM_INCLUDE_DIR glm/glm.hpp)

add_executable(${PROJECT_NAME} Main.cpp EBO.cpp shaderClass.cpp VAO.cpp VBO.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include ${GLM_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} glad OpenGL::GL ${GLFW_LIBRARIES})
