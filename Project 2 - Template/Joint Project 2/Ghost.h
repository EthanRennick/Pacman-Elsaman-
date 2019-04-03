#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"
#include "Cell.h"
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
	int health;
	int respawnCount;
	sf::RectangleShape healthBar;

public:
	Ghost();
	void loadImages();
	sf::Vector2f getPosition();
	void setPosition();
	sf::Sprite getBody();
	void draw(sf::RenderWindow &t_window);
	void move(Cell t_maze[][MAX_COLS]); // moves the ghost -> changes its row or column, boundary checking can be done within the move function
	int getRow();
	int getCol();
	void setGhostPos(int pos1, int pos2);
	void respawnGhost();
	void lowerHealthBar();
	void destroy();
	sf::RectangleShape getHealthBar();

};
