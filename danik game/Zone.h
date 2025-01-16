#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

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
        zoneSprite.setPosition(position.x + 150, position.y - 50);

        message.setFont(font);
        message.setString("Нажмите E");
        message.setCharacterSize(24);
        message.setOutlineColor(sf::Color::Black); 
        message.setOutlineThickness(3); 
        message.setFillColor(sf::Color::White);
        message.setPosition(position.x, position.y - 30);
    }

    void update(sf::Sprite& player) {
        if (zone.getGlobalBounds().intersects(player.getGlobalBounds())) {
            isPlayerInside = true;
        } else {
            isPlayerInside = false;
        }
    }

    void render() {
        if (upDoor >= 1 && upDoor < 200) {
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
        sf::RenderWindow answerWindow(sf::VideoMode(400, 300), "Решите уравнение");

        std::pair<int, int> coefficients = generateEquation();
        int a = coefficients.first;
        int b = coefficients.second;
        double correctAnswer = solveEquation(a, b);

        sf::Text equationText;
        equationText.setFont(font);
        std::ostringstream equation;
        equation << a << "x + " << b << " = 0";
        equationText.setString(equation.str());
        equationText.setCharacterSize(24);
        equationText.setFillColor(sf::Color::White);
        equationText.setPosition(50, 50);

        sf::Text feedback;
        feedback.setFont(font);
        feedback.setCharacterSize(20);
        feedback.setFillColor(sf::Color::Red);
        feedback.setPosition(50, 200);

        sf::String userInput;
        sf::Text inputText;
        inputText.setFont(font);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::White);
        inputText.setPosition(50, 150);

        bool correct = false;

        while (answerWindow.isOpen()) {
            sf::Event event;
            while (answerWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    answerWindow.close();
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b' && !userInput.isEmpty()) {
                        userInput.erase(userInput.getSize() - 1, 1);
                    } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                        userInput += event.text.unicode;
                    }
                    inputText.setString(userInput);
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                    double userAnswer = std::stod(userInput.toAnsiString());
                    if (std::abs(userAnswer - correctAnswer) < 0.01) {
                        feedback.setString("Ответ правильный");
                        feedback.setFillColor(sf::Color::Green);
                        correct = true;
                    } else {
                        feedback.setString("Ответ неправильный. Попробуйте снова.");
                        feedback.setFillColor(sf::Color::Red);
                    }
                }
            }

            answerWindow.clear();
            answerWindow.draw(equationText);
            answerWindow.draw(inputText);
            answerWindow.draw(feedback);
            answerWindow.display();

            if (correct) {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                answerWindow.close();
                actionCompleted = true;
                performAction();
            }
        }
    }

    void performAction() {
        upDoor++;
        zoneSprite.move(0, -2);
    }

    void setPosition(sf::Vector2f position) {
        zone.setPosition(position);
        zoneSprite.setPosition(position.x + 150, position.y - 50);  // Обновляем позицию спрайта
        message.setPosition(position.x, position.y - 30);  // Обновляем позицию текста
    }

     sf::Sprite& getZoneSprite()  {
        return zoneSprite;
    }

};

