#ifndef MESH_BUILDER
#define MESH_BUILDER

#include "TriangularMesh.h"
#include <vector>
#include <queue>
#include <map>

class MeshBuilder {
public:

	// Constructor
	MeshBuilder(const TriangularMesh* mesh);

	// Destructor
	~MeshBuilder();

	// Calculates the heuristic matching of the triangles
	void calculateMatching();

	// Return the map of the matched triangles
	std::map<unsigned int, unsigned int> getMatching();

	// Return the list of unmatched faces
	std::vector<FaceData*> getUnmatchedFaces();

private:

	// The mesh instance
	const TriangularMesh* mesh;

	// Map to store matching face list
	std::map<unsigned int, unsigned int> matchingMap;

	// Vector to store the faces that are not matched
	std::vector<FaceData*> unmatchedFaces;

	// Priority queue to store the order of the faces
	std::priority_queue<FaceData*, std::vector<FaceData*>, PriorityOrder> priorityQueue;

	// Try to match a face with one of its neighbors and return matched face's id
	int matchFace(FaceData* face);

	// Update the priority of the neighbors of a matched face
	void updateNeighbors(FaceData* face);

	// Update the priority of a face depending on its neighbors
	void updatePriority(FaceData* face);

};

#endif
