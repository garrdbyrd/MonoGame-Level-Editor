#include <cstdint>
#include <fstream>
#include <iostream>

#include "levelheader.cpp"

int main() {
  // Header
  LevelHeader header;

  // DOTLEVEL magic number
  const uint8_t magicNumbers[] = {
      0x44, 0x4F, 0x54, 0x4C, 0x45, 0x56, 0x45, 0x4C,
  };
  std::copy(std::begin(magicNumbers), std::end(magicNumbers),
            std::begin(header.magicNumbers));
  // Version
  header.versionMajor = 0;
  header.versionMinor = 1;
  header.versionBugfix = 0;
  // Timestamp
  header.timestamp = static_cast<uint64_t>(time(nullptr));

  // Open a file in binary mode
  std::ofstream outputFile("example.level", std::ios::binary);

  if (!outputFile) {
    std::cerr << "Error opening file for writing.\n";
    return 1;
  }

  // Write the header
  outputFile.write(reinterpret_cast<const char *>(&header), sizeof(header));

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