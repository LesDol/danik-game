#ifndef AIENEMY_H
#define AIENEMY_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Animation.h"
#include <vector>

class AIEnemy {
public:
    AIEnemy(float x, float y, float patrolDistance);
    void update(float deltaTime, const Sprite& sprite, const std::vector<sf::Sprite>& groundSprites, bool& AttackPlayer);
    void render(sf::RenderWindow& window) const;

    void setScale(float x, float y);
    sf::Vector2f getPosition() const;
    bool checkCollision(const sf::FloatRect& playerBounds) const;
    void setTexture(const sf::Texture& texture);
    void setSpeed(float speed);
    void setPosition(float AddposX, float AddposY);

private:
	    const sf::Sprite& getSprite() const {
        return sprite;
    }
	void handlePlayerCollision(const sf::FloatRect& playerBounds, bool& AttackEnemy) ;
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
    int health = 3;
    bool movingRight;
    bool isPlayerInRange;
    bool onGround;
    bool isLive  = true ;
    float sizeX , sizeY;
    sf::Clock patrolTimer;
    float gravity = 1.f;       // Ускорение падения
    float maxFallSpeed = 10.f; // Максимальная скорость падения
  
	
    sf::Sprite sprite;
    
    Animation walkAnimation;
    Animation idleAnimation;
    
};




AIEnemy::AIEnemy(float x, float y, float patrolDistance)
    : position(x, y), patrolDistance(patrolDistance), movingRight(true), isPlayerInRange(false), onGround(false), speed(50.f),
      walkAnimation("EnemySprites/Slime/FreeSlime/slime_run.png", sprite, 4), // 10 — ???????? ????? ???????
      idleAnimation("EnemySprites/Slime/FreeSlime/slime_idle.png", sprite, 4) // 15 — ???????? ????? ???????
{
    velocity = sf::Vector2f(0.f, 0.f);
    zoneRadius = 150.f; // ?????? ?????????
    patrolTimer.restart();
    walkAnimation.changeAnimationOn(sprite); // ????????????? ???????? ???????? ?? ?????????
}

void AIEnemy::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void AIEnemy::update(float deltaTime, const Sprite& spritePlayer, const std::vector<sf::Sprite>& groundSprites,bool& AttackPlayer) {
    //if(isLive){
    	
	
	applyGravity(deltaTime);
	checkPlayerInRange(spritePlayer.getPosition());
    patrol(deltaTime, spritePlayer.getPosition());
    checkGroundCollision(groundSprites); // ???????? ??????? ????????
    move(deltaTime);
    handlePlayerCollision(spritePlayer.getGlobalBounds(), AttackPlayer);
    //checkLive();

    // Определяем, какую анимацию использовать
    if (std::abs(velocity.x) > 0.1f || std::abs(velocity.x) < -0.1f) {
        // Если враг движется, используем анимацию ходьбы
        walkAnimation.updateAnimation(sprite);
    } else {
        // Если враг стоит, используем анимацию ожидания
        idleAnimation.updateAnimation(sprite);
    }

}


void AIEnemy::applyGravity(float deltaTime) {
    if (!onGround) {
        velocity.y += gravity * deltaTime; // Увеличиваем скорость падения
        if (velocity.y > maxFallSpeed) {
            velocity.y = maxFallSpeed; // Ограничение скорости падения
        }
    } else {
        velocity.y = 0; // Обнуляем скорость при контакте с землёй
    }

    sprite.move(0, velocity.y); // Применяем смещение
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

//        if (newMovingRight != movingRight) {
//            // Смена направления, смещаем спрайт
//            float offset = sprite.getGlobalBounds().width;
//            position.x += newMovingRight ? -offset : offset;
//            sprite.setPosition(position);
//            movingRight = newMovingRight; // Обновляем направление
//        }

//        velocity.x = newVelocityX;
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
    enemyBounds.top -= 17.f; // Поднимаем проверку на 17 пикселей вверх
    onGround = false;

    for (const auto& groundSprite : groundSprites) {
        sf::FloatRect groundBounds = groundSprite.getGlobalBounds();

        // Проверка на нахождение на земле
        if (groundBounds.intersects(enemyBounds) && 
            enemyBounds.top + enemyBounds.height <= groundBounds.top + 5.f) {
            onGround = true;
            sprite.setPosition(sprite.getPosition().x, groundBounds.top - (enemyBounds.height - 17.f));
            break;
        }

        // Проверка на столкновение по горизонтали
        if (groundBounds.intersects(enemyBounds)) {
            if (enemyBounds.left < groundBounds.left && 
                enemyBounds.left + enemyBounds.width > groundBounds.left) {
                // Столкновение с правой стороной препятствия
                sprite.setPosition(groundBounds.left - enemyBounds.width, sprite.getPosition().y);
            } else if (enemyBounds.left > groundBounds.left && 
                       enemyBounds.left < groundBounds.left + groundBounds.width) {
                // Столкновение с левой стороной препятствия
                sprite.setPosition(groundBounds.left + groundBounds.width, sprite.getPosition().y);
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


void AIEnemy::handlePlayerCollision(const sf::FloatRect& playerBounds, bool& AttackEnemy) {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();

    if (enemyBounds.intersects(playerBounds)) {
        float playerBottom = playerBounds.top + playerBounds.height;
        float enemyBottom = enemyBounds.top + enemyBounds.height;

        if (playerBounds.left  + playerBounds.width > enemyBounds.left &&
            playerBounds.left < enemyBounds.left + enemyBounds.width) {
            if (playerBottom <= enemyBounds.top + 5.f) {  

//                velocity.y = -200.f; 
//                movingRight = !movingRight; 
//                
//
//                sprite.setColor(sf::Color::White);
//                sf::sleep(sf::milliseconds(50));
//                sprite.setColor(sf::Color::Red);
//                sf::sleep(sf::milliseconds(50));
//                sprite.setColor(sf::Color::White);
//                
//                health -= 1;  
            } else {  

                AttackEnemy = true;
            }
        }
    }
}



sf::Vector2f AIEnemy::getPosition() const {
    return position;
}

bool AIEnemy::checkCollision(const sf::FloatRect& playerBounds) const {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();
    return enemyBounds.intersects(playerBounds);
}

void AIEnemy::render(sf::RenderWindow& window) const{
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
void AIEnemy::setPosition(float AddposX, float AddposY) {
    sprite.setPosition(AddposX, AddposY);
}

#endif // AIENEMY_H

