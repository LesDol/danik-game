#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional> 

using namespace std;
using namespace sf;

class Button {
public:
    Button(sf::Vector2f position, float width, float height, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, std::string buttonText, sf::Font& font)
        : m_position(position), m_idleColor(idleColor), m_hoverColor(hoverColor), m_pressedColor(pressedColor) {
        m_shape.setPosition(position);
        m_shape.setSize(sf::Vector2f(width, height));
        m_shape.setFillColor(m_idleColor);

        m_text.setFont(font);
        m_text.setString(buttonText);
        m_text.setCharacterSize(20);
        m_text.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        m_text.setPosition(position.x + width / 2.0f, position.y + height / 2.0f);
    }

    void setOnClick(const std::function<void()>& onClick) {
        m_onClick = onClick;
    }

void update(sf::RenderWindow& window, sf::View& view) {
    // Получаем позицию мыши в мировых координатах
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, view);  // Преобразуем в мировые координаты с учётом камеры

    bool isMouseOver = m_shape.getGlobalBounds().contains(worldPos);

    if (isMouseOver) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            m_shape.setFillColor(m_pressedColor);
            m_shape.setOutlineColor(m_hoverColor);

            if (m_onClick) {
                m_onClick();
            }
        } else {
            m_shape.setFillColor(m_hoverColor);
            m_shape.setOutlineColor(m_hoverColor);
        }
    } else {
        m_shape.setFillColor(m_idleColor);
        m_shape.setOutlineColor(m_idleColor);
    }
}
    void draw(sf::RenderWindow& window) {
        window.draw(m_shape);
        window.draw(m_text);
    }

    void setSize(float width, float height) {
        m_shape.setSize(sf::Vector2f(width, height));
        // Recenter text
        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        m_text.setPosition(m_position.x + width / 2.0f, m_position.y + height / 2.0f);
    }

private:
    std::function<void()> m_onClick;
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Vector2f m_position;
    sf::Color m_idleColor;
    sf::Color m_hoverColor;
    sf::Color m_pressedColor;
};

class Menu {
public:
    Menu(sf::RenderWindow& window, sf::Font& font)
        : m_window(window),
          m_startButton(sf::Vector2f(300, 150), 200, 50, sf::Color(204, 255, 204), sf::Color(102, 204, 102), sf::Color(51, 153, 51), "СТАРТ", font),
          m_aboutButton(sf::Vector2f(300, 250), 200, 50, sf::Color(204, 229, 255), sf::Color(102, 153, 255), sf::Color(51, 102, 204), "ОБ ИГРЕ", font),
          m_exitButton(sf::Vector2f(300, 350), 200, 50, sf::Color(255, 204, 204), sf::Color(255, 153, 153), sf::Color(204, 51, 51), "ВЫХОД", font),
          m_isGameStarted(false) {

        m_startButton.setOnClick([this]() { startGame(); });
        m_aboutButton.setOnClick([this]() { showAbout(); });
        m_exitButton.setOnClick([this]() { exitGame(); });
    }

void update(sf::RenderWindow& window, sf::View& view) {
    m_startButton.update(window, view);
    m_aboutButton.update(window, view);
    m_exitButton.update(window, view);
}

    void draw() {
        m_startButton.draw(m_window);
        m_aboutButton.draw(m_window);
        m_exitButton.draw(m_window);
    }

    bool isGameStarted() const {
        return m_isGameStarted;
    }

private:
    void startGame() {
        m_isGameStarted = true;
        std::cout << "Игра началась!" << std::endl;
    }

    void showAbout() {
        std::cout << "Это простая игра на SFML. Наслаждайтесь!" << std::endl;
    }

    void exitGame() {
        std::cout << "Выход из игры..." << std::endl;
        m_window.close();
    }

private:
    sf::RenderWindow& m_window;
    Button m_startButton;
    Button m_aboutButton;
    Button m_exitButton;
    bool m_isGameStarted;
};
class MainParallax {
public:
    MainParallax(const std::vector<sf::Texture*>& textures, const std::vector<float>& speeds) {
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                layers[i][j].setTexture(*textures[i]);
                layers[i][j].setScale(2.7, 2.7);
                layers[i][j].setPosition(j * layers[i][j].getGlobalBounds().width, -100);
            }
            scrollSpeeds[i] = speeds[i];
        }
    }

    void update(float deltaTime) {
        for (size_t i = 0; i < 4; ++i) {
            for (auto& layer : layers[i]) {
                layer.move(-scrollSpeeds[i] * deltaTime, 0);
            }
            if (layers[i][0].getPosition().x + layers[i][0].getGlobalBounds().width < 0) {
                layers[i][0].setPosition(layers[i][2].getPosition().x + layers[i][2].getGlobalBounds().width, -100);
                std::rotate(layers[i], layers[i] + 1, layers[i] + 3);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (size_t i = 0; i < 4; ++i) {
            for (const auto& layer : layers[i]) {
                window.draw(layer);
            }
        }
    }

private:
    sf::Sprite layers[4][3];
    float scrollSpeeds[4];
};


    

