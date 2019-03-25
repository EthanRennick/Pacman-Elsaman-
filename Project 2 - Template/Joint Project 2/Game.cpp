// Name: 
// Login: 
// Date: 
// Approximate time taken: 
//---------------------------------------------------------------------------
// Project 2 -  Description Template
// ---------------------------------------------------------------------------
// Known Bugs:
// List your bugs here

//////////////////////////////////////////////////////////// 
// Headers for SFML projects
// include correct library file for release and debug versions
// include iostream for console window output
// include 
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"   // include Game header file

//main
int main()
{
	Game aGame;
	aGame.LoadContent();
	aGame.run();

	return 0;
}

Game::Game() : window(sf::VideoMode(832, 928), "Project 2 - Elsaman")
// Default constructor
{

}


void Game::LoadContent()
// Load the font file & set up message
{
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}
	
	// set up the message string 
	m_message.setFont(m_font);  // set the font for the text
	m_message.setCharacterSize(24); // set the text size
	m_message.setFillColor(sf::Color::White); // set the text colour
	m_message.setPosition(10, 10);  // its position on the screen

}


void Game::run()
{
	srand(time(nullptr)); // set the seed once
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	setUpGame(); //setup initialise stuff

	// the clock object keeps the time.
	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			update();
			draw();
			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}



void Game::update()
// This function takes the keyboard input and updates the game world
{
	counter--;
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		ghostCounter[i]--;
	}

	// update any game variables here ...
	if (counter == 0)
	{
		pacman.move(maze); //pacman movement
		pacman.collectGold(maze); //pacman gold collecting (pellets)
		pacman.playerParticlesGold.Update();
		pacman.playerParticlesBlood.Update();

		counter = 10; //reset pacman timer
	}

	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		if (ghostCounter[i] == 0) //if timer is empty
		{	
			ghost[i].move(maze); //ghost moving
			pacman.collisionWithGhosts(ghost[i].getRow(), ghost[i].getCol()); //has pacman collided with ghost?
			ghostCounter[i] = 10; //reset timer
		}
	}
}


void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	window.clear();

	
	drawMaze();
	pacman.draw(window);
	pacman.playerParticlesGold.Draw(window);
	pacman.playerParticlesBlood.Draw(window);
	for (int i = 0; i < MAX_GHOSTS; i++)
	{
		ghost[i].draw(window);
	}
	m_message.setPosition(2, 2);
	m_message.setString("Treasure Collected: " + std::to_string(pacman.getGold()));
	window.draw(m_message);  // write message to the screen

	m_message.setPosition(2, 30);
	m_message.setString("Lives: " + std::to_string(pacman.getLives()));
	window.draw(m_message);  // write message to the screen
	window.display();
}


void Game::setUpGame()
// Initialize the game objects to play a new game
{
	setUpMaze(); //initialise data like walls and pellets
	setupGhosts(); //move ghosts to new positions
}


void Game::setUpMaze()
// Setup the sprites for the 2D maze game
{
	//level data (local)
	int levelData[MAX_ROWS][MAX_COLS] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1, },
	{ 1,2,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,2,1, },
	{ 1,2,1,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,1,2,1, },
	{ 1,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1, },
	{ 1,2,1,1,1,2,1,2,2,1,1,2,1,1,2,1,1,2,2,1,2,1,1,1,2,1, },
	{ 1,2,2,2,2,2,1,1,2,2,1,2,1,1,2,1,2,2,1,1,2,2,2,2,2,1, },
	{ 1,2,1,1,1,2,1,1,1,2,2,2,2,2,2,2,2,1,1,1,2,1,1,1,2,1, },
	{ 1,2,1,1,1,2,1,1,2,2,1,1,2,2,1,1,2,2,1,1,2,1,1,1,2,1, },
	{ 1,2,2,2,2,2,1,2,2,2,1,2,2,2,2,1,2,2,2,1,2,2,2,2,2,1, },
	{ 1,1,1,1,1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,1,1,1,1,1, },
	{ 1,2,2,2,2,2,1,1,1,2,1,1,1,1,1,1,2,1,1,1,2,2,2,2,2,1, },
	{ 1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1, },
	{ 1,2,1,1,1,1,2,2,1,1,1,2,1,1,2,1,1,1,2,2,1,1,1,1,2,1, },
	{ 1,2,1,2,2,2,2,2,2,2,1,2,1,1,2,1,2,2,2,2,2,2,2,1,2,1, },
	{ 1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1, },
	{ 1,2,1,2,1,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1, },
	{ 1,2,2,2,1,2,1,2,2,2,1,1,1,1,1,1,2,2,2,1,2,1,2,2,2,1, },
	{ 1,1,1,2,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,1,1,1, },
	{ 1,2,1,2,1,2,2,2,1,2,1,2,1,1,2,1,2,1,2,2,2,1,2,1,2,1, },
	{ 1,2,2,2,1,1,1,1,1,2,1,2,2,2,2,1,2,1,1,1,1,1,2,2,2,1, },
	{ 1,2,1,2,1,2,2,2,1,2,1,1,1,1,1,1,2,1,2,2,2,1,2,1,2,1, },
	{ 1,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,1, },
	{ 1,2,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,2,1, },
	{ 1,2,1,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1, },
	{ 1,2,1,2,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,2,1,2,1, },
	{ 1,2,1,2,2,2,1,2,2,2,1,2,1,1,2,1,2,2,2,1,2,2,2,1,2,1, },
	{ 1,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,1, },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1  },
	};

	//set the textures
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			maze[row][col].typeOfCellData = levelData[row][col];

			if(levelData[row][col]==0)
			{
				maze[row][col].setCellTextureEmpty();
			}
			if (levelData[row][col] == 1)
			{
				maze[row][col].setCellTextureWall();
			}
			if (levelData[row][col] == 2)
			{
				maze[row][col].setCellTexturePellet();
			}
			maze[row][col].setPosition(sf::Vector2f{ (float)col * 32, (float)row * 32 });
		}	
	}
}

//should be called in update to change each time in case a cell changes?
void Game::drawMaze()
// Draw the 2D maze
{
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			window.draw(maze[row][col].getSprite());
		}
	}
}

//move ghosts to other positions
void Game::setupGhosts()
{
	ghost[0].setGhostPos(160, 32);
	ghost[1].setGhostPos(256, 512);
	ghost[2].setGhostPos(640, 32);
	ghost[3].setGhostPos(640, 640);
}
