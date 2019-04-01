// Name: Ethan Rennick
// Login: C00240102
// Date: March 2019
// Approximate time taken: 24 hours spent 
//---------------------------------------------------------------------------
// Project 2 -  Description Template
// This is Elsaman, a parody of Pacman
// it was made for a programming project, year 1
// Bernadette Lab ^
// 
// ---------------------------------------------------------------------------
// Known Bugs:
// Ghosts (snowmen) walk into each other
// if you hold down several arrow keys at once you can sometimes walk through walls
//

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

Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Project 2 - Elsaman")
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

	// main menu
	if (!menuTexture.loadFromFile("Assets/Images/menu.png"))
	{
		std::cout << "error with menu file ";
	}
	menuSprite.setTexture(menuTexture);
	menuSprite.setScale(0.52, 0.65);
	menuSprite.setPosition(0, 0);

	//help screen
	if (!helpTexture.loadFromFile("Assets/Images/olaf.png"))
	{
		std::cout << "error with help screen";
	}
	helpSprite.setTexture(helpTexture);
	helpSprite.setPosition(650, 600);

	//game over screen
	if (!gameOverTexture.loadFromFile("Assets/Images/hans.png"))
	{
		std::cout << "error with game over screen";
	}
	gameOverSprite.setTexture(gameOverTexture);

	//victory
	if (!victoryTexture.loadFromFile("Assets/Images/victory.png"))
	{
		std::cout << "error with victory screen";
	}
	victorySprite.setTexture(victoryTexture);

	//sound loading
	//menumusicBuffer.loadFromFile("Assets/Audio/menumusic.wav");
	//menumusicSound.setBuffer(menumusicBuffer);

	//musicBuffer.loadFromFile("Assets/Audio/music.wav");
	//musicSound.setBuffer(musicBuffer);

	throwBuffer.loadFromFile("Assets/Audio/throw.wav");
	throwSound.setBuffer(throwBuffer);
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

			if (sf::Event::KeyReleased == event.type) //If the space key is pressed and released
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					throwSound.play();
					bulletFiring(); //fire a bullet
				}
			}
			if (acceptName == true)
			{
				if (event.type == sf::Event::TextEntered)
				{
					bool backSpace_down =
						sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace);
					if (backSpace_down == true && playerName.length() != 0)
					{
						playerName.pop_back();
					}
					else if (event.text.unicode < 128)
					{
						playerName.push_back((char)event.text.unicode);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					acceptName = false;
					gamePlay = true;
					//menumusicSound.stop();
					//musicSound.play();
				}
			}
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


//update every 1/60th of a second
void Game::update()
// This function takes the keyboard input and updates the game world
{
	
	updateMenuAndInput(); //handles the key input on different screens
	updateGamePlay(); //this is the main gameplay loop that needs to run
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i].bulletMovement();	//move bullets
		bullets[i].collisionsWithGhosts(ghost,maze);
	}
}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	window.clear();
	drawTheCorrectScreen();

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].getBulletBody().getPosition() != bullets[i].storageVector)
		{
			window.draw(bullets[i].getBulletBody());
		}
	}
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

//this game function totally resets the whole game
//mostly just used for when user wins or loses
void Game::totalGameReset()
{
	pacman.getBody().setPosition(32, 32);
	pacman.changeLives(3);
	pacman.changeScore(0);
	pacman.treasure = 0;
	setupGhosts();
	setUpMaze();
	menu = true;
	gamePlay = false;
	gameOver = false;
	winGame = false;
	playerName = "";
}

//update the core game loop
void Game::updateGamePlay()
{
	if (gamePlay == true)
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
			counter = 10; //reset pacman timer
		}

		//particles
		pacman.playerParticlesGold.Update();
		pacman.playerParticlesBlood.Update();

		for (int i = 0; i < MAX_GHOSTS; i++)
		{
			if (ghostCounter[i] == 0) //if timer is empty
			{
				ghost[i].move(maze); //ghost moving
				pacman.collisionWithGhosts(ghost[i].getRow(), ghost[i].getCol(), gameOver, gamePlay); //has pacman collided with ghost?
				ghostCounter[i] = 10; //reset timer
			}
		}

		if (pacman.getLives() == 0) //if pacman dies, display bad screen
		{
			gamePlay = false;
			gameOver = true;
		}

		if (pacman.treasure >= MAX_GOLD) //if elsaman collected all gold, she wins
		{
			winGame = true;
			gamePlay = false;
		}
	

	}
}

//this function looks at the screens and will accept input for each one
void Game::updateMenuAndInput()
{
	if (menumusic == false)
	{
		//menumusicSound.play();
	//	menumusic = true;
	}
	//menu screen -> playing game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && menu == true)
	{
		menu = false;
		acceptName = true;
	}
	//menu screen -> help screen
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && menu == true)
	{
		menu = false;
		help = true;
	}
	//help screen -> menu 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && help == true)
	{
		menu = true;
		help = false;
	}
	//game over screen -> menu
	if (gameOver == true) //let user restart if he presses enter
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			totalGameReset(); //reset
		}
	}
	
	//victory screen -> menu
	if (winGame == true) //let user restart if he presses enter
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			totalGameReset(); //reset
		}
	}
}

//this looks at the bools controlling the screens and will display the correct ones
void Game::drawTheCorrectScreen()
{
	if (menu == true)
	{
		window.draw(menuSprite);
		m_message.setPosition(375, 550);
		m_message.setString("Main Menu");
		window.draw(m_message);  // write message to the screen
		m_message.setPosition(362, 590);
		m_message.setString("Play Game [1]");
		window.draw(m_message);  // write message to the screen
		m_message.setPosition(360, 630);
		m_message.setString("Help Screen [2]");
		window.draw(m_message);  // write message to the screen
	}
	if (help == true)
	{
		window.draw(helpSprite);
		m_message.setPosition(200, 300);
		m_message.setString("         Use the arrow keys to move\n\n      Dodge the ghosts or lose a life\n\n Pick up treasure for a better score \n\nRescue as many friends as possible\n                   for a better score\n\nPress lShift to return to main menu");
		window.draw(m_message);  // write message to the screen
	}
	if (acceptName == true)
	{
		std::string playerNameDisplay;
		playerNameDisplay = "Enter your player name: " + playerName;
		m_message.setPosition(200, 300);
		m_message.setString(playerNameDisplay);
		window.draw(m_message);  // write message to the screen
	}
	if (gamePlay == true)
	{
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

		m_message.setPosition(2, 58);
		m_message.setString("Player name: " + playerName);
		window.draw(m_message);  // write message to the screen
		if (pacman.invincibleStatus() > 0)
		{
			m_message.setPosition(2, 86);
			m_message.setString("Invincible: " + std::to_string(pacman.invincibleStatus()));
			window.draw(m_message);  // write message to the screen
		}
	}

	if (gameOver == true)
	{
		window.draw(gameOverSprite);
		m_message.setPosition(300, 550);
		m_message.setString("You have lost. Shoddy work, " + playerName + "\nScore : " + std::to_string(pacman.getGold()) + "\nPress enter to return to main menu");
		window.draw(m_message);  // write message to the screen
	}

	if (winGame == true)
	{
		window.draw(victorySprite);
		m_message.setPosition(300, 700);
		m_message.setString("You have won! Good work, " + playerName + "\nScore : " + std::to_string(pacman.getGold()) + "\nPress enter to return to main menu");
		window.draw(m_message);  // write message to the screen
	}
}

//function for bullet firing
void Game::bulletFiring()
{
	//loop to look at all the bullets
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].readyToFire == true) //if the current bullet and the next one are good to go
		{
			if (bullets[i].bulletsScreen.getPosition() == bullets[i].storageVector) //AND if they're in storage
			{
				//then setup the bullet like so
				bullets[i].bulletsScreen.setPosition(pacman.getBody().getPosition()); // bullet should go to the sprite

				bullets[i].bulletVelocity = (pacman.getPlayerLookDirection()); //the velocity is enlarged
				bullets[i].bulletVelocity.x = bullets[i].bulletVelocity.x * 6;
				bullets[i].bulletVelocity.y = bullets[i].bulletVelocity.y * 6;
				bullets[i].readyToFire = false; //the bullet is not ready to fire again until the counter is at 0 
				bullets[i].waitToFireCounter = 40;

				break; //also get out of the loop
			}
		}
		else //if the bullets aren't ready
		{
			//lower the  counters, and if it gets to 0, set ready to fire
			
			bullets[i].waitToFireCounter--;
			if (bullets[i].waitToFireCounter <= 0)
			{
				bullets[i].readyToFire = true;
			}
		}
	}
}
