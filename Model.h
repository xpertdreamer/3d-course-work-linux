#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model
{
public:
    Model(const char* file);

    void Draw(Shader& shader, Camera& camera);
};

#endif
