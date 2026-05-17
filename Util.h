#ifndef UTIL_H
#define UTIL_H

#include <cstdio>

#include "shaderClass.h"
#include <cstring>
#include <ctime>
#include <vector>

#define W_WIDTH 1920
#define W_HEIGHT 1080
#define PATH "../Resources/Screenshots"
#define SCENE_PATH "../Resources/Scenes/scene.scn"

struct SceneState
{
    float camPos[3] = { 0.f, 0.f, 0.f };

    float skullPos[3] = {0.f, 0.f, 0.f};
    float skullScale = 0.05f;
    float skullRotX = 90.f;

    float cubePos[3] = {5.f, 0.f, 0.f};

    float lightPos[3] = {0.f, 4.f, 0.f};
    float lightColor[4] = {1.f, 1.f, 0.5f, 1.f};

    bool  wireframe = false;
    bool  showAxes = true;
    bool  skullSelected = false;
};

void saveScreenshot();
bool saveScene(const SceneState& scene, const std::string& path=SCENE_PATH);
bool loadScene(SceneState& scene, const std::string& path=SCENE_PATH);

#endif
