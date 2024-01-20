#ifndef TILE_H
#define TILE_H

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <vector>

struct tileOffsets {
	// Sizes (in bytes)
	static const int xCoordinateSize  = sizeof(u_int16_t);
	static const int yCoordinateSize  = sizeof(u_int16_t);
	static const int uniqueIDSize     = sizeof(u_int32_t);
	static const int tileTypeSize     = 128; // arbitrary
	static const int collisionSize    = sizeof(bool);
	static const int frictionSize     = sizeof(float);
	static const int frictionBoolSize = sizeof(bool);
	// Tile size
	static const int tileSize = 1024;

	// Main
	static const int xCoordinateOffset  = 0;
	static const int yCoordinateOffset  = xCoordinateSize;
	static const int uniqueIDOffset     = yCoordinateOffset + yCoordinateSize;
	static const int tileTypeOffset     = uniqueIDOffset + uniqueIDSize;
	static const int collisionOffset    = tileTypeOffset + tileTypeSize;
	static const int frictionOffset     = collisionOffset + collisionSize;
	static const int frictionBoolOffset = frictionOffset + frictionSize;

	// Padding
	static const int paddingOffset = frictionBoolOffset + frictionBoolSize; // Update when other properties are added
	static const int paddingSize   = tileSize - paddingOffset;
};

// Known incorrect warning on following line
// see: https://github.com/clangd/clangd/issues/1167
#pragma clang diagnostic ignored "-Wpragma-pack"
#pragma pack(push, 1)
class Tile {
  public:
	// Constructor/Destructor
	Tile()  = default;
	~Tile() = default;

	// Main
	//
	u_int16_t xCoordinate;
	u_int16_t yCoordinate;
	u_int32_t uniqueID;
	char tileType[tileOffsets::tileTypeSize] = "default";
	bool collision                           = true;
	float friction                           = 1.0f;
	bool frictionBool                        = false;
	// Padding
	uint8_t padding[tileOffsets::tileSize - 142];

	// Methods
	bool readFromFile(const std::string &filename, u_int32_t offset);

  private:
	// Methods
	int headerOffset();
	int tileSize();
	bool readXCoordinate(std::ifstream &file);
	bool readYCoordinate(std::ifstream &file);
	bool readTileType(std::ifstream &file);
	bool readCollision(std::ifstream &file);
	bool readFriction(std::ifstream &file);
	bool readFrictionBool(std::ifstream &file);
};
#pragma pack(pop)

#endif // TILE_H