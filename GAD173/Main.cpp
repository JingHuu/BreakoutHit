#include <SFML/Graphics.hpp>
#include "Main.h"



template <class c1, class c2>
bool isOverlapping(c1& mA, c2& mB)
{
	return mA.right() >= mB.left() && mA.left() <= mB.right() &&
		mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void CollisionTest(Ball& mBall, Paddle& mPaddle)
{
	// check if the ball is overlapping with the paddle
	if (!isOverlapping(mBall, mPaddle))
	{
		return;
	}
	mBall.velocity.y = -mBall.ballVelocity;
	if (mBall.x() < mPaddle.x())
	{
		mBall.velocity.x = -mBall.ballVelocity;
	}
	else
	{
		mBall.velocity.x = mBall.ballVelocity;
	}

}

void CollisionTest(Ball& mBall, Wall& mWall)
{

}

int main()
{
	// Render the window
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Breakout Hit!");
	window.setFramerateLimit(60); // stop the game from going insanely fast

	Wall wall;
	Paddle paddle{ windowX / 2, windowY / 1.5 }; // set paddle position
	Ball ball{ windowX / 2, windowY / 2 }; // set ball position
	Brick brick;


	// code runs while window is open
	while (window.isOpen())
	{
		wall.DrawWall();
		paddle.Update();
		ball.Update();
		CollisionTest(ball, paddle);
		CollisionTest(ball, wall);

		sf::Event event;
		//PollEvent is our window updating
		while (window.pollEvent(event))
		{
			// if window closed
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(paddle.shape);
		window.draw(ball.shape);
		window.display();
	}

	return 0;
}
