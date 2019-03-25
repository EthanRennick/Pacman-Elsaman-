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
