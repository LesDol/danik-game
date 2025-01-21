#include "AIenemy.h"

AIEnemy::AIEnemy(float x, float y, float patrolDistance)
    : position(x, y), patrolDistance(patrolDistance), movingRight(true), isPlayerInRange(false), onGround(false) {
    velocity = sf::Vector2f(0.f, 0.f);
    zoneRadius = 150.f; // �������� ���� ���������
    patrolTimer.restart();
}

void AIEnemy::update(float deltaTime, const sf::Vector2f& playerPosition, const sf::FloatRect& groundBounds) {
    applyGravity(deltaTime);
    checkPlayerInRange(playerPosition);
    patrol(deltaTime);
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

void AIEnemy::patrol(float deltaTime) {
    if (!isPlayerInRange) {
        if (patrolTimer.getElapsedTime().asSeconds() > 3.0f) { // ����� ��������
            movingRight = !movingRight;
            patrolTimer.restart();
        }
        velocity.x = movingRight ? 50.f : -50.f; // �������� ��������������
    } else {
        velocity.x = 0.f; // ���������������, ���� ����� � ����
    }
}

void AIEnemy::checkGroundCollision(const sf::FloatRect& groundBounds) {
    sf::FloatRect enemyBounds(position.x, position.y, 50.f, 50.f); // �������� ������ �����
    sf::FloatRect probeBounds = enemyBounds;
    probeBounds.top += 1.f; // �������� ���� ��� �������� ����

    onGround = groundBounds.intersects(probeBounds);
    if (!onGround) {
        velocity.x = 0.f; // ������������� ��������, ���� ��� ������ ��� ����
    }
}

void AIEnemy::move(float deltaTime) {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

sf::Vector2f AIEnemy::getPosition() const {
    return position;
}

bool AIEnemy::checkCollision(const sf::FloatRect& playerBounds) const {
    sf::FloatRect enemyBounds(position.x, position.y, 50.f, 50.f); // �������� ������ �����
    return enemyBounds.intersects(playerBounds);
}

void AIEnemy::render(sf::RenderWindow& window) {
    sf::RectangleShape enemyShape(sf::Vector2f(50.f, 50.f)); // �������� ������ �����
    enemyShape.setPosition(position);
    enemyShape.setFillColor(sf::Color::Red);
    window.draw(enemyShape);
}

