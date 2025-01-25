#include <SFML/Graphics.hpp>
#include "AIEnemy.h"

int main() {
    // Создание окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "AI Enemies Example");
    window.setFramerateLimit(60);

    // Загрузка текстур
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("EnemySprites/Slime/FreeSlime/slime_idle.png")) {
        return -1; // Завершаем программу, если текстура не загружена
    }

    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("animation/tile.png")) {
        return -1;
    }

    // Создание объекта AIEnemy
    AIEnemy enemies(5, enemyTexture, 200.f);

    // Создание земли
    std::vector<sf::Sprite> groundSprites;
    for (int i = 0; i < 8; ++i) {
        sf::Sprite ground(groundTexture);
        ground.setPosition(i * 100.f, 500.f); // Устанавливаем плитки земли
        groundSprites.push_back(ground);
    }

    // Параметры игрока
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(400.f, 300.f);

    float playerSpeed = 200.f;
    sf::Vector2f playerVelocity(0.f, 0.f);
    float gravity = 800.f;
    bool onGround = false;

    sf::Clock clock;

    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Управление игроком
        playerVelocity.x = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerVelocity.x = -playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerVelocity.x = playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
            playerVelocity.y = -400.f; // Прыжок
        }

        playerVelocity.y += gravity * deltaTime; // Применение гравитации
        if (playerVelocity.y > 800.f) {
            playerVelocity.y = 800.f; // Ограничение скорости падения
        }

        player.move(playerVelocity * deltaTime);

        // Проверка коллизий игрока с землей
        onGround = false;
        sf::FloatRect playerBounds = player.getGlobalBounds();
        for (const auto& ground : groundSprites) {
            sf::FloatRect groundBounds = ground.getGlobalBounds();
            if (groundBounds.intersects(playerBounds)) {
                if (playerBounds.top + playerBounds.height - playerVelocity.y * deltaTime <= groundBounds.top) {
                    player.setPosition(player.getPosition().x, groundBounds.top - playerBounds.height);
                    playerVelocity.y = 0.f;
                    onGround = true;
                }
            }
        }

        // Обновление врагов
        enemies.update(deltaTime, player.getPosition(), groundSprites);

        // Рендеринг
        window.clear();

        // Отрисовка земли
        for (const auto& ground : groundSprites) {
            window.draw(ground);
        }

        // Отрисовка игрока
        window.draw(player);

        // Отрисовка врагов
        enemies.render(window);

        window.display();
    }

    return 0;
}

