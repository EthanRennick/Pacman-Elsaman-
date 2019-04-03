// Game class declaration
#pragma once

#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function

#include "Cell.h"   // include Cell header file
#include "Pacman.h"   // include Pacman header file
#include "Ghost.h"   // include Ghost header file
#include "Bullet.h"
#include "Globals.h"
#include "Particles.h"
#include <string>
//sound
#include <SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Sound.hpp>
class Game
{
	// private data members
	// put your game objects here eg 2D array and Pacman object and 1D array of ghosts objects etc.

	//objects
	sf::RenderWindow window;   //game window
	Cell maze[MAX_ROWS][MAX_COLS]; //2d array to create the maze
	Pacman pacman;
	Ghost ghost[MAX_GHOSTS];
	Bullet bullets[MAX_BULLETS];
	//sprites
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	sf::Texture gamePlayTexture;
	sf::Sprite gamePlaySprite;
	sf::Texture helpTexture;
	sf::Sprite helpSprite;
	sf::Texture gameOverTexture;
	sf::Sprite gameOverSprite;
	sf::Texture victoryTexture;
	sf::Sprite  victorySprite;
	sf::Texture scoreTexture;
	sf::Sprite  scoreSprite;
	//player name string
	std::string playerName;


public:
	//sounds
	//sf::SoundBuffer musicBuffer; //game music
	//sf::Sound musicSound;

	//sf::SoundBuffer menumusicBuffer; //menu music
	//sf::Sound menumusicSound;



	sf::SoundBuffer throwBuffer; //music elsa makes when throwing snowballs
	sf::Sound throwSound;

	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text to write on the screen
	//counters to control movement turns
	int counter = 10;
	int ghostCounter[MAX_GHOSTS] = { 10,10,10,10 };
	//screen controls
	bool menu = true;
	bool help = false;
	bool gameOver = false; //has game ended?
	bool gamePlay = false;
	bool acceptName = false;
	bool winGame = false;
	//music controls
	bool menumusic = false;
	bool music = false;
	bool stopGame =false;
	bool scoreBoard = false;
	bool scoreDisplayed = false;
	sf::String playerNames[10];
	sf::String playerDisplay;

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
	void	totalGameReset();
	void updateGamePlay();
	void updateMenuAndInput();
	void drawTheCorrectScreen();
	void bulletFiring();
};

