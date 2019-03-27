#pragma once
#include "SFML/Graphics.hpp" 
#include "Globals.h"

//These are the particles used in my game

class Particle
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;
	int framesToLive;
};

//blood particles
class ParticleSystemBlood
{
public:
	static const int numParticles = 10;
	Particle particles[16];
	float maxSpeed = 2;
	sf::Vector2f center;

	ParticleSystemBlood()
	{

	}
	void Initialise(sf::Vector2f position)
	{
		center = position;
		//for loop to initialise all the particles

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setSize(sf::Vector2f{ 10.0f,10.0f });
			particles[i].shape.setPosition(center);
			particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(220), static_cast<unsigned int>(20), static_cast<unsigned int>(60)));
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].framesToLive = 20;
		}


	}
	void Update()
	{
		//for loop to move all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				particles[i].shape.move(particles[i].velocity);

			}

		}
	}
	void Draw(sf::RenderWindow &window)
	{
		//for loop to draw all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				window.draw(particles[i].shape);
				particles[i].framesToLive--;
			}

		}
	}
};

//treasure collecting particles
class ParticleSystemGold
{
public:
	static const int numParticles = 8;
	Particle particles[numParticles];
	float maxSpeed = 4;
	sf::Vector2f center;

	ParticleSystemGold()
	{

	}
	void Initialise(sf::Vector2f position)
	{
		center = position;
		//for loop to initialise all the particles

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setSize(sf::Vector2f{ 10.0f,10.0f });
			particles[i].shape.setPosition(center);
			particles[i].shape.setFillColor(sf::Color(static_cast<unsigned int>(255), static_cast<unsigned int>(255), static_cast<unsigned int>(0)));
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].framesToLive = 20;
		}


	}
	void Update()
	{
		//for loop to move all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				particles[i].shape.move(particles[i].velocity);

			}

		}
	}
	void Draw(sf::RenderWindow &window)
	{
		//for loop to draw all the particles
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{
				window.draw(particles[i].shape);
				particles[i].framesToLive--;
			}

		}
	}
};
