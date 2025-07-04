#pragma once
#include <string>

class Texture {
public:
	unsigned int ID;
	int width, height, nrChannels;
	std::string type;
	std::string path;

	Texture(const std::string& path, bool flip = true);
	void Bind(unsigned int unit = 0) const;
};