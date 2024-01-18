#include "levelheader.h"

void LevelHeader::setLevelTitle(const std::string &title) {
	// Clear the existing title
	std::fill(std::begin(this->levelTitle), std::end(this->levelTitle), '\0');

	// Copy the new title, ensuring it's not longer than the buffer
	std::strncpy(this->levelTitle, title.c_str(), 128 - 1);
	this->levelTitle[128 - 1] = '\0'; // Explicit null termination
}