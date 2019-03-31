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
	bulletsScreen.setOrigin(15, 15);

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

//void Bullet::collisionsWithAsteroids(Asteroid t_asteroid[])
//{
	//MyVector3 distanceVector; //distance between asteroid and bullet
	//float length; //length of distance vector
	//const int BULLET_ORIGIN_TO_ASTEROID_ORIGIN = 35;

	//for (int j = 0; j < MAX_ASTEROIDS; j++)
	//{
	//	distanceVector = bulletsScreen.getPosition() - t_asteroid[j].getBody().getPosition();
	//	length = distanceVector.length();

	//	if (length < BULLET_ORIGIN_TO_ASTEROID_ORIGIN)
	//	{
	//		std::cout << "asteroid shot by bullet";
	//	}
	//}


//}


