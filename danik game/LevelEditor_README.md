# SFML Level Editor

This is a simple level editor created using the SFML library. It allows you to create and edit maps for 2D games.

## Requirements

- DEV C++ 5.11
- SFML 2.x

## Compilation

1. Open the `LevelEditor.dev` file in DEV C++ 5.11
2. Press F11 or select "Compile & Run" from the "Execute" menu

## Usage

### Controls

- **LMB** - Place selected tile
- **RMB** - Remove tile (place empty space)
- **Mouse wheel** - Zoom in/out
- **WASD** - Move around the map
- **1-9** - Quick select tiles from palette
- **F2** - Show/hide grid
- **F5** - Save map to `Library/map.h` file
- **F9** - Load map from `Library/map.h` file
- **F1** - Create new map
- **Esc** - Exit editor

### Tile Types

- **0** - Wall
- **space** - Empty space
- **m** - Coin
- **e** - Enemy
- **p** - Player (starting position)
- **k** - Key
- **d** - Door
- **s** - Level border
- **g** - Platform

## Interface

The editor is divided into two main areas:
1. **Editing Area** - The main part of the window where you can place tiles
2. **Tile Palette** - The right panel where you can select tiles to place

## Map Format

The map is saved in a format compatible with the game, to the `Library/map.h` file. File format:

```cpp
const int HEIGHT_MAP = 25;//height of the level map
const int WIDTH_MAP = 60;//width of the level map
 
 
sf::String TileMap[HEIGHT_MAP] = {
    "s000000000000000000000000000000000000000000000000000000000s",
    "s       mm      mee     m       m        mmmeeee    iem eks",
    "s00   0000000   0000   00000   00000   0000000000   000000s",
    "sp  g      me g  m   g   md  g       g m      mm  g       s",
    "s000000   0000000000   0000000000   00000   00000000   000s",
    "s mki   g    m e     g  e   m     g   m   g     mmm  gi  ks",
    "s00000000000000000000000000000000000000000000000000000000s",
};
```

## Level Design Tips

1. Always surround your level with borders (`s`) to prevent the player from going outside the map
2. Place the player (`p`) in an accessible location where they won't get stuck
3. Create interesting paths with obstacles and rewards
4. Use enemies (`e`) to create difficulty
5. Place coins (`m`) in hard-to-reach places to encourage exploration
6. Use platforms (`g`) to create jumping challenges and interesting level layouts

## Extending the Editor

You can easily extend the editor by adding new tile types:

1. Add a new symbol and its texture in the `initTextures()` method
2. Add handling for the new tile type in the game

## Known Issues

- On first launch, the editor will create a `tiles` folder and basic tile textures
- If textures cannot be loaded, the editor will use colored rectangles instead 