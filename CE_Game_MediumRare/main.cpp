#define SFML_NO_DEPRECATED_WARNINGS
// Food Menu
#include "Menu.h";
#include "GameMain.h"
#include "Player.h"
#include "Platform.h";
#include <sstream>
#include <string>
#include <math.h>
#include <fstream>

int main()
{

	srand(static_cast<unsigned int>(time(nullptr)));
	// General Variable
	int gameStateMachine = 1;
	int animationFrame = 0;
	int BDishStatus[10] = { 1,1,1,1,1,1,1,1,1,1 };
	int BEggStatus[10] = { 1,1,1,1,1,1,1,1,1,1 };
	int highscoreSet[5];
	std::string ingredient[27] = { "Raw Chicken","Raw Porkchop","Papaya","Raw Shrimp","Raw Chicken","Vegetable","Chrispy Porkchop","Dough","Noodle Pasta"
		,"Sliced Raw Chicken","Krapao Gai","Sliced Raw Porkchop","Ko Moo Yang","Sliced Papaya","Som Tum","Cooked Shrimp","Tom Yum Kung","Grinded Raw Chicken","Gai Tom Nam Pla"
		,"Cleaned Vegetable","Salad","Grinded Chrispy Porkchop","Krapao Mookob","Sliced Dough","Pizza","Grinded Noodle Pasta","Spaghetti"};
	std::string foodNameList[10] = { "Krapao Gai","Ko Moo Yang","Som Tum","Tom Yum Kung","Gai Tom Nam Pla","Salad","Krapao Mookob","Pizza","Spaghetti" };
	std::string objectName[7] = { "Refrigerator","Oven","Cooking Basin","Grinder","Fryer Machine","Slicer","Delivery Point" };
	float receiptList[9][4] = { { 0,5,4,6 },{ 0,5,1,6 },{ 0,5,2,6 },{ 0,2,4,6 },{ 0,3,1,6 },{ 0,2,3,6 },{ 0,3,4,6 },{ 0,5,1,6 },{ 0,3,1,6 } };
	int receiptNameList[9][3] = { { 0,9,10 },{ 1,11,12 },{ 2,13,14 },{ 3,15,16 },{ 4,17,18 },{ 5,19,20 },{ 6,21,22 },{ 7,23,24 },{ 8,25,26 } };
	float BPosition[24];

	for (int low = 0; low < 24; low++)
	{
		float randnum1 = (rand() % 500) + 300;
		BPosition[low] = randnum1;
	}

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
	sf::Texture SideLeft;
	if (!SideLeft.loadFromFile("Asset/Image/Game-Map-Side_Left.jpg"))
	{
		std::cout << "Load Title failed" << std::endl;
	}
	sf::Texture SideRight;
	if (!SideRight.loadFromFile("Asset/Image/Game-Map-Side_Right.jpg"))
	{
		std::cout << "Load Title failed" << std::endl;
	}
	sf::Texture SideTransparent;
	if (!SideTransparent.loadFromFile("Asset/Image/Game-Map-Side_Transparent.png"))
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
	bgMusic.play();

	////// Sound Effect
	sf::SoundBuffer soundBufferStove;
	if (!soundBufferStove.loadFromFile("Asset/Sound/Stove.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundStove;
	soundStove.setBuffer(soundBufferStove);

	sf::SoundBuffer soundBufferBasin;
	if (!soundBufferBasin.loadFromFile("Asset/Sound/Basin.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundBasin;
	soundBasin.setBuffer(soundBufferBasin);

	sf::SoundBuffer soundBufferDeliver;
	if (!soundBufferDeliver.loadFromFile("Asset/Sound/Deliver.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundDeliver;
	soundDeliver.setBuffer(soundBufferDeliver);

	sf::SoundBuffer soundBufferFryer;
	if (!soundBufferFryer.loadFromFile("Asset/Sound/Fryer.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundFryer;
	soundFryer.setBuffer(soundBufferFryer);

	sf::SoundBuffer soundBufferGrinder;
	if (!soundBufferGrinder.loadFromFile("Asset/Sound/Grinder.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundGrinder;
	soundGrinder.setBuffer(soundBufferGrinder);

	sf::SoundBuffer soundBufferRefri;
	if (!soundBufferRefri.loadFromFile("Asset/Sound/Refri.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundRefri;
	soundRefri.setBuffer(soundBufferRefri);

	sf::SoundBuffer soundBufferSlicer;
	if (!soundBufferSlicer.loadFromFile("Asset/Sound/Slicer.wav"))
	{
		std::cout << "Load Music failed" << std::endl;
	}
	sf::Sound soundSlicer;
	soundSlicer.setBuffer(soundBufferSlicer);

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

	Platform platformOven(&objectOven, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(570.0f, 90.0f));
	Platform platformRefri(&objectRefri, sf::Vector2f(129.0f, 129.0f), sf::Vector2f(350.0f, 70.0f));
	Platform platformDeliver(&objectDeliver, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(615.0f, 600.0f));
	Platform platformFryer(&objectFryer, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(355.0f, 600.0f));
	Platform platformSlicer(&objectSlicer, sf::Vector2f(129.0f, 129.0f), sf::Vector2f(915.0f, 135.0f));
	Platform platformBasin(&objectBasin, sf::Vector2f(136.0f, 136.0f), sf::Vector2f(915.0f, 285.0f));
	Platform platformGrinder(&objectGrinder, sf::Vector2f(86.0f, 86.0f), sf::Vector2f(915.0f, 555.0f));

	Platform platformBDish(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[0], BPosition[1]));
	Platform platformBDish2(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[2], BPosition[3]));

	Platform platformBDish3(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[4], BPosition[5]));
	Platform platformBDish4(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[6], BPosition[7]));
	Platform platformBDish5(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[8], BPosition[9]));

	Platform platformBDish6(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[10], BPosition[11]));
	Platform platformBDish7(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[12], BPosition[13]));
	Platform platformBDish8(&objectBDish, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[14], BPosition[15]));

	Platform platformBEgg1(&objectBEgg, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[16], BPosition[17]));

	Platform platformBEgg2(&objectBEgg, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[18], BPosition[19]));

	Platform platformBEgg3(&objectBEgg, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[20], BPosition[21]));
	Platform platformBEgg4(&objectBEgg, sf::Vector2f(43.0f, 43.0f), sf::Vector2f(BPosition[22], BPosition[23]));


	// Edge Background
	Platform platformLeft(&SideTransparent, sf::Vector2f(400.0f, 1500.0f), sf::Vector2f(75.0f, 0.0f));
	Platform platformRight(&SideTransparent, sf::Vector2f(200.0f, 1500.0f), sf::Vector2f(1105.0f, 0.0f));
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
	int currentMenu = rand() % 9;
	float nextObjectTemp = 0.0f;
	bool countdownTimerStatus = false;
	int availbleButtonStatus = 1;
	int availbleLimit = 0;
	int cooldownCounter = 0;
	int availbleCooldownCounter = 0;
	int stageStatus = 1;
	int stageTime = 121;
	int endpageStatus = 0;
	int stageCooldownTime;
	int pauseTimeAddStatus = 1;
	int saveGameStatus = 1;
	int soundLimit = 1;
	int soundLimit2 = 1;
	int soundLimit3 = 1;
	int stepTutorial = 1;


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

	sf::Texture stagePage2;
	if (!stagePage2.loadFromFile("Asset/Image/Stage_Page_2.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite stagePageDist2;
	stagePageDist2.setTexture(stagePage2);
	stagePageDist2.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePage3;
	if (!stagePage3.loadFromFile("Asset/Image/Stage_Page_3.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite stagePageDist3;
	stagePageDist3.setTexture(stagePage3);
	stagePageDist3.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	// Pause Menu
	sf::Texture stagePagePause;
	if (!stagePagePause.loadFromFile("Asset/Image/Pause_Page.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite stagePageDistPause;
	stagePageDistPause.setTexture(stagePagePause);
	stagePageDistPause.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	//////////

	sf::Texture stagePage1End;
	if (!stagePage1End.loadFromFile("Asset/Image/Stage_Page_1_End.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageDistEnd1;
	stagePageDistEnd1.setTexture(stagePage1End);
	stagePageDistEnd1.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePage2End;
	if (!stagePage2End.loadFromFile("Asset/Image/Stage_Page_2_End.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageDistEnd2;
	stagePageDistEnd2.setTexture(stagePage2End);
	stagePageDistEnd2.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePage3End;
	if (!stagePage3End.loadFromFile("Asset/Image/Stage_Page_3_End.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageDistEnd3;
	stagePageDistEnd3.setTexture(stagePage3End);
	stagePageDistEnd3.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePageEnding;
	if (!stagePageEnding.loadFromFile("Asset/Image/End_Game_Page.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageDistEnding;
	stagePageDistEnding.setTexture(stagePageEnding);
	stagePageDistEnding.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	Menu menu(window.getSize().x, window.getSize().y);


	sf::Texture stagePageHighScore;
	if (!stagePageHighScore.loadFromFile("Asset/Image/Leader_Page.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageDistHighScore;
	stagePageDistHighScore.setTexture(stagePageHighScore);
	stagePageDistHighScore.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePageTutotial1;
	if (!stagePageTutotial1.loadFromFile("Asset/Image/Tutorial1.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageTutotial1Dist;
	stagePageTutotial1Dist.setTexture(stagePageTutotial1);
	stagePageTutotial1Dist.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePageTutotial2;
	if (!stagePageTutotial2.loadFromFile("Asset/Image/Tutorial2.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageTutotial2Dist;
	stagePageTutotial2Dist.setTexture(stagePageTutotial2);
	stagePageTutotial2Dist.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	sf::Texture stagePageTutotial3;
	if (!stagePageTutotial3.loadFromFile("Asset/Image/Tutorial3.jpg"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite stagePageTutotial3Dist;
	stagePageTutotial3Dist.setTexture(stagePageTutotial3);
	stagePageTutotial3Dist.setTextureRect(sf::IntRect(0, 0, 1280, 720));

	////// Scoreboard

	sf::Font scoreboardFont;
	if (!scoreboardFont.loadFromFile("Sriracha.ttf"))
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
	scoreboard.setCharacterSize(30);
	scoreboard.setColor(sf::Color::White);
	scoreboard.setString("ScoreNow");
	scoreboard.setPosition(sf::Vector2f(65, 10));
	// Scoreboard - ScoreNow
	int scoreDisplay = 0000;
	std::ostringstream scorePrintSS;
	scorePrintSS << scorePrint;
	std::string scorePrintString(scorePrintSS.str());
	sf::Text scoreNow;
	scoreNow.setFont(scoreboardFont);
	scoreNow.setCharacterSize(80);
	scoreNow.setColor(sf::Color::White);
	scoreNow.setString("0000");
	scoreNow.setPosition(sf::Vector2f(55, 45));

	////// Food Menu System

	float requiredInt = 0.0f;
	sf::Text foodMenuTitle;
	foodMenuTitle.setFont(scoreboardFont);
	foodMenuTitle.setCharacterSize(30);
	foodMenuTitle.setColor(sf::Color::White);
	foodMenuTitle.setString("Status");
	foodMenuTitle.setPosition(sf::Vector2f(1100, 155));
	sf::Text requiredIntMenu;
	requiredIntMenu.setFont(scoreboardFont);
	requiredIntMenu.setCharacterSize(30);
	requiredIntMenu.setColor(sf::Color::White);
	requiredIntMenu.setPosition(sf::Vector2f(1050, 225));
	sf::Text foodNameTitle;
	foodNameTitle.setFont(scoreboardFont);
	foodNameTitle.setCharacterSize(30);
	foodNameTitle.setColor(sf::Color::White);
	foodNameTitle.setString("Menu");
	foodNameTitle.setPosition(sf::Vector2f(1110, 10));
	sf::Text foodName;
	foodName.setFont(scoreboardFont);
	foodName.setCharacterSize(30);
	foodName.setColor(sf::Color::White);
	foodName.setString("Null");
	foodName.setPosition(sf::Vector2f(1050, 80));


	// Equipment Indicator System

	sf::Text indicatorTitle;
	indicatorTitle.setFont(scoreboardFont);
	indicatorTitle.setCharacterSize(30);
	indicatorTitle.setColor(sf::Color::White);
	indicatorTitle.setString("Go to This");
	indicatorTitle.setPosition(sf::Vector2f(1075, 300));

	sf::Texture indicatorTexture;
	if (!indicatorTexture.loadFromFile("Asset/Image/None.png"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite indicator;
	indicator.setTexture(indicatorTexture);
	indicator.setTextureRect(sf::IntRect(0, 0, 140, 140));
	indicator.setPosition(sf::Vector2f(1070, 370));

	sf::Texture indicatorTexture2;
	if (!indicatorTexture2.loadFromFile("Asset/Image/None.png"))
	{
		std::cout << "Load failed" << std::endl;
	}

	sf::Sprite indicator2;
	indicator2.setTexture(indicatorTexture2);
	indicator2.setTextureRect(sf::IntRect(0, 0, 140, 140));
	indicator2.setPosition(sf::Vector2f(1020, 470));

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
	titleTimer.setCharacterSize(30);
	titleTimer.setColor(sf::Color::White);
	titleTimer.setString("Time Left");
	titleTimer.setPosition(sf::Vector2f(70, 155));

	sf::Text showTimer;
	showTimer.setFont(scoreboardFont);
	showTimer.setCharacterSize(80);
	showTimer.setColor(sf::Color::White);
	showTimer.setString("90");
	showTimer.setPosition(sf::Vector2f(75, 190));

	sf::Text titleCoolDown;
	titleCoolDown.setFont(scoreboardFont);
	titleCoolDown.setCharacterSize(30);
	titleCoolDown.setColor(sf::Color::White);
	titleCoolDown.setString("Cooldown");
	titleCoolDown.setPosition(sf::Vector2f(70, 300));

	sf::Text coolDownTimer;
	coolDownTimer.setFont(scoreboardFont);
	coolDownTimer.setCharacterSize(80);
	coolDownTimer.setColor(sf::Color::White);
	coolDownTimer.setString("0");
	coolDownTimer.setPosition(sf::Vector2f(110, 335));
	// CooldownTimer System

	sf::Clock clockCooldownTimer;
	float cooldownTimerTime = 0.0f;
	int initialTimerCooldown = 1;
	int limitTimerCooldown = 6;
	int distCooldownTime = 6;

	// Delay System
	sf::Time delay = sf::seconds(0.1);
	 
	//Pause Timer System
	int initalTimePause = 0;
	int timerPause = 0;
	sf::Clock clockTimerPause;
	int pauseTime = 0;
	int initialPauseStatus = 1;
	sf::Time mainTimerPause;

	// Speed Control System

	// HighScoreBoard System
	sf::Text HighScore1;
	HighScore1.setFont(scoreboardFont);
	HighScore1.setCharacterSize(100);
	HighScore1.setColor(sf::Color::White);
	HighScore1.setString("0");
	HighScore1.setPosition(sf::Vector2f(370,160));

	sf::Text HighScore2;
	HighScore2.setFont(scoreboardFont);
	HighScore2.setCharacterSize(100);
	HighScore2.setColor(sf::Color::White);
	HighScore2.setString("0");
	HighScore2.setPosition(sf::Vector2f(370, 260));

	sf::Text HighScore3;
	HighScore3.setFont(scoreboardFont);
	HighScore3.setCharacterSize(100);
	HighScore3.setColor(sf::Color::White);
	HighScore3.setString("0");
	HighScore3.setPosition(sf::Vector2f(370, 360));

	sf::Text HighScore4;
	HighScore4.setFont(scoreboardFont);
	HighScore4.setCharacterSize(100);
	HighScore4.setColor(sf::Color::White);
	HighScore4.setString("0");
	HighScore4.setPosition(sf::Vector2f(370, 460));

	sf::Text HighScore5;
	HighScore5.setFont(scoreboardFont);
	HighScore5.setCharacterSize(100);
	HighScore5.setColor(sf::Color::White);
	HighScore5.setString("0");
	HighScore5.setPosition(sf::Vector2f(370, 560));

	// End Page Title
	sf::Text EndPagePlayerName;
	EndPagePlayerName.setFont(scoreboardFont);
	EndPagePlayerName.setCharacterSize(200);
	EndPagePlayerName.setColor(sf::Color::White);
	EndPagePlayerName.setString("0");
	EndPagePlayerName.setPosition(sf::Vector2f(370, 280));

	sf::Text EndPageFinalScore;
	EndPageFinalScore.setFont(scoreboardFont);
	EndPageFinalScore.setCharacterSize(150);
	EndPageFinalScore.setColor(sf::Color::White);
	EndPageFinalScore.setString("0");
	EndPageFinalScore.setPosition(sf::Vector2f(830, 520));

	while (window.isOpen())
	{
		int effectObjectIDPic = receiptList[currentMenu][nextObjectRequest];
		int effectObjectIDPic2 = receiptList[currentMenu][nextObjectRequest+1];
		if (effectObjectIDPic2 == 7)
		{
			//Assign Variable to 1:1 Data Connective
			effectObjectIDPic2 = 0;
		}
		switch (effectObjectIDPic)
		{
		case 0:
			indicator.setTexture(objectRefri);
			break;
		case 1:
			indicator.setTexture(objectOven);
			break;
		case 2:
			indicator.setTexture(objectBasin);
			break;
		case 3:
			indicator.setTexture(objectGrinder);
			break;
		case 4:
			indicator.setTexture(objectFryer);
			break;
		case 5:
			indicator.setTexture(objectSlicer);
			break;
		case 6:
			indicator.setTexture(objectDeliver);
			break;
		}
		switch (effectObjectIDPic2)
		{
		case 0:
			indicator2.setTexture(objectRefri);
			break;
		case 1:
			indicator2.setTexture(objectOven);
			break;
		case 2:
			indicator2.setTexture(objectBasin);
			break;
		case 3:
			indicator2.setTexture(objectGrinder);
			break;
		case 4:
			indicator2.setTexture(objectFryer);
			break;
		case 5:
			indicator2.setTexture(objectSlicer);
			break;
		case 6:
			indicator2.setTexture(objectDeliver);
			break;
		}
		if (buttonStatus == 4.0f)
		{
			if (soundLimit3 == 1)
			{
				soundDeliver.play();
				soundLimit3 = 0;
			}
			if (currentMenu == 7)
			{
				scoreDisplay += 500;
			}
		 	//currentMenu = 1;
			currentMenu = rand() % 9;
			buttonStatus = 0.0f;
			nextObjectRequest = 0;
			soundLimit2 = 1;
			scoreDisplay += 1000;
			soundLimit3 = 1;
		}
		if (buttonStatus == 1.0f)
		{
			if (soundLimit2 == 1)
			{
				soundRefri.play();
				soundLimit2 = 0;
			}
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
					if (soundLimit == 1)
					{
						soundStove.play();
						soundLimit = 0;
					}
					break;
				case 3:
					objectGrinder.loadFromFile("Asset/Image/Object_4_Grinder_Active.png");
					if (soundLimit == 1)
					{
						soundGrinder.play();
						soundLimit = 0;
					}
					break;
				case 4:
					objectFryer.loadFromFile("Asset/Image/Object_3_Fryer_Active.png");
					if (soundLimit == 1)
					{
						soundFryer.play();
						soundLimit = 0;
					}
					break;
				case 2:
					objectBasin.loadFromFile("Asset/Image/Object_5_Basin_Active.png");
					if (soundLimit == 1)
					{
						soundBasin.play();
						soundLimit = 0;
					}
					break;
				case 5:
					objectSlicer.loadFromFile("Asset/Image/Object_6_Slicer_Active.png");
					if (soundLimit == 1)
					{
						soundSlicer.play();
						soundLimit = 0;
					}
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
					soundStove.stop();
					soundLimit = 1;
					break;
				case 3:
					objectGrinder.loadFromFile("Asset/Image/Object_4_Grinder.png");
					soundGrinder.stop();
					soundLimit = 1;
					break;
				case 4:
					objectFryer.loadFromFile("Asset/Image/Object_3_Fryer.png");
					soundFryer.stop();
					soundLimit = 1;
					break;
				case 2:
					objectBasin.loadFromFile("Asset/Image/Object_5_Basin.png");
					soundBasin.stop();
					soundLimit = 1;
					break;
				case 5:
					objectSlicer.loadFromFile("Asset/Image/Object_6_Slicer.png");
					soundSlicer.stop();
					soundLimit = 1;
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
				limitTime = stageTime + Timer;
				intialTime = 0;
			}
			distTime = (int)floor(limitTime - Timer);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				distTime = 0;
			}
			if (distTime <= 0)
			{
				distTime = 0;
				gameStateMachine = 4;
				int endStageScore = (int)scoreDisplay;
				endpageStatus += 1;
				cooldownCounter = 0;
				initialTimerCooldown = 1;
				countdownTimerStatus = false;
				distCooldownTime = 0;
				buttonStatus = 0.0f;
				nextObjectRequest = 0;
				currentMenu = rand() % 9;
				availbleButtonStatus = 1;
				scoreStage.setString(std::to_string(endStageScore));
				coolDownTimer.setString("0");

				
				objectOven.loadFromFile("Asset/Image/Object_1_Stove.png");
				soundStove.stop();
				objectGrinder.loadFromFile("Asset/Image/Object_4_Grinder.png");
				soundGrinder.stop();
				objectFryer.loadFromFile("Asset/Image/Object_3_Fryer.png");
				soundFryer.stop();
				objectBasin.loadFromFile("Asset/Image/Object_5_Basin.png");
				soundBasin.stop();
				objectSlicer.loadFromFile("Asset/Image/Object_6_Slicer.png");
				soundSlicer.stop();
				soundLimit = 1;
				

			}
			//std::cout << floor(distTime) << std::endl;
			
			if (countdownTimerStatus == true)
			{

				cooldownTimerTime += clockCooldownTimer.restart().asSeconds();
				if (initialTimerCooldown == 1)
				{
					if (stageStatus == 1)
					{
						stageCooldownTime = ((rand() % 3) + 3);
					}
					if (stageStatus == 2)
					{
						stageCooldownTime = ((rand() % 4) + 4);
					}
					if (stageStatus == 3)
					{
						stageCooldownTime = ((rand() % 4) + 5);
					}
					limitTimerCooldown = (stageCooldownTime + 1) + cooldownTimerTime;
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
							gameStateMachine = 11;
							//shapeSpriteCharacter.setPosition({ 200.f, 200.f });

							bgMusic.stop();

							break;
						case 1:
							std::cout << "OptionButton" << std::endl;
							gameStateMachine = 10;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				timerPause = clockTimerPause.restart().asSeconds();
				gameStateMachine = 8;
				pauseTimeAddStatus = 1; 
				initialPauseStatus = 1;
				/*std::cout << nextObjectRequest << std::endl;
				std::cout << cooldownCounter << std::endl;*/
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				gameStateMachine = 9;
				/*std::cout << nextObjectRequest << std::endl;
				std::cout << cooldownCounter << std::endl;*/
			}
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
		if (gameStateMachine == 6)
		{ 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				gameStateMachine = 2;
				stageTime = 91;
				intialTime = 1;
				stageStatus = 2;
				cooldownCounter = 0;
			}
		}
		if (gameStateMachine == 7)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				gameStateMachine = 2;
				stageTime = 81;
				intialTime = 1;
				stageStatus = 3;
				cooldownCounter = 0;

			}
		}
		if (gameStateMachine == 8)
		{
			if (initialPauseStatus == 1)
			{
				initalTimePause = timerPause;
				initialPauseStatus = 0;
			}
			mainTimerPause = clockTimerPause.getElapsedTime();
			pauseTime = (int)floor(initalTimePause - timerPause);
			int printTime = (int)floor(mainTimerPause.asSeconds());
			std::cout << printTime << std::endl;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				
					gameStateMachine = 2;
					limitTime += printTime;
					pauseTimeAddStatus = 0;
					
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				window.close();
			}
		}
		if (gameStateMachine == 10)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				gameStateMachine = 1;
			}
			std::ifstream file_2("Save.txt");
			std::string highscoreShow;
			int iRun = 0;
			int numstrTemp;
			if (file_2.is_open())
			{
				while (file_2 >> highscoreShow)
				{
					numstrTemp = atoi(highscoreShow.c_str());
					highscoreSet[iRun] = numstrTemp;
					iRun++;
				}
				file_2.close();

			}
			HighScore1.setString(std::to_string(highscoreSet[0]));
			HighScore2.setString(std::to_string(highscoreSet[1]));
			HighScore3.setString(std::to_string(highscoreSet[2]));
			HighScore4.setString(std::to_string(highscoreSet[3]));
			HighScore5.setString(std::to_string(highscoreSet[4]));

		}
		if (gameStateMachine == 11)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if (stepTutorial == 1 || stepTutorial == 2)
				{
					stepTutorial++;
					sf::sleep(delay);

				}
				else if (stepTutorial == 3)
				{
					gameStateMachine = 5;
					sf::sleep(delay);
				}
			}
		}
		if (gameStateMachine == 4)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (endpageStatus == 1)
				{
					gameStateMachine = 6;

				}
				else if (endpageStatus == 2)
				{
					gameStateMachine = 7;
				}
			}
		}
		if (endpageStatus == 3)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				gameStateMachine = 9;
			}
		}
		if (gameStateMachine == 9)
		{
			EndPagePlayerName.setString(playerInput);
			EndPageFinalScore.setString(std::to_string(scoreDisplay));
			if (saveGameStatus == 1)
			{
				int num;
				std::ifstream file_("Save.txt");
				std::string highscore;
				int i = 0;
				int numstr;
				int score[5];
				num = scoreDisplay;
				if (file_.is_open())
				{
					while (file_ >> highscore)
					{
						numstr = atoi(highscore.c_str());
						score[i] = numstr;
						i++;
					}
					file_.close();

				}
				int posPoint;
				int joint;
				for (joint = 0; joint < 5; joint++)
				{
					if (num > score[joint])
					{
						posPoint = joint;
						break;
					}
				}
				int size = 5, index = joint;
				int tempI = size - 1; // Not i=size (this is the size of the array not the last index)
				while (tempI > index) {
					score[tempI] = score[tempI - 1];
					tempI--;
				}
				score[tempI] = num;
				std::ofstream myfile;
				myfile.open("Save.txt");
				for (int m = 0; m < 5; m++)
				{
					myfile << score[m];
					if (m != 4)
					{
						myfile << "\n";
					}
				}
				myfile.close();
				saveGameStatus = 0;
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
		case 6:
			window.clear();
			window.draw(stagePageDist2);
			window.display();
			break;
		case 7:
			window.clear();
			window.draw(stagePageDist3);
			window.display();
			break;
		case 8:
			window.clear();
			window.draw(stagePageDistPause);
			window.display();
			break;
		case 9:
			window.clear();
			window.draw(stagePageDistEnding);
			window.draw(EndPagePlayerName);
			window.draw(EndPageFinalScore);
			window.display();
			break;
		case 10:
			window.clear();
			window.draw(stagePageDistHighScore);
			window.draw(HighScore1);
			window.draw(HighScore2);
			window.draw(HighScore3);
			window.draw(HighScore4);
			window.draw(HighScore5);
			window.display();
			break;
		case 11:
			window.clear();
			if (stepTutorial == 1)
			{
				window.draw(stagePageTutotial1Dist);
			}
			else if (stepTutorial == 2)
			{
				window.draw(stagePageTutotial2Dist);
			}
			else if (stepTutorial == 3)
			{
				window.draw(stagePageTutotial3Dist);
			}
			window.display();
			break;
		case 4:
			window.clear();
			if (endpageStatus == 1)
			{
				window.draw(stagePageDistEnd1);
			}
			else if (endpageStatus == 2)
			{
				window.draw(stagePageDistEnd2);
			}
			else if (endpageStatus == 3)
			{
				window.draw(stagePageDistEnd3);
			}
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
			if (BDishStatus[0] == 1 && stageStatus == 1)
			{
				platformBDish.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[0], &scoreDisplay,&nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish.Draw(window);
			}
			if (BDishStatus[1] == 1 && stageStatus == 1)
			{
				platformBDish2.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[1], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish2.Draw(window);
			}

			if (BDishStatus[2] == 1 && stageStatus == 2)
			{
				platformBDish3.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[2], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish3.Draw(window);
			}

			if (BDishStatus[3] == 1 && stageStatus == 2)
			{
				platformBDish4.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[3], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish4.Draw(window);
			}
			if (BDishStatus[4] == 1 && stageStatus == 2)
			{
				platformBDish5.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[4], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish5.Draw(window);
			}

			if (BDishStatus[5] == 1 && stageStatus == 3)
			{
				platformBDish6.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[5], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish6.Draw(window);
			}

			if (BDishStatus[6] == 1 && stageStatus == 3)
			{
				platformBDish7.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[6], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish7.Draw(window);
			}
			if (BDishStatus[7] == 1 && stageStatus == 3)
			{
				platformBDish8.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BDishStatus[7], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBDish8.Draw(window);
			}

			if (BEggStatus[0] == 1 && stageStatus == 1)
			{
				platformBEgg1.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BEggStatus[0], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBEgg1.Draw(window);
			}


			if (BEggStatus[1] == 1 && stageStatus == 2)
			{
				platformBEgg2.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BEggStatus[1], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBEgg2.Draw(window);
			}

			if (BEggStatus[2] == 1 && stageStatus == 3)
			{
				platformBEgg3.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BEggStatus[2], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBEgg3.Draw(window);
			}
			if (BEggStatus[3] == 1 && stageStatus == 3)
			{
				platformBEgg4.GetCollider().CheckCollision(playerCollision, 1.0f, 2.0f, buttonStatusTemp, 3.0f, &BEggStatus[3], &scoreDisplay, &nextObjectTemp, &availbleButtonStatus, &cooldownCounter);
				platformBEgg4.Draw(window);
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
			window.draw(indicator);
			//window.draw(indicator2);
			window.draw(indicatorTitle);
			window.display();
			break;
		}
	}
}