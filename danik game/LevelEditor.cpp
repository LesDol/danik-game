#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

// Constants for the editor
const int TILE_SIZE = 32;
const int GRID_WIDTH = 60;
const int GRID_HEIGHT = 25;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;
const int PALETTE_WIDTH = 200;

// Helper function to convert int to string (for older compilers without std::to_string)
std::string toString(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Level editor class
class LevelEditor {
private:
    sf::RenderWindow window;
    sf::View editorView;
    sf::View paletteView;
    
    // Textures and sprites
    std::map<char, sf::Texture> tileTextures;
    std::map<char, sf::Sprite> tileSprites;
    std::vector<char> availableTiles;
    
    // Current map
    std::vector<std::string> currentMap;
    
    // Editor state
    char currentTile;
    bool isDragging;
    sf::Vector2i lastTilePos;
    sf::Vector2f viewOffset;
    float zoom;
    
    // Font and text
    sf::Font font;
    sf::Text infoText;
    sf::Text helpText;
    
    // Grid
    sf::VertexArray grid;
    bool showGrid;
    
    // Initialize textures
    void initTextures() {
        // Load textures for different tile types
        sf::Texture texture;
        
        // Wall (0)
        if (texture.loadFromFile("tiles/wall.png")) {
            tileTextures['0'] = texture;
            tileSprites['0'].setTexture(tileTextures['0']);
            availableTiles.push_back('0');
        }
        
        // Empty space ( )
        if (texture.loadFromFile("tiles/empty.png")) {
            tileTextures[' '] = texture;
            tileSprites[' '].setTexture(tileTextures[' ']);
            availableTiles.push_back(' ');
        }
        
        // Coin (m)
        if (texture.loadFromFile("tiles/coin.png")) {
            tileTextures['m'] = texture;
            tileSprites['m'].setTexture(tileTextures['m']);
            availableTiles.push_back('m');
        }
        
        // Enemy (e)
        if (texture.loadFromFile("tiles/enemy.png")) {
            tileTextures['e'] = texture;
            tileSprites['e'].setTexture(tileTextures['e']);
            availableTiles.push_back('e');
        }
        
        // Player (p)
        if (texture.loadFromFile("tiles/player.png")) {
            tileTextures['p'] = texture;
            tileSprites['p'].setTexture(tileTextures['p']);
            availableTiles.push_back('p');
        }
        
        // Key (k)
        if (texture.loadFromFile("tiles/key.png")) {
            tileTextures['k'] = texture;
            tileSprites['k'].setTexture(tileTextures['k']);
            availableTiles.push_back('k');
        }
        
        // Door (d)
        if (texture.loadFromFile("tiles/door.png")) {
            tileTextures['d'] = texture;
            tileSprites['d'].setTexture(tileTextures['d']);
            availableTiles.push_back('d');
        }
        
        // Door (i)
        if (texture.loadFromFile("tiles/indoor.png")) {
            tileTextures['i'] = texture;
            tileSprites['i'].setTexture(tileTextures['i']);
            availableTiles.push_back('i');
        }
        
        // Border (s)
        if (texture.loadFromFile("tiles/border.png")) {
            tileTextures['s'] = texture;
            tileSprites['s'].setTexture(tileTextures['s']);
            availableTiles.push_back('s');
        }
        
        // Platform (g)
        if (texture.loadFromFile("tiles/platform.png")) {
            tileTextures['g'] = texture;
            tileSprites['g'].setTexture(tileTextures['g']);
            availableTiles.push_back('g');
        }
        
        // If textures failed to load, use colored rectangles
        if (availableTiles.empty()) {
            std::cout << "Failed to load textures, using colored rectangles instead" << std::endl;
            
            sf::Texture defaultTexture;
            defaultTexture.create(TILE_SIZE, TILE_SIZE);
            
            sf::Image wallImage;
            wallImage.create(TILE_SIZE, TILE_SIZE, sf::Color(100, 100, 100));
            defaultTexture.update(wallImage);
            tileTextures['0'] = defaultTexture;
            tileSprites['0'].setTexture(tileTextures['0']);
            availableTiles.push_back('0');
            
            sf::Image emptyImage;
            emptyImage.create(TILE_SIZE, TILE_SIZE, sf::Color(200, 200, 200));
            defaultTexture.update(emptyImage);
            tileTextures[' '] = defaultTexture;
            tileSprites[' '].setTexture(tileTextures[' ']);
            availableTiles.push_back(' ');
            
            sf::Image coinImage;
            coinImage.create(TILE_SIZE, TILE_SIZE, sf::Color(255, 255, 0));
            defaultTexture.update(coinImage);
            tileTextures['m'] = defaultTexture;
            tileSprites['m'].setTexture(tileTextures['m']);
            availableTiles.push_back('m');
            
            sf::Image enemyImage;
            enemyImage.create(TILE_SIZE, TILE_SIZE, sf::Color(255, 0, 0));
            defaultTexture.update(enemyImage);
            tileTextures['e'] = defaultTexture;
            tileSprites['e'].setTexture(tileTextures['e']);
            availableTiles.push_back('e');
            
            sf::Image playerImage;
            playerImage.create(TILE_SIZE, TILE_SIZE, sf::Color(0, 255, 0));
            defaultTexture.update(playerImage);
            tileTextures['p'] = defaultTexture;
            tileSprites['p'].setTexture(tileTextures['p']);
            availableTiles.push_back('p');
            
            sf::Image keyImage;
            keyImage.create(TILE_SIZE, TILE_SIZE, sf::Color(0, 255, 255));
            defaultTexture.update(keyImage);
            tileTextures['k'] = defaultTexture;
            tileSprites['k'].setTexture(tileTextures['k']);
            availableTiles.push_back('k');
            
            sf::Image doorImage;
            doorImage.create(TILE_SIZE, TILE_SIZE, sf::Color(150, 75, 0));
            defaultTexture.update(doorImage);
            tileTextures['d'] = defaultTexture;
            tileSprites['d'].setTexture(tileTextures['d']);
            availableTiles.push_back('d');
            
            sf::Image indoorImage;
            indoorImage.create(TILE_SIZE, TILE_SIZE, sf::Color(120, 60, 0));
            defaultTexture.update(indoorImage);
            tileTextures['i'] = defaultTexture;
            tileSprites['i'].setTexture(tileTextures['i']);
            availableTiles.push_back('i');
            
            sf::Image borderImage;
            borderImage.create(TILE_SIZE, TILE_SIZE, sf::Color(50, 50, 50));
            defaultTexture.update(borderImage);
            tileTextures['s'] = defaultTexture;
            tileSprites['s'].setTexture(tileTextures['s']);
            availableTiles.push_back('s');
            
            sf::Image platformImage;
            platformImage.create(TILE_SIZE, TILE_SIZE, sf::Color(180, 120, 70));
            defaultTexture.update(platformImage);
            tileTextures['g'] = defaultTexture;
            tileSprites['g'].setTexture(tileTextures['g']);
            availableTiles.push_back('g');
        }
        
        // Set current tile
        currentTile = availableTiles[0];
    }
    
    // Initialize grid
    void initGrid() {
        grid = sf::VertexArray(sf::Lines, (GRID_WIDTH + 1 + GRID_HEIGHT + 1) * 2);
        
        // Vertical lines
        for (int i = 0; i <= GRID_WIDTH; ++i) {
            grid[i * 2].position = sf::Vector2f(i * TILE_SIZE, 0);
            grid[i * 2 + 1].position = sf::Vector2f(i * TILE_SIZE, GRID_HEIGHT * TILE_SIZE);
            grid[i * 2].color = sf::Color(128, 128, 128, 128);
            grid[i * 2 + 1].color = sf::Color(128, 128, 128, 128);
        }
        
        // Horizontal lines
        for (int i = 0; i <= GRID_HEIGHT; ++i) {
            grid[(GRID_WIDTH + 1) * 2 + i * 2].position = sf::Vector2f(0, i * TILE_SIZE);
            grid[(GRID_WIDTH + 1) * 2 + i * 2 + 1].position = sf::Vector2f(GRID_WIDTH * TILE_SIZE, i * TILE_SIZE);
            grid[(GRID_WIDTH + 1) * 2 + i * 2].color = sf::Color(128, 128, 128, 128);
            grid[(GRID_WIDTH + 1) * 2 + i * 2 + 1].color = sf::Color(128, 128, 128, 128);
        }
    }
    
    // Initialize text
    void initText() {
        if (!font.loadFromFile("ArialRegular.ttf")) {
            std::cout << "Failed to load font" << std::endl;
        }
        
        infoText.setFont(font);
        infoText.setCharacterSize(14);
        infoText.setFillColor(sf::Color::White);
        
        helpText.setFont(font);
        helpText.setCharacterSize(12);
        helpText.setFillColor(sf::Color::White);
        helpText.setString(
            "Controls:\n"
            "LMB - Place tile\n"
            "RMB - Remove tile\n"
            "Mouse wheel - Zoom\n"
            "WASD - Move camera\n"
            "1-9 - Select tile\n"
            "F2 - Show/hide grid\n"
            "F5 - Save map\n"
            "F9 - Load map\n"
            "F1 - New map\n"
            "Esc - Exit"
        );
    }
    
    // Create new map
    void createNewMap() {
        currentMap.clear();
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            std::string row;
            for (int x = 0; x < GRID_WIDTH; ++x) {
                if (y == 0 || y == GRID_HEIGHT - 1 || x == 0 || x == GRID_WIDTH - 1) {
                    row.push_back('s');
                } else {
                    row.push_back(' ');
                }
            }
            currentMap.push_back(row);
        }
    }
    
    // Save map to file
    void saveMap(const std::string& filename) {
        std::ofstream file(filename.c_str());
        if (!file.is_open()) {
            std::cout << "Failed to open file for writing: " << filename << std::endl;
            return;
        }
        
        file << "const int HEIGHT_MAP = " << GRID_HEIGHT << ";//height of the level map" << std::endl;
        file << "const int WIDTH_MAP = " << GRID_WIDTH << ";//width of the level map" << std::endl;
        file << " " << std::endl;
        file << " " << std::endl;
        file << "sf::String TileMap[HEIGHT_MAP] = {" << std::endl;
        
        for (size_t y = 0; y < currentMap.size(); ++y) {
            file << "\t\"" << currentMap[y] << "\"";
            if (y < currentMap.size() - 1) {
                file << ",";
            }
            file << std::endl;
        }
        
        file << "};" << std::endl;
        file.close();
        
        std::cout << "Map saved to file: " << filename << std::endl;
    }
    
    // Load map from file
    void loadMap(const std::string& filename) {
        std::ifstream file(filename.c_str());
        if (!file.is_open()) {
            std::cout << "Failed to open file for reading: " << filename << std::endl;
            return;
        }
        
        currentMap.clear();
        std::string line;
        bool readingMap = false;
        
        while (std::getline(file, line)) {
            if (line.find("sf::String TileMap[HEIGHT_MAP] = {") != std::string::npos) {
                readingMap = true;
                continue;
            }
            
            if (readingMap) {
                if (line.find("};") != std::string::npos) {
                    break;
                }
                
                // Extract map row from quotes
                size_t start = line.find("\"");
                size_t end = line.rfind("\"");
                if (start != std::string::npos && end != std::string::npos && start < end) {
                    std::string mapRow = line.substr(start + 1, end - start - 1);
                    currentMap.push_back(mapRow);
                }
            }
        }
        
        file.close();
        std::cout << "Map loaded from file: " << filename << std::endl;
    }
    
    // Handle input
    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseButtonPress(event);
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left || 
                    event.mouseButton.button == sf::Mouse::Right) {
                    isDragging = false;
                }
            } else if (event.type == sf::Event::MouseMoved) {
                if (isDragging) {
                    handleMouseDrag(event);
                }
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                handleMouseWheel(event);
            }
        }
        
        // Handle camera movement with WASD keys
        float moveSpeed = 10.0f / zoom;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            viewOffset.y -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            viewOffset.y += moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            viewOffset.x -= moveSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            viewOffset.x += moveSpeed;
        }
        
        // Update camera position
        editorView.setCenter(WINDOW_WIDTH / 2 - PALETTE_WIDTH / 2 + viewOffset.x, 
                             WINDOW_HEIGHT / 2 + viewOffset.y);
        editorView.setSize(WINDOW_WIDTH - PALETTE_WIDTH, WINDOW_HEIGHT);
        editorView.zoom(1.0f / zoom);
    }
    
    // Handle key presses
    void handleKeyPress(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Escape) {
            window.close();
        } else if (key == sf::Keyboard::F2) {
            showGrid = !showGrid;
        } else if (key == sf::Keyboard::F5) {
            saveMap("Library/map.h");
        } else if (key == sf::Keyboard::F9) {
            loadMap("Library/map.h");
        } else if (key == sf::Keyboard::F1) {
            createNewMap();
        } else if (key >= sf::Keyboard::Num1 && key <= sf::Keyboard::Num9) {
            int index = key - sf::Keyboard::Num1;
            if (index < availableTiles.size()) {
                currentTile = availableTiles[index];
            }
        }
    }
    
    // Handle mouse button presses
    void handleMouseButtonPress(const sf::Event& event) {
        if (event.mouseButton.button == sf::Mouse::Left || 
            event.mouseButton.button == sf::Mouse::Right) {
            
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            
            // Check if cursor is in the palette area
            if (mousePos.x >= WINDOW_WIDTH - PALETTE_WIDTH) {
                // Select tile from palette
                int tileIndex = (mousePos.y - 50) / (TILE_SIZE + 10);
                if (tileIndex >= 0 && tileIndex < availableTiles.size()) {
                    currentTile = availableTiles[tileIndex];
                }
            } else {
                // Place tile on the map
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, editorView);
                int tileX = static_cast<int>(worldPos.x) / TILE_SIZE;
                int tileY = static_cast<int>(worldPos.y) / TILE_SIZE;
                
                if (tileX >= 0 && tileX < GRID_WIDTH && tileY >= 0 && tileY < GRID_HEIGHT) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        currentMap[tileY][tileX] = currentTile;
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        currentMap[tileY][tileX] = ' ';
                    }
                    
                    isDragging = true;
                    lastTilePos = sf::Vector2i(tileX, tileY);
                }
            }
        }
    }
    
    // Handle mouse drag
    void handleMouseDrag(const sf::Event& event) {
        sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
        
        // Check if cursor is in the editor area
        if (mousePos.x < WINDOW_WIDTH - PALETTE_WIDTH) {
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, editorView);
            int tileX = static_cast<int>(worldPos.x) / TILE_SIZE;
            int tileY = static_cast<int>(worldPos.y) / TILE_SIZE;
            
            if (tileX >= 0 && tileX < GRID_WIDTH && tileY >= 0 && tileY < GRID_HEIGHT &&
                (tileX != lastTilePos.x || tileY != lastTilePos.y)) {
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    currentMap[tileY][tileX] = currentTile;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    currentMap[tileY][tileX] = ' ';
                }
                
                lastTilePos = sf::Vector2i(tileX, tileY);
            }
        }
    }
    
    // Handle mouse wheel
    void handleMouseWheel(const sf::Event& event) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            float delta = event.mouseWheelScroll.delta;
            float zoomFactor = 1.1f;
            
            if (delta > 0) {
                zoom *= zoomFactor;
            } else if (delta < 0) {
                zoom /= zoomFactor;
            }
            
            // Limit zoom
            if (zoom < 0.2f) zoom = 0.2f;
            if (zoom > 5.0f) zoom = 5.0f;
        }
    }
    
    // Render the editor
    void render() {
        window.clear(sf::Color(50, 50, 50));
        
        // Render editing area
        window.setView(editorView);
        
        // Render tiles
        for (int y = 0; y < currentMap.size(); ++y) {
            for (int x = 0; x < currentMap[y].size(); ++x) {
                char tile = currentMap[y][x];
                if (tileSprites.find(tile) != tileSprites.end()) {
                    sf::Sprite sprite = tileSprites[tile];
                    sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    window.draw(sprite);
                }
            }
        }
        
        // Render grid
        if (showGrid) {
            window.draw(grid);
        }
        
        // Render palette
        window.setView(paletteView);
        
        // Palette background
        sf::RectangleShape paletteBackground(sf::Vector2f(PALETTE_WIDTH, WINDOW_HEIGHT));
        paletteBackground.setPosition(WINDOW_WIDTH - PALETTE_WIDTH, 0);
        paletteBackground.setFillColor(sf::Color(30, 30, 30));
        window.draw(paletteBackground);
        
        // Palette title
        sf::Text paletteTitle("Tile Palette", font, 18);
        paletteTitle.setPosition(WINDOW_WIDTH - PALETTE_WIDTH + 10, 10);
        paletteTitle.setFillColor(sf::Color::White);
        window.draw(paletteTitle);
        
        // Render available tiles
        for (size_t i = 0; i < availableTiles.size(); ++i) {
            char tile = availableTiles[i];
            sf::Sprite sprite = tileSprites[tile];
            sprite.setPosition(WINDOW_WIDTH - PALETTE_WIDTH + 10, 50 + i * (TILE_SIZE + 10));
            
            // Highlight current tile
            if (tile == currentTile) {
                sf::RectangleShape highlight(sf::Vector2f(TILE_SIZE + 4, TILE_SIZE + 4));
                highlight.setPosition(sprite.getPosition().x - 2, sprite.getPosition().y - 2);
                highlight.setFillColor(sf::Color::Transparent);
                highlight.setOutlineColor(sf::Color::Yellow);
                highlight.setOutlineThickness(2);
                window.draw(highlight);
            }
            
            window.draw(sprite);
            
            // Tile name
            sf::Text tileText;
            tileText.setFont(font);
            tileText.setCharacterSize(14);
            tileText.setFillColor(sf::Color::White);
            
            std::string tileName;
            switch (tile) {
                case '0': tileName = "Wall (0)"; break;
                case ' ': tileName = "Empty ( )"; break;
                case 'm': tileName = "Coin (m)"; break;
                case 'e': tileName = "Enemy (e)"; break;
                case 'p': tileName = "Player (p)"; break;
                case 'k': tileName = "Key (k)"; break;
                case 'd': tileName = "Exit (d)"; break;
                case 'i': tileName = "Door (i)"; break;
                case 's': tileName = "Border (s)"; break;
                case 'g': tileName = "Platform (g)"; break;
                default: tileName = std::string(1, tile);
            }
            
            tileText.setString(tileName);
            tileText.setPosition(sprite.getPosition().x + TILE_SIZE + 10, sprite.getPosition().y + TILE_SIZE / 2 - 7);
            window.draw(tileText);
        }
        
        // Render help text
        helpText.setPosition(WINDOW_WIDTH - PALETTE_WIDTH + 10, WINDOW_HEIGHT - 200);
        window.draw(helpText);
        
        // Render info about current tile and position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, editorView);
        int tileX = static_cast<int>(worldPos.x) / TILE_SIZE;
        int tileY = static_cast<int>(worldPos.y) / TILE_SIZE;
        
        std::string infoString = "Current tile: ";
        switch (currentTile) {
            case '0': infoString += "Wall (0)"; break;
            case ' ': infoString += "Empty ( )"; break;
            case 'm': infoString += "Coin (m)"; break;
            case 'e': infoString += "Enemy (e)"; break;
            case 'p': infoString += "Player (p)"; break;
            case 'k': infoString += "Key (k)"; break;
            case 'd': infoString += "Exit (d)"; break;
            case 'i': infoString += "Door (i)"; break;
            case 's': infoString += "Border (s)"; break;
            case 'g': infoString += "Platform (g)"; break;
            default: infoString += std::string(1, currentTile);
        }
        
        infoString += "\nPosition: " + toString(tileX) + ", " + toString(tileY);
        infoString += "\nZoom: " + toString(zoom);
        
        infoText.setString(infoString);
        infoText.setPosition(WINDOW_WIDTH - PALETTE_WIDTH + 10, WINDOW_HEIGHT - 80);
        window.draw(infoText);
        
        window.display();
    }
    
public:
    LevelEditor() : 
        window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Level Editor"),
        editorView(sf::FloatRect(0, 0, WINDOW_WIDTH - PALETTE_WIDTH, WINDOW_HEIGHT)),
        paletteView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)),
        isDragging(false),
        viewOffset(0, 0),
        zoom(1.0f),
        showGrid(true)
    {
        window.setFramerateLimit(60);
        
        initTextures();
        initGrid();
        initText();
        createNewMap();
        
        // Try to load existing map
        try {
            loadMap("Library/map.h");
        } catch (...) {
            std::cout << "Failed to load map, created new one" << std::endl;
        }
    }
    
    void run() {
        while (window.isOpen()) {
            handleInput();
            render();
        }
    }
};

int main() {
    setlocale(LC_ALL, "English");
    
    // Create tiles directory if it doesn't exist
    system("mkdir tiles 2>nul");
    
    // Create basic tiles if they don't exist
    sf::Image wallImage, emptyImage, coinImage, enemyImage, playerImage, keyImage, doorImage, indoorImage, borderImage, platformImage;
    
    wallImage.create(TILE_SIZE, TILE_SIZE, sf::Color(100, 100, 100));
    emptyImage.create(TILE_SIZE, TILE_SIZE, sf::Color(200, 200, 200));
    coinImage.create(TILE_SIZE, TILE_SIZE, sf::Color(255, 255, 0));
    enemyImage.create(TILE_SIZE, TILE_SIZE, sf::Color(255, 0, 0));
    playerImage.create(TILE_SIZE, TILE_SIZE, sf::Color(0, 255, 0));
    keyImage.create(TILE_SIZE, TILE_SIZE, sf::Color(0, 255, 255));
    doorImage.create(TILE_SIZE, TILE_SIZE, sf::Color(150, 75, 0));
    indoorImage.create(TILE_SIZE, TILE_SIZE, sf::Color(120, 60, 0));
    borderImage.create(TILE_SIZE, TILE_SIZE, sf::Color(50, 50, 50));
    platformImage.create(TILE_SIZE, TILE_SIZE, sf::Color(180, 120, 70));
    
    // Save basic tiles
    wallImage.saveToFile("tiles/wall.png");
    emptyImage.saveToFile("tiles/empty.png");
    coinImage.saveToFile("tiles/coin.png");
    enemyImage.saveToFile("tiles/enemy.png");
    playerImage.saveToFile("tiles/player.png");
    keyImage.saveToFile("tiles/key.png");
    doorImage.saveToFile("tiles/door.png");
    indoorImage.saveToFile("tiles/indoor.png");
    borderImage.saveToFile("tiles/border.png");
    platformImage.saveToFile("tiles/platform.png");
    
    LevelEditor editor;
    editor.run();
    
    return 0;
} 