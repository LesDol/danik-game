#ifndef AIENEMY_H
#define AIENEMY_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Animation.h"

class AIEnemy {
public:
    AIEnemy(float x, float y, float patrolDistance);
    void update(float deltaTime, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& groundSprites);
    void render(sf::RenderWindow& window);
    void setScale(float x, float y);
    sf::Vector2f getPosition() const;
    bool checkCollision(const sf::FloatRect& playerBounds) const;
    void setTexture(const sf::Texture& texture);
    void setSpeed(float speed);

private:
	    const sf::Sprite& getSprite() const {
        return sprite;
    }
	
    void applyGravity(float deltaTime);
    void checkPlayerInRange(const sf::Vector2f& playerPosition);
    void patrol(float deltaTime, const sf::Vector2f& playerPosition);
    void checkGroundCollision(const std::vector<sf::Sprite>& groundSprites);
    void move(float deltaTime);

    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float patrolDistance;
    float zoneRadius;
    bool movingRight;
    bool isPlayerInRange;
    bool onGround;
    float sizeX , sizeY;
    sf::Clock patrolTimer;
	
    sf::Sprite sprite;
    
    Animation walkAnimation;
    Animation idleAnimation;
    
};




AIEnemy::AIEnemy(float x, float y, float patrolDistance)
    : position(x, y), patrolDistance(patrolDistance), movingRight(true), isPlayerInRange(false), onGround(false), speed(50.f),
      walkAnimation("EnemySprites/Slime/FreeSlime/slime_run.png", sprite, 6), // 10 — ???????? ????? ???????
      idleAnimation("EnemySprites/Slime/FreeSlime/slime_idle.png", sprite, 9) // 15 — ???????? ????? ???????
{
    velocity = sf::Vector2f(0.f, 0.f);
    zoneRadius = 150.f; // ?????? ?????????
    patrolTimer.restart();
    walkAnimation.changeAnimationOn(sprite); // ????????????? ???????? ???????? ?? ?????????
}

void AIEnemy::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void AIEnemy::update(float deltaTime, const sf::Vector2f& playerPosition, const std::vector<sf::Sprite>& groundSprites) {
    applyGravity(deltaTime);
    checkPlayerInRange(playerPosition);
    patrol(deltaTime, playerPosition);
    checkGroundCollision(groundSprites); // ???????? ??????? ????????
    move(deltaTime);

    // Определяем, какую анимацию использовать
    if (std::abs(velocity.x) > 0.1f) {
        // Если враг движется, используем анимацию ходьбы
        walkAnimation.updateAnimation(sprite);
    } else {
        // Если враг стоит, используем анимацию ожидания
        idleAnimation.updateAnimation(sprite);
    }
}


void AIEnemy::applyGravity(float deltaTime) {
    if (!onGround) {
        velocity.y += 9.8f * deltaTime; // Простая модель гравитации
    }
}

void AIEnemy::checkPlayerInRange(const sf::Vector2f& playerPosition) {
    float distanceToPlayer = sqrt(pow(playerPosition.x - position.x, 2) + pow(playerPosition.y - position.y, 2));
    isPlayerInRange = (distanceToPlayer <= zoneRadius);
}

void AIEnemy::patrol(float deltaTime, const sf::Vector2f& playerPosition) {
    if (isPlayerInRange) {
        // Движение в сторону игрока
        bool newMovingRight = (playerPosition.x > position.x);
        float newVelocityX = newMovingRight ? speed : -speed;

        if (newMovingRight != movingRight) {
            // Смена направления, смещаем спрайт
            float offset = sprite.getGlobalBounds().width;
            position.x += newMovingRight ? -offset : offset;
            sprite.setPosition(position);
            movingRight = newMovingRight; // Обновляем направление
        }

        velocity.x = newVelocityX;
    } else {
        // Рандомное патрулирование
        if (patrolTimer.getElapsedTime().asSeconds() > 3.0f) {
            int action = std::rand() % 3; // Генерируем случайное число: 0, 1, или 2
            float newVelocityX = 0.f;
            bool newMovingRight = movingRight; // По умолчанию сохраняем текущее направление

            switch (action) {
                case 0: // Движение влево
                    newVelocityX = -speed;
                    newMovingRight = false;
                    break;
                case 1: // Движение вправо
                    newVelocityX = speed;
                    newMovingRight = true;
                    break;
                case 2: // Остановка
                    newVelocityX = 0;
                    break;
            }

            if (newMovingRight != movingRight) {
                // Смена направления, смещаем спрайт
                float offset = sprite.getGlobalBounds().width;
                position.x += newMovingRight ? -offset : offset;
                sprite.setPosition(position);
                movingRight = newMovingRight; // Обновляем направление
            }

            velocity.x = newVelocityX;
            patrolTimer.restart(); // Перезапуск таймера
        }
    }
}


void AIEnemy::checkGroundCollision(const std::vector<sf::Sprite>& groundSprites) {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();

    // Проверка соприкосновения с каждым спрайтом земли
    onGround = false; // Сброс состояния "на земле"

    for (const auto& groundSprite : groundSprites) {
        sf::FloatRect groundBounds = groundSprite.getGlobalBounds();

        sf::FloatRect probeBounds = enemyBounds;
        probeBounds.top += 1.f; // Смещение вниз для проверки земли

        if (groundBounds.intersects(probeBounds)) {
            onGround = true; // Враг находится на земле
            break;          // Достаточно найти одно пересечение
        }
    }

    // Если враг уходит за пределы земли, меняем направление
    if (onGround) {
        for (const auto& groundSprite : groundSprites) {
            sf::FloatRect groundBounds = groundSprite.getGlobalBounds();

            if (movingRight && (enemyBounds.left + enemyBounds.width > groundBounds.left + groundBounds.width)) {
                movingRight = false;
                break;
            } else if (!movingRight && (enemyBounds.left < groundBounds.left)) {
                movingRight = true;
                break;
            }
        }
    }
}


void AIEnemy::move(float deltaTime) {
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
    position = sprite.getPosition();

    // Поворот спрайта в зависимости от направления движения
    if (velocity.x > 0) {
        sprite.setScale(sizeX, sizeY); // Спрайт смотрит вправо
    } else if (velocity.x < 0) {
        sprite.setScale(-sizeX, sizeY); // Спрайт смотрит влево
    }
}


sf::Vector2f AIEnemy::getPosition() const {
    return position;
}

bool AIEnemy::checkCollision(const sf::FloatRect& playerBounds) const {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();
    return enemyBounds.intersects(playerBounds);
}

void AIEnemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void AIEnemy::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void AIEnemy::setScale(float AddsizeX, float AddsizeY) {
	sizeX = AddsizeX;
	sizeY = AddsizeY;
    sprite.setScale(sizeX, sizeY);
}

#endif // AIENEMY_H

