# SFML 2.4 Engine

A simple game engine based on SFML 2.4 with a visual interface.

## Requirements

- Dev-C++ 5.11
- SFML 2.4
- C++14

## Project Structure

- `Engine.h` and `Engine.cpp` - core engine
- `UI.h` and `UI.cpp` - user interface components
- `main.cpp` - example of using the engine
- `Makefile.win` - file for compilation in Dev-C++

## Engine Components

### Core Engine (Engine)

The main engine class provides the following features:
- Window management
- Scene management
- Resource management (textures, fonts)
- Game loop

### User Interface (UI)

UI components:
- `Button` - button with click handling
- `Label` - text label
- `Panel` - panel that can contain other UI elements
- `UIManager` - manager for UI elements

## How to Use

1. Create a scene class by inheriting from `Scene`
2. Implement the `handleEvent`, `update`, and `render` methods
3. Create an engine instance and set the scene
4. Run the engine using the `run` method

Example:

```cpp
// Create engine instance
Engine engine("Window Title", 800, 600);

// Create and set scene
auto scene = std::make_unique<MyScene>();
engine.setScene(std::move(scene));

// Run engine
engine.run();
```

## Compilation

To compile the project in Dev-C++ 5.11:

1. Open the project in Dev-C++
2. Make sure SFML 2.4 is installed and configured
3. Compile the project using Makefile

## Notes

- The engine uses C++14, make sure your compiler supports this standard
- For SFML to work, you need to copy the SFML DLL files to the folder with the executable file 