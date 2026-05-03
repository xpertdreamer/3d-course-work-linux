#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "include/glad/glad.h"
#include <vector>

struct Vertex
{
    float position[3];
    float normal[3];
    float color[3];
    float textUV[2];
};

class VBO {
  public:
    GLuint ID;
    VBO(std::vector<Vertex>& vertices);

    void Bind();
    void Unbind();
    void Delete();
};

#endif
