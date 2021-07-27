#pragma once
#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable
{
public:
	Paddle() : height(0), speed(0), width(0), score(0) {}
	Paddle(float spawnX, float spawnY);
	virtual void Clamp(float xMin, float xMax, float yMin, float yMax);
	void SetPosition(float x, float y);
	void SetMovement(float x, float y);
	sf::Vector2f GetPosition();
	sf::Vector2f GetMovement();

protected:
	virtual void sf::Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(Paddle::shape, states); }

public:
	float speed;
	float width;
	float height;
	int score;

protected:
	sf::RectangleShape shape;
	sf::Vector2f position;
	sf::Vector2f move;
};