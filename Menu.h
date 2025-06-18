#pragma once
#include"SFML/Graphics.hpp"
#define max_number_of_items 3
class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() 
	{
		
		return selectedItemIndex; 
	}

public:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[max_number_of_items];

};

