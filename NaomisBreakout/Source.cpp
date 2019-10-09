#include <SFML/Graphics.hpp>
#include "Main.h"

using namespace std;

int main()
{
	Game myGame;
	if (!myGame.Start())
	{
		return EXIT_FAILURE;
	}
	return myGame.Update();
	return 0;

}

Brick brick; //defining a brick
vector<Brick> Bricks(15, Brick(brick)); //creating a brick vector (list) of bricks
bool Game::Start()
{


	sf::VideoMode vMode(windowWidth, windowHeight);
	window.create(vMode, "breakout!");
	window.setFramerateLimit(60);

	for (int i = 0; i < 15; i++)
	{
		Bricks[i].bShape.setSize(sf::Vector2f(75, 30));
		Bricks[i].bShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		if (i <= 5)
		{
			Bricks[i].bShape.setPosition(75 * i, 0);
		}
		else if (i > 10)
		{
			Bricks[i].bShape.setPosition(75 * (i - 11), 0);
		}
		else if (i > 5)
		{
			Bricks[i].bShape.setPosition(75 * (i - 6), 0);
		}
	}


	//setup borders
	top.setSize((sf::Vector2f(windowWidth, 1)));
	top.setPosition(0, 0);
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowWidth, 1));
	bottom.setPosition(sf::Vector2f(windowHeight, -1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(1, windowWidth));
	right.setPosition(sf::Vector2f(-1, windowWidth));


	return true;

}

int Game::Update()
{
	Paddle paddle;
	ball ball;
	bool HitsWall = false;


	//collision vector to make it easier to tweak


	window.setFramerateLimit(60);
	//sf::RectangleShape paddle(paddle.pSize);

	ball.ballShape.setPosition(ball.ballPos);
	while (window.isOpen())
	{
		window.draw(paddle.pShape);
		window.draw(ball.ballShape);
		//paddle movement based on mouse position
		if (sf::Mouse::getPosition(window).x > 0 &&
			sf::Mouse::getPosition(window).x < (window.getSize().x - paddle.pShape.getSize().x))
		{
			paddle.pShape.setPosition(sf::Mouse::getPosition(window).x - paddle.pShape.getSize().x / 2, paddle.pShape.getPosition().y);

		}

		//ball & paddle collision
		if (paddle.pShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
		}
		for (int i = 0; i < Bricks.size(); i++)
		{
			if (Bricks[i].bShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
			{
				ball.Bounce(0);
				Bricks[i].bShape.setPosition(1200, 0);
				score += 1;
				ball.ballVelocity = ball.ballVelocity * 1.03f;

			}
		}




		//makes sure the ball is moving?
		ball.ballShape.move(ball.ballVelocity);

		//ball boundaries
		if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
		}
		if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
			lives -= 1;
			if (lives < 1)
			{
				return 1;
			}
		}
		if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(1);
		}
		if (right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(1);
		}

		ball.ballShape.move(ball.ballVelocity);

		sf::Event event;
		//Pollevent is our window updating 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		for (int i = 0; i < Bricks.size(); i++)
		{
			window.draw(Bricks[i].bShape);
		}


		window.display();
		window.draw(top);
		window.draw(left);
		window.draw(right);
		window.draw(bottom);

	}

	return 0;

}
