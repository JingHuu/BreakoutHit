#include <SFML/Graphics.hpp>
#include "Main.h"

using namespace std;


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
	mBall.velocity.y = -mBall.velocity.y;
	if (mBall.x() < mPaddle.x())
	{
		mBall.velocity.x = -mBall.velocity.x;
	}
	else
	{
		mBall.velocity.x = mBall.velocity.x;
	}
}

/*template <class c1, class c2>
bool DoWallCollision(c1& mA, c2& mB)
{
	return mA.right() >= mB.right() || mA.left() <= mB.left() ||
		mA.bottom() >= mB.bottom() || mA.top() <= mB.top();
}

void WallCollision(Ball& mBall, Wall& walls)
{
	Game game;
	if (!DoWallCollision(mBall, walls))
	{
		return;
	}
	mBall.velocity.x = -mBall.ballVelocity;
	mBall.velocity.y = -mBall.ballVelocity;
	if (mBall.bottom() <= walls.bottom())
	{
		game.LossLife();
	}
}*/

int main()
{
	Game mGame;
	if (!mGame.Start())
	{
		return EXIT_FAILURE;
	}
	return mGame.Update();
	return 0;
}

Brick brick; //define a brick object
vector<Brick> Bricks(31, Brick(brick)); //create a vector(list) of bricks
bool Game::Start() // setting up the game
{
	// Render the window
	sf::VideoMode vMode(windowX, windowY);
	window.create(vMode, "Breakout Hit!");
	window.setFramerateLimit(60); // stop the game from going insanely fast



	//setup bricks
	srand(time(NULL));
	for (int i = 0; i < 31; i++)
	{
		Bricks[i].bShape.setSize(sf::Vector2f(100, 50));
		Bricks[i].bShape.setFillColor(sf::Color(rand() % 255 + 50, rand() % 255 + 50, rand() % 255 + 50));
		if (i <= 10) {
			Bricks[i].bShape.setPosition(100 * i, 0);
		}
		else if (i > 20) {
			Bricks[i].bShape.setPosition(100 * (i - 21), 100);
		}
		else if (i > 10)
		{
			Bricks[i].bShape.setPosition(100 * (i - 11), 50);
		}
	}

	return true;
}

int Game::Update()
{
	Wall wall;
	Paddle paddle{ windowX / 2, windowY - 100 }; // set paddle position
	Ball ball{ windowX / 2, windowY / 2 }; // set ball position
	// code runs while window is open
	while (window.isOpen())
	{
		wall.SetWall();
		paddle.Update();
		ball.Update();
		//ball collision with borders
		if (wall.top.getGlobalBounds().intersects(ball.shape.getGlobalBounds())) 
		{
			ball.velocity.y = -ball.velocity.y;
		}
		if (wall.bottom.getGlobalBounds().intersects(ball.shape.getGlobalBounds()))
		{
			//bounce and reduce lives
			ball.velocity.y = -ball.velocity.y;
			LossLife();
		}
		if (wall.left.getGlobalBounds().intersects(ball.shape.getGlobalBounds()) ||
			wall.right.getGlobalBounds().intersects(ball.shape.getGlobalBounds())) 
		{
			ball.velocity.x = -ball.velocity.x;
		}

		CollisionTest(ball, paddle);

		//ball and brick collision
		for (int i = 0; i < Bricks.size(); i++)
		{
			if (Bricks[i].bShape.getGlobalBounds().intersects(ball.shape.getGlobalBounds()))
			{
				ball.velocity.y = -ball.velocity.y;
				Bricks[i].bShape.setPosition(1200, 0);
				score += 1;
			}
		}

		sf::Event event;
		//PollEvent is our window updating
		while (window.pollEvent(event))
		{
			// if window closed
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//draw bricks
		for (int i = 0; i < Bricks.size(); i++)
		{
			window.draw(Bricks[i].bShape);
		}
		window.draw(paddle.shape);
		window.draw(ball.shape);
		window.display();
	}
	return 0;
}

int Game::LossLife() // not working properly, reason unknown
{
	lives -= 1;
	if(lives < 1)
	{
		return 1;
	}

}
