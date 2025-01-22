#include <SFML/Graphics.hpp>
#include "AIEnemy.h"

int main() {
    // �������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "AI Enemy Example");
    window.setFramerateLimit(60);

    // ���� ��� ������� ������� �����
    sf::Clock clock;

    // ��������� ��� ����� � ������
    sf::RectangleShape ground(sf::Vector2f(800.f, 50.f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0.f, 550.f);

    // �������� �����
    AIEnemy enemy(200.f, 500.f, 150.f);

    // �������� ������
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(100.f, 500.f);
    enemy.setScale(2, 2);

    // �������� ������
    const float playerSpeed = 200.f;

    // ����������
    float velocityY = 0.f;
    const float gravity = 500.f;
    const float jumpForce = -300.f;
    bool onGround = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // ������ ������� �����
        float deltaTime = clock.restart().asSeconds();

        // ���������� �������
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= playerSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += playerSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
            velocityY = jumpForce;
            onGround = false;
        }

        // ���������� ����������
        velocityY += gravity * deltaTime;
        movement.y += velocityY * deltaTime;

        // ����������� ������
        player.move(movement);

        // �������� �� �����
        if (player.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            player.setPosition(player.getPosition().x, ground.getPosition().y - player.getSize().y);
            velocityY = 0.f;
            onGround = true;
        }

        // ���������� �����
        enemy.update(deltaTime, player.getPosition(), ground.getGlobalBounds());

        // ���������
        window.clear();
        window.draw(ground);
        window.draw(player);
        enemy.render(window); // ��������� �����
        window.display();
    }

    return 0;
}

