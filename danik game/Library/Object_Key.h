#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "Animation.h"
class GameObject {
public:
    GameObject(float x, float y, float scale = 1.0f);

    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    sf::Vector2f getPosition() const;

    void render(sf::RenderWindow& window) const;
    void update(float deltaTime);

private:
    sf::Sprite sprite;
    float baseY;      // ������� Y-���������� ��� �����������
    float time = 0.0f; // ����� ��� ��������
    Animation rotatingAnim;
    
};

GameObject::GameObject(float x, float y, float scale) 
    : baseY(y) , rotatingAnim("GameObjects/key/key.png", sprite, 4) {
    sprite.setPosition(x, y);
    rotatingAnim.changeAnimationOn(sprite);
    sprite.setScale(scale, scale);
    
}

void GameObject::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    baseY = y; // ��������� ������� ����������
}

void GameObject::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

sf::Vector2f GameObject::getPosition() const {
    return sprite.getPosition();
}

void GameObject::render(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void GameObject::update(float deltaTime) {
    // ����������� �����-����
    rotatingAnim.updateAnimation(sprite);
    time += deltaTime;
    float offsetY = std::sin(time * 3.0f) * 5.0f; // ��������� �����������
    sprite.setPosition(sprite.getPosition().x, baseY + offsetY);
    
}
