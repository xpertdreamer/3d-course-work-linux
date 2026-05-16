#include "Util.h"
#include "Axis.h"
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

bool skullSelected = false;
bool rightPressed = false;
bool showAxis = true;

float skullCenter[3] = {0.f, 0.f, 0.f};


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

int main()
{
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
    Shader lightShader("../Resources/Shaders/light.vert",
                       "../Resources/Shaders/light.frag");
    Shader axisShader("../Resources/Shaders/axis.vert",
                      "../Resources/Shaders/axis.frag");
    
    Axis axis;
    
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

        if (showAxis)
        {
            glStencilMask(0x00);
            glDisable(GL_DEPTH_TEST);
            axis.Draw(axisShader, camera);
            glEnable(GL_DEPTH_TEST);
        }

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

                  bool hitSkull = rayIntersectsSphere(ray, skullCenter, 0.05f);

                  if (hitSkull)
                  {
                      skullSelected = !skullSelected;
                  }
                  else
                  {
                      skullSelected = false;
                  }
              }
              rightPressed = rightNow;
        }

        glStencilMask(0x00);
        matrix4 cubeModel = createIdentityMatrix();
        cubeModel = multiplyMatrices(cubeModel, createTranslationMatrix(5.f, 0.f, 0.f));
        float timeRot = glfwGetTime();
        cubeModel = multiplyMatrices(cubeModel, createRotationMatrixY(timeRot));
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

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        ImGui::Begin("GUI");
        if (ImGui::Checkbox("Wireframe", &wireframe))
        {
            if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        if (skullSelected) ImGui::Text("Selected: Skull");
        else ImGui::Text("Selected: None");

        ImGui::Separator();
        static char lastScreen[64] = "";
        if (ImGui::Button("Save Screenshot"))
        {
            time_t timeNow = time(nullptr);
            strftime(lastScreen, sizeof(lastScreen),
                     "screenshot_%Y%m%d_%H%M%S.png", localtime(&timeNow));
            saveScreenshot();
        }
        if (lastScreen[0]) ImGui::Text("Saved: %s", lastScreen);

        ImGui::Separator();
        ImGui::Checkbox("Show Axes", &showAxis);
        
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
