#include "AIenemy.h"

class PatrolAI : public AIEntity {
public:
    PatrolAI(const std::string& name, sf::Vector2f initialPosition, sf::Vector2f patrolPoint)
        : AIEntity(name, initialPosition), patrolPoint(patrolPoint) {}

    void update(float deltaTime) override {
        sf::Vector2f direction = patrolPoint - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.1f) {
            velocity = direction / length * speed * deltaTime;
            position += velocity;
        } else {
            // Сменить патрульную точку или остановиться
            velocity = sf::Vector2f(0.f, 0.f);
        }
    }

private:
    sf::Vector2f patrolPoint;
    float speed = 100.f; // Скорость движения
};

