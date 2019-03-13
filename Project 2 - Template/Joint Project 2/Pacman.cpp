// Pacman function definitions here

#include "Pacman.h"
#include "Globals.h"
#include <iostream>
#include "Game.h"

Pacman::Pacman()
{
	loadImages();
	setPosition();

}

void Pacman::loadImages()
{
	if (!texture.loadFromFile("Assets/Images/4294f27f5748384.png"))
	{
		std::cout << "error with player pacman file";
	}
	sprite.setTexture(texture);
}

void Pacman::setPosition()
{
	sprite.setPosition(64, 64);
}

sf::Sprite Pacman::getBody()
{
	return sprite;
}

void Pacman::move(Game levelData[MAX_ROWS][MAX_COLS])
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite.move(32, 0);
		//if(sprite.getPosition().x )

	}
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			if(levelData[row][col].)
		}
	}
}

sf::Vector2f Pacman::getPosition()
{
	return sprite.getPosition();
}