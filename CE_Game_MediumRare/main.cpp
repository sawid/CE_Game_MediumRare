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

	Platform platformOven(&objectOven, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(425.0f, 145.0f));
	Platform platformRefri(&objectRefri, sf::Vector2f(129.0f, 129.0f), sf::Vector2f(415.0f, 600.0f));
	Platform platformDeliver(&objectDeliver, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(615.0f, 600.0f));
	Platform platformFryer(&objectFryer, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(615.0f, 135.0f));
	Platform platformSlicer(&objectSlicer, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(715.0f, 135.0f));
	Platform platformBasin(&objectBasin, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(795.0f, 245.0f));
	Platform platformGrinder(&objectGrinder, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(715.0f, 405.0f));
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
	bool countdownTimerStatus = false;
	int availbleButtonStatus = 1;
	int availbleLimit = 0;
	int cooldownCounter = 0;
	int availbleCooldownCounter = 0;

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
	foodMenuTitle.setString("Holding Ingredient");
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

	sf::Text titleCoolDown;
	titleCoolDown.setFont(scoreboardFont);
	titleCoolDown.setCharacterSize(50);
	titleCoolDown.setColor(sf::Color::Black);
	titleCoolDown.setString("Cooldown Left");
	titleCoolDown.setPosition(sf::Vector2f(20, 280));

	sf::Text coolDownTimer;
	coolDownTimer.setFont(scoreboardFont);
	coolDownTimer.setCharacterSize(50);
	coolDownTimer.setColor(sf::Color::Black);
	coolDownTimer.setString("0");
	coolDownTimer.setPosition(sf::Vector2f(20, 330));
	// CooldownTimer System

	sf::Clock clockCooldownTimer;
	float cooldownTimerTime = 0.0f;
	int initialTimerCooldown = 1;
	int limitTimerCooldown = 6;
	int distCooldownTime = 6;

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
			scoreDisplay += 1000;
		}
		if (buttonStatus == 1.0f)
		{
			nextObjectRequest = 1;

		}
		else if (buttonStatus == 2.0f)
		{
			if (availbleLimit == 1)
			{
				if (cooldownCounter == 2)
				{
					
				}
				if (cooldownCounter == 3)
				{
					nextObjectRequest = 2;
					cooldownCounter = 0;
					availbleLimit = 0;
				}
				
			}
			else if (cooldownCounter == 1)
			{
				availbleButtonStatus = 0;
				countdownTimerStatus = true;
			}
		}
		else if (buttonStatus == 3.0f)
		{
			if (availbleLimit == 1)
			{
				if (cooldownCounter == 2)
				{
				}
				if (cooldownCounter == 3)
				{
					nextObjectRequest = 3;
					availbleLimit = 0;
					cooldownCounter = 0;
				}

			}
			else if (cooldownCounter == 1)
			{
				availbleButtonStatus = 0;
				countdownTimerStatus = true;
			}
		}
		if (buttonStatus == 0.0f)
		{
			foodName.setString(foodNameList[currentMenu]);
			requiredIntMenu.setString("-");
		}
		else
		{
			if (cooldownCounter == 1)
			{
				foodName.setString(foodNameList[currentMenu]);
				requiredIntMenu.setString("Undercooking");
				int effectObjectID = receiptList[currentMenu][nextObjectRequest];
				switch (effectObjectID)
				{
				case 1:
					objectOven.loadFromFile("Asset/Image/Object_1_Stove_Active.png");
					break;
				case 3:
					objectGrinder.loadFromFile("Asset/Image/Object_4_Grinder_Active.png");
					break;
				case 4:
					objectFryer.loadFromFile("Asset/Image/Object_3_Fryer_Active.png");
					break;
				case 2:
					objectBasin.loadFromFile("Asset/Image/Object_5_Basin_Active.png");
					break;
				case 5:
					objectSlicer.loadFromFile("Asset/Image/Object_6_Slicer_Active.png");
					break;
				}
			}
			else if (cooldownCounter == 2)
			{
				foodName.setString(foodNameList[currentMenu]);
				requiredIntMenu.setString("Ready to Get!");
				int effectObjectID = receiptList[currentMenu][nextObjectRequest];
				switch (effectObjectID)
				{
				case 1:
					objectOven.loadFromFile("Asset/Image/Object_1_Stove.png");
					break;
				case 3:
					objectGrinder.loadFromFile("Asset/Image/Object_4_Grinder.png");
					break;
				case 4:
					objectFryer.loadFromFile("Asset/Image/Object_3_Fryer.png");
					break;
				case 2:
					objectBasin.loadFromFile("Asset/Image/Object_5_Basin.png");
					break;
				case 5:
					objectSlicer.loadFromFile("Asset/Image/Object_6_Slicer.png");
					break;
				}
			}
			else
			{
				foodName.setString(foodNameList[currentMenu]);
				requiredIntMenu.setString(ingredient[receiptNameList[currentMenu][(int)buttonStatus - 1]]);
			}
			
		}
		

		scoreNow.setString(std::to_string(scoreDisplay));
		deltaTime = clock.restart().asSeconds();
		if (gameStateMachine == 2)
		{
			Timer += clockTimer.restart().asSeconds();
			if (intialTime == 1)
			{
				limitTime = 91 + Timer;
				intialTime = 0;
			}
			distTime = (int)floor(limitTime - Timer);
			if (distTime <= 0)
			{
				distTime = 0;
				gameStateMachine = 4;
				int endStageScore = (int)scoreDisplay;
				scoreStage.setString(std::to_string(endStageScore));
			}
			//std::cout << floor(distTime) << std::endl;
			
			if (countdownTimerStatus == true)
			{
				cooldownTimerTime += clockCooldownTimer.restart().asSeconds();
				if (initialTimerCooldown == 1)
				{
					limitTimerCooldown = 6 + cooldownTimerTime;
					initialTimerCooldown = 0;
				}
				distCooldownTime = (int)floor(limitTimerCooldown - cooldownTimerTime);
				if (distCooldownTime <= 0)
				{
					distCooldownTime = 0;
					availbleButtonStatus = 1;
					countdownTimerStatus = false;
					availbleLimit = 1;
					initialTimerCooldown = 1;
					cooldownCounter = 2;
				}
				coolDownTimer.setString(std::to_string(distCooldownTime));
			}
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
			platformOven.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp,1.0f, statusTemp,&scoreDisplay, &receiptList[currentMenu][nextObjectRequest],&availbleButtonStatus,&cooldownCounter);
			platformRefri.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 0.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest], &availbleButtonStatus, &cooldownCounter);
			platformDeliver.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 6.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest], &availbleButtonStatus, &cooldownCounter);
			platformFryer.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 4.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest], &availbleButtonStatus, &cooldownCounter);
			platformSlicer.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 5.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest], &availbleButtonStatus, &cooldownCounter);
			platformBasin.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 2.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest], &availbleButtonStatus, &cooldownCounter);
			platformGrinder.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp, 3.0f, statusTemp, &scoreDisplay, &receiptList[currentMenu][nextObjectRequest], &availbleButtonStatus, &cooldownCounter);

			platformLeft.GetCollider().CheckCollision(playerCollision, 1.0f,0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
			platformRight.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
			platformTop.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
			platformBottom.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f, statusTemp, &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
			//window.draw(shapeSpriteCharacter);
			if (BDishStatus[0] == 1)
			{
				
				platformBDish.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[0], &scoreDisplay,&nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish.Draw(window);
			}
			platformFryer.Draw(window);
			platformOven.Draw(window);
			platformRefri.Draw(window);
			platformDeliver.Draw(window);
			platformSlicer.Draw(window);
			platformBasin.Draw(window);
			platformGrinder.Draw(window);
			platformLeft.Draw(window);
			platformRight.Draw(window);
			window.draw(scoreboard);
			window.draw(scoreNow);
			window.draw(coolDownTimer);
			window.draw(titleTimer);
			window.draw(titleCoolDown);
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