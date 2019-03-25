// Pacman function definitions here

#include "Pacman.h"
#include "Globals.h"
#include <iostream>

Pacman::Pacman()
{
	row = 0;
	col = 0;
	loadImages();
	setPosition();
	treasure = 0;
	lives = 3;
	score = 0;
	alive = true;
	invincible = 50; //invulnerability timer

}

//draw pacman
void Pacman::draw(sf::RenderWindow &t_window)
{
	t_window.draw(sprite);
	row = sprite.getPosition().y / 32;
	col = sprite.getPosition().x / 32;
}

//collecting treasure function
void Pacman::collectGold(Cell t_maze[][MAX_COLS])
{
	if (t_maze[row][col].typeOfCellData == 2)
	{
		playerParticlesGold.Initialise(sf::Vector2f(sprite.getPosition()));
		t_maze[row][col].typeOfCellData = 0;
		t_maze[row][col].setCellTextureEmpty();
		treasure++;
	}
}

//get player score
int Pacman::getGold()
{
	return treasure;
}

//return lives of elsaman
int Pacman::getLives()
{
	return lives;
}

//pacman - ghost collision function
void Pacman::collisionWithGhosts(int t_ghostRow, int t_ghostCol)
{
	invincible--;
	if (invincible <= 0)
	{
		if (t_ghostRow == row && t_ghostCol == col)
		{
			playerParticlesBlood.Initialise(sf::Vector2f(sprite.getPosition()));
			invincible = 50; //invulnerable timer
			lives--;
		}
	}
}

//load sprites etc
void Pacman::loadImages()
{
	if (!textureLeft.loadFromFile("Assets/Images/ElsaLeft.png"))
	{
		std::cout << "error with player pacman file left";
	}
	if (!textureRight.loadFromFile("Assets/Images/elsaRight.png"))
	{
		std::cout << "error with player pacman file right";
	}
	sprite.setTexture(textureLeft);
}

//set up pacman's position
void Pacman::setPosition()
{
	sprite.setPosition(32,32);
}

//return his body (sprite)
sf::Sprite Pacman::getBody()
{
	return sprite;
}

//elsaman movement
void Pacman::move(Cell t_maze[][MAX_COLS])
{
	//right hand movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (t_maze[row][col + 1].typeOfCellData != 1)
		{
			sprite.setTexture(textureRight);

			sprite.move(32, 0);
		}
	
	}
	/// downward movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (t_maze[row + 1][col].typeOfCellData != 1)
		{
			sprite.move(0, 32);
		}
	
	}
	//left hand movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (t_maze[row][col - 1].typeOfCellData != 1)
		{			
			sprite.setTexture(textureLeft);
			sprite.move(-32,0);
		}
	}
	//upward movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (t_maze[row - 1][col].typeOfCellData != 1)
		{
			sprite.move(0, -32);
		}
	}
}

//return elsaman position
sf::Vector2f Pacman::getPosition()
{
	return sprite.getPosition();
}