#include "Cell.h"
#include "Game.h"

Cell::Cell()
{
	loadTextures();
}

int Cell::typeOfCell()
{
	return typeOfCellData;
}

void Cell::setCellTextureEmpty()
{
	//set Texture to empty cell
	sprite.setTexture(emptyTexture);
}

void Cell::setCellTextureWall()
{
	//set Texture to wall cell
	sprite.setTexture(wallTexture);
}

void Cell::setCellTexturePellet()
{
	//set Texture to pellet cell
	sprite.setTexture(pelletTexture);
}

sf::Sprite Cell::getSprite()
{
	return sprite;
}

void Cell::loadTextures()
{
	//make empty tile the normal black screen
	/*if (!emptyTexture.loadFromFile("Assets/Images/emptyCell.png"))
	{
		std::cout << "error with empty cell image file";
	}*/


	if (!wallTexture.loadFromFile("Assets/Images/wallCell.jpg"))
	{
		std::cout << "error with wall image file";
	}


	if (!pelletTexture.loadFromFile("Assets/Images/bigpill.png"))
	{
		std::cout << "error with pellet cell image file";
	}
	
}
