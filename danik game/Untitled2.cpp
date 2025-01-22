#include <SFML/Graphics.hpp>
#include "AIEnemy.h"

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "AI Enemy Example");
    window.setFramerateLimit(60);

    // Часы для расчета времени кадра
    sf::Clock clock;

    // Платформа для врага и игрока
    sf::RectangleShape ground(sf::Vector2f(800.f, 50.f));
    ground.setFillColor(sf::Color::Green);
    ground.setPosition(0.f, 550.f);

    // Создание врага
    AIEnemy enemy(200.f, 500.f, 150.f);

    // Создание игрока
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(100.f, 500.f);
    enemy.setScale(2, 2);

    // Скорость игрока
    const float playerSpeed = 200.f;

    // Гравитация
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

        // Расчет времени кадра
        float deltaTime = clock.restart().asSeconds();

        // Управление игроком
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

        // Применение гравитации
        velocityY += gravity * deltaTime;
        movement.y += velocityY * deltaTime;

        // Перемещение игрока
        player.move(movement);

        // Проверка на землю
        if (player.getGlobalBounds().intersects(ground.getGlobalBounds())) {
            player.setPosition(player.getPosition().x, ground.getPosition().y - player.getSize().y);
            velocityY = 0.f;
            onGround = true;
        }

        // Обновление врага
        enemy.update(deltaTime, player.getPosition(), ground.getGlobalBounds());

        // Рендеринг
        window.clear();
        window.draw(ground);
        window.draw(player);
        enemy.render(window); // Отрисовка врага
        window.display();
    }

    return 0;
}

