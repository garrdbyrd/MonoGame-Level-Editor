#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

#include "level.h"

bool Level::readFromFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return false;
  }

  if (!isValidMagicNumber(file)) {
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
    std::cerr << "Failed to read width/height" << std::endl;
    return false;
  }

  return true;
}

bool Level::isValidMagicNumber(std::ifstream &file) {
  std::vector<uint8_t> fileMagicNumber(levelMagicNumbers.size());

  file.read(reinterpret_cast<char *>(fileMagicNumber.data()),
            fileMagicNumber.size());
  if (!file) {
    std::cerr << "Failed to read magic number from file." << std::endl;
    return false;
  }

  return fileMagicNumber == levelMagicNumbers;
}

bool Level::readVersionInfo(std::ifstream &file) {
  file.seekg(8, std::ios::beg);
  if (!file) {
    std::cerr << "Failed to seek to the version info position in the file."
              << std::endl;
    return false;
  }
  file.read(reinterpret_cast<char *>(&versionMajor), sizeof(versionMajor));
  file.read(reinterpret_cast<char *>(&versionMinor), sizeof(versionMinor));
  file.read(reinterpret_cast<char *>(&versionBugfix), sizeof(versionBugfix));

  return file.good();
}

bool Level::readLevelTitle(std::ifstream &file) {
  // Seek to the position of levelTitle
  file.seekg(19, std::ios::beg); // 19 bytes
  if (!file) {
    std::cerr << "Failed to seek to the levelTitle position in the file."
              << std::endl;
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
  file.seekg(147, std::ios::beg);
  if (!file) {
    std::cerr << "Failed to seek to the width/height position in the file."
              << std::endl;
    return false;
  }

  // Read the levelTitle
  file.read(reinterpret_cast<char *>(&width), sizeof(width));
  file.read(reinterpret_cast<char *>(&height), sizeof(height));

  return true;
}