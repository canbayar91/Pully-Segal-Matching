#ifndef DEFINITIONS
#define DEFINITIONS

#include "Triangle.h"
#include <map>

typedef std::pair<unsigned int, unsigned int> VertexPair;

struct HalfEdgeData;

struct VertexData {
	unsigned int id;
	Vertex coordinate;
	HalfEdgeData* half;
};

struct FaceData {
	bool matched = false;
	bool processed = false;
	unsigned int id;
	int priority = 0;
	HalfEdgeData* half;
};

struct HalfEdgeData {
	bool matched = false;
	VertexData* origin;
	HalfEdgeData* pair;
	HalfEdgeData* next;
	FaceData* face;
};

struct PriorityOrder {
	bool operator()(FaceData* &lhs, FaceData* &rhs) {
		return lhs->priority < rhs->priority;
	}
};

#endif
