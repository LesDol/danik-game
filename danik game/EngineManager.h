#include <SFML/Graphics.hpp>
#include <iostream>
#include<locale>
#include<sstream>
#include<string>
#include <vector>
#include<windows.h> 




#include "Library/view.h" 
#include "Library/map.h"
#include "Library/Zone.h"
#include "Library/AIenemy.h"
#include "Library/GameObject.h"

using namespace std;
using namespace sf; 
/////// Зона которая реагирует на вхождение в нее игрока 

/////// Зона которая реагирует на вхождение в нее игрока 

/////PARALAX

/////Функция для подсчета количества кадров в текстуре
sf::Vector2f getAspectRatio(const sf::Texture& texture,float& aspectRatio){
    sf::Vector2u size = texture.getSize();
    aspectRatio = static_cast<float>(size.y) / size.x;
    return sf::Vector2f(aspectRatio, 1.0f);
}
/////Булевая Функция для проверки коллизиии
bool checkSpriteOverlap(sf::Sprite playerSprite, std::vector<sf::Sprite> otherSprites) {
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

    for (const sf::Sprite& otherSprite : otherSprites) {
        sf::FloatRect otherBounds = otherSprite.getGlobalBounds();

        if (playerBounds.intersects(otherBounds)) {
            return true;
        }
    }
    
    return false; 
}
/////Булевая Функция для проверки коллизиии
bool checkSprite(sf::Sprite playerSprite, sf::Sprite otherSprite) {
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
    sf::FloatRect otherBounds = otherSprite.getGlobalBounds();
    if (playerBounds.intersects(otherBounds)) {
        return true;
    }
    return false;
}

sf::FloatRect getViewBounds(const sf::View& view) {
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f topLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
    return sf::FloatRect(topLeft, viewSize);
}

// Проверка видимости объекта
bool isVisible(const sf::FloatRect& bounds, const sf::FloatRect& viewBounds) {
    return bounds.intersects(viewBounds);
}

// Фильтрация видимых объектов
std::vector<const sf::Sprite*> getVisibleObjects(const std::vector<sf::Sprite>& objects, const sf::View& view) {
    sf::FloatRect viewBounds = getViewBounds(view);
    std::vector<const sf::Sprite*> visibleObjects;

    for (const auto& obj : objects) {
        if (isVisible(obj.getGlobalBounds(), viewBounds)) {
            visibleObjects.push_back(&obj);
        }
    }

    return visibleObjects;
}

// Отрисовка только видимых объектов
void renderVisibleObjects(sf::RenderWindow& window, const std::vector<sf::Sprite>& objects, const sf::View& view) {
    auto visibleObjects = getVisibleObjects(objects, view);
    for (const auto* obj : visibleObjects) {
        window.draw(*obj);
    }
}

void renderGameObjects(sf::RenderWindow& window, sf::View& view, 
                       const std::vector<sf::Sprite>& obstacleSprites,
                       const std::vector<sf::Sprite>& coins,
                       const std::vector<sf::Sprite>& enemies) {
    // Устанавливаем текущий вид
    window.setView(view);

    // Отрисовка препятствий
    renderVisibleObjects(window, obstacleSprites, view);

    // Отрисовка монет
    renderVisibleObjects(window, coins, view);

    // Отрисовка врагов
    renderVisibleObjects(window, enemies, view);
}

//Функции

//Slime


//Slime
