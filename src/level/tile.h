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
	//								   this	    total	offset
	u_int32_t xCoordinate = 0;         //   4	//   4	//   0
	u_int32_t yCoordinate = 0;         //   4	//   8	//   4
	u_int64_t uniqueID    = 0;         //   8	//   16	//   8
	char tileType[128]    = "default"; // 128	//  144	//  16
	bool collision        = true;      //   1	//  145	// 144
	float friction        = 1.0f;      //   4 	//  149	// 145
	bool icy              = false;     //   1	//  150	// 149
	// Padding
	uint8_t padding[1024 - 150];

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
	bool readIcy(std::ifstream &file);
};
#pragma pack(pop)

static_assert(sizeof(Tile) == 1024, "Tile size is not 1024 bytes.");

#endif // TILE_H