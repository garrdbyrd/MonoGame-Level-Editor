# Caspian: A MonoGame Level Editor
This is a level editor for my game made with MonoGame, project named "Pevensie". This level editor is made with Qt6.

(repo: https://github.com/garrdbyrd/MonoGame-Example)

This is made with Qt. This will not have its own dev diary, that is also in Pevensie. It can be built with cmake, edited with your favorite Qt tools.

Disclaimer: I am extremely new to Qt and don't really know how it works.

# To-do list
- [ ] Implement primary/secondary color system
- [x] Add undo/redo (drag commands; not single tiles)
- [x] Refresh button for tile picker menu
- [ ] Open recents
- [ ] "Restore defaults" button in preferences tabs
- [ ] Fullscreen mainGraphicsView

# Harder to-do list
- [ ] Implement palette
- [ ] Add all standard shortcuts (cut, copy, paste, ctrl + left click, save, etc)
- [ ] Autosave functionality
- [ ] Implement tabs so the user can edit multiple levels at once
- [ ] Export image (.png, .jpg, .tif) (checkbox: ignore default)

# Nightmare to-do list
- [ ] Read/write proprietary `.level` and `.chunk` file types
- [ ] Inspect tiles in main graphics view (change properties of particular tiles) (and everything else having to do with the properties menu)