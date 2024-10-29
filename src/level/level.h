#ifndef LEVEL_H
#define LEVEL_H

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "tile.h"

struct levelHeaderOffsets {
    // Sizes (in bytes)
    static const int magicNumberSize = sizeof(uint8_t[8]);
    static const int versionMajorSize = sizeof(uint8_t);
    static const int versionMinorSize = sizeof(uint8_t);
    static const int versionBugfixSize = sizeof(uint8_t);
    static const int versionPaddingSize = sizeof(uint8_t[5]);
    static const int timestampSize = sizeof(uint64_t);
    static const int levelTitleSize = 128;  // arbitrary
    static const int widthSize = sizeof(uint16_t);
    static const int heightSize = sizeof(uint16_t);

    // Main
    static const int magicNumberOffset = 0;
    static const int versionMajorOffset = magicNumberSize;
    static const int versionMinorOffset = versionMajorOffset + versionMajorSize;
    static const int versionBugfixOffset =
        versionMinorOffset + versionMinorSize;
    static const int versionPaddingOffset =
        versionBugfixOffset + versionBugfixSize;
    static const int timestampOffset =
        versionPaddingOffset + versionPaddingSize;
    static const int levelTitleOffset = timestampOffset + timestampSize;
    static const int widthOffset = levelTitleOffset + levelTitleSize;
    static const int heightOffset = widthOffset + widthSize;

    // Header size
    static const int headerSize = 1024;
    // The following line minimizes the header size. Could be useful one
    // day? static const int headerSize = heightOffset + heightSize +
    // sizeof(std::vector<std::vector<Tile>>);

    // Padding
    static const int paddingOffset =
        heightOffset + heightSize;  // Update when other properties are added
    static const int paddingSize = headerSize - paddingOffset;
};

// Known incorrect warning on following line
// see: https://github.com/clangd/clangd/issues/1167
#pragma clang diagnostic ignored "-Wpragma-pack"
#pragma pack(push, 1)
class Level
{
    public:
    // Constructor/Destructor
    Level() = default;
    ~Level() = default;

    // Header
    const uint8_t magicNumber[8] = {
        0x44,
        0x4F,
        0x54,
        0x4C,
        0x45,
        0x56,
        0x45,
        0x4C,
    };

    uint8_t versionMajor;
    uint8_t versionMinor;
    uint8_t versionBugfix;
    uint8_t versionPadding[5];  // Padding to align timestamp
    uint64_t timestamp;
    char levelTitle[levelHeaderOffsets::levelTitleSize];
    uint16_t width;
    uint16_t height;
    // Header padding
    uint8_t padding
        [levelHeaderOffsets::headerSize - levelHeaderOffsets::paddingOffset -
         sizeof(std::vector<std::vector<Tile>>)];

    // Main
    std::vector<std::vector<Tile>> grid;

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

static_assert(
    offsetof(Level, grid) ==
    levelHeaderOffsets::headerSize - sizeof(std::vector<std::vector<Tile>>)
);

#endif  // LEVEL_H