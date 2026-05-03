#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "include/glad/glad.h"
#include <vector>
#include <array>

struct Vertex {
    float position[3];
    float normal[3];
    float color[3];
    float texCoord[2];
    
    Vertex() {}
    
    Vertex(std::array<float, 3> pos, std::array<float, 3> norm, 
           std::array<float, 3> col, std::array<float, 2> tex)
    {
        for (int i = 0; i < 3; i++) {
            position[i] = pos[i];
            normal[i] = norm[i];
            color[i] = col[i];
        }
        texCoord[0] = tex[0];
        texCoord[1] = tex[1];
    }
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
