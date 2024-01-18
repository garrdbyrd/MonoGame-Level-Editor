#ifndef TILE_H
#define TILE_H

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
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
	char tileType[128]    = "default"; // 128	// 136	//   8
	bool collision        = true;      //   1	// 137	// 136
	float friction        = 1.0f;      //   1 	// 138	// 137
	bool icy              = false;     //   1	// 139	// 138

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

#endif // TILE_H