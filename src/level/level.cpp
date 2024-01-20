#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

#include "level.h"
#include "tile.h"

void Level::initializeGrid(const Tile &defaultTile) {
	this->grid.resize(this->height, std::vector<Tile>(this->width));
	uint16_t x  = 0;
	uint16_t y  = 0;
	uint32_t id = 0;
	for (auto &row : this->grid) {
		x = 0;
		for (Tile &tile : row) {
			tile             = defaultTile;
			tile.xCoordinate = x;
			tile.yCoordinate = y;
			tile.uniqueID    = id;
			id++;
			x++;
		}
		y++;
	}
}

bool Level::readFromFile(const std::string &filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	if (!readMagicNumber(file)) {
		std::cerr << "Invalid file format (magic number mismatch)." << std::endl;
		return false;
	}

	if (!readVersionInfo(file)) {
		std::cerr << "Error reading version information." << std::endl;
		return false;
	}

	if (!readLevelTitle(file)) {
		std::cerr << "Failed to read level title." << std::endl;
		return false;
	}

	if (!readWidthHeight(file)) {
		std::cerr << "Failed to read width/height." << std::endl;
		return false;
	}

	return true;
}

bool Level::readMagicNumber(std::ifstream &file) {
	uint8_t fileMagicNumber[8];

	file.read(reinterpret_cast<char *>(fileMagicNumber), sizeof(fileMagicNumber));
	if (!file) {
		std::cerr << "Failed to read magic number from file." << std::endl;
		return false;
	}

	return std::memcmp(fileMagicNumber, magicNumber, sizeof(fileMagicNumber)) == 0;
}

bool Level::readVersionInfo(std::ifstream &file) {
	file.seekg(levelHeaderOffsets::versionMajorOffset, std::ios::beg);
	if (!file) {
		std::cerr << "Failed to seek to the version info position in the file." << std::endl;
		return false;
	}
	file.read(reinterpret_cast<char *>(&versionMajor), sizeof(versionMajor));
	file.read(reinterpret_cast<char *>(&versionMinor), sizeof(versionMinor));
	file.read(reinterpret_cast<char *>(&versionBugfix), sizeof(versionBugfix));

	return file.good();
}

bool Level::readLevelTitle(std::ifstream &file) {
	// Seek to the position of levelTitle
	file.seekg(levelHeaderOffsets::levelTitleOffset, std::ios::beg);
	if (!file) {
		std::cerr << "Failed to seek to the levelTitle position in the file." << std::endl;
		return false;
	}

	// Read the levelTitle
	file.read(levelTitle, sizeof(levelTitle));
	if (!file) {
		std::cerr << "Failed to read levelTitle from file." << std::endl;
		return false;
	}

	return true;
}

bool Level::readWidthHeight(std::ifstream &file) {
	file.seekg(levelHeaderOffsets::widthOffset, std::ios::beg);
	if (!file) {
		std::cerr << "Failed to seek to the width/height position in the file." << std::endl;
		return false;
	}

	// Read the levelTitle
	file.read(reinterpret_cast<char *>(&width), sizeof(width));
	file.read(reinterpret_cast<char *>(&height), sizeof(height));

	return true;
}

void Level::setLevelTitle(const std::string &title) {
	// Clear the existing title
	std::fill(std::begin(this->levelTitle), std::end(this->levelTitle), '\0');

	// Copy the new title, ensuring it's not longer than the buffer
	std::strncpy(this->levelTitle, title.c_str(), 128 - 1);
	this->levelTitle[128 - 1] = '\0'; // Explicit null termination
}