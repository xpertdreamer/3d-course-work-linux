#ifndef UTIL_H
#define UTIL_H

#include <cstdio>

#include "shaderClass.h"
#include <cstring>
#include <ctime>
#include <vector>
#include "Matrix.hpp"

#define W_WIDTH 1920
#define W_HEIGHT 1080
#define PATH "../Resources/Screenshots"
#define SCENE_PATH "../Resources/Scenes/scene.scn"

struct SceneState
{
    float camPos[3] = { 0.f, 0.f, 10.f };

    float skullPos[3] = {0.f, 0.f, 0.f};
    float skullScale = 0.5f;
    float skullRotY = -90.f;

    float cubePos[3] = {5.f, 0.f, 0.f};

    float lightPos[3] = {0.f, 6.f, 0.f};
    float lightColor[4] = {1.f, 1.f, 0.5f, 1.f};

    bool  wireframe = false;
    bool  showAxes = true;
    bool  skullSelected = false;

    float rightFlapAngle = 0.f;
    float rightFlapOffsetX = 0.4f;
    float rightFlapOffsetY = 0.f;
    float rightFlapOffsetZ = 0.f;
    
    float leftFlapAngle = 0.f;
    float leftFlapOffsetX = 0.4f;
    float leftFlapOffsetY = 0.f;
    float leftFlapOffsetZ = 0.f; 
    
    float flapScale[3] = { 0.6f, 0.08f, 0.25f };

    float planeRotY = 0.f;
};

void saveScreenshot();
bool saveScene(const SceneState& scene, const std::string& path=SCENE_PATH);
bool loadScene(SceneState& scene, const std::string& path=SCENE_PATH);
matrix4 makeFlapMatrix(const SceneState& scene, float signX);

#endif
