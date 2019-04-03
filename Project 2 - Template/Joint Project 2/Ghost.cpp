// Ghost function definitions here

#include "Ghost.h"
#include "Globals.h"
#include <iostream>

Ghost::Ghost()
{
	row = 0;
	col = 0;
	loadImages();
	//setPosition();
	randomDirectionNumber = 1;
	health = 20;
	int respawnCount = 40;

	healthBar.setSize(sf::Vector2f(health, 5));
	healthBar.setFillColor(sf::Color::Green);
	healthBar.setOutlineThickness(2);
	healthBar.setOutlineColor(sf::Color::White);

}

void Ghost::loadImages()
{
	if (!ghostTextureRight.loadFromFile("Assets/Images/monsterRight.png"))
	{
		std::cout << "error with player pacman file right";
	}
	if (!ghostTextureLeft.loadFromFile("Assets/Images/monsterLeft.png"))
	{
		std::cout << "error with player pacman file right";
	}
	ghostSprite.setTexture(ghostTextureLeft);
}

sf::Vector2f Ghost::getPosition()
{
	return ghostSprite.getPosition();
}

void Ghost::setPosition()
{
	ghostSprite.setPosition(256, 512);
}

sf::Sprite Ghost::getBody()
{
	return ghostSprite;
}

void Ghost::draw(sf::RenderWindow & t_window)
{
	t_window.draw(ghostSprite);
	row = ghostSprite.getPosition().y / 32;
	col = ghostSprite.getPosition().x / 32;
}

//ghost movement
void Ghost::move(Cell t_maze[][MAX_COLS])
{
	healthBar.setPosition(ghostSprite.getPosition()); //move healthbar with ghost
	//generate a random number
	randomDirectionNumber = rand() % 4 + 1;
	switch (randomDirectionNumber) //switch statement to decide movement
	{
	case 1:
		if (t_maze[row][col - 1].typeOfCellData != 1) // 1 = move ghost left
		{
			ghostSprite.setTexture(ghostTextureLeft);
			ghostSprite.move(-32, 0);
			break;
		}
		else
		{
			randomDirectionNumber = rand() % 3 + 2;
		}
	case 2:
		if (t_maze[row][col + 1].typeOfCellData != 1)  //2 = move ghost right
		{
			ghostSprite.setTexture(ghostTextureRight);
			ghostSprite.move(32, 0);
			break;
		}
		else
		{
			randomDirectionNumber = rand() % 1 + 3;

		}
	case 3:
		if (t_maze[row - 1][col].typeOfCellData != 1) //3 = move ghost up
		{
			ghostSprite.move(0, -32);
			break;
		}
		else
		{
			randomDirectionNumber = 4;
		}
	case 4:
		if (t_maze[row + 1][col].typeOfCellData != 1) // 4 = move ghost down
		{
			ghostSprite.move(0, 32);
			break;
		}
		else
		{
			randomDirectionNumber = rand() % 4 + 1;
		}
	}
	
}

int Ghost::getRow()
{
	return row;
}

int Ghost::getCol()
{
	return col;
}

//setup ghot's position
void Ghost::setGhostPos(int pos1, int pos2)
{
	ghostSprite.setPosition(pos1, pos2);
}

//respawn ghost when shot
void Ghost::respawnGhost()
{
	
	int randomNumber = rand() %4+1;
	switch (randomNumber)
	{
		case 1:
			setGhostPos(160, 32);

			break;

		case 2:
			setGhostPos(256, 512);
			break;

		case 3:
			setGhostPos(640, 32);
			break;

		case 4:
			setGhostPos(640, 640);
			break;
	}
	healthBar.setFillColor(sf::Color::Green);
	health = 20;
	healthBar.setSize(sf::Vector2f(health, 5));
}

void Ghost::lowerHealthBar() //lower ghost health
{	
	if (health == 20)
	{
		health = 10;
		healthBar.setSize(sf::Vector2f(health, 5));
		healthBar.setFillColor(sf::Color::Red);
	}
	else if (health == 10)
	{
		destroy();
	}
}

void Ghost::destroy()
{
	respawnGhost();
}

sf::RectangleShape Ghost::getHealthBar()
{
	return healthBar;
}
