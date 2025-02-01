#ifndef AIENEMY_H
#define AIENEMY_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Animation.h"
#include <vector>
int cool = 0;
class AIEnemy {
public:
    AIEnemy(float x, float y, float patrolDistance);
    void update(float deltaTime, const Sprite& sprite, const std::vector<sf::Sprite>& groundSprites, bool& AttackEnemy ,  bool& AttackPlayer);
    void render(sf::RenderWindow& window) const;

    void setScale(float x, float y);
    sf::Vector2f getPosition() const;
    bool checkCollision(const sf::FloatRect& playerBounds) const;
    void setTexture(const sf::Texture& texture);
    void setSpeed(float speed);
    void setPosition(float AddposX, float AddposY);
    bool checkDead();

private:
	    const sf::Sprite& getSprite() const {
        return sprite;
    }
	void handlePlayerCollision(const sf::FloatRect& playerBounds, bool& AttackEnemy,  bool& AttackPlayer) ;
    void applyGravity(float deltaTime);
    void checkPlayerInRange(const sf::Vector2f& playerPosition);
    void patrol(float deltaTime, const sf::Vector2f& playerPosition);
    void checkGroundCollision(const std::vector<sf::Sprite>& groundSprites);
    void move(float deltaTime);
   
//	sf::RectangleShape collisionHorizontal;
//    
//    sf::RectangleShape collisionVertical;
    
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float patrolDistance;
    float zoneRadius;
    int health = 1;
    bool movingRight;
    bool isPlayerInRange;
    bool onGround;
    bool isLive  = true ;
    bool finalDie  = false ;
    int dieframe = 0;
    float sizeX , sizeY;
    sf::Clock patrolTimer;
    float gravity = 1.f;       // ��������� �������
    float maxFallSpeed = 10.f; // ������������ �������� �������
  
	
    sf::Sprite sprite;
    
    Animation walkAnimation;
    Animation idleAnimation;
    Animation deadAimation;
    
};


//      walkAnimation("EnemySprites/Slime/FreeSlime/slime_run.png", sprite, 4), 
//      idleAnimation("EnemySprites/Slime/FreeSlime/slime_idle.png", sprite, 4),
//      deadAimation("EnemySprites/Slime/FreeSlime/slime_die.png", sprite, 4)

AIEnemy::AIEnemy(float x, float y, float patrolDistance)
    : position(x, y), patrolDistance(patrolDistance), movingRight(true), isPlayerInRange(false), onGround(false), speed(50.f),
      walkAnimation("EnemySprites/Slime/FreeSlime/slime_run.png", sprite, 4), 
      idleAnimation("EnemySprites/Slime/FreeSlime/slime_idle.png", sprite, 4),
      deadAimation("EnemySprites/Slime/FreeSlime/slime_die.png", sprite, 4)
{
    velocity = sf::Vector2f(0.f, 0.f);
    zoneRadius = 150.f; 
    patrolTimer.restart();
    walkAnimation.changeAnimationOn(sprite);
    
//    collisionHorizontal.setFillColor(sf::Color::Blue);
//    collisionHorizontal.setSize(sf::Vector2f(75, 50));
//    collisionHorizontal.setPosition(x,y);
//    
//    collisionVertical.setFillColor(sf::Color::Red);
//    collisionVertical.setSize(sf::Vector2f(50, 50));
//    collisionVertical.setPosition(x,y);
	}

void AIEnemy::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void AIEnemy::update(float deltaTime, const Sprite& spritePlayer, const std::vector<sf::Sprite>& groundSprites,bool& AttackEnemy ,  bool& AttackPlayer) {
    //if(isLive){
	
    if(!checkDead()){
    	
	applyGravity(deltaTime);
	checkPlayerInRange(spritePlayer.getPosition());
    patrol(deltaTime, spritePlayer.getPosition());
    checkGroundCollision(groundSprites); // ???????? ??????? ????????
    move(deltaTime);
    handlePlayerCollision(spritePlayer.getGlobalBounds(), AttackEnemy, AttackPlayer);
    //checkLive();

    // ����������, ����� �������� ������������
    if (std::abs(velocity.x) > 0.1f || std::abs(velocity.x) < -0.1f) {
        // ���� ���� ��������, ���������� �������� ������
        walkAnimation.updateAnimation(sprite);
    } else {
        // ���� ���� �����, ���������� �������� ��������
        idleAnimation.updateAnimation(sprite);
    }
    
    

	}else{
		if(isLive){
			deadAimation.changeAnimationOn(sprite);
			isLive = false;
		}else{
		deadAimation.updateAnimationFinish(sprite);	
		}
				
		}

		
	
	


}


void AIEnemy::applyGravity(float deltaTime) {
    if (!onGround) {
        velocity.y += gravity * deltaTime; // ����������� �������� �������
        if (velocity.y > maxFallSpeed) {
            velocity.y = maxFallSpeed; // ����������� �������� �������
        }
    } else {
        velocity.y = 0; // �������� �������� ��� �������� � �����
    }
    sprite.move(0, velocity.y); // ��������� ��������
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

//        if (newMovingRight != movingRight) {
//            // ����� �����������, ������� ������
//            float offset = sprite.getGlobalBounds().width;
//            position.x += newMovingRight ? -offset : offset;
//            sprite.setPosition(position);
//            movingRight = newMovingRight; // ��������� �����������
//        }

//        velocity.x = newVelocityX;
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
    enemyBounds.top -= 17.f; // ��������� �������� �� 17 �������� �����
    onGround = false;

    for (const auto& groundSprite : groundSprites) {
        sf::FloatRect groundBounds = groundSprite.getGlobalBounds();

        // �������� �� ���������� �� �����
        if (groundBounds.intersects(enemyBounds) && 
            enemyBounds.top + enemyBounds.height <= groundBounds.top + 5.f) {
            onGround = true;
            sprite.setPosition(sprite.getPosition().x, groundBounds.top - (enemyBounds.height - 17.f));
            break;
        }

        // �������� �� ������������ �� �����������
        if (groundBounds.intersects(enemyBounds)) {
            if (enemyBounds.left < groundBounds.left && 
                enemyBounds.left + enemyBounds.width > groundBounds.left) {
                // ������������ � ������ �������� �����������
                sprite.setPosition(groundBounds.left - enemyBounds.width, sprite.getPosition().y);
            } else if (enemyBounds.left > groundBounds.left && 
                       enemyBounds.left < groundBounds.left + groundBounds.width) {
                // ������������ � ����� �������� �����������
                sprite.setPosition(groundBounds.left + groundBounds.width, sprite.getPosition().y);
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


void AIEnemy::handlePlayerCollision(const sf::FloatRect& playerBounds, bool& AttackEnemy ,  bool& AttackPlayer) {
    sf::FloatRect enemyBounds = sprite.getGlobalBounds();

    if (enemyBounds.intersects(playerBounds)) {
        float playerBottom = playerBounds.top + playerBounds.height;
        float enemyBottom = enemyBounds.top + enemyBounds.height;

//        if (playerBounds.left  + playerBounds.width > enemyBounds.left &&
//            playerBounds.left < enemyBounds.left + enemyBounds.width) {
            if (playerBottom - 44 <= enemyBounds.top + 15) {               
                health -= 1;  
                AttackPlayer = true;
            } else {  

                AttackEnemy = true;
            }
       // }
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
	
//    window.draw(collisionHorizontal);
//    window.draw(collisionVertical);
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
//    collisionHorizontal.setPosition(AddposX, AddposY);
//    collisionVertical.setPosition(AddposX, AddposY);
}
bool AIEnemy::checkDead(){
	if(health == 0){
	

	return true;
	}
	return false;
}

#endif // AIENEMY_H

