#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, sf::Font& font, const std::string& text, std::function<void()> onClick)
        : isHovered(false), callback(onClick) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Blue);
        
        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);
        label.setPosition(position.x + 10, position.y + 10);
    }

    void update(const sf::Vector2f& mousePos, bool isPressed) {
        if (shape.getGlobalBounds().contains(mousePos)) {
            shape.setFillColor(sf::Color::Red);
            isHovered = true;
            if (isPressed && callback) {
                callback();
            }
        } else {
            shape.setFillColor(sf::Color::Blue);
            isHovered = false;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(label);
    }

private:
    sf::RectangleShape shape;
    sf::Text label;
    bool isHovered;
    std::function<void()> callback;
};

class UI {
public:
    UI(sf::Font& font) {
        buttons.emplace_back(sf::Vector2f(100, 100), sf::Vector2f(200, 50), font, "Click Me", [](){
            printf("Button Clicked!\n");
        });
    }

    void update(const sf::Vector2f& mousePos, bool isPressed) {
        for (auto& button : buttons) {
            button.update(mousePos, isPressed);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (auto& button : buttons) {
            button.draw(window);
        }
    }

private:
    std::vector<Button> buttons;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "UI Example");
    
    sf::Font font;
    if (!font.loadFromFile("ArialRegular.ttf")) {
        return -1;
    }
    
    UI ui(font);
    
    while (window.isOpen()) {
        sf::Event event;
        bool mousePressed = false;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePressed = true;
            }
        }
        
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
        ui.update(mousePos, mousePressed);
        
        window.clear();
        ui.draw(window);
        window.display();
    }
    
    return 0;
}
