#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class GameObject {
public:
    GameObject(float x, float y, float scale = 1.0f);

    virtual void setPosition(float x, float y);
    virtual void move(float offsetX, float offsetY);
    virtual sf::Vector2f getPosition() const;

    virtual void render(sf::RenderWindow& window) const;
    virtual void update(float deltaTime);

    virtual ~GameObject() = default;

protected:
    sf::Sprite sprite;
    float baseY;       // Базовая Y-координата для покачивания
    float time = 0.0f; // Время для анимации
};

GameObject::GameObject(float x, float y, float scale)
    : baseY(y) {
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
}

void GameObject::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    baseY = y; // Обновляем базовую координату
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
    // Базовое поведение (может быть пустым)
}

// Наследуемый класс Key
class Key : public GameObject {
public:
    Key(float x, float y, float scale = 1.0f);

    void update(float deltaTime, const sf::Sprite& player); // ?????????? ? ?????? ??????
    bool collect(const sf::FloatRect& playerBounds); // ???????? ?? ???? ?????

    void render(sf::RenderWindow& window) const override;

private:
    Animation rotatingAnim;
    bool isCollected = false;
};

Key::Key(float x, float y, float scale)
    : GameObject(x, y, scale),
      rotatingAnim("GameObjects/key/key.png", sprite, 4) {
    rotatingAnim.changeAnimationOn(sprite);
}

void Key::update(float deltaTime, const sf::Sprite& player) {
    if (!isCollected) {
        rotatingAnim.updateAnimation(sprite);

        // ??????????? ?????-????
        time += deltaTime;
        float offsetY = std::sin(time * 3.0f) * 5.0f;
        sprite.setPosition(sprite.getPosition().x, baseY + offsetY);

        // ????????? ?????????????? ? ???????
        if (collect(player.getGlobalBounds())) {
            isCollected = true; // ???????? ????
        }
    }
}

bool Key::collect(const sf::FloatRect& playerBounds) {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

void Key::render(sf::RenderWindow& window) const {
    if (!isCollected) {
        window.draw(sprite);
    }
}
