#ifndef UTIL_H
#define UTIL_H

#include <cstdio>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb/stb_image_write.h"

#include "shaderClass.h"
#include <cstring>
#include <ctime>
#include <vector>

#define W_WIDTH 1920
#define W_HEIGHT 1080
#define PATH "../Resources/Screenshots"

bool wireframe = false;


inline void saveScreenshot()
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

#endif
