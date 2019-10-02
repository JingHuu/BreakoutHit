#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr int windowX = { 600 }; // window width
constexpr int windowY = { 600 }; // window height
const sf::Color colour = sf::Color(255, 255, 0, 255); // custom colour. value between 0-255 for R,G,B,A


class Game // gonna make this a game manager
{
public: // functions to run the game
	bool Start();
	int Update();

	sf::RenderWindow window;
	const float windowWidth = 1000;
	const float windowHeight = 600;
	int score = 0;
	int lives = 3;
};

class Rectangle
{
public:
	sf::RectangleShape shape;
	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; } // Rectangle boundaries. The origin would be set to the center of the shape. 

};

// class of the Walls
class Wall
{
public:
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;

	void DrawWall() 
	{
		top.setSize(sf::Vector2f(windowX, 1.f ));
		top.setPosition(0, 0);
		bottom.setSize(sf::Vector2f(windowX, 1.f));
		bottom.setPosition(0, windowY - 1.f);
		left.setSize(sf::Vector2f(1.f, windowY));
		left.setPosition(0, 0);
		right.setSize(sf::Vector2f(1.f, windowY));
		right.setPosition(windowX - 1.f, windowX);
	}
};

// make a class of the Paddle
class Paddle : public Rectangle
{
public:
	const int velocity = 10; // paddle speed is constant, unless making powerups or debuff for it later
	sf::Vector2f speed;
	sf::Vector2f paddleSize = sf::Vector2f(200.f, 50.f); // size of the rectangle

	Paddle(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setSize(paddleSize);
		shape.setFillColor(colour);
		shape.setOrigin(paddleSize.x / 2.f, paddleSize.y / 2.f); // set origin to the center
	}

	// Check player input within Update function
	void Update()
	{
		shape.move(speed);
		// check if left is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && left() > 0)
		{
			speed.x = -velocity;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && right() < windowX)
		{
			speed.x = velocity;
		}
		else
		{
			speed.x = 0;
		}
	}

};

// make a class of the bricks
class Brick : public Rectangle
{
public:

private:
	sf::Vector2f brickSize;
	sf::Vector2f brickPos;
};

// make a class of ball
class Ball
{
public:
	int ballRadius = 10; // setup ball size
	int ballVelocity = 5;
	sf::CircleShape shape;
	sf::Vector2f velocity{ -ballVelocity, -ballVelocity };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(sf::Color::Cyan);
		shape.setOrigin(ballRadius, ballRadius);
	}

	float x() { return shape.getPosition().x; } // Reminder: Object origin is set to the center. 
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getRadius(); }
	float right() { return x() + shape.getRadius(); }
	float top() { return y() - shape.getRadius(); }
	float bottom() { return y() + shape.getRadius(); }

	void Update()
	{
		shape.move(velocity);
		// Set the window barrier for the ball. TODO should change this to using the "isOverlapping"
		if (left() < 0)
		{
			velocity.x = ballVelocity;
		}
		else if (right() > windowX)
		{
			velocity.x = -ballVelocity;
		}

		if (top() < 0)
		{
			velocity.y = ballVelocity;
		}
		else if (bottom() > windowY)
		{
			velocity.y = -ballVelocity;
		}
	}
};

