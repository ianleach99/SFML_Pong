#include "Ball.hpp"

Ball::Ball(float spawnX, float spawnY)
{
	width = 20;
	height = 20;

	SetPosition(spawnX, spawnY);
	SetRandomDirection();

	/* Settings for the Balls */
	speed = 200;
	shape.setSize(sf::Vector2f(width, height));
}

void Ball::SetRandomDirection()
{
	int moveX = RandomNumberHelper();
	int moveY = RandomNumberHelper();
	if (moveX == 0 && moveY == 0)
	{
		moveY = -1;
	}

	SetMovement((float)moveX, (float)moveY);
}

int Ball::RandomNumberHelper()
{
	srand(time(0));
	int roll = 1 + (rand() % 6);

	if (roll % 2 == 0)
	{
		return 1;
	}
	else if (roll % 2 == 1)
	{
		return -1;
	}
}

void Ball::Clamp(float xMin, float xMax, float yMin, float yMax)
{
	if (position.x < xMin)
	{
		SetPosition(xMin, position.y);
		SetMovement(-move.x, move.y);
	}
	if (position.x > xMax)
	{
		SetPosition(xMax, position.y);
		SetMovement(-move.x, move.y);
	}
	if (position.y < yMin)
	{
		SetPosition(position.x, yMin);
		SetMovement(move.x, -move.y);
	}
	if (position.y > yMax)
	{
		SetPosition(position.x, yMax);
		SetMovement(move.x, -move.y);
	}
}