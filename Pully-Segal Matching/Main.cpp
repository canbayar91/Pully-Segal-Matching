#include "MeshReader.h"
#include "MeshBuilder.h"
#include "MeshWriter.h"
#include <iostream>
#include <ctime>

int main(int argc, char **argv) {

	// Read the file name from command line
	std::string filename = argv[1];

	// Read the triangular mesh from the given file
	const TriangularMesh* mesh = MeshReader::getInstance()->readMesh(filename);

	// Output the total face count of the mesh
	std::cout << "Face count: " << mesh->getFaceCount() << std::endl;

	// Initialize a mesh builder instance with the mesh read from the file
	MeshBuilder* builder = new MeshBuilder(mesh);

	// Start time of matching
	const clock_t beginTime = clock();

	// Calculate the matching on the mesh
	builder->calculateMatching();

	// End time of matching
	const clock_t endTime = clock();

	// Output the time difference
	float timeDifference = float(endTime - beginTime);
	std::cout << "Running time: " << timeDifference / CLOCKS_PER_SEC;

	// Write the quadrilateral mesh into an off file
	// std::map<unsigned int, unsigned int> matching = builder->getMatching();
	// MeshWriter::getInstance()->writeMesh("output.off", mesh, matching);

	// Delete the mesh builder instance
	delete builder;
	builder = 0;

	// Close the program on key press
	getchar();
	return 0;
}