#include <SFML/Graphics.hpp>
#include "AIenemy.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Enemy AI");
     window.setFramerateLimit(45);

    Enemy enemy(400, 300); // �������������� ����� � ������ ����

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ������������ ����� � ��������� ����
        enemy.update(sf::Vector2f(sf::Mouse::getPosition(window)));

        window.clear();
        enemy.draw(window);
        window.display();
    }

    return 0;
}
