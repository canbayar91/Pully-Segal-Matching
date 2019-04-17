#include "TriangularMesh.h"

TriangularMesh::TriangularMesh(std::vector<Vertex> vertexList, std::vector<Triangle> faceList) {

	// Create and store the vertex data
	vertexCount = vertexList.size();
	for (size_t i = 0; i < vertexCount; i++) {

		// Create a new vertex data
		VertexData* vertex = new VertexData();

		// Set vertex id in order to find the coordinates using index information
		vertex->id = i;

		// Copy the coordinate information to vertex data
		vertex->coordinate = vertexList[i];

		// Store the vertex information
		vertices.push_back(vertex);
	}

	// Create and store the face information using half-edges
	faceCount = faceList.size();
	for (size_t i = 0; i < faceCount; i++) {

		// Create a new face for each triangle
		Triangle triangle = faceList[i];
		FaceData* face = new FaceData();

		// Create original half-edges
		HalfEdgeData* halfEdge1 = new HalfEdgeData();
		HalfEdgeData* halfEdge2 = new HalfEdgeData();
		HalfEdgeData* halfEdge3 = new HalfEdgeData();

		// Set the face information to half-edges
		halfEdge1->face = face;
		halfEdge2->face = face;
		halfEdge3->face = face;

		// Set the origination vertices to the half-edges
		halfEdge1->origin = vertices[triangle.a];
		halfEdge2->origin = vertices[triangle.b];
		halfEdge3->origin = vertices[triangle.c];

		// Set the face half-edges on the surface
		halfEdge1->next = halfEdge2;
		halfEdge2->next = halfEdge3;
		halfEdge3->next = halfEdge1;

		// Pair the half edges
		pairHalfEdges(triangle.a, triangle.b, halfEdge1);
		pairHalfEdges(triangle.b, triangle.c, halfEdge2);
		pairHalfEdges(triangle.c, triangle.a, halfEdge3);

		// Set half edge information to the vertices
		vertices[triangle.a]->half = halfEdge1;
		vertices[triangle.b]->half = halfEdge2;
		vertices[triangle.c]->half = halfEdge3;

		// Set the first half-edge as the half-edge of the face
		face->half = halfEdge1;

		// Set face id in order to find it when needed
		face->id = i;

		// Initially assign all faces to priority set 0
		face->priority = 0;

		// Store the face information
		faces.push_back(face);
	}
}

TriangularMesh::~TriangularMesh() {

	// Delete all faces
	for (size_t i = 0; i < faceCount; i++) {
		delete faces[i];
		faces[i] = 0;
	}

	// Delete all vertices with half edge data
	for (size_t i = 0; i < vertexCount; i++) {

		// Delete the pair of the half edge
		HalfEdgeData* pair = vertices[i]->half->pair;
		delete pair;
		pair = 0;

		// Delete the half edge
		HalfEdgeData* half = vertices[i]->half;
		delete half;
		half = 0;

		// Delete the vertex
		delete vertices[i];
		vertices[i] = 0;
	}
}

void TriangularMesh::pairHalfEdges(unsigned int origin, unsigned int destination, HalfEdgeData* halfEdge) {

	// For the given half-edge, check if its pair already added to the map and if so, pair them
	VertexPair lookupKey = std::make_pair(destination, origin);
	if (lookupMap.find(lookupKey) != lookupMap.end()) {
		HalfEdgeData* pair = lookupMap[lookupKey];
		halfEdge->pair = pair;
		pair->pair = halfEdge;
		lookupMap.erase(lookupKey);
	} else {
		VertexPair insertionKey = std::make_pair(origin, destination);
		lookupMap.insert(std::make_pair(insertionKey, halfEdge));
	}
}

const std::vector<VertexData*> TriangularMesh::getVertices() const {
	return vertices;
}

const std::vector<FaceData*> TriangularMesh::getFaces() const {
	return faces;
}

size_t TriangularMesh::getVertexCount() const {
	return vertexCount;
}

size_t TriangularMesh::getFaceCount() const {
	return faceCount;
}
