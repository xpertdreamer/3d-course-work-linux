#include "Axis.h"
#include "shaderClass.h"

Axis::Axis()
{
    float axisLength = 100.f;
    float verts[] = {
        // X axis
        0.f, 0.f, 0.f,   1.f, 0.f, 0.f,
        axisLength, 0.f, 0.f,   1.f, 0.f, 0.f,
        // Y axis
        0.f, 0.f, 0.f,   0.f, 1.f, 0.f,
        0.f, axisLength, 0.f,   0.f, 1.f, 0.f,
        // Z axis
        0.f, 0.f, 0.f,   0.f, 0.f, 1.f,
        0.f, 0.f, axisLength,   0.f, 0.f, 1.f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                              6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Axis::Draw(Shader& shader, Camera& camera)
{
    shader.Activate();
    camera.Matrix(shader, "camMatrix");
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}

void Axis::Delete()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
