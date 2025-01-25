#include <SFML/Graphics.hpp>
#include "AIEnemy.h"

int main() {
    // �������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "AI Enemies Example");
    window.setFramerateLimit(60);

    // �������� �������
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("EnemySprites/Slime/FreeSlime/slime_idle.png")) {
        return -1; // ��������� ���������, ���� �������� �� ���������
    }

    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("animation/tile.png")) {
        return -1;
    }

    // �������� ������� AIEnemy
    AIEnemy enemies(5, enemyTexture, 200.f);

    // �������� �����
    std::vector<sf::Sprite> groundSprites;
    for (int i = 0; i < 8; ++i) {
        sf::Sprite ground(groundTexture);
        ground.setPosition(i * 100.f, 500.f); // ������������� ������ �����
        groundSprites.push_back(ground);
    }

    // ��������� ������
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(400.f, 300.f);

    float playerSpeed = 200.f;
    sf::Vector2f playerVelocity(0.f, 0.f);
    float gravity = 800.f;
    bool onGround = false;

    sf::Clock clock;

    while (window.isOpen()) {
        // ��������� �������
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // ���������� �������
        playerVelocity.x = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerVelocity.x = -playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerVelocity.x = playerSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onGround) {
            playerVelocity.y = -400.f; // ������
        }

        playerVelocity.y += gravity * deltaTime; // ���������� ����������
        if (playerVelocity.y > 800.f) {
            playerVelocity.y = 800.f; // ����������� �������� �������
        }

        player.move(playerVelocity * deltaTime);

        // �������� �������� ������ � ������
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

        // ���������� ������
        enemies.update(deltaTime, player.getPosition(), groundSprites);

        // ���������
        window.clear();

        // ��������� �����
        for (const auto& ground : groundSprites) {
            window.draw(ground);
        }

        // ��������� ������
        window.draw(player);

        // ��������� ������
        enemies.render(window);

        window.display();
    }

    return 0;
}

