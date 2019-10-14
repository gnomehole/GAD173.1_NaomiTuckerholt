#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>	

using namespace std;

class Brick
{
public:


	sf::RectangleShape bShape;
	sf::Color bClolour;
	sf::Vector2f bSize;
	sf::Vector2f bPos;
};
//cool so i have to remember to capatilaze classes or im gonna mess my day up. 

class Ball
{
public: //fuctions 
	void Bounce(int direction)
	{
		switch (direction)
		{
		case 0: //Vertical
			ballVelocity.y = -ballVelocity.y;
			break;
		case 1:
			ballVelocity.x = -ballVelocity.x;
			break;
		case 2:
			ballVelocity.y = -ballVelocity.y;
			ballVelocity.x = -ballVelocity.x;
			break;
		}
	}


	bool State();
	int Update();
	sf::Vector2f ballPos;
	sf::Vector2f ballVelocity;
	sf::CircleShape ballShape;
};

class Game
{
public:
	bool Start();
	int Update();

private:
	sf::RenderWindow window;
	sf::RectangleShape top;
	sf::RectangleShape left;
	sf::RectangleShape bottom;
	sf::RectangleShape right;
	//for some reason when i made the window to big the paddle doesn't spawn 
	float windowWidth = 750;
	float windowHeight = 600;
	int score = 0;
	int lives = 3;
	sf::RectangleShape paddle;
};

class Paddle
{
public:
	int speed = 5;
	sf::RectangleShape pShape;
	sf::Vector2f pSize;
	sf::Color pColour;
	void UpdatePosition(float direction)
	{
		pShape.setPosition(direction * speed, pShape.getPosition().y);
	};
};