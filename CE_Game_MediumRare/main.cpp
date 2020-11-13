#define SFML_NO_DEPRECATED_WARNINGS
// Food Menu
#include "Menu.h";
#include "GameMain.h"
#include "Player.h"
#include "Platform.h";
#include <sstream>
#include <string>

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	// General Variable
	int gameStateMachine = 1;
	int animationFrame = 0;
	int BDishStatus[10] = { 1,1,1,1,1,1,1,1,1,1 };
	std::string ingredient[27] = { "Raw Chicken","Raw Porkchop","Papaya","Raw Shrimp","Raw Chicken","Vegetable","Chrispy Porkchop","Dough","Noodle Pasta"
		,"Sliced Raw Chicken","Krapao Gai","Sliced Raw Porkchop","Ko Moo Yang","Sliced Papaya","Som Tum","Cooked Shrimp","Tom Yum Kung","Grinded Raw Chicken","Gai Tom Nam Pla"
		,"Cleaned Vegetable","Salad","Grinded Chrispy Porkchop","Krapao Mookob","Sliced Dough","Pizza","Grinded Noodle Pasta","Spaghetti"};
	std::string foodNameList[10] = { "Krapao Gai","Ko Moo Yang","Som Tum","Tom Yum Kung","Gai Tom Nam Pla","Salad","Krapao Mookob","Pizza","Spaghetti" };
	std::string objectName[7] = { "Refrigerator","Oven","Cooking Basin","Grinder","Fryer Machine","Slicer","Delivery Point" };
	float receiptList[9][4] = { { 0,5,4,6 },{ 0,5,1,6 },{ 0,5,2,6 },{ 0,2,4,6 },{ 0,3,1,6 },{ 0,2,3,6 },{ 0,3,4,6 },{ 0,5,1,6 },{ 0,3,1,6 } };
	int receiptNameList[9][3] = { { 0,9,10 },{ 1,11,12 },{ 2,13,14 },{ 3,15,16 },{ 4,17,18 },{ 5,19,20 },{ 6,21,22 },{ 7,23,24 },{ 8,25,26 } };
	sf::RenderWindow window(sf::VideoMode(1280, 720), "MediumRare!");

	////// TitleTexture
	sf::Texture TitleTexture;
	if (!TitleTexture.loadFromFile("Asset/Image/Game_Title.jpg"))
	{
		std::cout << "Load Title failed" << std::endl;
	}
	////// Map BG Texture
	sf::Texture BgTexture;
	if (!BgTexture.loadFromFile("Asset/Image/Game-Map.jpg"))
	{
		std::cout << "Load Title failed" << std::endl;
	}
	////// BG Music
	sf::Music bgMusic;
	if (!bgMusic.openFromFile("Asset/Sound/BG_Music.ogg"))
	{	
		std::cout << "Load Music failed" << std::endl;
	}
	bgMusic.setVolume(30);
	//bgMusic.play();

	////// TitleTexture Sprite
	sf::Sprite shapeSprite;
	shapeSprite.setTexture(TitleTexture);
	shapeSprite.setTextureRect(sf::IntRect(0, 0, 1280, 720));
	////// Map BG Texture Sprite
	sf::Sprite mapBgSprite;
	mapBgSprite.setTexture(BgTexture);
	mapBgSprite.setTextureRect(sf::IntRect(0, 0, 1280, 720));


	////// Texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("Asset/Image/Character.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	
	/////// Object
	sf::Texture objectOven;
	if (!objectOven.loadFromFile("Asset/Image/Object_1_Stove.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectRefri;
	if (!objectRefri.loadFromFile("Asset/Image/Object_2_Refri.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectFryer;
	if (!objectFryer.loadFromFile("Asset/Image/Object_3_Fryer.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectGrinder;
	if (!objectGrinder.loadFromFile("Asset/Image/Object_4_Grinder.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectBasin;
	if (!objectBasin.loadFromFile("Asset/Image/Object_5_Basin.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectSlicer;
	if (!objectSlicer.loadFromFile("Asset/Image/Object_6_Slicer.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectDeliver;
	if (!objectDeliver.loadFromFile("Asset/Image/Object_7_Deliver.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectBEgg;
	if (!objectBEgg.loadFromFile("Asset/Image/Object_BEgg.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Texture objectBDish;
	if (!objectBDish.loadFromFile("Asset/Image/Object_BDish.png"))
	{
		std::cout << "Load failed" << std::endl;
	}

	////// Character

	Player PlayerA(&playerTexture, sf::Vector2u(4, 4), 0.3f,300.0f);

	////// Platform

	Platform platformOven(&objectOven, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(415.0f, 135.0f));
	Platform platformRefri(&objectRefri, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(415.0f, 600.0f));
	Platform platformDeliver(&objectDeliver, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(615.0f, 600.0f));
	Platform platformFryer(&objectFryer, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(615.0f, 135.0f));
	Platform platformBDish(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(555.0f, 600.0f));

	// Edge Background
	Platform platformLeft(nullptr, sf::Vector2f(400.0f, 1500.0f), sf::Vector2f(75.0f, 0.0f));
	Platform platformRight(nullptr, sf::Vector2f(200.0f, 1500.0f), sf::Vector2f(1105.0f, 0.0f));
	Platform platformTop(nullptr, sf::Vector2f(1200.0f, 1100.0f), sf::Vector2f(505.0f, -550.0f));
	Platform platformBottom(nullptr, sf::Vector2f(1200.0f, 1100.0f), sf::Vector2f(505.0f, 1270.0f));

	////// Variable Pointer

	float deltaTime = 0.0f;
	float buttonStatus = 0.0f;
	float* buttonStatusTemp;
	float bStatusTemp = 0.0f;
	float scorePrint = 0.0f;
	int* statusTemp = 0;
	int nextObjectRequest = 0;
	int currentMenu = 0;
	float nextObjectTemp = 0.0f;
	sf::Clock clock;
	/*sf::Sprite shapeSpriteCharacter;
	shapeSpriteCharacter.setTexture(playerTexture);
	int spriteSizeX = playerTexture.getSize().x / 4;
	int spriteSizeY = playerTexture.getSize().y / 4;

	shapeSpriteCharacter.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	shapeSpriteCharacter.setPosition({ -200.f, -200.f });*/
	////// Object

	////// Menu

	////// Stage Page
	// Input Name System
	sf::Font inputNameFont;
	if (!inputNameFont.loadFromFile("DB.ttf"))
	{
		std::cout << "Load Font Scoreboard failed" << std::endl;
	}
	sf::Texture stageName;
	if (!stageName.loadFromFile("Asset/Image/Stage_Page_Name.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite stagePageName;
	stagePageName.setTexture(stageName);
	stagePageName.setTextureRect(sf::IntRect(0, 0, 1280, 720));
	sf::String playerInput;
	sf::Text playerText;
	playerText.setPosition(sf::Vector2f(520, 510));
	playerText.setColor(sf::Color::Black);
	playerText.setFont(inputNameFont);
	playerText.setCharacterSize(50);


	sf::Texture stagePage1;
	if (!stagePage1.loadFromFile("Asset/Image/Stage_Page_1.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite stagePageDist1;
	stagePageDist1.setTexture(stagePage1);
	stagePageDist1.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePage1End;
	if (!stagePage1End.loadFromFile("Asset/Image/Stage_Page_1_End.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite stagePageDistEnd1;
	stagePageDistEnd1.setTexture(stagePage1End);
	stagePageDistEnd1.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	Menu menu(window.getSize().x, window.getSize().y);

	////// Scoreboard

	sf::Font scoreboardFont;
	if (!scoreboardFont.loadFromFile("DB.ttf"))
	{
		std::cout << "Load Font Scoreboard failed" << std::endl;
	}

	// Score End Stage
	sf::Text scoreStage;
	scoreStage.setFont(scoreboardFont);
	scoreStage.setCharacterSize(150);
	scoreStage.setColor(sf::Color::Black);
	scoreStage.setString("0");
	scoreStage.setPosition(sf::Vector2f(850, 470));

	// Scoreboard - Title
	sf::Text scoreboard;
	scoreboard.setFont(scoreboardFont);
	scoreboard.setCharacterSize(50);
	scoreboard.setColor(sf::Color::Black);
	scoreboard.setString("ScoreNow");
	scoreboard.setPosition(sf::Vector2f(20, 10));
	// Scoreboard - ScoreNow
	int scoreDisplay = 0000;
	std::ostringstream scorePrintSS;
	scorePrintSS << scorePrint;
	std::string scorePrintString(scorePrintSS.str());
	sf::Text scoreNow;
	scoreNow.setFont(scoreboardFont);
	scoreNow.setCharacterSize(50);
	scoreNow.setColor(sf::Color::Black);
	scoreNow.setString("0");
	scoreNow.setPosition(sf::Vector2f(20, 50));

	////// Food Menu System

	float requiredInt = 0.0f;
	sf::Text foodMenuTitle;
	foodMenuTitle.setFont(scoreboardFont);
	foodMenuTitle.setCharacterSize(50);
	foodMenuTitle.setColor(sf::Color::Black);
	foodMenuTitle.setString("Required Next");
	foodMenuTitle.setPosition(sf::Vector2f(1020, 140));
	sf::Text requiredIntMenu;
	requiredIntMenu.setFont(scoreboardFont);
	requiredIntMenu.setCharacterSize(50);
	requiredIntMenu.setColor(sf::Color::Black);
	requiredIntMenu.setPosition(sf::Vector2f(1020, 190));
	sf::Text foodNameTitle;
	foodNameTitle.setFont(scoreboardFont);
	foodNameTitle.setCharacterSize(50);
	foodNameTitle.setColor(sf::Color::Black);
	foodNameTitle.setString("Current Menu");
	foodNameTitle.setPosition(sf::Vector2f(1020, 10));
	sf::Text foodName;
	foodName.setFont(scoreboardFont);
	foodName.setCharacterSize(50);
	foodName.setColor(sf::Color::Black);
	foodName.setString("Null");
	foodName.setPosition(sf::Vector2f(1020, 50));

	////// Timer System

	float Timer = 0;
	int limitTime = 90;
	int intialTime = 1;
	int distTime = 90;
	sf::Time timerAsSec = sf::seconds(1000);
	sf::Time timerDec = sf::seconds(1);
	sf::Clock clockTimer;
	sf::Text titleTimer;
	titleTimer.setFont(scoreboardFont);
	titleTimer.setCharacterSize(50);
	titleTimer.setColor(sf::Color::Black);
	titleTimer.setString("Time Left");
	titleTimer.setPosition(sf::Vector2f(20, 140));

	sf::Text showTimer;
	showTimer.setFont(scoreboardFont);
	showTimer.setCharacterSize(50);
	showTimer.setColor(sf::Color::Black);
	showTimer.setString("90");
	showTimer.setPosition(sf::Vector2f(20, 190));

	// Delay System
	sf::Time delay = sf::seconds(0.1);
	// Speed Control System
	

	while (window.isOpen())
	{
		if (buttonStatus == 4.0f)
		{
			currentMenu = 1;
			//currentMenu = rand() % 10;
			buttonStatus = 0.0f;
			nextObjectRequest = 0;
		}
		if (buttonStatus == 1.0f)
		{
			nextObjectRequest = 1;
		}
		else if (buttonStatus == 2.0f)
		{
			nextObjectRequest = 2;
		}
		else if (buttonStatus == 3.0f)
		{
			nextObjectRequest = 3;
		}
		if (buttonStatus == 0.0f)
		{
			foodName.setString(foodNameList[currentMenu]);
			requiredIntMenu.setString("-");
		}
		else
		{
			foodName.setString(foodNameList[currentMenu]);
			requiredIntMenu.setString(ingredient[receiptNameList[currentMenu][(int)buttonStatus - 1]]);
		}
		
		// Set food
		/*switch ((int)buttonStatus)
		{
		case 1 :
			requiredIntMenu.setString(ingredient[0]);
			break;
		case 2:
			requiredIntMenu.setString(ingredient[1]);
			break;
		case 3:
			currentMenu = 2;
			requiredIntMenu.setString(ingredient[2]);
			break;
		}*/
		/*switch (currentMenu)
		{
		case 1:
			foodName.setString(foodNameList[0]);

			break;
		case 2:
			foodName.setString(foodNameList[1]);
			break;
		case 3:
			foodName.setString(foodNameList[2]);
			break;
		case 4:
			foodName.setString(foodNameList[3]);
			break;
		case 5:
			foodName.setString(foodNameList[4]);
			break;
		case 6:
			foodName.setString(foodNameList[5]);
			break;
		case 7:
			foodName.setString(foodNameList[6]);
			break;
		case 8:
			foodName.setString(foodNameList[7]);
			break;
		case 9:
			foodName.setString(foodNameList[8]);
			break;

		}*/

		scoreNow.setString(std::to_string(scoreDisplay));
		deltaTime = clock.restart().asSeconds();
		if (gameStateMachine == 2)
		{
			Timer += clockTimer.restart().asSeconds();
			if (intialTime == 1)
			{
				limitTime = 21 + Timer;
				intialTime = 0;
			}
			distTime = (int)floor(limitTime - Timer);
			if (distTime <= 0)
			{
				distTime = 0;
				gameStateMachine = 4;
				int endStageScore = (int)buttonStatus;
				scoreStage.setString(std::to_string(endStageScore));
			}
			std::cout << floor(distTime) << std::endl;
		}
		
		showTimer.setString(std::to_string(distTime));
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (gameStateMachine)
			{
			case 1:
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Left:
						menu.MoveUp();
						break;

					case sf::Keyboard::Right:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							std::cout << "PlayButton" << std::endl;
							gameStateMachine = 5;
							//shapeSpriteCharacter.setPosition({ 200.f, 200.f });

							bgMusic.stop();

							break;
						case 1:
							std::cout << "OptionButton" << std::endl;
							break;
						case 2:
							window.close();
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					window.close();

					break;

				}
				break;
			case 2:

				break;
			}
			
		}
		if (gameStateMachine == 2)
		{
			//Set Object type ID if 1 = Wall 2 = Interact 3 = Buff
			//Sent CurrentObjectID //Return Object ID
		}
		if (gameStateMachine == 3)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				gameStateMachine = 2;
			}
		}
		if (gameStateMachine == 5)
		{
			if (event.type == sf::Event::TextEntered)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					gameStateMachine = 3;
				}
				if (event.text.unicode != 0x000008)
				{
					playerInput.insert(playerInput.getSize(), event.text.unicode);
					playerText.setString(playerInput);
					sf::sleep(delay);
				}
				else
				{
					if (playerInput.getSize() != 0)
					{
						playerInput.erase(playerInput.getSize() - 1, 1);
						playerText.setString(playerInput);
						sf::sleep(delay);
					}
					
				}
			}
		}
		
		
		switch (gameStateMachine)
		{
		case 1:
			window.clear();
			window.draw(shapeSprite);
			menu.draw(window);
			window.display();
			break;
		case 3:
			window.clear();
			window.draw(stagePageDist1);
			window.display();
			break;
		case 4:
			window.clear();
			window.draw(stagePageDistEnd1);
			window.draw(scoreStage);
			window.display();
			break;
		case 5:
			window.clear();
			window.draw(stagePageName);
			window.draw(playerText);
			window.display();
			break;
		case 2:
			window.clear();
			window.draw(mapBgSprite);
			PlayerA.Draw(window);
			PlayerA.Update(deltaTime);
			Collider playerCollision = PlayerA.GetCollider();
			buttonStatusTemp = &buttonStatus;
			platformOven.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp,5.0f, statusTemp,&scoreDisplay, &receiptList[currentMenu][nextObjectRequest]);
			platformRefri.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 0.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest]);
			platformDeliver.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 6.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest]);
			platformFryer.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 4.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest]);

			platformLeft.GetCollider().CheckCollision(playerCollision, 1.0f,0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp);
			platformRight.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp);
			platformTop.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp);
			platformBottom.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp);
			//window.draw(shapeSpriteCharacter);
			if (BDishStatus[0] == 1)
			{
				
				platformBDish.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[0], &scoreDisplay,&nextObjectTemp);
				platformBDish.Draw(window);
			}
			platformFryer.Draw(window);
			platformOven.Draw(window);
			platformRefri.Draw(window);
			platformDeliver.Draw(window);
			platformLeft.Draw(window);
			platformRight.Draw(window);
			window.draw(scoreboard);
			window.draw(scoreNow);
			window.draw(titleTimer);
			window.draw(showTimer);
			window.draw(foodMenuTitle);
			window.draw(requiredIntMenu);
			window.draw(foodNameTitle);
			window.draw(foodName);
			window.display();
			break;
		
		}
		
		
	}
}