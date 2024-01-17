#ifndef LEVEL_H
#define LEVEL_H

#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "tile.h"

class Level {
public:
  // Constructor/Destructor
  Level() = default;
  ~Level() = default;

  // Header
  const std::vector<uint8_t> levelMagicNumber = {
      0x44, 0x4F, 0x54, 0x4C, 0x45, 0x56, 0x45, 0x4C,
  };
  uint8_t versionMajor;
  uint8_t versionMinor;
  uint8_t versionBugfix;

  // Main
  char levelTitle[128];
  uint16_t width;
  uint16_t height;
  std::vector<std::vector<Tile>> grid;

  // Methods
  bool readFromFile(const std::string &filename);
  void initializeGrid(const Tile &defaultTile);

private:
  // Methods
  bool readMagicNumber(std::ifstream &file);
  bool readVersionInfo(std::ifstream &file);
  bool readLevelTitle(std::ifstream &file);
  bool readWidthHeight(std::ifstream &file);
};

#endif // LEVEL_H