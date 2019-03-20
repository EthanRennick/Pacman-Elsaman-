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
	//direction = 1;

}

void Pacman::draw(sf::RenderWindow &t_window)
{
	t_window.draw(sprite);
	row = sprite.getPosition().y / 32;
	col = sprite.getPosition().x / 32;
}

void Pacman::collectGold(int t_maze[][MAX_COLS])
{
	if (t_maze[row][col] == 2)
	{
		t_maze[row][col] = 0;
		treasure++;
	}
}

int Pacman::getGold()
{
	return treasure;
}

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

void Pacman::setPosition()
{
	sprite.setPosition(32,32);
}

sf::Sprite Pacman::getBody()
{
	return sprite;
}

void Pacman::move(int t_maze[][MAX_COLS])
{
//	sprite.setPosition(row,col);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (t_maze[row][col + 1] != 1)
		{
			sprite.setTexture(textureRight);

			sprite.move(32, 0);
		}
	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (t_maze[row + 1][col] != 1)
		{
			sprite.move(0, 32);
		}
	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (t_maze[row][col - 1] != 1)
		{			
			sprite.setTexture(textureLeft);
			sprite.move(-32,0);
		}
	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (t_maze[row - 1][col] != 1)
		{
			sprite.move(0, -32);
		}
	
	}

}

sf::Vector2f Pacman::getPosition()
{
	return sprite.getPosition();
}