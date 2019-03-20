// Ghost function definitions here

#include "Ghost.h"
#include "Globals.h"
#include <iostream>

Ghost::Ghost()
{
	row = 0;
	col = 0;
	loadImages();
	setPosition();
	randomDirectionNumber = 1;

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
	//ghostSprite.setPosition(256, 512);
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

void Ghost::move(int t_maze[][MAX_COLS])
{
	randomDirectionNumber = rand() % 4 + 1;
	switch (randomDirectionNumber)
	{
	case 1:
		if (t_maze[row][col - 1] != 1)
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
		if (t_maze[row][col + 1] != 1)
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
		if (t_maze[row - 1][col] != 1)
		{
			ghostSprite.move(0, -32);
			break;
		}
		else
		{
			randomDirectionNumber = 4;
		}
	case 4:
		if (t_maze[row + 1][col] != 1)
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
