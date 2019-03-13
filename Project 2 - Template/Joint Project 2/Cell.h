#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"


class Cell
{
	// private data members

	int typeOfCellData;       //is the cell empty or contain a pellet or a wall ?
		//0 could represent an empty cell, 1 a pellet and 2 a wall.

	sf::Texture emptyTexture;   //the texture of the empty square
	sf::Texture pelletTexture;	    //the texture of the pellet
	sf::Texture wallTexture;	    //the texture of the wall
	sf::Sprite sprite; 	   //sprite used to represent the cell


public:
	Cell();
	int typeOfCell();
	void setCellTextureEmpty();
	void setCellTextureWall();
	void setCellTexturePellet();

	sf::Sprite getSprite();

	void loadTextures();
	inline void setPosition(sf::Vector2f t_pos) { sprite.setPosition(t_pos); }
};