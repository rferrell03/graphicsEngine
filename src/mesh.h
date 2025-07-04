#pragma once
#include <glad/glad.h>
#include "VertexLayout.h"
class Mesh {
private:
	unsigned int VAO, VBO;
	int vertexCount;

public:
	Mesh(const float* verticies, size_t size, const VertexLayout& layout);

	void draw() const;

	~Mesh();
};