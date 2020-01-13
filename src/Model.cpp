#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Model.h"

Model::Model()
{ }

Model::Model(const char* filename)
{
    LoadModel(filename);
}

Model::~Model()
{ }

void Model::LoadModel(const char* filename)
{
    std::cout << "# Opening file: " << filename << "\n";
    
    nverts = 0;
    nfaces = 0;
    
    std::ifstream ifs;
    ifs.open(filename, std::ifstream::in);

    if(ifs.fail())
    {
	std::cout << "Filename: " << filename << " -- cannot open.\n";
	return;
    }

    std::string line;
    

    while (!ifs.eof())
    {
	std::getline(ifs, line);
	std::istringstream iss(line.c_str());
	char temp;
	int vt, vn; // ! TEMP HOLDERS FOR NOW !

	// Reading Vertices
	if (!line.compare(0, 2, "v "))
	{
	    // NEEDS TO BE OF FORM...
	    // eg: v 0.608654 -0.568839 -0.416318
	    iss >> temp;
	    Vec3f v;

	    for (int i = 0; i < 3; i++)
	    {
		iss >> v.raw[i];
	    }
	    
	    verts.push_back(v);
	    ++nverts;
	}

	// Reading Faces
	int v;
	if (!line.compare(0, 2, "f "))
	{
	    std::vector<int> fverts; // Face's vertices
	    // NEEDS TO BE OF FORM...
	    // f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
	    iss >> temp;
	    while (iss >> v >> temp >> vt >> temp >> vn)
	    {
		--v; // Wavefront OBJ vertex indices start from 1. We need from 0.
		fverts.push_back(v);

	    }
	    faces.push_back(fverts);
	    ++nfaces;
	}
    }
    std::cout << "# nverts: " << nverts << " -- # nfaces: " << nfaces << "\n";
}

int Model::GetVertexCount()
{
    return nverts;
}

int Model::GetFaceCount()
{
    return nfaces;
}

Vec3f Model::GetVertex(int index)
{
    return verts[index];
}

std::vector<int> Model::GetFace(int index)
{
    return faces[index];
}

const std::vector<Vec3f>& Model::GetVertices()
{
    return verts;
}

const std::vector<std::vector<int>>& Model::GetFaces()
{
    return faces;
}
