#include <cstdint>

struct ChunkHeader {
  uint8_t magicNumbers[8];
  uint8_t versionMajor;
  uint8_t versionMinor;
  uint8_t versionBugfix;
  uint64_t timestamp;
};