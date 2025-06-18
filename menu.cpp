#include "menu.h"

Menu::Menu(float width,float height)
{
	
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(width / 2, height / (max_number_of_items + 1 ) * 1);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Load");
	menu[1].setPosition(width / 2, height / (max_number_of_items + 1) * 2);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exits");
	menu[2].setPosition(width / 2, height / (max_number_of_items + 1) * 3);

	selectedItemIndex = 0;
}


Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < max_number_of_items; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex  - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}

}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < max_number_of_items)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}

}