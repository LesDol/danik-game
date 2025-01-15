class InteractionZone {
private:
    sf::RectangleShape zone;
    sf::Sprite zoneSprite;
    sf::Texture zoneTexture;
    sf::Font font;
    sf::Text message;
    sf::RenderWindow* window;
    bool isPlayerInside;
    bool isAnswerWindowOpen;
    bool actionCompleted;
    int upDoor = 0;

    // Генерация квадратного уравнения с целым числом в качестве решения
    std::pair<int, int> generateEquation() {
        int a = rand() % 9 + 1; // Коэффициент a (от 1 до 9)
        int x = rand() % 21 - 10; // Целое решение x (от -10 до 10)
        int b = -a * x; // Коэффициент b, чтобы решение оставалось целым
        return {a, b};
    }

    // Решение квадратного уравнения
    double solveEquation(int a, int b) {
        return -b / static_cast<double>(a);
    }

public:
    InteractionZone(sf::RenderWindow* win, sf::Vector2f position, sf::Vector2f size) :
        window(win), isPlayerInside(false), isAnswerWindowOpen(false), actionCompleted(false) {

        zone.setSize(size);
        zone.setPosition(position);
        zone.setFillColor(sf::Color(0, 0, 255, 100));

        font.loadFromFile("ArialRegular.ttf");
        zoneTexture.loadFromFile("animation/tile.png");

        zoneSprite.setTexture(zoneTexture);
        zoneSprite.setPosition(position.x+150,position.y-50);

        message.setFont(font);
        message.setString("Нажмите E");
        message.setCharacterSize(24);
        message.setOutlineColor(sf::Color::Black);
        message.setOutlineThickness(3);
        message.setFillColor(sf::Color::White);
        message.setPosition(position.x, position.y - 30);
    }

    void setZoneColor(sf::Color color) {
        zone.setFillColor(color);  // Изменение цвета зоны
    }

    void setMessageText(const std::string& newText) {
        message.setString(newText);  // Изменение текста на экране
    }

    void setPosition(sf::Vector2f newPosition) {
        zone.setPosition(newPosition);  // Изменение позиции зоны
        zoneSprite.setPosition(newPosition.x + 150, newPosition.y - 50);
        message.setPosition(newPosition.x, newPosition.y - 30);
    }

    void update(sf::Sprite& player) {
        if (zone.getGlobalBounds().intersects(player.getGlobalBounds())) {
            isPlayerInside = true;
        } else {
            isPlayerInside = false;
        }
    }

    void render() {
        if(upDoor >= 1 && upDoor < 200 ) {
            performAction();
        }
        window->draw(zone);
        window->draw(zoneSprite);
        if (isPlayerInside && !isAnswerWindowOpen && !actionCompleted) {
            window->draw(message);
        }
    }

    void handleEvent(sf::Event& event) {
        if (isPlayerInside && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E && !actionCompleted) {
            isAnswerWindowOpen = true;
            openAnswerWindow();
        }
    }

    void openAnswerWindow() {
        // Этот метод не изменился
    }

    void performAction() {
        upDoor++;
        zoneSprite.move(0,-2);
    }

    const sf::Sprite& getZoneSprite() const {
        return zoneSprite;
    }
};

