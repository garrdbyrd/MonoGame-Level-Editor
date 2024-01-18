#ifndef LEVELHEADER_H
#define LEVELHEADER_H

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

// Known incorrect warning on following line
// see: https://github.com/clangd/clangd/issues/1167
#pragma clang diagnostic ignored "-Wpragma-pack"
#pragma pack(push, 1)
struct LevelHeader {
	// ----------------------- this   total
	uint8_t magicNumber[8]; // 8   // 8
	uint8_t versionMajor;   // 1   // 9
	uint8_t versionMinor;   // 1   // 10
	uint8_t versionBugfix;  // 1   // 11
	uint64_t timestamp;     // 8   // 19
	char levelTitle[128];   // 128 // 147 -- 128 is arbitrary length for title
	uint16_t width;         // 2   // 149
	uint16_t height;        // 2   // 151
	// Padding
	uint8_t padding[1024 - 151];
	// Methods
	void setLevelTitle(const std::string &title);
};
#pragma pack(pop)

#endif // LEVELHEADER_H