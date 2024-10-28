#include <fstream>
#include <iostream>
#include <vector>

#include "tile.h"

bool Tile::readFromFile(const std::string &filename, u_int32_t offset)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::vector<char> buffer(tileSize());  // Buffer for tiles
    file.seekg(
        tileSize() * offset + headerOffset(),
        std::ios::beg
    );  // Offset for other tiles

    if (!file) {
        std::cerr << "Error seeking to offset in file: " << offset << std::endl;
        return false;
    }

    if (!readXCoordinate(file)) {
        std::cerr << "Failed to read xCoordinate." << std::endl;
        return false;
    }

    if (!readYCoordinate(file)) {
        std::cerr << "Failed to read yCoordinate." << std::endl;
        return false;
    }

    if (!readTileType(file)) {
        std::cerr << "Failed to read tileType." << std::endl;
        return false;
    }

    if (!readCollision(file)) {
        std::cerr << "Failed to read collision." << std::endl;
        return false;
    }

    if (!readFriction(file)) {
        std::cerr << "Failed to read friction." << std::endl;
        return false;
    }

    if (!readFrictionBool(file)) {
        std::cerr << "Failed to read icy." << std::endl;
        return false;
    }

    return true;
}

int Tile::headerOffset()
{
    return 1024;
}

int Tile::tileSize()
{
    return 1024;
}

bool Tile::readXCoordinate(std::ifstream &file)
{
    int offset = headerOffset();
    file.seekg(offset, std::ios::beg);
    if (!file) {
        std::cerr << "Failed to read xCoordinate from file.";
        return false;
    }
    file.read(reinterpret_cast<char *>(&xCoordinate), sizeof(xCoordinate));
    return true;
}

bool Tile::readYCoordinate(std::ifstream &file)
{
    int offset = headerOffset() + tileOffsets::yCoordinateOffset;
    file.seekg(offset, std::ios::beg);
    if (!file) {
        std::cerr << "Failed to read yCoordinate from file.";
        return false;
    }
    file.read(reinterpret_cast<char *>(&yCoordinate), sizeof(yCoordinate));
    return true;
}

bool Tile::readTileType(std::ifstream &file)
{
    int offset = headerOffset() + tileOffsets::tileTypeOffset;
    file.seekg(offset, std::ios::beg);
    if (!file) {
        std::cerr << "Failed to read tileType from file.";
        return false;
    }
    file.read(tileType, sizeof(tileType));
    if (!file) {
        std::cerr << "Failed to read tileType from file." << std::endl;
        return false;
    }

    return true;
}

bool Tile::readFriction(std::ifstream &file)
{
    int offset = headerOffset() + tileOffsets::frictionOffset;
    file.seekg(offset, std::ios::beg);
    if (!file) {
        std::cerr << "Failed to read friction from file.";
        return false;
    }
    file.read(reinterpret_cast<char *>(&friction), sizeof(friction));
    return true;
}

bool Tile::readCollision(std::ifstream &file)
{
    int offset = headerOffset() + tileOffsets::collisionOffset;
    file.seekg(offset, std::ios::beg);
    if (!file) {
        std::cerr << "Failed to read collision from file.";
        return false;
    }
    file.read(reinterpret_cast<char *>(&collision), sizeof(collision));
    return true;
}

bool Tile::readFrictionBool(std::ifstream &file)
{
    int offset = headerOffset() + tileOffsets::frictionBoolOffset;
    file.seekg(offset, std::ios::beg);
    if (!file) {
        std::cerr << "Failed to read frictionBool from file.";
        return false;
    }
    file.read(reinterpret_cast<char *>(&frictionBool), sizeof(frictionBool));
    return true;
}