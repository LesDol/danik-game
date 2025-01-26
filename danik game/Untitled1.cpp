
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Library/Animation.h"
#include <vector>

class AIEnemy {
public:
    AIEnemy(const sf::Texture& texture, float x, float y, float patrolDistance);

    void update(float deltaTime, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& groundSprites);
    void render(sf::RenderWindow& window) const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setScale(float x, float y);
    bool checkCollision(const sf::FloatRect& playerBounds) const;

private:
    void applyGravity(float deltaTime);
    void checkPlayerInRange(const sf::Vector2f& playerPosition);
    void patrol(float deltaTime);
    void checkGroundCollision(const std::vector<sf::Sprite>& groundSprites);
    void move(float deltaTime);

    sf::Sprite sprite;
    sf::Vector2f velocity;
    sf::Vector2f position;

    float patrolDistance;
    float speed;
    float gravity = 1.0f;
    float maxFallSpeed = 10.0f;
    bool movingRight;
    bool onGround;

    sf::Clock patrolTimer;
    Animation walkAnimation;
    Animation idleAnimation;
};
AIEnemy::AIEnemy(const sf::Texture& texture, float x, float y, float patrolDistance)
    : patrolDistance(patrolDistance), speed(50.f), movingRight(true), onGround(false),
      walkAnimation("EnemySprites/Slime/FreeSlime/slime_run.png", sprite, 4),
      idleAnimation("EnemySprites/Slime/FreeSlime/slime_idle.png", sprite, 4) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    position = {x, y};
    velocity = {0.f, 0.f};
    patrolTimer.restart();
    walkAnimation.changeAnimationOn(sprite);
}

void AIEnemy::update(float deltaTime, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& groundSprites) {
    applyGravity(deltaTime);
    checkPlayerInRange(playerPosition);
    patrol(deltaTime);
    checkGroundCollision(groundSprites);
    move(deltaTime);

    if (std::abs(velocity.x) > 0.1f) {
        walkAnimation.updateAnimation(sprite);
    } else {
        idleAnimation.updateAnimation(sprite);
    }
}

void AIEnemy::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void AIEnemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    position = {x, y};
}

sf::Vector2f AIEnemy::getPosition() const {
    return sprite.getPosition();
}

void AIEnemy::setScale(float x, float y) {
    sprite.setScale(x, y);
}

bool AIEnemy::checkCollision(const sf::FloatRect& playerBounds) const {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

void AIEnemy::applyGravity(float deltaTime) {
    if (!onGround) {
        velocity.y += gravity * deltaTime;
        if (velocity.y > maxFallSpeed) {
            velocity.y = maxFallSpeed;
        }
    } else {
        velocity.y = 0;
    }
    sprite.move(0, velocity.y);
}

void AIEnemy::checkPlayerInRange(const sf::Vector2f& playerPosition) {
    float distance = std::hypot(playerPosition.x - position.x, playerPosition.y - position.y);
    movingRight = (playerPosition.x > position.x && distance < patrolDistance);
}

void AIEnemy::patrol(float deltaTime) {
    float moveDistance = speed * deltaTime;
    velocity.x = movingRight ? moveDistance : -moveDistance;
}

void AIEnemy::checkGroundCollision(const std::vector<sf::Sprite>& groundSprites) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    onGround = false;

    for (const auto& ground : groundSprites) {
        if (bounds.intersects(ground.getGlobalBounds())) {
            onGround = true;
            sprite.setPosition(sprite.getPosition().x, ground.getGlobalBounds().top - bounds.height);
            break;
        }
    }
}

void AIEnemy::move(float deltaTime) {
    sprite.move(velocity.x, 0);
    position = sprite.getPosition();
    if (velocity.x < 0) {
        sprite.setScale(-1.f, 1.f); // Смотрит влево
    } else if (velocity.x > 0) {
        sprite.setScale(1.f, 1.f); // Смотрит вправо
    }
}

int main() {
    // Создаем окно для игры
    sf::RenderWindow window(sf::VideoMode(800, 600), "AIEnemy Example");
    window.setFramerateLimit(45);

    // Загружаем текстуры для врагов
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("EnemySprites/Slime/FreeSlime/slime_idle.png")) {
        return -1; // Если не удалось загрузить текстуру
    }

    // Создаем список врагов
    std::vector<AIEnemy> enemies;
    
    // Добавляем несколько врагов с разными позициями и расстоянием патруля
    enemies.push_back(AIEnemy(enemyTexture, 100.f, 100.f, 300.f));
    enemies.push_back(AIEnemy(enemyTexture, 300.f, 100.f, 300.f));
    enemies.push_back(AIEnemy(enemyTexture, 500.f, 100.f, 300.f));

    // Создаем список спрайтов для земли (платформы)
    std::vector<sf::Sprite> groundSprites;

    // Пример создания земли (платформы)
    sf::Texture groundTexture;
    groundTexture.loadFromFile("EnemySprites/Slime/FreeSlime/slime_idle.png");
    sf::Sprite groundSprite(groundTexture);
    groundSprite.setPosition(0.f, 500.f);
    groundSprites.push_back(groundSprite);

    // Игровой цикл
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Обновляем поведение каждого врага
        sf::Vector2f playerPosition(400.f, 300.f);  // Примерная позиция игрока
        for (auto& enemy : enemies) {
            enemy.update(dt, playerPosition, groundSprites);
        }

        // Очистка экрана
        window.clear();

        // Отображение платформ
        for (const auto& ground : groundSprites) {
            window.draw(ground);
        }

        // Отображение каждого врага
        for (const auto& enemy : enemies) {
            enemy.render(window);
        }

        // Отображаем все на экране
        window.display();
    }

    return 0;
}
