#ifndef TRIANGLE
#define TRIANGLE

#include "Vertex.h"

struct Triangle {

	unsigned int a;
	unsigned int b;
	unsigned int c;

	Triangle(unsigned int a = 0, unsigned int b = 0, unsigned int c = 0) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Triangle(const Triangle& triangle) {
		a = triangle.a;
		b = triangle.b;
		c = triangle.c;
	}
};

#endif
