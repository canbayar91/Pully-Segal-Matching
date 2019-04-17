#ifndef VERTEX
#define VERTEX

struct Vertex {

	float x;
	float y;
	float z;

	Vertex(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vertex(const Vertex& vertex) { 
		x = vertex.x;
		y = vertex.y;
		z = vertex.z;
	}

	Vertex operator+(const Vertex& vertex) const {
		return Vertex(x + vertex.x, y + vertex.y, z + vertex.z);
	}

	Vertex operator-(const Vertex& vertex) const {
		return Vertex(x - vertex.x, y - vertex.y, z - vertex.z);
	}

	Vertex operator*(const float value) const {
		return Vertex(value * x, value * y, value * z);
	}

	Vertex operator*(const Vertex& vertex) const {
		return Vertex(x * vertex.x, y * vertex.y, z * vertex.z);
	}

	Vertex operator/(const float value) const {
		float r = float(1.0) / value;
		return *this * r;
	}

	Vertex& operator+=(const Vertex& vertex) {
		x += vertex.x;  
		y += vertex.y;  
		z += vertex.z;  
		return *this;
	}

	Vertex& operator-=(const Vertex& vertex) {
		x -= vertex.x;  
		y -= vertex.y;  
		z -= vertex.z;  
		return *this;
	}

	Vertex& operator*=(const float value) {
		x *= value; 
		y *= value;  
		z *= value;  
		return *this;
	}

	Vertex& operator*=(const Vertex& vertex) {
		x *= vertex.x;  
		y *= vertex.y;  
		z *= vertex.z;  
		return *this;
	}

	Vertex& operator/=(const float value) {
		float r = float(1.0) / value;
		*this *= r;
		return *this;
	}
};

#endif
