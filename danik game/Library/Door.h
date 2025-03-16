#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Door {
private:
    sf::Text finishText;
    bool levelFinished = false;
    sf::RectangleShape triggerZone;
    sf::Text messageText;
    sf::Font font;
    sf::Sprite doorSprite;
    bool isOpen = false;
    int requiredKeys;
    int* playerKeys;
    int SizeX , SizeY;

public:
    Door(float x, float y, int requiredKeys, int* playerKeys, sf::Texture& doorTexture, sf::Font& font) : requiredKeys(requiredKeys), playerKeys(playerKeys) {
        doorSprite.setTexture(doorTexture);
        doorSprite.setTextureRect(sf::IntRect(0, 0, doorTexture.getSize().x / 2, doorTexture.getSize().y));
        doorSprite.setScale(0.3,0.3);
        doorSprite.setPosition(x, y);
        SizeX =doorTexture.getSize().x / 2 ;
        SizeY = doorTexture.getSize().y;
        
        triggerZone.setSize(sf::Vector2f(240, 300));
        triggerZone.setPosition(x - 70, y - 100);
        triggerZone.setFillColor(sf::Color(255, 255, 255, 50));
        
        this->font = font;
        finishText.setFont(this->font);
        finishText.setCharacterSize(24);
        finishText.setOutlineThickness(2.0f);
        finishText.setFillColor(sf::Color::White);
        finishText.setString("Нажмите Enter, чтобы завершить уровень");
        messageText.setFont(this->font);
        messageText.setCharacterSize(24);
        messageText.setOutlineThickness(2.0f);
        messageText.setFillColor(sf::Color::White);
        messageText.setString("Соберите 3 ключа, чтобы открыть дверь");
    }
    
    void setPosition(float x, float y) {
        doorSprite.setPosition(x, y);
        triggerZone.setPosition(x - 50, y - 100);
        messageText.setPosition(x, y);
    }
    
    
    void update(const sf::Vector2f& playerPos, sf::RenderWindow& window) {
        if (doorSprite.getGlobalBounds().contains(playerPos)) {
            if (isOpen && !levelFinished) {
                finishText.setPosition(playerPos.x, playerPos.y - 50);
                window.draw(finishText);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    levelFinished = true;
                }
            }
            if (!isOpen && *playerKeys < requiredKeys) {
                messageText.setPosition(playerPos.x, playerPos.y - 30);
            } else if (!isOpen && *playerKeys >= requiredKeys) {
                isOpen = true;
                doorSprite.setTextureRect(sf::IntRect(SizeX, 0, SizeX, SizeY)); 
            }
        }
    }
    
    void draw(sf::RenderWindow& window) {
    
        window.draw(doorSprite);
        //window.draw(triggerZone);
        if (!isOpen && *playerKeys < requiredKeys) {
            window.draw(messageText);
        }    
		if (isOpen && !levelFinished) {
            window.draw(finishText);
        }
        
    }
    
    bool hasCollision() const {
        return !isOpen && !levelFinished;
    }
    bool levelFinish() const {
        return levelFinished;
    }
};


