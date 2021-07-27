#include "Paddle.hpp"

Paddle::Paddle(float spawnX, float spawnY)
{
	width = 10;
	height = 90;

	SetPosition(spawnX, spawnY);
	SetMovement(0.0f, 0.0f);

	/* Setting for the paddles */
	speed = 500;
	shape.setSize(sf::Vector2f(width, height));
}

void Paddle::Clamp(float xMin, float xMax, float yMin, float yMax)
{
	if (position.x < xMin)
	{
		SetPosition(xMin, position.y);
	}
	if (position.x > xMax)
	{
		SetPosition(xMax, position.y);
	}
	if (position.y < yMin)
	{
		SetPosition(position.x, yMin);
	}
	if (position.y > yMax)
	{
		SetPosition(position.x, yMax);
	}
}

void Paddle::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	shape.setPosition(position);
}

void Paddle::SetMovement(float x, float y)
{
	move.x = x;
	move.y = y;
}

sf::Vector2f Paddle::GetPosition()
{
	return position;
}

sf::Vector2f Paddle::GetMovement()
{
	return move;
}

