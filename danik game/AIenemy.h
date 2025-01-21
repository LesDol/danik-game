#ifndef AIENEMY_H
#define AIENEMY_H

#include <SFML/Graphics.hpp>
#include <cmath>

class AIEnemy {
public:
    AIEnemy(float x, float y, float patrolDistance);
    void update(float deltaTime, const sf::Vector2f& playerPosition, const sf::FloatRect& groundBounds);
    void render(sf::RenderWindow& window);
    void setScale(float x, float y);
    sf::Vector2f getPosition() const;
    bool checkCollision(const sf::FloatRect& playerBounds) const;
    void setTexture(const sf::Texture& texture);
    void setSpeed(float speed);

private:
    void applyGravity(float deltaTime);
    void checkPlayerInRange(const sf::Vector2f& playerPosition);
    void patrol(float deltaTime, const sf::Vector2f& playerPosition);
    void checkGroundCollision(const sf::FloatRect& groundBounds);
    void move(float deltaTime);

    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float patrolDistance;
    float zoneRadius;
    bool movingRight;
    bool isPlayerInRange;
    bool onGround;
    sf::Clock patrolTimer;

    sf::Sprite sprite;
};




AIEnemy::AIEnemy(float x, float y, float patrolDistance)
    : position(x, y), patrolDistance(patrolDistance), movingRight(true), isPlayerInRange(false), onGround(false), speed(50.f) {
    velocity = sf::Vector2f(0.f, 0.f);
    zoneRadius = 150.f; // �������� ���� ���������
    patrolTimer.restart();
}

void AIEnemy::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void AIEnemy::update(float deltaTime, const sf::Vector2f& playerPosition, const sf::FloatRect& groundBounds) {
    applyGravity(deltaTime);
    checkPlayerInRange(playerPosition);
    patrol(deltaTime, playerPosition);
    checkGroundCollision(groundBounds);
    move(deltaTime);
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
        velocity.x = (playerPosition.x > position.x) ? speed : -speed;
        movingRight = (velocity.x > 0);
    } else {
        // ��������������, ���� ����� �� � ���� ���������
        if (patrolTimer.getElapsedTime().asSeconds() > 3.0f) {
            movingRight = !movingRight;
            patrolTimer.restart();
        }
        velocity.x = movingRight ? speed : -speed;
    }
}



void AIEnemy::checkGroundCollision(const sf::FloatRect& groundBounds) {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();

    // �������� ��������������� � ������ (���������� ������)
    sf::FloatRect probeBounds = enemyBounds;
    probeBounds.top += 1.f; // �������� ���� ��� �������� �����
    onGround = groundBounds.intersects(probeBounds);

    // ���� ���� ������ �� ������� �����, ������ �����������
    if (onGround) {
        if (movingRight && (enemyBounds.left + enemyBounds.width > groundBounds.left + groundBounds.width)) {
            movingRight = false;
        } else if (!movingRight && (enemyBounds.left < groundBounds.left)) {
            movingRight = true;
        }
    }
}


void AIEnemy::move(float deltaTime) {
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
    position = sprite.getPosition();

    // ������� ������� � ����������� �� ����������� ��������
    if (velocity.x > 0) {
        sprite.setScale(0.1f, 0.1f); // ������ ������� ������
    } else if (velocity.x < 0) {
        sprite.setScale(-0.1f, 0.1f); // ������ ������� �����
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

void AIEnemy::setScale(float x, float y) {
    sprite.setScale(x, y);
}

#endif // AIENEMY_H

