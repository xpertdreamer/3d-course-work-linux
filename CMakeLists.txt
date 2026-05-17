cmake_minimum_required(VERSION 3.16)
project(3d_course_work)
set(CMAKE_CXX_STANDARD 17)

# GLAD
add_library(glad glad.c)
target_include_directories(glad PUBLIC include)

# GLFW и OpenGL & ImGUI
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

# glm
find_path(GLM_INCLUDE_DIR glm/glm.hpp)

add_executable(${PROJECT_NAME} stb.cpp Main.cpp EBO.cpp shaderClass.cpp VAO.cpp VBO.cpp Texture.cpp Camera.cpp Mesh.cpp ${IMGUI_SOURCES} Axis.cpp Util.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include ${GLM_INCLUDE_DIR} ${IMGUI_DIR})
target_link_libraries(${PROJECT_NAME} glad OpenGL::GL ${GLFW_LIBRARIES})
