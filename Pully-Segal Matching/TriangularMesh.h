#ifndef TRIANGULAR_MESH
#define TRIANGULAR_MESH

#include "Definitions.h"
#include <vector>

class TriangularMesh {
public:

	TriangularMesh(std::vector<Vertex> vertices, std::vector<Triangle> faces);
	~TriangularMesh();

	const std::vector<VertexData*> getVertices() const;
	const std::vector<FaceData*> getFaces() const;

	size_t getVertexCount() const;
	size_t getFaceCount() const;

private:

	std::vector<VertexData*> vertices;
	std::vector<FaceData*> faces;

	size_t vertexCount;
	size_t faceCount;

	std::map<VertexPair, HalfEdgeData*> lookupMap;

	void pairHalfEdges(unsigned int origin, unsigned int destination, HalfEdgeData* halfEdge);

};

#endif
