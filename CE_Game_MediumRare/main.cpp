#define SFML_NO_DEPRECATED_WARNINGS
#include "Menu.h";
#include "GameMain.h"
#include "Player.h"
#include "Platform.h";



int main()
{
	int gameStateMachine = 1;
	int animationFrame = 0;
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
	bgMusic.play();

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
	

	////// Character

	Player PlayerA(&playerTexture, sf::Vector2u(4, 4), 0.3f,200.0f);

	////// Platform

	Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f));
	Platform platform2(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 400.0f));
	Platform platformLeft(nullptr, sf::Vector2f(400.0f, 1500.0f), sf::Vector2f(75.0f, 0.0f));
	Platform platformRight(nullptr, sf::Vector2f(200.0f, 1500.0f), sf::Vector2f(1105.0f, 0.0f));
	Platform platformTop(nullptr, sf::Vector2f(1200.0f, 1100.0f), sf::Vector2f(505.0f, -550.0f));
	Platform platformBottom(nullptr, sf::Vector2f(1200.0f, 1100.0f), sf::Vector2f(505.0f, 1270.0f));

	////// Variable Pointer
	float deltaTime = 0.0f;
	float buttonStatus = 1.0f;
	float* buttonStatusTemp;
	float bStatusTemp = 0.0f;
	sf::Clock clock;
	/*sf::Sprite shapeSpriteCharacter;
	shapeSpriteCharacter.setTexture(playerTexture);
	int spriteSizeX = playerTexture.getSize().x / 4;
	int spriteSizeY = playerTexture.getSize().y / 4;

	shapeSpriteCharacter.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	shapeSpriteCharacter.setPosition({ -200.f, -200.f });*/
	////// Object

	////// Menu
	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
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
							gameStateMachine = 2;
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
			//Set Object type ID if 1 = Wall 2 = Interact
			//Sent CurrentObjectID //Return Object ID
		}
		
		
		switch (gameStateMachine)
		{
		case 1:
			window.clear();
			window.draw(shapeSprite);
			menu.draw(window);
			window.display();
			break;
		case 2:
			window.clear();
			window.draw(mapBgSprite);
			PlayerA.Draw(window);
			PlayerA.Update(deltaTime);
			Collider playerCollision = PlayerA.GetCollider();
			buttonStatusTemp = &buttonStatus;
			platform1.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f, buttonStatusTemp,1.0f);
			platform2.GetCollider().CheckCollision(playerCollision, 1.0f, 1.0f,buttonStatusTemp,2.0f);
			platformLeft.GetCollider().CheckCollision(playerCollision, 1.0f,0.0f, &bStatusTemp,0.0f);
			platformRight.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f);
			platformTop.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f);
			platformBottom.GetCollider().CheckCollision(playerCollision, 1.0f, 0.0f, &bStatusTemp,0.0f);
			//window.draw(shapeSpriteCharacter);
			platform1.Draw(window);
			platformLeft.Draw(window);
			platformRight.Draw(window);
			window.display();
			break;
		}
		
		
	}
}

