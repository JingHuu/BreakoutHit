#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
	int speed = 10; // paddle speed
	int windowX = 600; // window width
	int windowY = 600; // window height
	sf::Vector2f rectSize = sf::Vector2f(200.f, 50.f); // size of the rectangle
	sf::Vector2f rectPos = sf::Vector2f((windowX / 2) - (rectSize.x / 2), (windowY / 2) - (rectSize.y / 2)); // rectangle position
	sf::Color colour = sf::Color(255, 255, 0, 255); // custom colour. value between 0-255 for R,G,B,A

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "SFML works!");
	window.setFramerateLimit(60); // stop the game from going insanely fast

	sf::RectangleShape paddle (sf::Vector2f(rectSize.x, rectSize.y)); // create the shape, in this case rectangle
	paddle.setFillColor(colour); // set rectangle colour
	paddle.setPosition(rectPos); // spawn in the center

	int ballSize = 50;
	sf::CircleShape ball(ballSize); // create the ball
	ball.setFillColor(sf::Color::Cyan); // set ball colour
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f); // setup velocity
	//velocity.x = rand() % 10; // initial x will be random between 0-9
	velocity.x = 5;
	velocity.y = -5;
	ball.setPosition(sf::Vector2f(rectPos.x, rectPos.y - rectSize.y)); // move the ball up by the height of the paddle

	// code runs while window is open
	while (window.isOpen())
	{
		// check if left is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// move left
			rectPos.x -= speed;
			// check if the position is out side of the left side window. If it is, reset it back to the edge of the window
			if (rectPos.x <= 0)
			{
				rectPos.x = 0;
			}
			// update the position of our paddle
			paddle.setPosition(rectPos);
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			// move right
			rectPos.x += speed;
			// check if the position is out side of the right side window. If it is, reset it back to the edge of the window
			if (rectPos.x >= windowX - rectSize.x)
			{
				rectPos.x = windowX - rectSize.x;
			}
			// update the position of our paddle
			paddle.setPosition(rectPos);
		}

		ball.move(velocity); // constant movement for ball
		// Set the window barrier for the ball
		if (ball.getPosition().x <= 0 || ball.getPosition().x >= windowX - ballSize*2)
		{
			velocity.x = -velocity.x;
		}
		else if (ball.getPosition().y <= 0 || ball.getPosition().y >= windowY - ballSize*2)
		{
			velocity.y = -velocity.y;
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
		window.draw(paddle);
		window.draw(ball);
		window.display();
	}

	return 0;
}