#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"

class Pacman
{
	// private data members

	sf::Texture texture;	   //texture for elsa player
	sf::Sprite sprite; 	   //sprite used to represent elsa player

	int row;		  //stores the row the elsa is in within 2D array
	int col;		  //stores the column the elsa is in within 2D array
	int score;		  //players score
	int lives;		  //contains players lives
	int direction;	  //the direction the player is facing in
	bool alive;		  //is the player alive


public:
	Pacman();
	void Pacman::move(Game levelData[MAX_ROWS][MAX_COLS]); // moves the player via keyboard input– changes its row or column, boundary checking can be done within the move function
	void loadImages();
	sf::Vector2f getPosition();
	void setPosition();
	sf::Sprite getBody();

	//eat(); // the player eats a pellet and his score increases
	//die(); // if lives 0 game over & call respawn function else take away 1 life
	//respawn(); // causes the player to be reset to a starting position

	//collision(); // if the player moves into a cell containing a ghost the player loses a life.


};