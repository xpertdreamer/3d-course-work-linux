#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 color;

uniform mat4 camMatrix;
uniform mat4 model;
uniform float time;

void main()
{
    color = aColor;

    vec3 pos = aPos;
    float tip = max(0.0, -aPos.y);
    pos.x += sin(time * 7.0 + aPos.y * 3.0) * tip * 0.15;
    pos.z += cos(time * 5.0 + aPos.y * 3.0) * tip * 0.15;

    gl_Position = camMatrix * model * vec4(pos, 1.0);
}
