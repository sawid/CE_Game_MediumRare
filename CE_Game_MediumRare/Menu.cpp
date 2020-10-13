#define SFML_NO_DEPRECATED_WARNINGS
#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("DB.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(50);
	menu[0].setColor(sf::Color::Black);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(20, 10));

	menu[1].setFont(font);
	menu[1].setCharacterSize(50);
	menu[1].setColor(sf::Color::Color(255, 193, 54));
	menu[1].setString("Leader Board");
	menu[1].setPosition(sf::Vector2f(143, 10));

	menu[2].setFont(font);
	menu[2].setCharacterSize(50);
	menu[2].setColor(sf::Color::Color(255, 193, 54));
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(420, 10));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::Color(255, 193, 54));
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Black);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::Color(255, 193, 54));
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Black);
	}
}