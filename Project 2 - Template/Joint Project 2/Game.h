// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Cell.h"   // include Cell header file
#include "Pacman.h"   // include Pacman header file
#include "Ghost.h"   // include Ghost header file
#include "Globals.h"

class Game
{
	// private data members
	// put your game objects here eg 2D array and Pacman object and 1D array of ghosts objects etc.


	sf::RenderWindow window;   //game window
	Cell maze[MAX_ROWS][MAX_COLS]; //2d array to create the maze
	Pacman pacman;
	Ghost ghost[MAX_GHOSTS];

	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	sf::Texture gamePlayTexture;
	sf::Sprite gamePlaySprite;
	sf::Texture helpTexture;
	sf::Sprite helpSprite;
	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;

	sf::String playerName;
	


public:
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	int counter = 10;
	int ghostCounter[MAX_GHOSTS] = { 10,10,10,10 };
	bool menu = false;
	bool help = false;
	bool gamePlay = false;
	bool gameOver = false;

public:	  // declaration of member functions	
	Game();  // default constructor
	void	LoadContent();
	void	run();
	void	update();
	void	draw();
	void	setUpGame();
	void	setUpMaze();
	void	drawMaze();
	void	setupGhosts();
};

