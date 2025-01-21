#include <SFML/Graphics.hpp>
#include <iostream>
#include "AIenemy.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "AI Enemy Example");
    window.setFramerateLimit(60);

    // ????????
    sf::Texture playerTexture;
    sf::Texture enemyTexture;

    if (!playerTexture.loadFromFile("animation/slime.png")) {
        std::cerr << "Failed to load player texture" << std::endl;
        return -1; // ?????? ???????? ???????? ??????
    }
    if (!enemyTexture.loadFromFile("animation/slime.png")) {
        std::cerr << "Failed to load enemy texture" << std::endl;
        return -1; // ?????? ???????? ???????? ?????
    }

    // ?????
    sf::Sprite player(playerTexture);
    player.setPosition(100.f, 500.f);
    player.setScale(0.1f, 0.1f);

    // ???
    sf::RectangleShape ground(sf::Vector2f(800.f, 50.f));
    ground.setPosition(0.f, 550.f);
    ground.setFillColor(sf::Color::Green);

    // ????
    AIEnemy enemy(400.f, 500.f, 200.f);
    enemy.setTexture(enemyTexture);
    enemy.setScale(0.1f, 0.1f);

    // ?????? ???????? ????? (????????, 100 ???????? ? ???????)
    enemy.setSpeed(100.f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ?????? ??????????? ??????
        float deltaTime = clock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-200.f * deltaTime, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(200.f * deltaTime, 0.f);
        }

        // ?????????? ?????
        enemy.update(deltaTime, player.getPosition(), ground.getGlobalBounds());

        // ???????? ???????????? ? ???????
        if (enemy.checkCollision(player.getGlobalBounds())) {
            player.setColor(sf::Color::Yellow); // ????????? ????? ??? ????????????
        } else {
            player.setColor(sf::Color::White);
        }

        // ?????????
        window.clear();
        window.draw(ground);
        window.draw(player);
        enemy.render(window);
        window.display();
    }

    return 0;
}

