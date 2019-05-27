#include "MeshBuilder.h"
#include <iostream>

MeshBuilder::MeshBuilder(const TriangularMesh* mesh) {

	// Store mesh triangles on a priority queue
	const std::vector<FaceData*> faceList = mesh->getFaces();
	for (size_t i = 0; i < mesh->getFaceCount(); i++) {
		priorityQueue.push(faceList[i]);
	}

	// Store the mesh
	this->mesh = mesh;
}

MeshBuilder::~MeshBuilder() {

	// Delete the mesh
	delete mesh;
	mesh = 0;
}

void MeshBuilder::calculateMatching() {

	// Pop and try to match triangles until the priority queue is empty
	while (priorityQueue.size() != 0) {

		// Take the face at the top of the queue and check if it is already matched
		FaceData* currentFace = priorityQueue.top();

		// Pop the face at the top in any case
		priorityQueue.pop();

		// Skip the faces that has already been processed
		if (!currentFace->processed) {

			// If the face is not already matched and encountered, try to find a matching
			if (!currentFace->matched) {

				// Try to match the face with one of its neighbors, add it to the unmatched faces list if it fails
				int neighborId = matchFace(currentFace);
				if (neighborId == -1) {
					unmatchedFaces.push_back(currentFace);
				} else {
					matchingMap[currentFace->id] = neighborId;
				}
			}

			// Keep track of the processed face's id
			currentFace->processed = true;
		}
	}

	// Calculate the matching percentage of the mesh
	double faceCount = (double) mesh->getFaceCount();
	double matchingPercentage = (faceCount - unmatchedFaces.size()) / faceCount * 100;

	// Print out the matching statistics
	std::cout << "Unmatched face count: " << unmatchedFaces.size() << std::endl;
	std::cout << "Matching percentage: " << matchingPercentage << std::endl;
}

int MeshBuilder::matchFace(FaceData* face) {

	// Create a runner half edge to iterate around the face
	HalfEdgeData* runner = face->half;

	// Create a temporary variable to store the face with the highest priority
	FaceData* highestFace = NULL;

	// Create a temporary half-edge data to store on which half-edge the match has been found
	HalfEdgeData* highestEdge = NULL;

	// Iterate through each neighbor face in order to find the on with the highest priority
	int highestPriority = -1;
	do {

		// Update the highest priority face if a more suitable face exists
		FaceData* pair = runner->pair->face;
		if (!pair->matched && pair->priority > highestPriority) {
			highestPriority = pair->priority;
			highestFace = pair;
			highestEdge = runner;
		}

		// Update the runner pointer
		runner = runner->next;

	} while (runner != face->half);

	// If a match is found, update the neighboring faces and return true
	if (highestPriority != -1) {

		// Mark the faces as matched
		face->matched = true;
		highestFace->matched = true;

		// Mark the corresponding half-edges as matched
		highestEdge->matched = true;
		highestEdge->pair->matched = true;

		// Update the neighbor priorities of the faces
		updateNeighbors(face);
		updateNeighbors(highestFace);

		// Return the matched neighbor's id
		return (int) highestFace->id;
	}

	// If all neighbors are previously matched, return -1
	return -1;
}

void MeshBuilder::updateNeighbors(FaceData* face) {

	// Update the priority of the first neighbor face
	HalfEdgeData* halfEdge = face->half;
	updatePriority(halfEdge->pair->face);

	// Update the priority of the second neighbor face
	halfEdge = halfEdge->next;
	updatePriority(halfEdge->pair->face);

	// Update the priority of the third neighbor face
	halfEdge = halfEdge->next;
	updatePriority(halfEdge->pair->face);
}

void MeshBuilder::updatePriority(FaceData* face) {

	// Update the priority of the face depending on its neighbors if it is not matched before
	if (!face->matched) {

		// Keep the count of free neighbors
		unsigned int freeNeighborCount = 0;

		// Keep the count of neighbors in priority set 0
		unsigned int lowPriorityNeighborCount = 0;

		// Create a runner half edge to iterate around the face
		HalfEdgeData* runner = face->half;
		do {

			// Update the free neighbor count
			FaceData* neighbor = runner->pair->face;
			if (!neighbor->matched) {

				// Increment the count of free neighbors
				freeNeighborCount++;

				// Update the low priority neighbor count
				if (neighbor->priority == 0) {
					lowPriorityNeighborCount++;
				}
			}

			// Update the runner pointer
			runner = runner->next;

		} while (runner != face->half);

		// Update the face priority depending on the free neighbor count
		if (freeNeighborCount == 0 || freeNeighborCount == 1) {
			face->priority = 3;
		} else if (freeNeighborCount == 2) {
			int priority = (lowPriorityNeighborCount == 2) ? 1 : 2;
			face->priority = priority;
		} else {
			face->priority = 0;
		}

		// This is an exploit to keep highest priority faces on top
		if (!face->processed) {
			priorityQueue.push(face);
		}
	}
}

std::map<unsigned int, unsigned int> MeshBuilder::getMatching() {
	return matchingMap;
}

std::vector<FaceData*> MeshBuilder::getUnmatchedFaces() {
	return unmatchedFaces;
}
