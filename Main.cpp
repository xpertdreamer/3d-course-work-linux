#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // GLFW initialization
    glfwInit();

    /*
     * In this line we tell glfw which version of opengl we gonna use
     * also the last line tells fw that we use core profile which meanse
     * "support modern functions witch backaward compatibility"
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*
     * Window creation proccess with error - handling
     * and introduce it into current context
     */
    GLFWwindow *window =
        glfwCreateWindow(800, 600, "3d-course-work", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    /*
     * In the next lines we gonna initialize GLAD to configure OpenGL
     * First - specify viewport of opengl in the window
     * Second - specify the color of the background
     * Third - clean the backbuffer and assingn the new color to it
     * Fourth - swap the back and front buffers
     */
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //    gladLoadGL();

    glViewport(0, 0, 800, 600);

    glClearColor(0.7f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    // Just a main loop to handle events
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // Free
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
