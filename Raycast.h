#ifndef RAYCAST_H
#define RAYCAST_H

#include "Matrix.hpp"

struct Ray
{
    float origin[3];
    float direction[3];
};

inline Ray screenToRay(
    double mouseX,
    double mouseY,
    int screenW,
    int screenH,
    const matrix4& camMatrix,
    const float camPos[3]
)
{
    float ndX = (2.f * mouseX) / screenW - 1.f;
    float ndY = 1.f - (2.f * mouseY) / screenH;

    float clipRay[4] = { ndX, ndY, -1.f, 1.f };

    matrix4 invCam;
    invertMatrix(camMatrix, invCam);

    float worldRay[4];
    mulMat4Vec4(invCam, clipRay, worldRay);

    worldRay[0] /= worldRay[3];
    worldRay[1] /= worldRay[3];
    worldRay[2] /= worldRay[3];

    float dir[3] =
    {
        worldRay[0] - camPos[0],
        worldRay[1] - camPos[1],
        worldRay[2] - camPos[2]
    };

    float len = std::sqrt(
        dir[0]*dir[0] +
        dir[1]*dir[1] +
        dir[2]*dir[2]
    );

    dir[0] /= len;
    dir[1] /= len;
    dir[2] /= len;

    Ray ray;
    ray.origin[0] = camPos[0];
    ray.origin[1] = camPos[1];
    ray.origin[2] = camPos[2];

    ray.direction[0] = dir[0];
    ray.direction[1] = dir[1];
    ray.direction[2] = dir[2];

    return ray;
}

inline bool rayIntersectsSphere(const Ray& ray,
                                 const float center[3], float radius)
{
    float oc[3] = {
        ray.origin[0] - center[0],
        ray.origin[1] - center[1],
        ray.origin[2] - center[2]
    };
    float a = dot(ray.direction, ray.direction);
    float b = 2.0f * dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - 4*a*c;
    return discriminant > 0;
}

#endif
