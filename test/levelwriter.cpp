#include <cstdint>
#include <fstream>
#include <iostream>

#include "../src/level/level.h"
#include "../src/level/tile.h"

int main() {
	// Header
	Level level;

	// DOTLEVEL magic number
	const uint8_t magicNumber[] = {
		0x44, 0x4F, 0x54, 0x4C, 0x45, 0x56, 0x45, 0x4C,
	};
	std::copy(std::begin(magicNumber), std::end(magicNumber), std::begin(level.magicNumber));
	// Version
	level.versionMajor  = 0;
	level.versionMinor  = 1;
	level.versionBugfix = 0;
	// Timestamp
	level.timestamp = static_cast<uint64_t>(time(nullptr));
	// Title
	level.setLevelTitle("Example Level Title");
	level.width  = 16;
	level.height = 9;

	// Open a file in binary mode
	std::ofstream outputFile("test/example.level", std::ios::binary);

	if (!outputFile) {
		std::cerr << "Error opening file for writing.\n";
		return 1;
	}

	// Init grid
	Tile tempTile;
	level.initializeGrid(tempTile);

	// Write the level
	// Header + vector
	outputFile.write(reinterpret_cast<const char *>(&level), sizeof(level));
	for (const auto &row : level.grid) {
		for (const auto &tile : row) {
			outputFile.write(reinterpret_cast<const char *>(&tile), sizeof(tile));
		}
	}

	// Check for write errors
	if (!outputFile) {
		std::cerr << "Error writing to file.\n";
		outputFile.close();
		return 1;
	}

	// Check for write errors again
	if (!outputFile) {
		std::cerr << "Error writing additional data to file.\n";
		outputFile.close();
		return 1;
	}

	// Close the file
	outputFile.close();
	return 0;
}
