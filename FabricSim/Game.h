/// @Author Michael Rainsford Ryan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

const unsigned WINDOW_WIDTH{ 800u };
const unsigned WINDOW_HEIGHT{ 800u };

const float POINT_RADIUS{ 6.0f };
const float RESTING_DISTANCE{ 20.0f };

const unsigned NO_OF_POINTS{ 20u };

struct PointMass
{
	sf::CircleShape renderPoint{ POINT_RADIUS };
	bool hook = false;
	float hookX, hookY;

	float x, y;
	float lastX, lastY;
	float accX, accY;

	void update() {
		// Inertia: objects in motion stay in motion.
		float velX = x - lastX;
		float velY = y - lastY;

		float nextX = x + velX + accX;
		float nextY = y + velY + accY;

		lastX = x;
		lastY = y;

		x = nextX;
		y = nextY;

		// Boundary collisions
		if (x < 0)
		{
			x = 0;
			if (velX < 0)
			{
				velX *= -1;
			}
		}

		if (x > WINDOW_WIDTH)
		{
			x = WINDOW_WIDTH;
			if (velX > 0)
			{
				velX *= -1;
			}
		}

		if (y < 0)
		{
			y = 0;
			if (velY < 0)
			{
				velY *= -1;
			}
		}

		if (y > WINDOW_HEIGHT)
		{
			y = WINDOW_HEIGHT;
			if (velY > 0)
			{
				velY *= -1;
			}
		}

		if (hook)
		{
			x = hookX;
			y = hookY;
		}

		renderPoint.setPosition(x, y);
	}
};

struct Link
{
	float restingDistance = RESTING_DISTANCE;

	PointMass *pointA;
	PointMass *pointB;

	void solve()
	{
		float diffX = pointA->x - pointB->x;
		float diffY = pointA->y - pointB->y;
		float d = sqrt(diffX * diffX + diffY * diffY);

		float difference = (restingDistance - d) / d;

		float translateX = diffX * 0.48f * difference;
		float translateY = diffY * 0.48f * difference;

		pointA->x += translateX;
		pointA->y += translateY;

		pointB->x -= translateX;
		pointB->y -= translateY;

		pointA->update();
		pointB->update();
	}

	void draw(sf::RenderWindow &t_window)
	{
		t_window.draw(pointA->renderPoint);
		t_window.draw(pointB->renderPoint);
	}
};

class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupShapes();

	sf::RenderWindow m_window;
	bool m_exitGame;

	sf::VertexArray m_lines{ sf::Lines };

	PointMass m_points[NO_OF_POINTS];
	Link m_links[NO_OF_POINTS - 1];
};

#endif // !GAME

