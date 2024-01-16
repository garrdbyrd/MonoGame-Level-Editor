#include <cstdint>

// Known incorrect warning on following line
// see: https://github.com/clangd/clangd/issues/1167
#pragma pack(push, 1)
struct LevelHeader {
  uint8_t magicNumbers[8];
  uint8_t versionMajor;
  uint8_t versionMinor;
  uint8_t versionBugfix;
  uint64_t timestamp;
  char levelTitle[128]; // Arbitrary length for title
};
#pragma pack(pop)