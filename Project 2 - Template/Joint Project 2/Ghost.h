#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"
class Ghost
{
	// private data members
	sf::Texture ghostTextureLeft;
	sf::Texture ghostTextureRight;

	sf::Sprite ghostSprite;
	int lives;
	bool alive;
	int row;
	int col;
	int randomDirectionNumber;



public:
	Ghost();
	void loadImages();
	sf::Vector2f getPosition();
	void setPosition();
	sf::Sprite getBody();
	void draw(sf::RenderWindow &t_window);
	void move(int t_maze[][MAX_COLS]); // moves the ghost -> changes its row or column, boundary checking can be done within the move function

};
