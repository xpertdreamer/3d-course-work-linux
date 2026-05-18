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
#include <glm/trigonometric.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Flame.h"

SceneState scene;
std::string bench;

bool rightPressed = false;

float rightFlapCenter[3] = {0.f, 0.f, 0.f};
float leftFlapCenter[3] = {0.f, 0.f, 0.f};

Vertex flapVertices[] =
{
    // Передняя грань
    Vertex{{-0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}, {0.8f, 0.8f, 0.8f}, {0.f, 0.f}},
    Vertex{{ 0.5f, -0.5f,  0.5f}, {0.f, 0.f, 1.f}, {0.8f, 0.8f, 0.8f}, {1.f, 0.f}},
    Vertex{{ 0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {0.8f, 0.8f, 0.8f}, {1.f, 1.f}},
    Vertex{{-0.5f,  0.5f,  0.5f}, {0.f, 0.f, 1.f}, {0.8f, 0.8f, 0.8f}, {0.f, 1.f}},
    // Задняя грань
    Vertex{{ 0.5f, -0.5f, -0.5f}, {0.f, 0.f,-1.f}, {0.7f, 0.7f, 0.7f}, {0.f, 0.f}},
    Vertex{{-0.5f, -0.5f, -0.5f}, {0.f, 0.f,-1.f}, {0.7f, 0.7f, 0.7f}, {1.f, 0.f}},
    Vertex{{-0.5f,  0.5f, -0.5f}, {0.f, 0.f,-1.f}, {0.7f, 0.7f, 0.7f}, {1.f, 1.f}},
    Vertex{{ 0.5f,  0.5f, -0.5f}, {0.f, 0.f,-1.f}, {0.7f, 0.7f, 0.7f}, {0.f, 1.f}},
    // Верхняя грань
    Vertex{{-0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {0.9f, 0.9f, 0.9f}, {0.f, 0.f}},
    Vertex{{ 0.5f,  0.5f,  0.5f}, {0.f, 1.f, 0.f}, {0.9f, 0.9f, 0.9f}, {1.f, 0.f}},
    Vertex{{ 0.5f,  0.5f, -0.5f}, {0.f, 1.f, 0.f}, {0.9f, 0.9f, 0.9f}, {1.f, 1.f}},
    Vertex{{-0.5f,  0.5f, -0.5f}, {0.f, 1.f, 0.f}, {0.9f, 0.9f, 0.9f}, {0.f, 1.f}},
    // Нижняя грань
    Vertex{{-0.5f, -0.5f, -0.5f}, {0.f,-1.f, 0.f}, {0.6f, 0.6f, 0.6f}, {0.f, 0.f}},
    Vertex{{ 0.5f, -0.5f, -0.5f}, {0.f,-1.f, 0.f}, {0.6f, 0.6f, 0.6f}, {1.f, 0.f}},
    Vertex{{ 0.5f, -0.5f,  0.5f}, {0.f,-1.f, 0.f}, {0.6f, 0.6f, 0.6f}, {1.f, 1.f}},
    Vertex{{-0.5f, -0.5f,  0.5f}, {0.f,-1.f, 0.f}, {0.6f, 0.6f, 0.6f}, {0.f, 1.f}},
    // Правая грань
    Vertex{{ 0.5f, -0.5f,  0.5f}, {1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{0.f, 0.f}},
    Vertex{{ 0.5f, -0.5f, -0.5f}, {1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{1.f, 0.f}},
    Vertex{{ 0.5f,  0.5f, -0.5f}, {1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{1.f, 1.f}},
    Vertex{{ 0.5f,  0.5f,  0.5f}, {1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{0.f, 1.f}},
    // Левая грань
    Vertex{{-0.5f, -0.5f, -0.5f},{-1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{0.f, 0.f}},
    Vertex{{-0.5f, -0.5f,  0.5f},{-1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{1.f, 0.f}},
    Vertex{{-0.5f,  0.5f,  0.5f},{-1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{1.f, 1.f}},
    Vertex{{-0.5f,  0.5f, -0.5f},{-1.f, 0.f, 0.f}, {0.75f,0.75f,0.75f},{0.f, 1.f}},
};

GLuint flapIndices[] =
{
     0,  1,  2,  0,  2,  3,
     4,  5,  6,  4,  6,  7,
     8,  9, 10,  8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23
};

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

    Texture cubeTextures[] =
    {
        Texture("../Resources/Textures/pop.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };

    Texture modelTextures[] =
    {
        Texture("../Resources/Textures/jet3.jpg", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE) };

    Shader shaderProgram("../Resources/Shaders/default.vert",
                         "../Resources/Shaders/default.frag");
    Shader outliningProgram("../Resources/Shaders/outlining.vert",
                            "../Resources/Shaders/outlining.frag");
    Shader lightShader("../Resources/Shaders/light.vert",
                       "../Resources/Shaders/light.frag");
    Shader axisShader("../Resources/Shaders/axis.vert",
                      "../Resources/Shaders/axis.frag");
    Shader flameShader("../Resources/Shaders/flame.vert",
                      "../Resources/Shaders/flame.frag");
    
    Axis axis;
    Flame flame;

    std::vector<Vertex> flapVerts(flapVertices,
                                  flapVertices + sizeof(flapVertices) / sizeof(Vertex));
    std::vector<GLuint> flapInd(flapIndices,
                                flapIndices + sizeof(flapIndices) / sizeof(GLuint));
    std::vector<Texture> flapTex(modelTextures,
                                 modelTextures + sizeof(modelTextures) / sizeof(Texture));
    Mesh flap(flapVerts, flapInd, flapTex);
    
    std::vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    std::vector<GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    std::vector<Texture> tex2(cubeTextures, cubeTextures + sizeof(cubeTextures) / sizeof(Texture));
    Mesh cube(cubeVerts, cubeInd, tex2);

    std::vector<Texture> modelTex(modelTextures, modelTextures + sizeof(modelTextures) / sizeof(Texture));
    Model model("../Resources/Models/jet3.obj", modelTex);

    std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex2);
    
    matrix4 lightModel = createIdentityMatrix();
    lightModel = createTranslationMatrix(scene.lightPos[0], scene.lightPos[1], scene.lightPos[2]);
    
    matrix4 objectModel = createIdentityMatrix();
    objectModel = createTranslationMatrix(0.0f, 0.0f, 0.0f);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, lightModel.data());
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"),
                scene.lightColor[0], scene.lightColor[1], scene.lightColor[2], scene.lightColor[3]);

    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, objectModel.data());
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"),
                scene.lightColor[0], scene.lightColor[1], scene.lightColor[2], scene.lightColor[3]);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"),
                scene.lightPos[0], scene.lightPos[1], scene.lightPos[2]);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    Camera camera(W_WIDTH, W_HEIGHT, scene.camPos);

    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    while (!glfwWindowShouldClose(window))
    {
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;
        if (timeDiff >= 1.0 / 30.0)
        {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            bench = FPS + "FPS / " + ms + "ms";
            prevTime = crntTime;
            counter = 0;
        }
        
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

        if (scene.showAxes)
        {
            glStencilMask(0x00);
            glDisable(GL_DEPTH_TEST);
            axis.Draw(axisShader, camera);
            glEnable(GL_DEPTH_TEST);
        }

        glStencilMask(0x00);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        shaderProgram.Activate();
        
        matrix4 cubeModel = createIdentityMatrix();
        cubeModel = multiplyMatrices(cubeModel, createTranslationMatrix(scene.cubePos[0], scene.cubePos[1], scene.cubePos[2]));
        float timeRot = glfwGetTime();
        cubeModel = multiplyMatrices(cubeModel, createRotationMatrixY(timeRot));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, cubeModel.data());
        cube.Draw(shaderProgram, camera);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(scene.rightFlapSelected ? 0xFF : 0x00);
        shaderProgram.Activate();
        matrix4 flopRightModel = makeFlapMatrix(scene, +1.f);
        rightFlapCenter[0] = flopRightModel[12];
        rightFlapCenter[1] = flopRightModel[13];
        rightFlapCenter[2] = flopRightModel[14];
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, flopRightModel.data());
        flap.Draw(shaderProgram, camera);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(scene.leftFlapSelected ? 0xFF : 0x00);
        shaderProgram.Activate();
        matrix4 flapLeftModel = makeFlapMatrix(scene, -1.f);
        leftFlapCenter[0] = flapLeftModel[12];
        leftFlapCenter[1] = flapLeftModel[13];
        leftFlapCenter[2] = flapLeftModel[14];
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"),
                           1, GL_FALSE, flapLeftModel.data());
        flap.Draw(shaderProgram, camera);

        if (!io.WantCaptureMouse)
        {
              bool rightNow = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
              if (rightNow && !rightPressed)
              {
                  double mX, mY;
                  glfwGetCursorPos(window, &mX, &mY);

                  Ray ray = screenToRay(mX, mY, W_WIDTH, W_HEIGHT, camera.cameraMatrix, camera.Position);

                  bool hitLeft = rayIntersectsSphere(ray, leftFlapCenter, 0.6f);
                  bool hitRight = rayIntersectsSphere(ray, rightFlapCenter, 0.6f);

                  if (hitLeft)
                  {
                      scene.leftFlapSelected = !scene.leftFlapSelected;
                  }
                  else if (hitRight)
                  {
                      scene.rightFlapSelected = !scene.rightFlapSelected;
                  }
                  else
                  {
                      scene.leftFlapSelected = false;
                      scene.rightFlapSelected = false;
                  }
              }
              rightPressed = rightNow;
        }

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(scene.skullSelected ? 0xFF : 0x00);
        matrix4 skullModel = createIdentityMatrix();
        skullModel = multiplyMatrices(
            createRotationMatrixY(glm::radians(scene.planeRotY)),
            multiplyMatrices(
                createRotationMatrixX(glm::radians(scene.planeRotX)),
                multiplyMatrices(
                    createRotationMatrixZ(glm::radians(scene.planeRotZ)),
                    multiplyMatrices(
                        createRotationMatrixY(glm::radians(scene.skullRotY)),
                        createScaleMatrix(scene.skullScale, scene.skullScale, scene.skullScale)))));
        shaderProgram.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, skullModel.data());
        model.Draw(shaderProgram, camera);

        matrix4 nozzleModel = multiplyMatrices(
            createRotationMatrixY(glm::radians(scene.planeRotY)),
            multiplyMatrices(
                createRotationMatrixX(glm::radians(scene.planeRotX)),
                multiplyMatrices(
                    createRotationMatrixZ(glm::radians(scene.planeRotZ)),
                    createTranslationMatrix(
                        scene.nozzleOffset[0],
                        scene.nozzleOffset[1],
                        scene.nozzleOffset[2]))));
        nozzleModel = multiplyMatrices(nozzleModel, createRotationMatrixZ(glm::radians(90.f)));
        nozzleModel = multiplyMatrices(nozzleModel, createScaleMatrix(0.4f, 0.4f, 0.4f));
        matrix4 nozzleModel2 = multiplyMatrices(nozzleModel, createTranslationMatrix(0.f, 0.f, 0.8f));
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glDepthMask(GL_FALSE);
        flame.Draw(flameShader, camera, nozzleModel, (float)glfwGetTime() * 10);
        flame.Draw(flameShader, camera, nozzleModel2, (float)glfwGetTime() * 10);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
        
        glStencilMask(0x00);
        lightShader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, lightModel.data());
        // light.Draw(lightShader, camera);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        outliningProgram.Activate();
        glUniform1f(glGetUniformLocation(outliningProgram.ID, "outlining"), 0.08f);
        if (scene.rightFlapSelected) {
            glUniformMatrix4fv(glGetUniformLocation(outliningProgram.ID, "model"),
                               1, GL_FALSE, flopRightModel.data());
            flap.Draw(outliningProgram, camera);
        }
        if (scene.leftFlapSelected) {
            glUniformMatrix4fv(glGetUniformLocation(outliningProgram.ID, "model"),
                               1, GL_FALSE, flapLeftModel.data());
            flap.Draw(outliningProgram, camera);
        }

        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);

        ImGui::Begin("GUI");
        ImGui::Text("%s", bench.c_str());
        ImGui::Separator();
        if (ImGui::Checkbox("Wireframe", &scene.wireframe))
        {
            if (scene.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        if (scene.leftFlapSelected) ImGui::Text("Selected: Left Flap");
        else if (scene.rightFlapSelected) ImGui::Text("Selected: Right Flap");
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
        ImGui::Checkbox("Show Axes", &scene.showAxes);

        ImGui::Separator();
        ImGui::Text("Scene");
        if (ImGui::Button("Save Scene"))
        {
            scene.camPos[0] = camera.Position[0];
            scene.camPos[1] = camera.Position[1];
            scene.camPos[2] = camera.Position[2];
            if (!saveScene(scene)) return -1;
        }
        ImGui::SameLine();
        if (ImGui::Button("Load Scene"))
        {
            if (loadScene(scene))
            {
                  camera.Position[0] = scene.camPos[0];
                  camera.Position[1] = scene.camPos[1];
                  camera.Position[2] = scene.camPos[2];
                  glPolygonMode(GL_FRONT_AND_BACK, scene.wireframe ? GL_LINE : GL_FILL);
                  shaderProgram.Activate();
                  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"),
                              scene.lightColor[0],
                              scene.lightColor[1],
                              scene.lightColor[2],
                              scene.lightColor[3]);
                  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"),
                              scene.lightPos[0],
                              scene.lightPos[1],
                              scene.lightPos[2]);
            }
            else
            {
                return -1;
            }
        }

        ImGui::Separator();
        ImGui::Text("Jet");
        ImGui::SliderFloat("Plane Rotation X", &scene.planeRotX, 0.f, 360.f);
        ImGui::SliderFloat("Plane Rotation Y", &scene.planeRotY, 0.f, 360.f);
        ImGui::SliderFloat("Plane Rotation Z", &scene.planeRotZ, 0.f, 360.f);
        ImGui::Separator();
        ImGui::Text("Flaps");
        ImGui::BeginDisabled(!scene.rightFlapSelected);
        ImGui::SliderFloat("Right Angle", &scene.rightFlapAngle, -20.f, 20.f);
        ImGui::EndDisabled();
        ImGui::Separator();
        ImGui::BeginDisabled(!scene.leftFlapSelected);
        ImGui::SliderFloat("Left Angle", &scene.leftFlapAngle, -20.f, 20.f);
        ImGui::EndDisabled();
        
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    axis.Delete();
    shaderProgram.Delete();
    lightShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
