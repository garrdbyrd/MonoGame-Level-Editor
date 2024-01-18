#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
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

void LevelHeader::setLevelTitle(const std::string &title) {
	// Clear the existing title
	std::fill(std::begin(this->levelTitle), std::end(this->levelTitle), '\0');

	// Copy the new title, ensuring it's not longer than the buffer
	std::strncpy(this->levelTitle, title.c_str(), 128 - 1);
	this->levelTitle[128 - 1] = '\0'; // Explicit null termination
}