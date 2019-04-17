#ifndef MESH_READER
#define MESH_READER

#include "TriangularMesh.h"
#include <string>

class MeshReader {
public:

	// Returns the singleton mesh reader instance
	static MeshReader* getInstance();

	// Reads the mesh in the given filepath
	const TriangularMesh* readMesh(std::string filepath);

private:

	// Singleton mesh reader instance
	static MeshReader* instance;

	// Default constuctor
	MeshReader();

	// Destructor
	~MeshReader();

};

#endif
