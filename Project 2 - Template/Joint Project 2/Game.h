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

	int levelData[MAX_ROWS][MAX_COLS] = { 
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,0,1,0 },
	{ 0,1,0,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0 },
	{ 0,1,0,0,0,0,0,0,1,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,1,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,1,1,1,1,1,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,0 },
	{ 0,1,1,1,1,0,1,1,1,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0 }, 
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,1,0,1,1,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	};


public:
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen

public:	  // declaration of member functions	
	Game();  // default constructor
	void	LoadContent();
	void	run();
	void	update();
	void	draw();
	void	setUpGame();
	void	setUpMaze();
	void	drawMaze();
};
