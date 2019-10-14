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
//made a brick amount int var to make it easier to change max brick amount
int Brickamount = 60; 
Brick brick; //defining a brick
vector<Brick> Bricks(Brickamount, Brick(brick)); //creating a brick vector (list) of bricks 
bool Game::Start()
{


	sf::VideoMode vMode(windowWidth, windowHeight);
	window.create(vMode, "breakout!");
	window.setFramerateLimit(60);

	//spawnin bricks yo
	//setting brick size
	int brickwidth = 75;
	int brickheight = 30;
	int RowLength = windowWidth / brickwidth;
	srand(time(NULL));

	for (int i = 0; i < Brickamount; i++)
	{
		
		Bricks[i].bShape.setSize(sf::Vector2f(brickwidth, brickheight));
		//setting brick colour
		Bricks[i].bShape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		
		if (i > 0 and i < RowLength)
		{
			Bricks[i].bShape.setPosition(brickwidth * i, 0);
		}
		else if (i > RowLength and i < RowLength*2)
		{
			Bricks[i].bShape.setPosition(brickwidth * (i- RowLength), brickheight);
		}
		else if (i > RowLength*2 and i < RowLength*3)
		{
			Bricks[i].bShape.setPosition(brickwidth * (i - RowLength*2), brickheight*2);
		}
	}


	//setup borders
	top.setSize((sf::Vector2f(windowWidth, 1)));
	top.setPosition(1, 1);
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowWidth, 1));
	bottom.setPosition(sf::Vector2f(windowHeight, 1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(1, windowHeight));
	left.setPosition(sf::Vector2f(1, 1));
	right.setSize(sf::Vector2f(1, windowHeight));
	right.setPosition(sf::Vector2f(windowWidth, 1));

	//changed stuff so heres backup
	//top.setSize((sf::Vector2f(windowWidth, 1)));
	//top.setPosition(0, 0);
	//top.setFillColor(sf::Color::Black);
	//bottom.setSize(sf::Vector2f(windowWidth, 1));
	//bottom.setPosition(sf::Vector2f(0, -windowHeight));


	return true;

}

int Game::Update()
{
	Paddle paddle;
	paddle.pShape.setSize(sf::Vector2f(120.f, 15.f));
	paddle.pShape.setFillColor(sf::Color::Green);
	paddle.pShape.setPosition(windowWidth / 2, windowHeight - windowHeight / 5);
	Ball ball;
	ball.ballShape.setRadius(12.f);
	ball.ballShape.setPosition(paddle.pShape.getPosition().x, paddle.pShape.getPosition().y - 75);
	ball.ballShape.setFillColor(sf::Color::Red);

	ball.ballVelocity.x = rand() % 10;
	ball.ballVelocity.y = -5;

	//Code runs while window is open
	while (window.isOpen())
	{	
		//paddle movement based on mouse position
		if (sf::Mouse::getPosition(window).x > paddle.pShape.getSize().x / 2 &&
			sf::Mouse::getPosition(window).x < (window.getSize().x - paddle.pShape.getSize().x / 2))
		{
			paddle.pShape.setPosition(sf::Mouse::getPosition(window).x - paddle.pShape.getSize().x /2, 
				paddle.pShape.getPosition().y);
		}

		//ball collision with borders
		if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds())) {
			ball.Bounce(0);
		}
		if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			//may want to reset, for now let's bounce and reduce lives
			ball.Bounce(0);
			lives -= 1;
			if (lives < 1) {
				//End game
				return 1;
			}
		}
		
		if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) || 
			right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds())) {
			ball.Bounce(1);
		}
		
		//paddle and ball collision
		if (paddle.pShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0);
		}

		//ball and brick collision
		for (int i = 0; i < Bricks.size(); i++) 
		{
			if (Bricks[i].bShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
			{
				ball.Bounce(0);
				Bricks[i].bShape.setPosition(1200, 0);
				score += 1;
				ball.ballVelocity = ball.ballVelocity * 1.03f; //increases speed of ball
			}
		}

		

		ball.ballShape.move(ball.ballVelocity); //moves the ball
		sf::Event event;
		//PollEvent is our window updating event
		while (window.pollEvent(event))
		{
			//if window closes
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//clear window and redraw images
		window.clear();
		//draw bricks
		for (int i = 0; i < Bricks.size(); i++) 
		{
			window.draw(Bricks[i].bShape);
		}
		window.draw(paddle.pShape);
		window.draw(ball.ballShape);
		window.draw(top);
		window.draw(left);
		window.draw(right);
		window.draw(bottom);
		window.display();
	}
	return 0;
}
