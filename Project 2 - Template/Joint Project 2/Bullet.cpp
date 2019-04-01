#include "Bullet.h"


Bullet::Bullet()
{
	loadImage();
	bulletsScreen.setPosition(-500.0f, -500.0f);
	bulletVelocity = { 0,0 };
	waitToFireCounter = 40;
	readyToFire = true;
	bool rightSide = true;
	bool leftSide = false;
}

void Bullet::loadImage()
{

	if (!bulletTexture.loadFromFile("ASSETS/IMAGES/laser.png")) //load
	{
		std::cout << "error with bullet laser file"; //error
	}
	bulletsScreen.setTexture(bulletTexture); //set texture to sprite
	//bulletsScreen.setOrigin(15, 15);

}

sf::Sprite Bullet::getBulletBody()
{
	return bulletsScreen;
}

int Bullet::getWaitToFire()
{
	return waitToFireCounter;
}

sf::Vector2f Bullet::getBulletVelocity()
{
	return bulletVelocity;
}

bool Bullet::getReadyToFire()
{
	return readyToFire;
}

void Bullet::setBulletVelocity(float t_val1, float t_val2)
{
	bulletVelocity = { t_val1,t_val2 };
}

void Bullet::setReadyToFire(bool t_bool)
{
	readyToFire = t_bool;
}

void Bullet::setWaitToFire(int t_waitCounter)
{
	waitToFireCounter = t_waitCounter;
}

void Bullet::lowerWaitToFire(int t_lower)
{
	waitToFireCounter = waitToFireCounter - t_lower;
}

void Bullet::setPos(sf::Vector2f t_position)
{
	bulletsScreen.setPosition(t_position);
}

//movement for bullet
void Bullet::bulletMovement()
{
	//if bullet is in use, move it
	if (bulletsScreen.getPosition().x != -500)
	{
		row = bulletsScreen.getPosition().y / 32;
		col = bulletsScreen.getPosition().x / 32;


		bulletsScreen.move(bulletVelocity);
		if (bulletsScreen.getPosition().x > SCREEN_WIDTH)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;
		}
		if (bulletsScreen.getPosition().x < 0)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;

		}
		if (bulletsScreen.getPosition().y > SCREEN_HEIGHT)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;

		}
		if (bulletsScreen.getPosition().y < 0)
		{
			bulletsScreen.setPosition(storageVector);
			bulletVelocity = { 0.0, 0.0 };
			readyToFire = true;

		}
	}
}

//collisions with ghost enemies
void Bullet::collisionsWithGhosts(Ghost t_Ghost[], Cell t_cell[][MAX_COLS])
{
	for (int j = 0; j < MAX_GHOSTS; j++)
	{
		if (bulletsScreen.getGlobalBounds().intersects(t_Ghost[j].getBody().getGlobalBounds()))
		{
			t_Ghost[j].respawnGhost();
		}
	}
	
	if (t_cell[row][col].typeOfCell() == 1)
	{
		bulletsScreen.setPosition(storageVector);
		bulletVelocity = { 0.0, 0.0 };
		readyToFire = true;
	}

}


