#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"
#include "Cell.h"

class Pacman
{
	// private data members

	sf::Texture textureLeft;	   //texture for elsa player
	sf::Texture textureRight;		//texture for when she looks right
	sf::Sprite sprite; 	   //sprite used to represent elsa player

	int row;		  //stores the row the elsa is in within 2D array
	int col;		  //stores the column the elsa is in within 2D array
	int score;		  //players score
	int lives;		  //contains players lives
	bool alive;		  //is the player alive
	int treasure;


public:
	Pacman();
	void move(int t_maze[][MAX_COLS]); // moves the player via keyboard input– changes its row or column, boundary checking can be done within the move function
	void loadImages();
	sf::Vector2f getPosition();
	void setPosition();
	sf::Sprite getBody();
	void draw(sf::RenderWindow &t_window);
	void collectGold(int t_maze[][MAX_COLS]);
	int getGold();
	
	//eat(); // the player eats a pellet and his score increases
	//die(); // if lives 0 game over & call respawn function else take away 1 life
	//respawn(); // causes the player to be reset to a starting position

	//collision(); // if the player moves into a cell containing a ghost the player loses a life.


};