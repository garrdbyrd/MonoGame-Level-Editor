#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>

class Chunk {
public:
  const uint8_t magicNumbers[8] = {
      0x44, 0x4F, 0x54, 0x43, 0x48, 0x55, 0x4E, 0x4B,
  };
  uint8_t versionMajor;
  uint8_t versionMinor;
  uint8_t versionBugfix;

private:
};

#endif // CHUNK_H