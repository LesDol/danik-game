#include <SFML/Graphics.hpp>

class Enemy {
public:
	Sprite sprite;
    Enemy(float startX, float startY) {
        shape.setPosition(startX, startY);
        sprite.setPosition(startX, startY);
        Texture texture;
        texture.loadFromFile("animation/slime.gif");
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0,0,50,50));
        shape.setSize(sf::Vector2f(50, 50)); // ??????? ?????? ????? ?? ?????? ??????????
        shape.setFillColor(sf::Color::Red); // ??????? ???? ????? ?? ?????? ??????????
        speed = 2.0f; // ??????? ???????? ????? ?? ?????? ??????????
    }

    void update(sf::Vector2f playerPosition) {
        sf::Vector2f direction = playerPosition - shape.getPosition();
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;

        shape.move(direction.x * speed,0);
        sprite.move(direction.x * speed,0);
    }
    void checkSpriteOverlap(sf::Sprite playerSprite, std::vector<sf::Sprite> otherSprites) {
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

    for (const sf::Sprite& otherSprite : otherSprites) {
        sf::FloatRect otherBounds = otherSprite.getGlobalBounds();

        
                if (playerBounds.intersects(otherBounds)) {
          shape.move(0,-7);
          sprite.move(0,-7);
        }

    }
    
    
}
    void draw(sf::RenderWindow& window) {
//        window.draw(shape);
    }

private:
    sf::RectangleShape shape;
    float speed;
};
