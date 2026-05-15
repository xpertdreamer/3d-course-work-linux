#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "VBO.h"
#include "shaderClass.h"
#include <cstring>
#include <string>
#include <vector>
inline bool loadOBJ
(
    const std::string& path,
    std::vector<Vertex>& verts,
    std::vector<GLuint>& idx
)
{
    struct V3 { float x,y,z; };
    struct V2 { float x,y;   };
    std::vector<V3> pos, nor;
    std::vector<V2> uv;

    std::ifstream f(path);
    if (!f) { std::cerr << "OBJLoader: cannot open " << path << "\n"; return false; }

    for (std::string line; std::getline(f, line); ) {
        const char* s = line.c_str();
        V3 v3{}; V2 v2{};

        if      (sscanf(s, "v %f %f %f",  &v3.x,&v3.y,&v3.z)==3) pos.push_back(v3);
        else if (sscanf(s, "vt %f %f",    &v2.x,&v2.y)       ==2) uv.push_back(v2);
        else if (sscanf(s, "vn %f %f %f", &v3.x,&v3.y,&v3.z)==3) nor.push_back(v3);
        else if (s[0]=='f' && s[1]==' ') {
            int vi[4]={},ti[4]={},ni[4]={}, n=0;
            s += 2;
            while (n < 4) {
                int matched = sscanf(s, "%d/%d/%d", &vi[n],&ti[n],&ni[n]);
                if (matched < 1) break;
                if (matched == 1) sscanf(s, "%d//%d", &vi[n],&ni[n]);
                n++;
                s = strchr(s, ' '); if (!s) break; s++;
            }
            for (int i = 1; i < n-1; i++)
                for (int k : {0, i, i+1}) {
                    Vertex v{};
                    if (vi[k] > 0 && vi[k] <= (int)pos.size()) {
                        auto P = pos[vi[k]-1];
                        v.position[0]=P.x; v.position[1]=P.y; v.position[2]=P.z;
                    }
                    if (ti[k] > 0 && ti[k] <= (int)uv.size()) {
                        auto T = uv[ti[k]-1];
                        v.texUv[0]=T.x; v.texUv[1]=T.y;
                    }
                    if (ni[k] > 0 && ni[k] <= (int)nor.size()) {
                        auto N = nor[ni[k]-1];
                        v.normal[0]=N.x; v.normal[1]=N.y; v.normal[2]=N.z;
                    }
                    v.color[0]=v.color[1]=v.color[2]=1.f;
                    idx.push_back(verts.size());
                    verts.push_back(v);
                }
        }
    }
    return !verts.empty();
}

#endif
