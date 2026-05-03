#include "Mesh.h"
#include "Texture.h"
#include "include/glad/glad.h"
#include "include/stb/stb_image.h"
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#define W_WIDTH 1920
#define W_HEIGHT 1080


// Vertices coordinates
Vertex vertices[] =
{
    Vertex{{-0.5f, 0.0f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.83f, 0.70f, 0.44f}, {0.0f, 0.0f}},
    Vertex{{-0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.83f, 0.70f, 0.44f}, {5.0f, 0.0f}},
    Vertex{{ 0.5f, 0.0f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.83f, 0.70f, 0.44f}, {0.0f, 0.0f}},
    Vertex{{ 0.5f, 0.0f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.83f, 0.70f, 0.44f}, {5.0f, 0.0f}},
    Vertex{{ 0.0f, 0.8f,  0.0f}, {0.0f, 1.0f, 0.0f}, {0.92f, 0.86f, 0.76f}, {2.5f, 5.0f}}
};

// Indices for vertices order
GLuint indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

Vertex cubeVertices[] =
{
    // Передняя грань
    Vertex{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    Vertex{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    // Задняя грань
    Vertex{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    Vertex{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    // Верхняя грань
    Vertex{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    // Нижняя грань
    Vertex{{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    Vertex{{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    // Правая грань
    Vertex{{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    // Левая грань
    Vertex{{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    Vertex{{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    Vertex{{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

GLuint cubeIndices[] =
{
    0, 1, 2, 0, 2, 3,       // Передняя
    4, 5, 6, 4, 6, 7,       // Задняя
    8, 9, 10, 8, 10, 11,    // Верхняя
    12, 13, 14, 12, 14, 15, // Нижняя
    16, 17, 18, 16, 18, 19, // Правая
    20, 21, 22, 20, 22, 23  // Левая
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

    Texture textures[]
    {
    Texture
    (
        "../Resources/Textures/pop_cat.png",
        GL_TEXTURE_2D,
        GL_TEXTURE0,
        GL_RGBA,
        GL_UNSIGNED_BYTE
    )
    };

    Texture textures2[]
    {
    Texture
    (
        "../Resources/Textures/pop_cat.png",
        GL_TEXTURE_2D,
        GL_TEXTURE0,
        GL_RGBA,
        GL_UNSIGNED_BYTE
    )
    };

    Shader shaderProgram("../Resources/Shaders/default.vert",
                         "../Resources/Shaders/default.frag");
    // Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    // Create floor mesh
	Mesh floor(verts, ind, tex);

    std::vector<Vertex> verts2(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    std::vector<GLuint> ind2(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    std::vector<Texture> tex2(textures2, textures2 + sizeof(textures2) / sizeof(Texture));
    Mesh cube(verts2, ind2, tex2);

    glEnable(GL_DEPTH_TEST);

    float pos[3] = {0.f, 0.f, 2.f};
    Camera camera(W_WIDTH, W_HEIGHT, pos); 

    // Just a main loop to handle events
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.996f, 0.996f, 0.874f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.f, 0.1f, 100.f);

        matrix4 model = createIdentityMatrix();
        model = createTranslationMatrix(-1.5f, 0.0f, 0.0f);
        floor.Draw(shaderProgram, camera, model);

        matrix4 model2 = createIdentityMatrix();
        model2 = createTranslationMatrix(1.5f, 0.0f, 0.0f);
        float time = glfwGetTime();
        model2 = multiplyMatrices(model2, createRotationMatrixY(time));
        cube.Draw(shaderProgram, camera, model2);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Free
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
