#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Library/GameObject.h"
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Key Animation Example");
    window.setFramerateLimit(45);

    Key key(400.f, 300.f, 2.0f);

    sf::Clock clock;
    int collectedKeys = 0; // Количество собранных ключей

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //float deltaTime = clock.restart().asSeconds();

        // Проверяем взаимодействие игрока с ключом
        sf::FloatRect playerBounds(390.f, 290.f, 40.f, 40.f); // Пример игрока
        if (key.collect(playerBounds)) {
            collectedKeys++;
        }

        // Обновление ключа
        key.update(0.022);

        // Отрисовка
        window.clear();
        key.render(window);
        window.display();
    }

    return 0;
}
