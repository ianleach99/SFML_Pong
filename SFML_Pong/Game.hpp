#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"

class Game 
{
public:
		 Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void resetBall();

private:
	int window_width = 800;
	int window_height = 600;
	sf::RenderWindow window;
	sf::Font font;
	sf::Text left_score_text;
	sf::Text right_score_text;
	Paddle left_paddle{ 50.0f, 50.0f };
	Paddle right_paddle{ 750.0f, 50.0f };
	Ball ball{ window_width / 2, window_height / 2 };
};

