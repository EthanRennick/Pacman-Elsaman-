#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"
#include "Cell.h"
#include"Particles.h"

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
	int invincible;
	

public:
	Pacman();
	ParticleSystemGold playerParticlesGold;
	ParticleSystemBlood playerParticlesBlood;
	void move(Cell t_maze[][MAX_COLS]); // moves the player via keyboard input� changes its row or column, boundary checking can be done within the move function
	void loadImages();
	sf::Vector2f getPosition();
	void setPosition();
	sf::Sprite getBody();
	void draw(sf::RenderWindow &t_window);
	void collectGold(Cell t_maze[][MAX_COLS]);
	int getGold();
	int getLives();
	void collisionWithGhosts(int t_ghostRow, int t_ghostCol,bool &t_gameOver,bool &t_gamePlay);
	
	//eat(); // the player eats a pellet and his score increases
	//die(); // if lives 0 game over & call respawn function else take away 1 life
	//respawn(); // causes the player to be reset to a starting position

	//collision(); // if the player moves into a cell containing a ghost the player loses a life.


};