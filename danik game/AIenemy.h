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
      walkAnimation("EnemySprites/Slime/FreeSlime/slime_run.png", sprite, 6), // 10 � ???????? ????? ???????
      idleAnimation("EnemySprites/Slime/FreeSlime/slime_idle.png", sprite, 9) // 15 � ???????? ????? ???????
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

    // ����������, ����� �������� ������������
    if (std::abs(velocity.x) > 0.1f) {
        // ���� ���� ��������, ���������� �������� ������
        walkAnimation.updateAnimation(sprite);
    } else {
        // ���� ���� �����, ���������� �������� ��������
        idleAnimation.updateAnimation(sprite);
    }
}


void AIEnemy::applyGravity(float deltaTime) {
    if (!onGround) {
        velocity.y += 9.8f * deltaTime; // ������� ������ ����������
    }
}

void AIEnemy::checkPlayerInRange(const sf::Vector2f& playerPosition) {
    float distanceToPlayer = sqrt(pow(playerPosition.x - position.x, 2) + pow(playerPosition.y - position.y, 2));
    isPlayerInRange = (distanceToPlayer <= zoneRadius);
}

void AIEnemy::patrol(float deltaTime, const sf::Vector2f& playerPosition) {
    if (isPlayerInRange) {
        // �������� � ������� ������
        bool newMovingRight = (playerPosition.x > position.x);
        float newVelocityX = newMovingRight ? speed : -speed;

        if (newMovingRight != movingRight) {
            // ����� �����������, ������� ������
            float offset = sprite.getGlobalBounds().width;
            position.x += newMovingRight ? -offset : offset;
            sprite.setPosition(position);
            movingRight = newMovingRight; // ��������� �����������
        }

        velocity.x = newVelocityX;
    } else {
        // ��������� ��������������
        if (patrolTimer.getElapsedTime().asSeconds() > 3.0f) {
            int action = std::rand() % 3; // ���������� ��������� �����: 0, 1, ��� 2
            float newVelocityX = 0.f;
            bool newMovingRight = movingRight; // �� ��������� ��������� ������� �����������

            switch (action) {
                case 0: // �������� �����
                    newVelocityX = -speed;
                    newMovingRight = false;
                    break;
                case 1: // �������� ������
                    newVelocityX = speed;
                    newMovingRight = true;
                    break;
                case 2: // ���������
                    newVelocityX = 0;
                    break;
            }

            if (newMovingRight != movingRight) {
                // ����� �����������, ������� ������
                float offset = sprite.getGlobalBounds().width;
                position.x += newMovingRight ? -offset : offset;
                sprite.setPosition(position);
                movingRight = newMovingRight; // ��������� �����������
            }

            velocity.x = newVelocityX;
            patrolTimer.restart(); // ���������� �������
        }
    }
}


void AIEnemy::checkGroundCollision(const std::vector<sf::Sprite>& groundSprites) {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();

    // �������� ��������������� � ������ �������� �����
    onGround = false; // ����� ��������� "�� �����"

    for (const auto& groundSprite : groundSprites) {
        sf::FloatRect groundBounds = groundSprite.getGlobalBounds();

        sf::FloatRect probeBounds = enemyBounds;
        probeBounds.top += 1.f; // �������� ���� ��� �������� �����

        if (groundBounds.intersects(probeBounds)) {
            onGround = true; // ���� ��������� �� �����
            break;          // ���������� ����� ���� �����������
        }
    }

    // ���� ���� ������ �� ������� �����, ������ �����������
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

    // ������� ������� � ����������� �� ����������� ��������
    if (velocity.x > 0) {
        sprite.setScale(sizeX, sizeY); // ������ ������� ������
    } else if (velocity.x < 0) {
        sprite.setScale(-sizeX, sizeY); // ������ ������� �����
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

