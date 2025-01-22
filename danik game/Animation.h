#include <SFML/Graphics.hpp>
#include <string>

class Animation {
public:
    Animation(const std::string& nameAnimation, sf::Sprite& sprite, int delayFrameRate);
    void updateAnimation(sf::Sprite& sprite);
    void changeAnimationOn(sf::Sprite& sprite);

private:
    int numFrames;
    float frameHeight;
    float frameWidth;
    float currentFrame;
    int delay;
    int delayFrame;
    sf::Texture texture;
};

Animation::Animation(const std::string& nameAnimation, sf::Sprite& sprite, int delayFrameRate) {
    if (!texture.loadFromFile(nameAnimation)) {
        // Обработка ошибки загрузки текстуры
    }
    delay = delayFrameRate;
    delayFrame = 0;
    currentFrame = 0;
    frameHeight = texture.getSize().y;
    numFrames = static_cast<int>(texture.getSize().x) / static_cast<int>(frameHeight); // Используем правильное деление
    frameWidth = texture.getSize().x / numFrames;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
}

void Animation::updateAnimation(sf::Sprite& sprite) {
	delayFrame++;
	if(delay < delayFrame){
	currentFrame = static_cast<int>(currentFrame + 1) % numFrames;
    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));	
    delayFrame = 0;
	}

}
void Animation::changeAnimationOn(sf::Sprite& sprite){
	sprite.setTexture(texture);
	currentFrame = 0;
	sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
}
