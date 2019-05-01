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

	// Start time of matching
	const clock_t beginTime = clock();

	// Calculate the matching on the mesh
	std::map<unsigned int, unsigned int> matching = MeshBuilder::getInstance()->calculateMatching(mesh);

	// End time of matching
	const clock_t endTime = clock();

	// Output the time difference
	float timeDifference = float(endTime - beginTime);
	std::cout << "Running time: " << timeDifference / CLOCKS_PER_SEC;

	// Write the quadrilateral mesh into an off file
	MeshWriter::getInstance()->writeMesh("output.off", mesh, matching);

	// Delete the mesh and all its data
	delete mesh;
	mesh = 0;

	// Close the program on key press
	getchar();
	return 0;
}