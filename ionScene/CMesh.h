#ifndef _ION_SCENE_CMESH_H_INCLUDED_
#define _ION_SCENE_CMESH_H_INCLUDED_

#include "SBoundingBox3.h"

#include "SVertex.h"
#include "CBufferObject.h"
#include "CRenderable.h"

#include <vector>

class CMesh
{

	bool Dirty;
	unsigned int Revision;

public:

    struct STriangle
    {
        unsigned int Indices[3];
        SVector3f Normal;
    };

    struct SMeshBuffer
    {
        std::vector<SVertex> Vertices;
        std::vector<STriangle> Triangles;

		CBufferObject<float> PositionBuffer, ColorBuffer, NormalBuffer, TexCoordBuffer, NormalLineBuffer, NormalColorBuffer;
		CBufferObject<uint> IndexBuffer, NormalIndexBuffer;

		void updateBuffers();
		void writeObjMesh(std::string const & fileName);

		CRenderable::SMaterial Material;
    };

    std::vector<SMeshBuffer *> MeshBuffers;

    CMesh();
    ~CMesh();

    unsigned int const getVertexCount() const;

    void centerMeshByAverage(SVector3f const & CenterLocation);
    void centerMeshByExtents(SVector3f const & CenterLocation);

    void resizeMesh(SVector3f const & Scale);

    SVector3f const getExtent() const;

	void reverseFaces();
    void calculateNormalsPerFace();
    void calculateNormalsPerVertex(bool CombineNear = true, float const NearTolerance = 0.01f);
	void calculateTextureCoordinates(vec3f const & uVec, vec3f const & vVec, vec2f const & Scale = vec2f(1.f));

    void updateBuffers();

    SBoundingBox3f const getBoundingBox() const;

    void linearizeIndices();

	bool const isDirty() const;
	void setDirty(bool const dirty);

	unsigned int const getRevision() const;

};

#endif
