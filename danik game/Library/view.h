#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;
 
sf::View view;

void getplayercoordinateforview(float x,float y) { 
	
view.setSize(1200, 720);	
	view.setCenter(x, y);
 	
}

