#ifndef MESH_WRITER
#define MESH_WRITER

#include "TriangularMesh.h"
#include <string>

class MeshWriter {
public:

	// Returns the singleton mesh writer instance
	static MeshWriter* getInstance();

	// Writes the quadrilateral mesh to the given file
	void writeMesh(std::string filepath, const TriangularMesh* mesh, std::map<unsigned int, unsigned int> matching);

private:

	// Singleton mesh writer instance
	static MeshWriter* instance;

	// Default constuctor
	MeshWriter();

	// Destructor
	~MeshWriter();

};

#endif
