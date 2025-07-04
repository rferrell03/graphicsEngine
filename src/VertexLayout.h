#pragma once
#include <vector>

struct VertexAttribute {
	unsigned int index;
	int size; //how many # make up the attribute
	size_t offset; //how far into the vertex does the attribute start
};

struct VertexLayout {
	std::vector<VertexAttribute> attributes;
	int stride;

	VertexLayout(std::initializer_list<VertexAttribute> attrib, int strideBytes) : attributes(attrib), stride(strideBytes) {};
};