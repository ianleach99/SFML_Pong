#include "Game.hpp"

Game::Game()
{
	window.create(sf::VideoMode(window_width, window_height), "SFML_Pong");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(144);

	//load font
	if (!font.loadFromFile("Roboto-Regular.ttf"))
	{
		std::cout << "Error while loading font." << std::endl;
	}

	//Set scores to 0
	left_paddle.score = 0;
	right_paddle.score = 0;

	//Setting text
	left_score_text.setFont(font);
	right_score_text.setFont(font);
	left_score_text.setString(std::to_string(left_paddle.score));
	right_score_text.setString(std::to_string(right_paddle.score));
	left_score_text.setCharacterSize(20);
	right_score_text.setCharacterSize(20);
	left_score_text.setFillColor(sf::Color::Green);
	right_score_text.setFillColor(sf::Color::Green);
	left_score_text.setPosition(20, 10);
	right_score_text.setPosition(770, 10);
}

void Game::run()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	/* Move the paddles - current position + movement vector * speed * delta time */
	left_paddle.SetPosition((left_paddle.GetPosition().x + left_paddle.GetMovement().x * left_paddle.speed * deltaTime.asSeconds()), (left_paddle.GetPosition().y + left_paddle.GetMovement().y * left_paddle.speed * deltaTime.asSeconds()));
	right_paddle.SetPosition((right_paddle.GetPosition().x + right_paddle.GetMovement().x * right_paddle.speed * deltaTime.asSeconds()), (right_paddle.GetPosition().y + right_paddle.GetMovement().y * right_paddle.speed * deltaTime.asSeconds()));
	/* Move the ball */
	ball.SetPosition((ball.GetPosition().x + ball.GetMovement().x * ball.speed * deltaTime.asSeconds()), (ball.GetPosition().y + ball.GetMovement().y * ball.speed * deltaTime.asSeconds()));
	/* Clamp paddle so it doesn't go out of bounds*/
	left_paddle.Clamp(0, (float)window_width, 0, (float)window_height - left_paddle.height);
	right_paddle.Clamp(0, (float)window_width, 0, (float)window_height - right_paddle.height);
	/* Check if the ball has hit the left or right of the screen*/
	if (ball.GetPosition().x + (ball.width / 2) <= left_paddle.GetPosition().x)
	{
		//Right's Point
		right_paddle.score += 1;
		right_score_text.setString(std::to_string(right_paddle.score));
		resetBall();
	}
	if ((ball.GetPosition().x - (ball.width / 2)) >= right_paddle.GetPosition().x)
	{
		//Left's Point
		left_paddle.score += 1;
		left_score_text.setString(std::to_string(left_paddle.score));
		resetBall();
	}
	/* Clamp the ball to the edges of the window */
	ball.Clamp(0, (float)window_width - ball.width, 0, (float)window_height - ball.height);
	/* Ball and paddle collisions */
	if ( (ball.GetPosition().y) >= (left_paddle.GetPosition().y - ((left_paddle.height / 2) + 35)) && (ball.GetPosition().y) <= (left_paddle.GetPosition().y + ((left_paddle.height / 2) + 35)) 
		&& (ball.GetPosition().x - (ball.width / 2) <= left_paddle.GetPosition().x + (left_paddle.width / 2)))
	{
		ball.SetMovement(-ball.GetMovement().x, ball.GetMovement().y);
	}

	if ((ball.GetPosition().y) >= (right_paddle.GetPosition().y - ((right_paddle.height / 2)) + 35) && (ball.GetPosition().y) <= (right_paddle.GetPosition().y + ((right_paddle.height / 2)) + 35)
		&& (ball.GetPosition().x + (ball.width / 2) >= right_paddle.GetPosition().x - (right_paddle.width / 2)))
	{
		ball.SetMovement(-ball.GetMovement().x, ball.GetMovement().y);
	}
}

void Game::render()
{
	window.clear();

	/* Draw Here */
	window.draw(left_paddle);
	window.draw(right_paddle);
	window.draw(ball);
	window.draw(left_score_text);
	window.draw(right_score_text);

	window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W && isPressed)
	{
		//Move left paddle up
		left_paddle.SetMovement(0.0f, -1.0f);
	}
	if (key == sf::Keyboard::S && isPressed)
	{
		//Move left paddle down
		left_paddle.SetMovement(0.0f, 1.0f);
	}

	if (key == sf::Keyboard::Up && isPressed)
	{
		//Move right paddle up
		right_paddle.SetMovement(0.0f, -1.0f);
	}
	if (key == sf::Keyboard::Down && isPressed)
	{
		//Move right paddle down
		right_paddle.SetMovement(0.0f, 1.0f);
	}

	/* Stop movement*/
	if ((key == sf::Keyboard::W && !isPressed) || (key == sf::Keyboard::S && !isPressed))
	{
		//Set left paddle movement to zero
		left_paddle.SetMovement(0.0f, 0.0f);
	}
	if ((key == sf::Keyboard::Up && !isPressed) || (key == sf::Keyboard::Down && !isPressed))
	{
		//Set right paddle movement to zero
		right_paddle.SetMovement(0.0f, 0.0f);
	}
}

void Game::resetBall()
{
	ball.SetPosition(800 / 2, 600 / 2);
}

int main()
{
	Game game;
	game.run();
	return 0;
}