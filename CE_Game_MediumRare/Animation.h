#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
class Animation
{
public:
	Animation(sf::Texture* texture,sf::Vector2u imageCount, float switchTime);
	~Animation();

	void Update(int row, float deltaTime);
public:
	sf::IntRect uvRect;
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

