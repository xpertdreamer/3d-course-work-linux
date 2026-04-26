#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"

#define W_WIDTH 800
#define W_HEIGHT 800

// Vertices coordinates
GLfloat vertices[] = {
    //               COORDINATES                  /     COLORS           //
    -0.5f,  -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f,
    0.02f, // Lower left corner
    0.5f,   -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f,
    0.02f, // Lower right corner
    0.0f,   0.5f * float(sqrt(3)) * 2 / 3,  0.0f, 1.0f, 0.6f,
    0.32f, // Upper corner
    -0.25f, 0.5f * float(sqrt(3)) * 1 / 6,  0.0f, 0.9f, 0.45f,
    0.17f, // Inner left
    0.25f,  0.5f * float(sqrt(3)) * 1 / 6,  0.0f, 0.9f, 0.45f,
    0.17f, // Inner right
    0.0f,   -0.5f * float(sqrt(3)) * 1 / 3, 0.0f, 0.8f, 0.3f,
    0.02f // Inner down
};

// Indices for vertices order
GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1  // Upper triangle
};

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
        glfwCreateWindow(W_WIDTH, W_HEIGHT, "3d-course-work", NULL, NULL);
    if (window == NULL) {
        const char *description;
        glfwGetError(&description);
        std::cout << "Failed to create window" << description << std::endl;
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
    glViewport(0, 0, W_WIDTH, W_HEIGHT);

    Shader shaderProgram("../default.vert", "../default.frag");
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributtes such as coord and color to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float),
                    (void *)(3 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Just a main loop to handle events
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.996f, 0.996f, 0.874f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
