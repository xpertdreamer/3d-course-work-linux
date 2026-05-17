#include "Util.h"
#include <fstream>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb/stb_image_write.h"

void saveScreenshot()
{
    std::vector<unsigned char> pixels(W_WIDTH * W_HEIGHT * 3);
    glReadPixels(0, 0, W_WIDTH, W_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    std::vector<unsigned char> flipped(W_WIDTH * W_HEIGHT * 3);
    for (int y = 0; y < W_HEIGHT; y++)
        memcpy(flipped.data() + y * W_WIDTH * 3, pixels.data() + (W_HEIGHT - 1 - y) * W_WIDTH * 3, W_WIDTH * 3);

    time_t timeNow = time(nullptr);
    char buffer[256];
    char timestamp[64];
    
    strftime(timestamp, sizeof(timestamp), "/screen_%Y%m%d_%H%M%S.png", localtime(&timeNow));
    snprintf(buffer, sizeof(buffer), "%s/%s", PATH, timestamp);
    stbi_write_png(buffer, W_WIDTH, W_HEIGHT, 3, flipped.data(), W_WIDTH * 3);
}

bool saveScene(const SceneState& scene, const std::string& path)
{
    std::ofstream file(path);
    if (!file)
    {
        std::cerr << "Cannot open " << path << "\n";
        return false;
    }

    file
        << scene.camPos[0] << " " << scene.camPos[1] << " " << scene.camPos[2] << " "
        << scene.skullPos[0] << " " << scene.skullPos[1] << " " << scene.skullPos[2] << " "
        << scene.skullScale << " "
        << scene.skullRotX << " "
        << scene.cubePos[0] << " " << scene.cubePos[1] << " " << scene.cubePos[2] << " "
        << scene.lightPos[0] << " " << scene.lightPos[1] << " " << scene.lightPos[2] << " "
        << scene.lightColor[0] << " " << scene.lightColor[1] << " " << scene.lightColor[2] << " " << scene.lightColor[3] << " "
        << scene.wireframe << " "
        << scene.showAxes << " "
        << scene.skullSelected << " "
        << "\n";
    
    return true;
}

bool loadScene(SceneState& scene, const std::string& path)
{
    std::ifstream file(path);
    if (!file)
    {
        std::cerr << "Cannot open " << path << "\n";
        return false;
    }

    file
        >> scene.camPos[0] >> scene.camPos[1] >> scene.camPos[2]
        >> scene.skullPos[0] >> scene.skullPos[1] >> scene.skullPos[2]
        >> scene.skullScale 
        >> scene.skullRotX 
        >> scene.cubePos[0] >> scene.cubePos[1] >> scene.cubePos[2] 
        >> scene.lightPos[0] >> scene.lightPos[1] >> scene.lightPos[2] 
        >> scene.lightColor[0] >> scene.lightColor[1] >> scene.lightColor[2] >> scene.lightColor[3] 
        >> scene.wireframe 
        >> scene.showAxes 
        >> scene.skullSelected;

    if (file.fail())
    {
        std::cerr << "Scene file corrupted\n" << std::endl;
        return false;
    }

    return true;
}
