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


int main()
{
	Game aGame;
	aGame.LoadContent();
	aGame.run();

	return 0;
}

Game::Game() : window(sf::VideoMode(896, 992), "Project 2")
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

	// update any game variables here ...
	pacman.move(levelData[MAX_ROWS][MAX_COLS]);
	drawMaze();
}


void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	window.clear();

	m_message.setString("Project 2 : Game Play");
	window.draw(m_message);  // write message to the screen
	drawMaze();
	window.draw(pacman.getBody());
	window.display();
}


void Game::setUpGame()
// Initialize the game objects to play a new game
{
	//setup shtuff

}


void Game::setUpMaze()
// Setup the sprites for the 2D maze game
{

	



	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			//maze[row][col].loadTextures();
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
		//	xPos += 32;
		}
		//xPos = 0;
		//yPos += 32;
	}
}

//should be called in update to change each time in case a cell changes?
void Game::drawMaze()
// Draw the 2D maze
{
	setUpMaze();
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			window.draw(maze[row][col].getSprite());
		}
	}
}