#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Camera.hpp"
#include "Matrix.hpp"
#include "Model.h"
#include "Raycast.h"
#include "Texture.h"
#include "shaderClass.h"
#include "VBO.h"
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#define W_WIDTH 1920
#define W_HEIGHT 1080

bool skullSelected = false;
bool cubeSelected = false;
bool rightPressed = false;

float skullCenter[3] = {0.f, 0.f, 0.f};
float cubeCenter[3] = {5.f, 0.f, 0.f};

// Vertex vertices[] =
// {
//     Vertex{{-1.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
//     Vertex{{-1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
//     Vertex{{ 1.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
//     Vertex{{ 1.0f, 0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}
// };

// GLuint indices[] =
// {
//     0, 2, 1,
//     0, 3, 2
// };


Vertex cubeVertices[] =
{
    Vertex{{-0.25f, 0.1f,  0.25f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.25f, 0.1f,  0.25f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.25f, 0.6f,  0.25f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.25f, 0.6f,  0.25f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    Vertex{{ 0.25f, 0.1f, -0.25f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{-0.25f, 0.1f, -0.25f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{-0.25f, 0.6f, -0.25f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{ 0.25f, 0.6f, -0.25f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    Vertex{{-0.25f, 0.6f,  0.25f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.25f, 0.6f,  0.25f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.25f, 0.6f, -0.25f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.25f, 0.6f, -0.25f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    Vertex{{-0.25f, 0.1f, -0.25f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.25f, 0.1f, -0.25f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.25f, 0.1f,  0.25f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.25f, 0.1f,  0.25f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    Vertex{{ 0.25f, 0.1f,  0.25f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{ 0.25f, 0.1f, -0.25f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{ 0.25f, 0.6f, -0.25f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{ 0.25f, 0.6f,  0.25f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

    Vertex{{-0.25f, 0.1f, -0.25f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    Vertex{{-0.25f, 0.1f,  0.25f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    Vertex{{-0.25f, 0.6f,  0.25f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    Vertex{{-0.25f, 0.6f, -0.25f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
};

GLuint cubeIndices[] =
{
    0,  1,  2,  0,  2,  3,
    4,  5,  6,  4,  6,  7,
    8,  9,  10, 8,  10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23 
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
    glfwWindowHint(GLFW_STENCIL_BITS, 8);

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

    
    Texture floorTextures[] =
    {
        Texture("../Resources/Textures/pop_cat.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };

    Texture cubeTextures[] =
    {
        Texture("../Resources/Textures/pop.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };

    Texture modelTextures[] =
    {
        Texture("../Resources/Textures/skull.jpg", "specular", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };

    

    Shader shaderProgram("../Resources/Shaders/default.vert",
                         "../Resources/Shaders/default.frag");
    Shader outliningProgram("../Resources/Shaders/outlining.vert",
                            "../Resources/Shaders/outlining.frag");
    
    // std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    // std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector<Texture> tex(floorTextures, floorTextures + sizeof(floorTextures) / sizeof(Texture));
    // Mesh floor(verts, ind, tex);

    std::vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    std::vector<GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    std::vector<Texture> tex2(cubeTextures, cubeTextures + sizeof(cubeTextures) / sizeof(Texture));
    Mesh cube(cubeVerts, cubeInd, tex2);

    std::vector<Texture> modelTex(modelTextures, modelTextures + sizeof(modelTextures) / sizeof(Texture));
    Model model("../Resources/Models/skull.obj", tex);

    Shader lightShader("../Resources/Shaders/light.vert",
                       "../Resources/Shaders/light.frag");
    std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex2);

    float lightColor[4] = {1.f, 1.f, 0.5f, 1.0f};
    float lightPos[3] = {0.f, 4.f, 0.f};
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
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    float pos[3] = {0.f, 0.f, 2.f};
    Camera camera(W_WIDTH, W_HEIGHT, pos);
    
//     while (!glfwWindowShouldClose(window)) {
//         glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         camera.Inputs(window);
//         camera.updateMatrix(45.f, 0.1f, 100.f);

//         floor.Draw(shaderProgram, camera);
//         cube.Draw(shaderProgram, camera);
// //        model.Draw(shaderProgram, camera);
//         light.Draw(lightShader, camera);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (!io.WantCaptureMouse)
        {
            camera.Inputs(window);            
        }

        camera.updateMatrix(45.f, 0.1f, 100.f);

        // matrix4 floorModel = createIdentityMatrix();
        // shaderProgram.Activate();
        // glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, floorModel.data());
        // floor.Draw(shaderProgram, camera);

        if (!io.WantCaptureMouse)
        {
              bool rightNow = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
              if (rightNow && !rightPressed)
              {
                  double mX, mY;
                  glfwGetCursorPos(window, &mX, &mY);

                  Ray ray = screenToRay(mX, mY, W_WIDTH, W_HEIGHT, camera.cameraMatrix, camera.Position);

                  bool hitSkull = rayIntersectsSphere(ray, skullCenter, 0.04f);
                  bool hitCube  = rayIntersectsSphere(ray, cubeCenter,  0.04f);

                  if (hitSkull)
                  {
                      skullSelected = !skullSelected;
                      cubeSelected = false;
                  }
                  else if (hitCube)
                  {
                      cubeSelected = !cubeSelected;
                      skullSelected = false;
                  }
                  else
                  {
                      cubeSelected = false;
                      skullSelected = false;
                  }
              }
              rightPressed = rightNow;
        }

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(cubeSelected ? 0xFF : 0x00);
        matrix4 cubeModel = createIdentityMatrix();
        cubeModel = multiplyMatrices(cubeModel, createTranslationMatrix(5.f, 0.f, 0.f));
        float time = glfwGetTime();
        cubeModel = multiplyMatrices(cubeModel, createRotationMatrixY(time));
        shaderProgram.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, cubeModel.data());
        cube.Draw(shaderProgram, camera);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(skullSelected ? 0xFF : 0x00);
        matrix4 skullModel = createIdentityMatrix();
        skullModel = multiplyMatrices(createRotationMatrixX(glm::radians(90.f)), createScaleMatrix(0.05f, 0.05f, 0.05f));
        shaderProgram.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, skullModel.data());
        model.Draw(shaderProgram, camera);

        glStencilMask(0x00);
        lightShader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, lightModel.data());
        light.Draw(lightShader, camera);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        outliningProgram.Activate();
        glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
        if (skullSelected) {
            glUniformMatrix4fv(glGetUniformLocation(outliningProgram.ID, "model"),
                               1, GL_FALSE, skullModel.data());
            model.Draw(outliningProgram, camera);
        }
        if (cubeSelected) {
            glUniformMatrix4fv(glGetUniformLocation(outliningProgram.ID, "model"),
                               1, GL_FALSE, cubeModel.data());
            cube.Draw(outliningProgram, camera);
        }

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        ImGui::Begin("Test window");
        ImGui::Text("Test test test");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    shaderProgram.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
