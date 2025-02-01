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
     
         ///�����
    sf::Font font; 
    font.loadFromFile("ArialRegular.ttf");
    int coolDown;
    ///�����
     
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

sf::Vector2i screenPos(50, 25); // ������� �������� �� ������
sf::Vector2i coutMoneyPos(50, 125);

// ������������ �������� ���������� � �������

     
     
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
    
    ///�������� �������
		Texture textureCoin;
        textureCoin.loadFromFile("animation/Daco.png");
    ///�������� �������
    
    ///-----
    
    ///������ ��� �������� �������
        Text text;
        text.setFont(font);
        text.setCharacterSize(25);
        text.setOutlineThickness(3);
        text.setOutlineColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
        text.setString("0");
    ///������ ��� �������� �������
    
    ///-----
        
        
bool money[20];
for(int i = 0; i < 20; i++){
 money[i] = true;	
}  
///-----

///�������� ���������� ��� ������ ������  

sf::Vector2f SpawnPlayerPosition;//���������� ��� ����������� ������ ������

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


//������ �� ������� ��������
    string file[anim];
    file[0] = "stop_right.png";
    file[1] = "stop_left.png";
    file[2] = "run_right.png";
    file[3] = "run_left.png";
    file[4] = "up_right.png";
    file[5] = "up_left.png";
//������ �� ������� ��������

//----------------

//�������� ������� � ���������� ���������
    int sheet = 0 ;
	Texture texture[anim];
    for(int i=0;i<=anim-1;i++){
    texture[i].loadFromFile("animation/"+file[i]);
    getAspectRatio(texture[sheet],frame);

}
//�������� ������� � ���������� ���������



//�������� ������� ������ 
    Sprite sprite;
    sprite.setTexture(texture[sheet]);
    sprite.setPosition(1,-50);
    sprite.setScale(2.0f,2.0f);
    bool AttackPlayer = false;
    bool AttackEnemy = false;

//�������� ������� ������

 
 
///�������� ���������� ��� ������ ������  
	
///-----

Image map_image;

	map_image.loadFromFile("animation/tile.png");///�������� �������� �����
	Texture obstacleTexture;///�������� �������� �������� �����
	obstacleTexture.loadFromImage(map_image);///�������� �������� �����	� �������
	
////------	

//// ������� ��� �������� ������� ������
	rectangley.setTexture(obstacleTexture);
	rectangley.setTextureRect(IntRect(0, 100, 20, 20));
	rectangley2.setTexture(obstacleTexture);
	rectangley2.setTextureRect(IntRect(0, 100, 20, 80));	
	rectangleX.setTexture(obstacleTexture);
	rectangleX.setTextureRect(IntRect(0, 100,50, 50));
	rectangleFall.setTexture(obstacleTexture);
	rectangleFall.setTextureRect(IntRect(0, 100, 100, 100));
//// ������� ��� �������� ������� ������

////------
	
////------	


    std::vector<sf::Sprite> obstacleSprites;// ��������� ��� ������ �����

////------ 
	int maxZone = 3;// ���������� ��� �������� ������������� ����� ��������� ���
// ������� ������� � �������
InteractionZone* interactionZones = new InteractionZone[3]{
    InteractionZone(&window, {100.0f, 100.0f}, {400.0f, 150.0f}),
    InteractionZone(&window, {300.0f, 100.0f}, {400.0f, 150.0f}),
    InteractionZone(&window, {500.0f, 100.0f}, {400.0f, 150.0f})
};
    int countZones = 0;// ���������� ��� �������� ���������� ������������ �� ����� ��� , ������ 3 ������ 
    
std::vector<sf::Sprite> spriteZone(maxZone);//������� �����

for (int i = 0; i < maxZone; ++i) {
    spriteZone[i] = interactionZones[i].getZoneSprite(); // ������� ������ "�����" �������, ��� ��� � �� ���� ����������� �������� ����� 
}
           

///���������� ������ ����� �� ���������� �������  
    //std::vector<AIEnemy> enemies; // �������� ������

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
        if (TileMap[i][j] == 'i') { // �������� ���������� ����
            interactionZones[countZones].setPosition(
                {static_cast<float>(-100 + j * 100), static_cast<float>(-300 + i * 145)});
            countZones++;
        }
        if (TileMap[i][j] == 'e') { // �������� �����    
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
///���������� ������ ����� �� ���������� �������  
    
////------

std::vector<sf::Sprite> sprite1Coin2;// ��������� ��� �������� �����
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
//�������� ������� �������
Sprite spriteCoin;
spriteCoin.setScale(0.15,0.15);
spriteCoin.setTexture(textureCoin);
spriteCoin.setPosition(1,-50);
spriteCoin.setTextureRect(sf::IntRect((frameCoinWidht*coinH),(0),frameCoinWidht,frameCoinHeight));
//�������� ������� �������

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
 
 
 /// ��� ��� ������� � ��������� ////		

    		
       		
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
   
       	sprite.setTextureRect(sf::IntRect(50*j,0,50,50)); // ������ �������� �������� ��������� j ������ ���� 
       	
	if (checkSpriteOverlap(rectangley2, obstacleSprites) ){
	sprite.move(0,speedPlaer);
        }
 
 
 ///   �������� ������� �� ��� X    
if (checkSpriteOverlap(rectangleX, obstacleSprites)){
	moveParalax = false ; /// ������ �� �������� ���������	
	if (moveR){ ///���� �������� �������� � ����� , �� ��� ����������� � ����
	sprite.move(-speedPlaer,0);	
	}
	if (moveL){///���� �������� �������� � ���� , �� ��� ����������� � �����
	sprite.move(speedPlaer,0);	
	}
  }else{
moveParalax = true ;/// ���������� �� �������� ���������	
} 


for (int i = 0; i < maxZone; ++i) {
    spriteZone[i].setPosition(interactionZones[i].getZoneSprite().getPosition());  
	// ������ , ��� ������� ������� �������� �������� ������� ����� ������� �������������� ������� ���� �� �����. 
	//������ �� , ����� ����� �������� ��������� , �� ����� ����� �� ����� ��������� �������� �������� ������� �����, ��� ������ ����������� �� �������� 
}


if (checkSpriteOverlap(rectangleX, spriteZone)){
	moveParalax = false ; /// ������ �� �������� ���������	
	if (moveR){ ///���� �������� �������� � ����� , �� ��� ����������� � ����
	sprite.move(-speedPlaer,0);	
	}
	if (moveL){///���� �������� �������� � ���� , �� ��� ����������� � �����
	sprite.move(speedPlaer,0);	
	}
  }else{
	
} 
//	
//}
	
/// ��� ��� ������� � ��������� ////		

/// -------

/// ������� ����������� ������ �� ������� , � ���������� , ��� ������ ������ �� ������ ��� ������� ��� ��������
		

		
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

		
		
	/// ������� ����������� ������ �� ������� , � ���������� , ��� ������ ������ �� ������ ��� ������� ��� ��������	
		
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
		
///��������� ���� ����

///---------------------------------------------------	

        window.clear(Color(255,255,255));
        
        ///��������� � ��������� ���������

// ���������� ��� ����������� �������� ����� ���������
int moveDirection = 0;  // 0 - �� �����, -1 - ����, 1 - �����

// �������� ����������� �������� ������ �� ��������
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    moveDirection = -1;  // �������� � ����
} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    moveDirection = 1;  // �������� � �����
} else {
    moveDirection = 0;  // ��� ��������
}

// ���� ��� ���������� ���������
for (int i = 0; i < colparalax; i++) {
    float offset = 0.0f;

    float speed = (i - 2) / 1.5f;  // �������� �������� ���������

    // �������� ���� �� �������� ��������� , � � ����� ������� �� ��������
    if (moveDirection == -1) {
        offset = speed;  // ����������� �������� ���������
    }
    // �������� ���� �� �������� ��������� , � � ����� ������� �� ��������
    else if (moveDirection == 1) {
        offset = -speed;  // ����������� �������� ���������
    }

    // ����������� ���������
    if(moveParalax){
    paralaxSprite[i].setPosition(paralaxSprite[i].getPosition().x + offset,paralaxSprite[i].getPosition().y);
    paralaxSprite1[i].setPosition(paralaxSprite1[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);
    paralaxSprite2[i].setPosition(paralaxSprite2[i].getPosition().x + offset,paralaxSprite[i].getPosition().y);  
	paralaxSprite3[i].setPosition(paralaxSprite3[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);	
	paralaxSprite4[i].setPosition(paralaxSprite4[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);	
	}


    // ��������� ���������
    window.draw(paralaxSprite[i]);
    window.draw(paralaxSprite1[i]);
    window.draw(paralaxSprite2[i]);
    window.draw(paralaxSprite3[i]);
}

	
        ///��������� � ��������� ���������
        

        window.draw(sprite);

///��������� �����  � �� ���������
        for (const sf::Sprite obstacle : obstacleSprites) {
            window.draw(obstacle);
        }

        for (int i = 0; i < maxZone; ++i) {
            interactionZones[i].update(sprite);
            interactionZones[i].render();  // ���������� ��� ����
        }

        	        
////        for (auto& enemy : enemies) {



	//float deltaTime = clock.restart().asSeconds();
	//std::cout<<deltaTime<< endl;
	
    enemies1.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies1.render(window); // ��������� �����	
    enemies2.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies2.render(window);
    enemies3.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies3.render(window);
    enemies4.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies4.render(window);
    enemies5.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies5.render(window);
    enemies6.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies6.render(window);
    enemies7.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies7.render(window);
    enemies8.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies8.render(window);
    enemies9.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies9.render(window);
    enemies10.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // ���������� �����
    enemies10.render(window);
    
      	key.update(deltaTime,sprite,haveKey);
		key.render(window);
		key2.update(deltaTime,sprite,haveKey);
		key2.render(window);
		key3.update(deltaTime,sprite,haveKey);
		key3.render(window);
///��������� �����  � �� ���������
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
      
      /////��������� 
      
      if(sprite.getPosition().y > 1200){//���� ����� ������ ���� ���� ������� , �� ��� ������������� �� ����� ������
      	sprite.setPosition(sprite.getPosition().x,SpawnPlayerPosition.y);
	  }
      
      ////��������� 
      
      
      
      
      sf::Vector2f worldPos = window.mapPixelToCoords(screenPos, view);
      

// ���������� ������� � ������� �����������


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
