#include <SFML/Graphics.hpp>
#include <iostream>
#include<locale>
#include<sstream>
#include<string>
#include "view.h" 
#include "map.h"

#include<windows.h>  
using namespace std;
using namespace sf;
/////// Зона которая реагирует на вхождение в нее игрока 
struct TriggerZone {
    sf::RectangleShape shape;
    sf::Text text;
    bool isPlayerInside = false;

    TriggerZone(sf::Vector2f position, sf::Vector2f size, const sf::Font& font, const std::string& message) {
        // Инициализация формы зоны
        shape.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(sf::Color(255, 0, 0, 100)); // Полупрозрачный красный

        // Инициализация текста
        text.setFont(font);
        text.setString(message);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White); // Белый цвет текста
        text.setOutlineColor(sf::Color::Black); // Чёрная обводка
        text.setOutlineThickness(2);
        text.setPosition(position.x, position.y - 30); // Располагаем текст над зоной
    }

    // Метод проверки вхождения спрайта в зону
    void checkCollision(const sf::Sprite& sprite) {
        isPlayerInside = shape.getGlobalBounds().intersects(sprite.getGlobalBounds());
    }


    // Метод отрисовки зоны и текста
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        if (isPlayerInside) {
            window.draw(text);
        }
    }
};
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
//Функции

//---------------------------------------------------------------------

///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN
int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 720), "SFML Keyboard Input");
    window.setFramerateLimit(45);
    setlocale(LC_ALL, "Russian");
    sf::Clock clock;
     
     ///PARALAX
    int colparalax = 6;
    bool moveParalax =  true;
     
    std::vector<sf::Texture> paralaxTexture(colparalax);
    
    paralaxTexture[0].loadFromFile("Paralax/Free Pixel Art Hill/PNG/Hills Layer 01.png");
    paralaxTexture[1].loadFromFile("Paralax/Free Pixel Art Hill/PNG/Hills Layer 02.png");
    paralaxTexture[2].loadFromFile("Paralax/Free Pixel Art Hill/PNG/Hills Layer 03.png");
    paralaxTexture[3].loadFromFile("Paralax/Free Pixel Art Hill/PNG/Hills Layer 04.png");
    paralaxTexture[4].loadFromFile("Paralax/Free Pixel Art Hill/PNG/Hills Layer 05.png");
    paralaxTexture[5].loadFromFile("Paralax/Free Pixel Art Hill/PNG/Hills Layer 06.png");
    

    
//	std::vector<float> speeds = {10.0f, 5.0f, 1.0f};
//	std::vector<float> sizes = {2.5f, 2.5f, 2.5f}; 

	std::vector<sf::Sprite> paralaxSprite(colparalax);
	std::vector<sf::Sprite> paralaxSprite1(colparalax);
	std::vector<sf::Sprite> paralaxSprite2(colparalax);
	int paralaxPos = -400;
	float paralaxSize = 5;
	for(int i = 0; i < colparalax;i++){
		paralaxSprite[i].setTexture(paralaxTexture[i]);
		paralaxSprite[i].setPosition(1,paralaxPos - (20*(10-i)));
		paralaxSprite[i].setScale(paralaxSize,paralaxSize);
		
		paralaxSprite1[i].setTexture(paralaxTexture[i]);
		paralaxSprite1[i].setPosition(paralaxSprite[i].getGlobalBounds().width ,paralaxPos - (20*(10-i)));
		paralaxSprite1[i].setScale(paralaxSize,paralaxSize);
		
		paralaxSprite2[i].setTexture(paralaxTexture[i]);
		paralaxSprite2[i].setPosition(1 - paralaxSprite[i].getGlobalBounds().width ,paralaxPos - (20*(10-i)));
		paralaxSprite2[i].setScale(paralaxSize,paralaxSize);
	}
	

     ///PARALAX
      
    sf::Time delay = sf::seconds(0.1);
	int coinH=0,g=0,moni=0,mon=0;
	float speedup=20 , speeddown = 0 , frameCoinWidht=(191),frameCoinHeight=171;
    Time time = clock.getElapsedTime();
    ///Шрифт
    sf::Font font; 
    font.loadFromFile("ArialRegular.ttf");
    ///Шрифт
    
    ///-----
    
    ///Текстура монеток
		Texture textureCoin;
        textureCoin.loadFromFile("animation/Daco.png");
    ///Текстура монеток
    
    ///-----
    
    ///Теккст для подсчета монеток
        Text text;
        text.setFont(font);
        text.setCharacterSize(25);
        text.setOutlineThickness(3);
        text.setOutlineColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
        text.setString("0");
    ///Теккст для подсчета монеток
    
    ///-----
        
        
bool money[20];
for(int i = 0; i < 20; i++){
 money[i] = true;	
}  
///-----

///Создание переменных для логики игрока  

sf::Vector2f SpawnPlayerPosition;//переменная для запоминания спавна игрока

int j=0,anim=6,upper=0;
float frame;
bool moveR = false;
bool moveL = false;
bool up = false;
bool upR = true;
bool upL = false;
int n = 3;
float speedPlaer = 7;
Sprite rectangley;
rectangley.setColor(Color(0,0,255));
Sprite rectangley2;
rectangley2.setColor(Color(0,0,255));
Sprite rectangleFall;
rectangleFall.setColor(Color(0,255,0));
Sprite rectangleX;
rectangleX.setColor(Color(0,0,255));


//Массив на именами анимаций
    string file[anim];
    file[0] = "stop_right.png";
    file[1] = "stop_left.png";
    file[2] = "run_right.png";
    file[3] = "run_left.png";
    file[4] = "up_right.png";
    file[5] = "up_left.png";
//Массив на именами анимаций

//----------------

//Загрузка текстур с анимациями персонажа
    int sheet = 0 ;
	Texture texture[anim];
    for(int i=0;i<=anim-1;i++){
    texture[i].loadFromFile("animation/"+file[i]);
    getAspectRatio(texture[sheet],frame);

}
//Загрузка текстур с анимациями персонажа



//Создание спрайта игрока 
    Sprite sprite;
    sprite.setTexture(texture[sheet]);
    sprite.setPosition(1,-50);
    sprite.setScale(2.0f,2.0f);
//Создание спрайта игрока

 
 
///Создание переменных для логики игрока  
	
///-----

Image map_image;

	map_image.loadFromFile("animation/tile.png");///Загрузка тайлсета карты
	Texture obstacleTexture;///создание текстуры тайлсета карты
	obstacleTexture.loadFromImage(map_image);///загрузка тайлсета карты	в спрайты
	
////------	

//// Области для проверки коллзии игрока
	rectangley.setTexture(obstacleTexture);
	rectangley.setTextureRect(IntRect(0, 100, 20, 20));
	rectangley2.setTexture(obstacleTexture);
	rectangley2.setTextureRect(IntRect(0, 100, 20, 80));	
	rectangleX.setTexture(obstacleTexture);
	rectangleX.setTextureRect(IntRect(0, 100,50, 50));
	rectangleFall.setTexture(obstacleTexture);
	rectangleFall.setTextureRect(IntRect(0, 100, 100, 100));
//// Области для проверки коллзии игрока

////------
	
////------	

	std::vector<TriggerZone> triggerZones; // Хранилище для триггерных зон
    std::vector<sf::Sprite> obstacleSprites;// Хранилище для тайлов карты
    
////------ 

///Растановка тайлов карты из текстового массива  
    
 		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++){if((TileMap[i][j] == '0')){
		        sf::Sprite obstacleSprite(obstacleTexture);
        obstacleSprite.setTextureRect(IntRect(0, 100, 100, 35));
        obstacleSprite.setPosition(-100 + j * 100, -300 + i * 145);
        obstacleSprites.push_back(obstacleSprite);}
        if((TileMap[i][j] == 'p')){
        sprite.setPosition(-100 + j * 100, -300 + i * 145);
        SpawnPlayerPosition = Vector2f(-100 + j * 100, -300 + i * 145);
		}
		if((TileMap[i][j] == 's')){
		        sf::Sprite obstacleSprite(obstacleTexture);
        obstacleSprite.setTextureRect(IntRect(0, 100, 100, 145));
        obstacleSprite.setPosition(-100 + j * 100, -300 + i * 145);
        obstacleSprites.push_back(obstacleSprite);
		}
        
                if((TileMap[i][j] == 'g')){
		        sf::Sprite obstacleSprite(obstacleTexture);
        obstacleSprite.setTextureRect(IntRect(0, 100, 100, 35));
        obstacleSprite.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
        obstacleSprites.push_back(obstacleSprite);
		}
                    if (TileMap[i][j] == 'i') { // Создание триггерной зоны
                sf::Vector2f position(-300 + j * 100, -300 + i * 145);
                sf::Vector2f size(300, 145); // Задайте размер триггерной зоны
                triggerZones.emplace_back(position, size,font, "Нажмите E");
            }
  

    }
///Растановка тайлов карты из текстового массива  
    
////------

std::vector<sf::Sprite> sprite1Coin2;// Хранилище для спрайтов монет

for (int i = 0; i < HEIGHT_MAP; i++) {
    for (int j = 0; j < WIDTH_MAP; j++) {
        if (TileMap[i][j] == 'm') {
            sf::Sprite sprite1(textureCoin);
            sprite1.setTextureRect(sf::IntRect((frameCoinWidht*coinH),(0),frameCoinWidht,frameCoinHeight));
            sprite1.setScale(0.2,0.2);
            sprite1.setPosition(-100 + j * 100, -200 + i * 145);
            sprite1Coin2.push_back(sprite1);
        }
    }
}
//Создание страйта монетки
Sprite spriteCoin;
spriteCoin.setScale(0.15,0.15);
spriteCoin.setTexture(textureCoin);
spriteCoin.setPosition(1,-50);
spriteCoin.setTextureRect(sf::IntRect((frameCoinWidht*coinH),(0),frameCoinWidht,frameCoinHeight));
//Создание страйта монетки

//----------------


    getAspectRatio(texture[sheet],frame);
    int time1 = 0,time2 = 0;
    float x,y;    
    x = sprite.getPosition().x;
	y = sprite.getPosition().y;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
			window.close();}
             if (event.type == sf::Event::KeyPressed){
             	if  ((Keyboard::isKeyPressed(Keyboard::Left)) && !up){
				    sheet = 3;
             		getAspectRatio(texture[sheet],frame);
					 sprite.setTexture(texture[sheet]);	
				 }
				 
if ((Keyboard::isKeyPressed(Keyboard::Right)) && !up){
	sheet = 2;
	getAspectRatio(texture[sheet],frame);
	sprite.setTexture(texture[sheet]);
	}
if ((Keyboard::isKeyPressed(Keyboard::Space)) && upR && !up){
	j=0;
	up = true;
	speedup=36;
	sheet = 4;
	getAspectRatio(texture[sheet],frame);
	sprite.setTexture(texture[sheet]);
	}
if ((Keyboard::isKeyPressed(Keyboard::Space)) && upL && !up){
	j=0;
	up = true;
	speedup=36;
	sheet = 5;
	getAspectRatio(texture[sheet],frame);
	sprite.setTexture(texture[sheet]);
	}					 
}
        }
	if  ((Keyboard::isKeyPressed(Keyboard::Left))){

             		sprite.move(-speedPlaer,0);
             		time1 = 0;
             		moveL = true;
             		moveR = false;
  
					upR =  false;
                    upL = true;
                    if(!up ){
						sheet = 3;
						getAspectRatio(texture[sheet],frame);
						sprite.setTexture(texture[sheet]);	
				}
             		
	}else if(time1 == 15 && moveL && !up ){
			time1 = 0;
			j =0 ;
			sheet = 1;
			getAspectRatio(texture[sheet],frame);
			sprite.setTexture(texture[sheet]);
		}else{
		time1++;
		} 
		 
if ((Keyboard::isKeyPressed(Keyboard::Right))){
	sprite.move(speedPlaer,0);
	time1 = 0;
	moveL =  false;
	moveR = true;
	upR = true ;
	upL = false;
	
	if(!up ){
		sheet = 2;
		getAspectRatio(texture[sheet],frame);
		sprite.setTexture(texture[sheet]);	
		}
	}else if(time1 == 15 && moveR && !up){
		time1 = 0;
		j =0 ;
		sheet = 0;
	
		getAspectRatio(texture[sheet],frame);
		sprite.setTexture(texture[sheet]);
		}else{
			time1++;
		} 




       	if(up){
       		upper++;
		   }else{
		   	upper=0;
		   }
		   if(upper<(16) && up){
		   	sprite.move(0,-speedup);
		   	speedup-=2;
		   }	

       		rectangley.setPosition(sprite.getPosition().x+40,sprite.getPosition().y+69);
       			rectangley2.setPosition(sprite.getPosition().x+40,sprite.getPosition().y-11);
       			rectangleX.setPosition(sprite.getPosition().x+25,sprite.getPosition().y+10);
       		rectangleFall.setPosition(sprite.getPosition().x,sprite.getPosition().y+28);
       		
 /// -------  
 
 
 /// ВСЕ ЧТО ЗВЯЗАНО С КОЛЛИЗИЕЙ ////		

    		
       		
    if (!checkSpriteOverlap(rectangley, obstacleSprites)){
    speeddown += 0.4;
	sprite.move(0,speeddown+7);
        }else{
        	
			speeddown = 0;
        	if(upR && frame <= j && up or upR && checkSpriteOverlap(rectangley, obstacleSprites ) && up ){
			up = false;
			j =0 ;
			sheet = 0;
			getAspectRatio(texture[sheet],frame);
			sprite.setTexture(texture[sheet]);	
						}
        	if(upL && frame <= j && up or upL && checkSpriteOverlap(rectangley, obstacleSprites) && up ){
				up = false ;        		
				j = 0 ;
				sheet = 1 ;
				getAspectRatio(texture[sheet],frame);
				sprite.setTexture(texture[sheet]);	
			}

		}

 
//if(j==frame){
//    	j=0;
//	}	
int totalFrames = texture[sheet].getSize().x / 50; 
j = (j + 1) % totalFrames;

	 if (!checkSpriteOverlap(rectangleFall, obstacleSprites) && up && upper>(11) ) {
     j  = 11;
	 }
   
       	sprite.setTextureRect(sf::IntRect(50*j,0,50,50)); // Запуск анимации текстуры персонажа j меняет кадр 
       	
	if (checkSpriteOverlap(rectangley2, obstacleSprites) ){
	sprite.move(0,speedPlaer);
        }
 
 
 ///   Проверка колизии по оси X    
if (checkSpriteOverlap(rectangleX, obstacleSprites)){
	moveParalax = false ; /// запрет на движение паралакса	
	if (moveR){ ///Если персонаж движется в право , то его отталкивает в лево
	sprite.move(-speedPlaer,0);	
	}
	if (moveL){///Если персонаж движется в лево , то его отталкивает в право
	sprite.move(speedPlaer,0);	
	}
  }else{
moveParalax = true ;/// разрешение на движение паралакса	
} 
		
/// ВСЕ ЧТО ЗВЯЗАНО С КОЛЛИЗИЕЙ ////		

/// -------

/// Плавное следдование камеры за игроком , с ускорением , чем дальше камера от игрока тем быстрее она движется
		
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
	/// Плавное следдование камеры за игроком , с ускорением , чем дальше камера от игрока тем быстрее она движется	
		
	/// -------
	
	
	sf::Time elapsed = clock.getElapsedTime();
if (elapsed >= delay)
        {
coinH++;
if(coinH >= 6){
coinH = 0;	
}
        clock.restart();
        }
    sf::Vector2f playerPosition(x, y);
    getplayercoordinateforview(x,y) ;
    spriteCoin.setPosition(x-550 ,y-325);
	text.setPosition(view.getCenter().x-500 , view.getCenter().y-325);
	
	
///---------------------------------------------------	
		
///Отрисовка всей игры

///---------------------------------------------------	

        window.clear(Color(255,255,255));
        
        ///Отрисовка и обработка паралакса

// Переменная для направления движения слоев паралакса
int moveDirection = 0;  // 0 - на месте, -1 - лево, 1 - право

// Проверка направления движения игрока по клавишам
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    moveDirection = -1;  // движение в лево
} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    moveDirection = 1;  // движение в право
} else {
    moveDirection = 0;  // Нет движения
}

// Цикл для обработтки паралакса
for (int i = 0; i < colparalax; i++) {
    float offset = 0.0f;

    float speed = (i - 2) / 1.5f;  // Скорость движения паралакса

    // Проверка есть ли движение персонажа , и в какую сторону он движется
    if (moveDirection == -1) {
        offset = speed;  // Направление движения паралакса
    }
    // Проверка есть ли движение персонажа , и в какую сторону он движется
    else if (moveDirection == 1) {
        offset = -speed;  // Направление движения паралакса
    }

    // Перемещение паралакса
    if(moveParalax){
    paralaxSprite[i].setPosition(paralaxSprite[i].getPosition().x + offset, -400 - (20 * (10 - i)));
    paralaxSprite1[i].setPosition(paralaxSprite1[i].getPosition().x + offset, -400 - (20 * (10 - i)));
    paralaxSprite2[i].setPosition(paralaxSprite2[i].getPosition().x + offset, -400 - (20 * (10 - i)));  	
	}


    // Отрисовка паралакса
    window.draw(paralaxSprite[i]);
    window.draw(paralaxSprite1[i]);
    window.draw(paralaxSprite2[i]);
}

	
        ///Отрисовка и обработка паралакса
        

        window.draw(sprite);

///Отрисовка карты  и ее элементов
        for (const sf::Sprite obstacle : obstacleSprites) {
            window.draw(obstacle);
        }
		    for (auto& trigger : triggerZones) {
			   
        trigger.checkCollision(sprite);// Проверяем зашел ли игрок в зону 
            window.draw(trigger.shape);
        }
        
        

///Отрисовка карты  и ее элементов
		        for ( sf::Sprite sprite1 : sprite1Coin2) {
		        		 if (checkSprite(sprite, sprite1) && money[moni]) {
     money[moni]=false;
     mon++;
     stringstream ss;
     ss << mon;
     string str;
     ss >> str;
	 text.setString(str);}
		        	sprite1.setTextureRect(sf::IntRect((frameCoinWidht*coinH),(0),frameCoinWidht,frameCoinHeight));
		        	if(money[moni]){
		      window.draw(sprite1);	
					}
            moni++;
        } 
		    moni=0; 
            spriteCoin.setTextureRect(sf::IntRect((frameCoinWidht*coinH),(0),frameCoinWidht,frameCoinHeight));
            window.draw(spriteCoin);
	  window.draw(text);
      window.setView(view);
      
      /////Доработка 
      
      if(sprite.getPosition().y > 1200){//Если игрок падает ниже этой границы , то его телепортирует на точку спавна
      	sprite.setPosition(SpawnPlayerPosition);
	  }
      
      ////Доработка 

        window.display();
    }

    return 0;
}
