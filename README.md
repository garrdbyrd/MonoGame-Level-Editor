# Caspian: A MonoGame Level Editor
This is a level editor for my game made with MonoGame, project named "Pevensie". This level editor is made with Qt6.

(repo: https://github.com/garrdbyrd/MonoGame-Example)

This is made with Qt. This will not have its own dev diary, that is also in Pevensie. It can be built with qmake, edited with your favorite Qt tools.

Disclaimer: I am extremely new to Qt and don't really know how it works.

## To-do list
- [ ] Implement primary/secondary color system
- [x] Add undo/redo (drag commands; not single tiles)
- [x] Refresh button for tile picker menu
- [ ] Open recents
- [ ] "Restore defaults" button in preferences tabs
- [ ] Fullscreen mainGraphicsView

## Harder to-do list
- [ ] Implement palette
- [ ] Add all standard shortcuts (cut, copy, paste, ctrl + left click, save, etc)
- [ ] Autosave functionality
- [ ] Implement tabs so the user can edit multiple levels at once
- [ ] Export image (.png, .jpg, .tif) (checkbox: ignore default)

## Nightmare to-do list
- [ ] Read/write proprietary `.level` and `.chunk` file types
- [ ] Inspect tiles in main graphics view (change properties of particular tiles) (and everything else having to do with the properties menu)

# `.level` Specification
This project utilizes a custom filetype to store/exchange level information. Appropriately, the extension of this filetype is `.level`. The dot level specification is provided in the following tables:

### First kilobyte:

| Value                 | Type       | Size                  | Byte offset | About                                                                                                                                           |
|-----------------------|------------|-----------------------|-------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| Magic Number          | uint8[8]   | 8                     | 0           | 44 4F 54 4C 45 56 45 4C                                                                                                                         |
| Major Version Number  | uint8      | 1                     | 8           | Major version number of .level specification                                                                                                    |
| Minor Version Number  | uint8      | 1                     | 9           | Minor version number of .level specification                                                                                                    |
| Bugfix Version Number | uint8      | 1                     | 10          | Bugfix/patch version number of .level specification                                                                                             |
| padding               | uint8[5]   | 5                     | 11          | To align timestamp                                                                                                                              |
| Timestamp             | uint64     | 8                     | 16          | Timestamp of file creation                                                                                                                      |
| Level Title           | char[128]  | 128                   | 24          | Title of the level                                                                                                                              |
| Level Width           | uint16     | 2                     | 152         | Number of tiles that span the width of the level                                                                                                |
| Level Height          | uint16     | 2                     | 154         | Number of tiles that span the height of the level                                                                                               |
| padding               | uint8[...] | 1024 - padding offset | 156         | First kilobyte is reserved for file metadata. The size of this padding may reduce as the specification changes and more fields are added above. |

### Remaining kilobytes:
Each remaining kilobyte corresponds to a tile within the level, which will be specified here as the tile specification is developed.

| Value                 | Type       | Size                  | Byte offset | About                                                                                                                                           |
|-----------------------|------------|-----------------------|-------------|-------------------------------------------------------------------------------------------------------------------------------------------------|
| xCoordinate           | uint16     | 2                     | 0           | Coordinate of tile on x axis                                                                                                                    |
| yCoordinate           | uint16     | 2                     | 2           | Coordinate of tile on y axis                                                                                                                    |
| uniqueID              | uint32     | 4                     | 4           | Unique ID for each tile in the level                                                                                                            |
| tileType              | char[128]  | 128                   | 8           | directory/texturename examples: "default/default", "plains/grass"                                                                               |
| friction              | float      | 4                     | 136         | Coefficient of friction                                                                                                                         |
| collision             | bool       | 1                     | 140         | Whether or not the tile can be collided with                                                                                                    |
| frictionBool          | bool       | 1                     | 141         | Whether or not friction is turned on                                                                                                            |
| padding               | uint8[...] | 1024 - padding offset | 142         | Padding                                                                                                                                         |                                                                                                                                   |