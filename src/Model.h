#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "Geometry.h"

class Model
{
    // We need:
    // A vector list of type Vec3f to hold all vertices.
    // A vector list of type vector<int> to hold all vector indices for each face. Note that wavefront objs start indexing from 1.
    // nfaces and nverts to signify their counts.

private:
    std::vector<Vec3f> verts;
    std::vector<std::vector<int>> faces;
    int nverts;
    int nfaces;

public:
    Model();
    Model(const char* filename);
    ~Model();
    
    void LoadModel(const char* filename);

    int GetVertexCount();
    int GetFaceCount();

    Vec3f GetVertex(int index);
    std::vector<int> GetFace(int index);

    // #TODO: Overload these two for range
    const std::vector<Vec3f>& GetVertices();
    const std::vector<std::vector<int>>& GetFaces();
};

#endif
