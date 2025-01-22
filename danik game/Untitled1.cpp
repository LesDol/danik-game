#include <SFML/Graphics.hpp>
#include "Animation.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simplified Animation");
    window.setFramerateLimit(60);

    Animation walkAnimation;
    if (!walkAnimation.loadFromFile("animation/slime_walk.png", 32, 32)) {
        std::cerr << "Failed to load animation" << std::endl;
        return -1;
    }

    walkAnimation.setSpeed(0.15f); // 150 мс на кадр

    sf::Vector2f enemyPosition(400.f, 500.f);
    bool facingRight = true;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Управление направлением
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            enemyPosition.x += 100.f * deltaTime;
            facingRight = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            enemyPosition.x -= 100.f * deltaTime;
            facingRight = false;
        }

        // Обновление анимации
        walkAnimation.update(deltaTime);

        // Рендеринг
        window.clear();
        walkAnimation.render(window, enemyPosition, facingRight);
        window.display();
    }

    return 0;
}

