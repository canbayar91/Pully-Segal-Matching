#ifndef MESH_BUILDER
#define MESH_BUILDER

#include "TriangularMesh.h"

class MeshBuilder {
public:

	// Returns the singleton mesh builder instance
	static MeshBuilder* getInstance();

	// Calculates the heuristic matching of the triangles
	void calculateMatching(const TriangularMesh* mesh);

private:

	// Singleton mesh builder instance
	static MeshBuilder* instance;

	// Default constuctor
	MeshBuilder();

	// Destructor
	~MeshBuilder();

	// Try to match a face with one of its neighbors
	bool matchFace(FaceData* face);

	// Update the priority of the neighbors of a matched face
	void updateNeighbors(FaceData* face);

	// Update the priority of a face depending on its neighbors
	void updatePriority(FaceData* face);

};

#endif
