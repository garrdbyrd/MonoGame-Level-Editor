#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "level.h"
#include "tile.h"

bool readFromFile(const std::string &filename, u_int32_t offset) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	uint16_t headerOffset = 1024;                                // Header is 1kb
	uint16_t tileSize     = 1024;                                // Tiles are 1kb
	std::vector<char> buffer(tileSize);                          // Buffer for tiles
	file.seekg(tileSize * offset + headerOffset, std::ios::beg); // Offset for other tiles

	if (!file) {
		std::cerr << "Error seeking to offset in file: " << offset << std::endl;
		return false;
	}
}

bool readXCoordinate(std::ifstream &file);
bool readYCoordinate(std::ifstream &file);
bool readCollision(std::ifstream &file);
bool readFriction(std::ifstream &file);
bool readIcy(std::ifstream &file);