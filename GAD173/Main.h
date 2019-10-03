#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr float windowX = { 1000 }; // window width
constexpr float windowY = { 600 }; // window height
const sf::Color colour = sf::Color(255, 255, 0, 255); // custom colour. value between 0-255 for R,G,B,A


class Game // gonna make this a game manager
{
public: // functions to run the game
	bool Start();
	int Update();
	int LossLife();
private:
	sf::RenderWindow window;
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

	bool SetWall()
	{
		top.setSize(sf::Vector2f(windowX, 1));
		top.setPosition(0, 0);
		top.setFillColor(sf::Color::Black);
		bottom.setSize(sf::Vector2f(windowX, 1));
		bottom.setPosition(sf::Vector2f(0, windowY - 1));
		bottom.setFillColor(sf::Color::Black);
		left.setSize(sf::Vector2f(1, windowY));
		left.setPosition(0, 0);
		left.setFillColor(sf::Color::Black);
		right.setSize(sf::Vector2f(1, windowY));
		right.setPosition(sf::Vector2f(windowX - 1, 0));
		right.setFillColor(sf::Color::Black);
		return true;
	}

	/*bool SetWall() 
	{
		shape.setPosition(windowX / 2, windowY / 2);
		shape.setSize( sf::Vector2f((windowX - 20.f), (windowY-20.f)));
		shape.setOrigin((windowX-20) / 2, (windowY-20) / 2);
		shape.setFillColor(sf::Color::Blue);
		return true;
	}*/
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
	sf::RectangleShape bShape;
	sf::Color bColour;
	sf::Vector2f bSize;
	sf::Vector2f bPos;
};

// make a class of ball
class Ball
{
public:
	int ballRadius = 10; // setup ball size
	int ballVelocity = 3;
	sf::CircleShape shape;
	sf::Vector2f velocity{ ballVelocity, ballVelocity };

	Ball(float mX, float mY)
	{
		shape.setPosition(mX, mY);
		shape.setRadius(ballRadius);
		shape.setFillColor(sf::Color::Cyan);
		shape.setOrigin(ballRadius, ballRadius); // set origin to the center of the ball
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
		// Set the window barrier for the ball. Temporary
		/*if (left() < 0)
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
		}*/
	}
};

