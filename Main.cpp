#include "Matrix.hpp"
#include "Texture.h"
#include "include/glad/glad.h"
#include "include/stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"

#define W_WIDTH 800
#define W_HEIGHT 800

// Vertices coordinates
GLfloat vertices[] =
    { //     COORDINATES     /        COLORS      /   TexCoord  //
        -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
        -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
        0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
        5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

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

    Shader shaderProgram("../Resources/Shaders/default.vert",
                         "../Resources/Shaders/default.frag");
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO attributtes such as coord and color to VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float),
                    (void *)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
                    (void *)(6 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Gets ID of uniform called "scale"
    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture
    Texture popCat("../Resources/Textures/pop_cat.png", GL_TEXTURE_2D,
                   GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    glEnable(GL_DEPTH_TEST);

    // Just a main loop to handle events
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.996f, 0.996f, 0.874f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60) {
            rotation += 0.5f;
            prevTime = crntTime;
        }

        matrix4 model = createIdentityMatrix();
        matrix4 view = createIdentityMatrix();
        matrix4 proj = createIdentityMatrix();
        model = multiplyMatrices(model,
                                 createRotationMatrixY(glm::radians(rotation)));
        view =
            multiplyMatrices(view, createTranslationMatrix(0.0f, -0.5f, -2.0f));
        proj = createPerspectiveMatrix(
            glm::radians(45.0f), (float)(W_WIDTH / W_HEIGHT), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());
        int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj.data());

        glUniform1f(uniID, 0.5f);
        popCat.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int),
                       GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
