#ifndef LEVEL_H
#define LEVEL_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "tile.h"

// Known incorrect warning on following line
// see: https://github.com/clangd/clangd/issues/1167
#pragma clang diagnostic ignored "-Wpragma-pack"
#pragma pack(push, 1)
class Level {
  public:
	// Constructor/Destructor
	Level()  = default;
	~Level() = default;

	// Header
	uint8_t magicNumber[8] = {
		0x44, 0x4F, 0x54, 0x4C, 0x45, 0x56, 0x45, 0x4C,
	};
	// 					   this	   total   offset
	//      magicNumber    //   8  //   8  //   0
	uint8_t versionMajor;  //   1  //   9  //   8
	uint8_t versionMinor;  //   1  //  10  //   9
	uint8_t versionBugfix; //   1  //  11  //  10
	uint64_t timestamp;    //   8  //  19  //  11
	char levelTitle[128];  // 128  // 147  //  19
	uint16_t width;        //   2  // 149  // 147
	uint16_t height;       //   2  // 151  // 149
	// Header padding
	uint8_t padding[1024 - 151 - sizeof(std::vector<std::vector<Tile>>)];

	// Main
	std::vector<std::vector<Tile>> grid;
	static_assert(sizeof(grid) == sizeof(std::vector<std::vector<Tile>>), "`grid` vector is not 24 bytes.");

	// Methods
	void setLevelTitle(const std::string &title);
	bool readFromFile(const std::string &filename);
	void initializeGrid(const Tile &defaultTile);

  private:
	// Methods
	bool readMagicNumber(std::ifstream &file);
	bool readVersionInfo(std::ifstream &file);
	bool readLevelTitle(std::ifstream &file);
	bool readWidthHeight(std::ifstream &file);
};
#pragma pack(pop)

// 1000 bytes instead of 1024 because final 24 bytes is grid vector
static_assert(offsetof(Level, grid) == 1024 - sizeof(std::vector<std::vector<Tile>>), "`grid` offset is not 1024 bytes.");

#endif // LEVEL_H