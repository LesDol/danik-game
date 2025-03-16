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
     

    sf::Font font; 
    font.loadFromFile("ArialRegular.ttf");
    bool MainMenu = true;
    
	start_game:
		
		if(MainMenu){
			 std::vector<sf::Texture> textures(4);
    std::vector<sf::Texture*> texturePtrs(4);
    std::vector<float> speeds = {25.0f, 37.0f, 50.0f, 75.0f};

    for (size_t i = 0; i < 4; ++i) {
        if (!textures[i].loadFromFile("Paralax/Clouds/Clouds 2/" + std::to_string(i + 1) + ".png")) {
            return -1;
        }
        texturePtrs[i] = &textures[i];
    }

    MainParallax parallax(texturePtrs, speeds);
    Menu menu(window, font);
    

    view.setSize(1200, 720);  
    view.setCenter(600, 360);
    
	sf::Font logofont; 
    logofont.loadFromFile("alagard-12px-unicode.ttf");
    
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("animation/logo.png")) {
        std::cout << "Не получилось загрузить лого!" << std::endl;
        logoTexture.create(200, 200);
    }
    

    sf::Sprite logoSprite;
    logoSprite.setTexture(logoTexture);
    
    sf::Vector2u textureSize = logoTexture.getSize();
    logoSprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    logoSprite.setPosition(800, 120); 

    float scale = 0.4f; 
    logoSprite.setScale(scale, scale);
    
    sf::Clock clock;
    
    Text logo;
    logo.setFont(logofont);
    logo.setString("     The  \nRed CLoaK");
    logo.setCharacterSize(72);
    logo.setPosition(600, 25);
    while (window.isOpen()) {
        sf::Event event;
        bool mousePressed = false;

       while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                mousePressed = true;
            }
        }

      float deltaTime = clock.restart().asSeconds();
        parallax.update(deltaTime);
        menu.update(window, view);

        if (menu.isGameStarted()) {
		MainMenu = false;
			break;
			
        }


        window.clear();
        window.setView(view);  
        parallax.draw(window);
        menu.draw();
        //window.draw(logo);
        window.draw(logoSprite); 
        window.display();
    }
    
			
		}
    
    //MainMenu(font,window);
    
    
    int coolDown = 0;
    ///
    
    
     
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
     int healnum = 6;
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

sf::Vector2i screenPos(50, 25); 
sf::Vector2i coutMoneyPos(50, 125);


     
     
     ///PARALAX
    int colparalax = 8;
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
if(i != 6){
    paralaxSprite[i].setTexture(paralaxTexture[i]);
    paralaxSprite[i].setPosition(-700, paralaxPos - (paralaxDiferent * (15 - i)));
    paralaxSprite[i].setScale(paralaxSize, paralaxSize);

    float width = paralaxSprite[i].getGlobalBounds().width;

    paralaxSprite1[i].setTexture(paralaxTexture[i]);
    paralaxSprite1[i].setPosition(paralaxSprite[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (15 - i)));
    paralaxSprite1[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite2[i].setTexture(paralaxTexture[i]);
    paralaxSprite2[i].setPosition(paralaxSprite1[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (15 - i)));
    paralaxSprite2[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite3[i].setTexture(paralaxTexture[i]);
    paralaxSprite3[i].setPosition(paralaxSprite2[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (15 - i)));
    paralaxSprite3[i].setScale(paralaxSize, paralaxSize);
    
    paralaxSprite4[i].setTexture(paralaxTexture[i]);
    paralaxSprite4[i].setPosition(paralaxSprite3[i].getPosition().x + width, paralaxPos - (paralaxDiferent * (10 - i)));
    paralaxSprite4[i].setScale(paralaxSize, paralaxSize);	
}else if(i == 6){
	paralaxPos = -350-150;
	    paralaxSprite[i].setTexture(paralaxTexture[3]);
    paralaxSprite[i].setPosition(-700, paralaxPos);
    paralaxSprite[i].setScale(paralaxSize, paralaxSize);

    float width = paralaxSprite[i].getGlobalBounds().width;

    paralaxSprite1[i].setTexture(paralaxTexture[3]);
    paralaxSprite1[i].setPosition(paralaxSprite[i].getPosition().x + width, paralaxPos);
    paralaxSprite1[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite2[i].setTexture(paralaxTexture[3]);
    paralaxSprite2[i].setPosition(paralaxSprite1[i].getPosition().x + width, paralaxPos);
    paralaxSprite2[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite3[i].setTexture(paralaxTexture[3]);
    paralaxSprite3[i].setPosition(paralaxSprite2[i].getPosition().x + width, paralaxPos );
    paralaxSprite3[i].setScale(paralaxSize, paralaxSize);
    
    paralaxSprite4[i].setTexture(paralaxTexture[3]);
    paralaxSprite4[i].setPosition(paralaxSprite3[i].getPosition().x + width, paralaxPos);
    paralaxSprite4[i].setScale(paralaxSize, paralaxSize);	
}
if(i == 7){
	paralaxPos = -350-50;
	    paralaxSprite[i].setTexture(paralaxTexture[2]);
    paralaxSprite[i].setPosition(-700, paralaxPos);
    paralaxSprite[i].setScale(paralaxSize, paralaxSize);

    float width = paralaxSprite[i].getGlobalBounds().width;
cout <<paralaxPos <<endl;
    paralaxSprite1[i].setTexture(paralaxTexture[2]);
    paralaxSprite1[i].setPosition(paralaxSprite[i].getPosition().x + width, paralaxPos);
    paralaxSprite1[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite2[i].setTexture(paralaxTexture[2]);
    paralaxSprite2[i].setPosition(paralaxSprite1[i].getPosition().x + width, paralaxPos);
    paralaxSprite2[i].setScale(paralaxSize, paralaxSize);

    paralaxSprite3[i].setTexture(paralaxTexture[2]);
    paralaxSprite3[i].setPosition(paralaxSprite2[i].getPosition().x + width, paralaxPos );
    paralaxSprite3[i].setScale(paralaxSize, paralaxSize);
    
    paralaxSprite4[i].setTexture(paralaxTexture[2]);
    paralaxSprite4[i].setPosition(paralaxSprite3[i].getPosition().x + width, paralaxPos);
    paralaxSprite4[i].setScale(paralaxSize, paralaxSize);	
}


}
bool frontPhone = true;

	

     ///PARALAX
      
    sf::Time delay = sf::seconds(0.1);
	int coinH=0,g=0,moni=0,mon=0;
	float speedup=20 , speeddown = 0 , frameCoinWidht=(191),frameCoinHeight=171;
    Time time = clock.getElapsedTime();

    
    ///-----
    
    ///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
		Texture textureCoin;
        textureCoin.loadFromFile("animation/Daco.png");
    ///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    
    ///-----
    
    ///пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
        Text text;
        text.setFont(font);
        text.setCharacterSize(25);
        text.setOutlineThickness(3);
        text.setOutlineColor(sf::Color::Black);
        text.setFillColor(sf::Color::White);
        text.setString("0");
    ///пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    
    ///-----
        
        
bool money[20];
for(int i = 0; i < 20; i++){
 money[i] = true;	
}  
///-----

///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ  

sf::Vector2f SpawnPlayerPosition;//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ

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


//пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    string file[anim];
    file[0] = "stop_right.png";
    file[1] = "stop_left.png";
    file[2] = "run_right.png";
    file[3] = "run_left.png";
    file[4] = "up_right.png";
    file[5] = "up_left.png";
//пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

//----------------

//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    int sheet = 0 ;
	Texture texture[anim];
    for(int i=0;i<=anim-1;i++){
    texture[i].loadFromFile("animation/"+file[i]);
    getAspectRatio(texture[sheet],frame);

}
//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ



//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ 
    Sprite sprite;
    sprite.setTexture(texture[sheet]);
    sprite.setPosition(1,-50);
    sprite.setScale(2.0f,2.0f);
    bool AttackPlayer = false;
    bool AttackEnemy = false;

//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ

 
 
///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ  
	
///-----

Image map_image;

	map_image.loadFromFile("animation/tile.png");///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
	Texture obstacleTexture;///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
	obstacleTexture.loadFromImage(map_image);///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ	пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
	
////------	

//// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
	rectangley.setTexture(obstacleTexture);
	rectangley.setTextureRect(IntRect(0, 100, 20, 20));
	rectangley2.setTexture(obstacleTexture);
	rectangley2.setTextureRect(IntRect(0, 100, 20, 80));	
	rectangleX.setTexture(obstacleTexture);
	rectangleX.setTextureRect(IntRect(0, 100,50, 50));
	rectangleFall.setTexture(obstacleTexture);
	rectangleFall.setTextureRect(IntRect(0, 100, 100, 100));
//// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ

////------
	
////------	


    std::vector<sf::Sprite> obstacleSprites;// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ

////------ 
	int maxZone = 3;// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
InteractionZone* interactionZones = new InteractionZone[3]{
    InteractionZone(&window, {100.0f, 100.0f}, {400.0f, 150.0f}),
    InteractionZone(&window, {300.0f, 100.0f}, {400.0f, 150.0f}),
    InteractionZone(&window, {500.0f, 100.0f}, {400.0f, 150.0f})
};
    int countZones = 0;// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ , пїЅпїЅпїЅпїЅпїЅпїЅ 3 пїЅпїЅпїЅпїЅпїЅпїЅ 
    
std::vector<sf::Sprite> spriteZone(maxZone);//пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ

for (int i = 0; i < maxZone; ++i) {
    spriteZone[i] = interactionZones[i].getZoneSprite(); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ "пїЅпїЅпїЅпїЅпїЅ" пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ 
}
           

///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ  
    //std::vector<AIEnemy> enemies; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ

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

  
	///пїЅпїЅпїЅпїЅпїЅ
	
	    sf::Texture doorTexture;
    if (!doorTexture.loadFromFile("GameObjects/door/door.png")) {
        std::cerr << "пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ!" << std::endl;
        return -1;
    }
    Door door(300, 200, 3, &haveKey, doorTexture, font);
	///пїЅпїЅпїЅпїЅпїЅ
	
	
	
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
        if ((TileMap[i][j] == 'd')) {
            door.setPosition(-100 + j * 100, -335 + i * 145);
        }
        if ((TileMap[i][j] == 'g')) {
            sf::Sprite obstacleSprite(obstacleTexture);
            obstacleSprite.setTextureRect(IntRect(0, 100, 100, 35));
            obstacleSprite.setPosition(-100 + j * 100, -300 + (i * 145) - 10);
            obstacleSprites.push_back(obstacleSprite);
        }
        if (TileMap[i][j] == 'i') { // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            interactionZones[countZones].setPosition(
                {static_cast<float>(-100 + j * 100), static_cast<float>(-300 + i * 145)});
            countZones++;
        }
        if (TileMap[i][j] == 'e') { // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ    
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
///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ  
    
////------

std::vector<sf::Sprite> sprite1Coin2;// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
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
//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
Sprite spriteCoin;
spriteCoin.setScale(0.15,0.15);
spriteCoin.setTexture(textureCoin);
spriteCoin.setPosition(1,-50);
spriteCoin.setTextureRect(sf::IntRect((frameCoinWidht*coinH),(0),frameCoinWidht,frameCoinHeight));
//пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ

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
 
 
 /// пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ ////		

    		
       		
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
   
       	sprite.setTextureRect(sf::IntRect(50*j,0,50,50)); // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ j пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ 
       	
	if (checkSpriteOverlap(rectangley2, obstacleSprites) ){
	sprite.move(0,speedPlaer);
        }
 
 
 ///   пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ X    
if (checkSpriteOverlap(rectangleX, obstacleSprites)){
	moveParalax = false ; /// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ	
	if (moveR){ ///пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ , пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ
	sprite.move(-speedPlaer,0);	
	}
	if (moveL){///пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ , пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ
	sprite.move(speedPlaer,0);	
	}
  }else{
moveParalax = true ;/// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ	
} 


for (int i = 0; i < maxZone; ++i) {
    spriteZone[i].setPosition(interactionZones[i].getZoneSprite().getPosition());  
	// пїЅпїЅпїЅпїЅпїЅпїЅ , пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ. 
	//пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ , пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
}


if (checkSpriteOverlap(rectangleX, spriteZone)){
	moveParalax = false ; /// пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ	
	if (moveR){ ///пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ , пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ
	sprite.move(-speedPlaer,0);	
	}
	if (moveL){///пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ , пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ
	sprite.move(speedPlaer,0);	
	}
  }else{
	
} 
//	
//}
	
/// пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ ////		

/// -------

/// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
		

		
if (AttackPlayer  == true  && CoutHeal == 0 ) {
	AttackPlayer = false;
}		
	folowCamera(x,y,sprite);
if (coolDown > 0) {
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
    coolDown = 10;
}

if (attackCooldown > 0) {
	AttackPlayer = false;
    attackCooldown--;
    coolDown --;
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

		
		
	/// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ	
		
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
		
///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ

///---------------------------------------------------	

        window.clear(Color(255,255,255));
        
        ///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
int moveDirection = 0;  // 0 - пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ, -1 - пїЅпїЅпїЅпїЅ, 1 - пїЅпїЅпїЅпїЅпїЅ

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    moveDirection = -1;  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅ
} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    moveDirection = 1;  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ
} else {
    moveDirection = 0;  // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
}

// пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
for (int i = 0; i < colparalax-2; i++) {
    float offset = 0.0f;

    float speed = (i - 2) / 1.5f;  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    if (moveDirection == -1) {
        offset = speed;  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    }
    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅ пїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    else if (moveDirection == 1) {
        offset = -speed;  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    }

    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    if(moveParalax){
    paralaxSprite[i].setPosition(paralaxSprite[i].getPosition().x + offset,paralaxSprite[i].getPosition().y);
    paralaxSprite1[i].setPosition(paralaxSprite1[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);
    paralaxSprite2[i].setPosition(paralaxSprite2[i].getPosition().x + offset,paralaxSprite[i].getPosition().y);  
	paralaxSprite3[i].setPosition(paralaxSprite3[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);	
	paralaxSprite4[i].setPosition(paralaxSprite4[i].getPosition().x + offset, paralaxSprite[i].getPosition().y);	
	}


    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
    window.draw(paralaxSprite[i]);
    window.draw(paralaxSprite1[i]);
    window.draw(paralaxSprite2[i]);
    window.draw(paralaxSprite3[i]);
}


	
        ///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
        
	    door.update(sprite.getPosition(),window);
        door.draw(window);
        window.draw(sprite);

///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ  пїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ


        for (const sf::Sprite obstacle : obstacleSprites) {
            window.draw(obstacle);
        }

        for (int i = 0; i < maxZone; ++i) {
            interactionZones[i].update(sprite);
            interactionZones[i].render();  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
        }

        	        
////        for (auto& enemy : enemies) {



	//float deltaTime = clock.restart().asSeconds();
	//std::cout<<deltaTime<< endl;
	
    enemies1.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies1.render(window); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ	
    enemies2.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies2.render(window);
    enemies3.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies3.render(window);
    enemies4.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies4.render(window);
    enemies5.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies5.render(window);
    enemies6.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies6.render(window);
    enemies7.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies7.render(window);
    enemies8.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies8.render(window);
    enemies9.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies9.render(window);
    enemies10.update(deltaTime, sprite, obstacleSprites,AttackPlayer,AttackEnemy); // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
    enemies10.render(window);
    
      	key.update(deltaTime,sprite,haveKey);
		key.render(window);
		key2.update(deltaTime,sprite,haveKey);
		key2.render(window);
		key3.update(deltaTime,sprite,haveKey);
		key3.render(window); 
		
	
        
        
        

        
        
        
        
///пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ  пїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
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
			
	if(frontPhone){
	window.draw(paralaxSprite[6]);
    window.draw(paralaxSprite1[6]);
    window.draw(paralaxSprite2[6]);
    window.draw(paralaxSprite3[6]);
    window.draw(paralaxSprite[7]);
    window.draw(paralaxSprite1[7]);
    window.draw(paralaxSprite2[7]);
    window.draw(paralaxSprite3[7]);
}
	  window.draw(text);
      window.setView(view);
      
      /////пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
      
      if(sprite.getPosition().y > 1200){//пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ , пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
      	sprite.setPosition(sprite.getPosition().x,SpawnPlayerPosition.y);
	  }
      
      ////пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 
      
      
      
      
      sf::Vector2f worldPos = window.mapPixelToCoords(screenPos, view);
      

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ


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
if(CoutHeal == 0 or door.levelFinish()){
	MainMenu = true;
	goto start_game;
}


       


        window.display();
    }

    return 0;
}
