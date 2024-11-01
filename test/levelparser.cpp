#include <iostream>

#include "../src/level/level.h"

void parseLevel()
{
    Level level;
    if (level.readFromFile("test/example.level")) {
        std::cout << 'v' << static_cast<int>(level.versionMajor) << "."
                  << static_cast<int>(level.versionMinor) << "."
                  << static_cast<int>(level.versionBugfix) << '\n'
                  << level.levelTitle << '\n'
                  << level.width << "x" << level.height << '\n';
    } else {
        std::cerr << "Failed to parse level file." << std::endl;
    }
}

int main()
{
    parseLevel();
    return 0;
}
