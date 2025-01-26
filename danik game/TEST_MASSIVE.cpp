#include <SFML/Graphics.hpp>
#include <vector>

class GameObject {
public:
    GameObject(const sf::Texture& texture, float x, float y, float scale = 1.0f);

    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);
    sf::Vector2f getPosition() const;

    void render(sf::RenderWindow& window) const;

private:
    sf::Sprite sprite;
};
GameObject::GameObject(const sf::Texture& texture, float x, float y, float scale) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
}

void GameObject::setPosition(float x, float y) {
    sprite.setPosition(x, y);
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
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "GameObject Example");

    // Загружаем текстуру
    sf::Texture texture;
    if (!texture.loadFromFile("animation/stop_right.png")) {
        return -1; // Ошибка загрузки текстуры
    }

    // Создаём массив игровых объектов
    std::vector<GameObject> gameObjects;
    for (int i = 0; i < 5; ++i) {
        gameObjects.emplace_back(texture, i * 100.f, 300.f,0.5);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Отрисовка
        window.clear();
        for (const auto& obj : gameObjects) {
            obj.render(window);
        }
        window.display();
    }

    return 0;
}
