#include <SFML/Graphics.hpp> 
#include "EngineManager.h"
using namespace std;
using namespace sf;

//---------------------------------------------------------------------

///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN///MAIN
int main()
{
	
    sf::RenderWindow window(sf::VideoMode(1200, 720), "SFML Keyboard Input");
    window.setFramerateLimit(45);
    setlocale(LC_ALL, "Russian");
    sf::Clock clock;
     
     std::srand(static_cast<unsigned>(std::time(nullptr)));
     
     //UI
     
         ///Шрифт
    sf::Font font; 
    font.loadFromFile("ArialRegular.ttf");
    int coolDown;
    ///Шрифт
     
     Sprite keyUI;
     Texture keyUITexture;
     keyUITexture.loadFromFile("GameObjects/key/keyUI.png");
     keyUI.setTexture(keyUITexture);
     keyUI.setScale(1.5,1.5);
     Text keyUItext;
     keyUItext.setFont(font);
     keyUItext.setCharacterSize(25);
     keyUItext.setOutlineThickness(3);
     keyUItext.setOutlineColor(sf::Color::Black);
     keyUItext.setFillColor(sf::Color::White);
     keyUItext.setString("0");
     int healnum = 20;
     Sprite heal[healnum];
     Texture healTexture;
     healTexture.loadFromFile("animation/heal.png");
     for(int i = 0 ; i < healnum; i++ ){
     heal[i].setTexture(healTexture);
     heal[i].setScale(0.03,0.03);
	 }
	int CoutHeal = healnum;
	int attackCooldown = 0; 
	
	//UI

sf::Vector2i screenPos(50, 25); // Позиция элемента на экране
sf::Vector2i coutMoneyPos(50, 125);

// Конвертируем экранные координаты в мировые

     
     
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
	std::vector<sf::Sprite> paralaxSprite3(colparalax);
	std::vector<sf::Sprite> paralaxSprite4(colparalax);
	int paralaxPos = -350;
	int paralaxDiferent = 20;
	float paralaxSize = 5;
for(int i = 0; i < colparalax; i++) { 
    paralaxSprite[i].setTexture(paralaxTexture[i]);
    paralaxSprite[i].setPosition(-700, paralaxPos - (paralaxDiferent * (10 - i)));
    paralaxSprite[i].setScale(paralaxSize, paralaxSize);

    float width = paralaxSprite[i].getGlobalBounds().width;

    paralaxSprite1[i].setTexture(paralaxTexture[i]);
    paralaxSprite1[i].setPosition(paralaxSprite[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (10 - i)));
    paralaxSprite1[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite2[i].setTexture(paralaxTexture[i]);
    paralaxSprite2[i].setPosition(paralaxSprite1[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (10 - i)));
    paralaxSprite2[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite3[i].setTexture(paralaxTexture[i]);
    paralaxSprite3[i].setPosition(paralaxSprite2[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (10 - i)));
    paralaxSprite3[i].setScale(paralaxSize, paralaxSize);
    
    paralaxSprite4[i].setTexture(paralaxTexture[i]);
    paralaxSprite4[i].setPosition(paralaxSprite3[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (10 - i)));
    paralaxSprite4[i].setScale(paralaxSize, paralaxSize);
}
	

     ///PARALAX
      
    sf::Time delay = sf::seconds(0.1);
	int coinH=0,g=0,moni=0,mon=0;
	float speedup=20 , speeddown = 0 , frameCoinWidht=(191),frameCoinHeight=171;
    Time time = clock.getElapsedTime();

    
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
    bool AttackPlayer = false;
    bool AttackEnemy = false;

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


    std::vector<sf::Sprite> obstacleSprites;// Хранилище для тайлов карты

////------ 
	int maxZone = 3;// Переменная для хранения максимального числа возможных зон
// Передаём ресурсы в объекты
InteractionZone* interactionZones = new InteractionZone[3]{
    InteractionZone(&window, {100.0f, 100.0f}, {400.0f, 150.0f}),
    InteractionZone(&window, {300.0f, 100.0f}, {400.0f, 150.0f}),
    InteractionZone(&window, {500.0f, 100.0f}, {400.0f, 150.0f})
};
    int countZones = 0;// переменная для хранения количества раставленных на карте зон , больше 3 нельзя 
    
std::vector<sf::Sprite> spriteZone(maxZone);//Создаем двери

for (int i = 0; i < maxZone; ++i) {
    spriteZone[i] = interactionZones[i].getZoneSprite(); // Копирую спрайт "Двери" объекта, так как я не смог реализовать коллизию двери 
}
           

///Растановка тайлов карты из текстового массива  
    //std::vector<AIEnemy> enemies; // Хранение врагов

AIEnemy enemies1(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies2(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies3(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies4(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies5(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies6(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies7(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies8(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies9(-100 + 4 * 100, -300 + 2 * -145, 150.f);
AIEnemy enemies10(-100 + 4 * 100, -300 + 2 * -145, 150.f);

int coutEnemy = 0 ; 

Key key(400.f, 300.f, 2.0f);
Key key2(400.f, 300.f, 2.0f);
Key key3(400.f, 300.f, 2.0f);

int coutKey = 0;

int haveKey = 0;            

for (int i = 0; i < HEIGHT_MAP; i++) {
    for (int j = 0; j < WIDTH_MAP; j++) {
        if ((TileMap[i][j] == '0')) {
            sf::Sprite obstacleSprite(obstacleTexture);
            obstacleSprite.setTextureRect(IntRect(0, 100, 100, 35));
            obstacleSprite.setPosition(-100 + j * 100, -300 + i * 145);
            obstacleSprites.push_back(obstacleSprite);
        }
        if ((TileMap[i][j] == 'p')) {
            sprite.setPosition(-100 + j * 100, -300 + i * 145);
            SpawnPlayerPosition = Vector2f(-100 + j * 100, -300 + i * 145);
        }
        if ((TileMap[i][j] == 's')) {
            sf::Sprite obstacleSprite(obstacleTexture);
            obstacleSprite.setTextureRect(IntRect(0, 100, 100, 145));
            obstacleSprite.setPosition(-100 + j * 100, -300 + i * 145);
            obstacleSprites.push_back(obstacleSprite);
        }
        if ((TileMap[i][j] == 'g')) {
            sf::Sprite obstacleSprite(obstacleTexture);
            obstacleSprite.setTextureRect(IntRect(0, 100, 100, 35));
            obstacleSprite.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
            obstacleSprites.push_back(obstacleSprite);
        }
        if (TileMap[i][j] == 'i') { // Создание триггерной зоны
            interactionZones[countZones].setPosition(
                {static_cast<float>(-100 + j * 100), static_cast<float>(-300 + i * 145)});
            countZones++;
        }
        if (TileMap[i][j] == 'e') { // Создание врага    
		coutEnemy++;    
switch (coutEnemy) {
    case 1:
       enemies1.setScale(2.5,2.5);
       enemies1.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
        break;
    case 2:
        enemies2.setScale(2.5,2.5);
       enemies2.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
        break;
    case 3:
       enemies3.setScale(2.5,2.5);
       enemies3.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
        break;
    case 4:
       enemies4.setScale(2.5,2.5);
       enemies4.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;
    case 5:
       enemies5.setScale(2.5,2.5);
       enemies5.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;
    case 6:
       enemies6.setScale(2.5,2.5);
       enemies6.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;
        case 7:
       enemies7.setScale(2.5,2.5);
       enemies7.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;
        case 8:
       enemies8.setScale(2.5,2.5);
       enemies8.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;
        case 9:
       enemies9.setScale(2.5,2.5);
       enemies9.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;
        case 10:
       enemies10.setScale(2.5,2.5);
       enemies10.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
    break;

    default:
      
        break;
}
        }
    if(TileMap[i][j] == 'k'){
    	
coutKey++;    
switch (coutKey) {
	    case 1:
		key.setPosition(-80 + j * 100, -300 + (i * 145) + 80);
        break;
        case 2:
		key2.setPosition(-80 + j * 100, -300 + (i * 145) + 80);
        break;
        case 3:
		key3.setPosition(-80 + j * 100, -300 + (i * 145) + 80);
        break;
        default :
        	
        break;	
	}
		}
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
    	float deltaTime = 0.022f;
    	
    	
    	
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
            for (int i = 0; i < maxZone; ++i) {
                interactionZones[i].handleEvent(event);
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


for (int i = 0; i < maxZone; ++i) {
    spriteZone[i].setPosition(interactionZones[i].getZoneSprite().getPosition());  
	// Короче , это кастыль который передает значение позиции двери заранее скопированному спрайту этой же двери. 
	//Почему то , когда таких объектов несколько , то тогда класс не может нормально передать значение спрайта двери, что делает невозможным ее коллизию 
}


if (checkSpriteOverlap(rectangleX, spriteZone)){
	moveParalax = false ; /// запрет на движение паралакса	
	if (moveR){ ///Если персонаж движется в право , то его отталкивает в лево
	sprite.move(-speedPlaer,0);	
	}
	if (moveL){///Если персонаж движется в лево , то его отталкивает в право
	sprite.move(speedPlaer,0);	
	}
  }else{
	
} 
//	
//}
	
/// ВСЕ ЧТО ЗВЯЗАНО С КОЛЛИЗИЕЙ ////		

/// -------

/// Плавное следдование камеры за игроком , с ускорением , чем дальше камера от игрока тем быстрее она движется
		

		
if (AttackPlayer  == true  && CoutHeal == 0 ) {
	AttackPlayer = false;
}		
	folowCamera(x,y,sprite);
if ((attackCooldown/50 )> 0) {
		shakeCamera(10,x,y);
	 if(moveL){
	 	sprite.move(10,0);
	 }
	 if(moveR){
	 	sprite.move(-10,0);
	 }
	}
	
	if(!up){
		if (AttackPlayer == true && attackCooldown == 0 && CoutHeal >= 0) {
    CoutHeal--;
    AttackPlayer = false;
    attackCooldown = 60; 
}

if (attackCooldown > 0) {
	AttackPlayer = false;
    attackCooldown--;
}
	
}
if(AttackEnemy){
	if (upR){
	j=0;
	up = true;
	speedup=36;
	sheet = 4;
	getAspectRatio(texture[sheet],frame);
	sprite.setTexture(texture[sheet]);
	}
if (upL){
	j=0;
	up = true;
	speedup=36;
	sheet = 5;
	getAspectRatio(texture[sheet],frame);
	sprite.setTexture(texture[sheet]);
	}	
	AttackEnemy = false;	
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
    getplayercoordinateforview(AttackPlayer,x,y) ;

	
	
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
    paralaxSprite[i].setPosition(paralaxSprite[i].getPosition().x + offset,paralaxSprite[i].getPosition().y);
    paralaxSprite1[i].setPosition(paralaxSprite1[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);
    paralaxSprite2[i].setPosition(paralaxSprite2[i].getPosition().x + offset,paralaxSprite[i].getPosition().y);  
	paralaxSprite3[i].setPosition(paralaxSprite3[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);	
	paralaxSprite4[i].setPosition(paralaxSprite4[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);	
	}


    // Отрисовка паралакса
    window.draw(paralaxSprite[i]);
    window.draw(paralaxSprite1[i]);
    window.draw(paralaxSprite2[i]);
    window.draw(paralaxSprite3[i]);
}

	
        ///Отрисовка и обработка паралакса
        

        window.draw(sprite);

///Отрисовка карты  и ее элементов
        for (const sf::Sprite obstacle : obstacleSprites) {
            window.draw(obstacle);
        }

        for (int i = 0; i < maxZone; ++i) {
            interactionZones[i].update(sprite);
            interactionZones[i].render();  // Отображаем все зоны
        }

        	        
////        for (auto& enemy : enemies) {



	//float deltaTime = clock.restart().asSeconds();
	//std::cout<<deltaTime<< endl;
	
    enemies1.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies1.render(window); // Отрисовка врага	
    enemies2.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies2.render(window);
    enemies3.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies3.render(window);
    enemies4.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies4.render(window);
    enemies5.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies5.render(window);
    enemies6.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies6.render(window);
    enemies7.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies7.render(window);
    enemies8.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies8.render(window);
    enemies9.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies9.render(window);
    enemies10.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // Обновление врага
    enemies10.render(window);
    
      	key.update(deltaTime,sprite,haveKey);
		key.render(window);
		key2.update(deltaTime,sprite,haveKey);
		key2.render(window);
		key3.update(deltaTime,sprite,haveKey);
		key3.render(window);
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
      	sprite.setPosition(sprite.getPosition().x,SpawnPlayerPosition.y);
	  }
      
      ////Доработка 
      
      
      
      
      sf::Vector2f worldPos = window.mapPixelToCoords(screenPos, view);
      

// Отображаем элемент в мировых координатах


    spriteCoin.setPosition(worldPos.x ,worldPos.y + 50);
	text.setPosition(worldPos.x + 50 ,worldPos.y + 50);

keyUI.setPosition(worldPos.x + 1 ,worldPos.y + 80);
keyUItext.setPosition(worldPos.x + 50 ,worldPos.y + 90);
if(haveKey != 0 ){
     stringstream ss;
     ss << haveKey;
     string str;
     ss >> str;
	 keyUItext.setString(str);	
}


window.draw(keyUI);
window.draw(keyUItext);
for(int i = 0 ; i < healnum; i++ ){
	
heal[i].setPosition(worldPos.x + 40 * i,worldPos.y);
window.draw(heal[i]);	

    if(CoutHeal < healnum){
    	heal[CoutHeal].setColor(sf::Color::Black);
	}

}

        window.display();
    }

    return 0;
}
