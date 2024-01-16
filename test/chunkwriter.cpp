#include <cstdint>
#include <fstream>
#include <iostream>

#include "chunkheader.cpp"

int main() {
  // Header
  ChunkHeader header;

  // DOTLEVEL magic number
  const uint8_t magicNumbers[] = {
      0x44, 0x4F, 0x54, 0x43, 0x48, 0x55, 0x4E, 0x4B,
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
  std::ofstream outputFile("example.chunk", std::ios::binary);

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
