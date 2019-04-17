#include "MeshReader.h"
#include <fstream>

MeshReader* MeshReader::instance;

MeshReader::MeshReader() {
	instance = new MeshReader();
}

MeshReader::~MeshReader() {
	delete instance;
	instance = 0;
}

MeshReader* MeshReader::getInstance() {
	return instance;
}

const TriangularMesh* MeshReader::readMesh(std::string filepath) {

	// Open the file in given location
	std::ifstream infile(filepath);

	// Read the file format
	std::string format;
	infile >> format;

	// Read the mesh information
	unsigned int numVertices, numFaces, numEdges;
	infile >> numVertices >> numFaces >> numEdges;

	// Read the vertices from the file
	std::vector<Vertex> vertexList(numVertices);
	for (unsigned int i = 0; i < numVertices; i++) {

		// Read vertex coordinates
		float x, y, z;
		infile >> x >> y >> z;

		// Add it to the vertex list
		vertexList[i] = Vertex(x, y, z);
	}

	// Read the triangular faces from the file and creates a triangular mesh
	std::vector<Triangle> faceList(numFaces);
	for (unsigned int i = 0; i < numFaces; i++) {

		// Read the number of vertices (always 4 for quadrilateral)
		unsigned int vertexCount;
		infile >> vertexCount;

		// Read the quadrilateral vertices
		unsigned int a, b, c;
		infile >> a >> b >> c;

		// Construct the triangle and add it to the list
		faceList[i] = Triangle(a, b, c);
	}

	// Close the input file
	infile.close();

	// Create the mesh using vertex and face list
	TriangularMesh* mesh = new TriangularMesh(vertexList, faceList);

	// Return the resulting list
	return mesh;
}
