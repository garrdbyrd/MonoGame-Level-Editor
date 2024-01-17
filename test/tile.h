#ifndef TILE_H
#define TILE_H

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

class Tile {
  public:
	// Constructor/Destructor
	Tile()  = default;
	~Tile() = default;

	// Main
	u_int32_t xCoordinate = 0;
	u_int32_t yCoordinate = 0;
	char tileType[128]    = "default";
	bool collision        = true;
	float friction        = 1.0f;
	bool icy              = false;

	// Methods
	bool readFromFile(const std::string &filename, u_int32_t offset);

  private:
	// Methods
	bool readXCoordinate(std::ifstream &file);
	bool readYCoordinate(std::ifstream &file);
	bool readCollision(std::ifstream &file);
	bool readFriction(std::ifstream &file);
	bool readIcy(std::ifstream &file);
};

#endif // TILE_H