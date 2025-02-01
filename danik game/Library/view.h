#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
 
sf::View view;


void shakeCamera(float intensity, float& offsetX, float& offsetY) {
        offsetX = offsetX + ((std::rand() % 2001 - 1000) / 1000.0f) * intensity;
        offsetY = offsetY + ((std::rand() % 2001 - 1000) / 1000.0f) * intensity;  
}
void folowCamera(float& x, float& y ,sf::Sprite& sprite){
		if (x < sprite.getPosition().x){
			x+=2;
		}
		if (x > sprite.getPosition().x){
			x-=2;
		}
		if (x + 30 > sprite.getPosition().x){
			x-=3;
			if (x + 60 > sprite.getPosition().x){
			x-=2;
		}
		}
				
		if (x - 30 < sprite.getPosition().x){
			x+=3;
			if (x - 60 < sprite.getPosition().x){
			x+=2;
		}
		}
		if (y < sprite.getPosition().y){
			y+=2;
		}
		if (y > sprite.getPosition().y){
			y-=2;
		}
		if (y + 30 > sprite.getPosition().y){
			y-=3;
		}
		if (y - 30 < sprite.getPosition().y){
			y+=3;
		}
}
void getplayercoordinateforview(bool Shake , float x,float y) { 
	
	if(Shake == true){
		
	}
    view.setSize(1200, 720);	
	view.setCenter(x, y);
}

