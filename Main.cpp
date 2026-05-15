#include "Mesh.h"
#include "Camera.hpp"
#include "Matrix.hpp"
#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

#define W_WIDTH 1920
#define W_HEIGHT 1080

Vertex vertices[] =
{
    Vertex{{-1.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{-1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    Vertex{{ 1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    Vertex{{ 1.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}
};

GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

Vertex cubeVertices[] =
{
    Vertex{{-0.25f, 0.1f,  0.25f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.25f, 0.1f,  0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.25f, 0.6f,  0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.25f, 0.6f,  0.25f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    Vertex{{ 0.25f, 0.1f, -0.25f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{-0.25f, 0.1f, -0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.25f, 0.6f, -0.25f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    Vertex{{-0.25f, 0.6f, -0.25f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

GLuint cubeIndices[] =
{
    0, 1, 2, 0, 2, 3,
    1, 4, 6, 1, 6, 2,
    4, 5, 7, 4, 7, 6,
    5, 0, 3, 5, 3, 7,
    3, 2, 6, 3, 6, 7,
    5, 4, 1, 5, 1, 0
};

Vertex lightVertices[] =
{
    Vertex{{-0.1f, -0.1f,  0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{-0.1f, -0.1f, -0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.1f, -0.1f, -0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.1f, -0.1f,  0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{-0.1f,  0.1f,  0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{-0.1f,  0.1f, -0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.1f,  0.1f, -0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.1f,  0.1f,  0.1f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}
};

GLuint lightIndices[] =
{
    0, 1, 2, 0, 2, 3,
    0, 4, 7, 0, 7, 3,
    3, 7, 6, 3, 6, 2,
    2, 6, 5, 2, 5, 1,
    1, 5, 4, 1, 4, 0,
    4, 5, 6, 4, 6, 7
};

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "3d-course-work", NULL, NULL);
    if (window == NULL) {
        const char *description;
        glfwGetError(&description);
        std::cout << "Failed to create window: " << description << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, W_WIDTH, W_HEIGHT);

    Texture textures[] =
    {
        Texture("../Resources/Textures/pop_cat.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("../Resources/Textures/pop.png", "specular", 1, GL_RGBA, GL_UNSIGNED_BYTE)
    };

    Shader shaderProgram("../Resources/Shaders/default.vert",
                         "../Resources/Shaders/default.frag");

    std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh floor(verts, ind, tex);

    std::vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    std::vector<GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    Mesh cube(cubeVerts, cubeInd, tex);

    Shader lightShader("../Resources/Shaders/light.vert",
                       "../Resources/Shaders/light.frag");
    std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex);

    float lightColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightPos[3] = {0.5f, 0.5f, 0.5f};
    matrix4 lightModel = createIdentityMatrix();
    lightModel = createTranslationMatrix(lightPos[0], lightPos[1], lightPos[2]);

    matrix4 objectModel = createIdentityMatrix();
    objectModel = createTranslationMatrix(0.0f, 0.0f, 0.0f);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, lightModel.data());
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);

    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, objectModel.data());
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);

    glEnable(GL_DEPTH_TEST);

    float pos[3] = {0.f, 0.f, 2.f};
    Camera camera(W_WIDTH, W_HEIGHT, pos);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.f, 0.1f, 100.f);

        floor.Draw(shaderProgram, camera);
        cube.Draw(shaderProgram, camera);
        light.Draw(lightShader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shaderProgram.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
