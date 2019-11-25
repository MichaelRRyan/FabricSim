#include "PointMass.h"

bool collision(sf::Vector2f t_point, sf::RectangleShape const& t_wall);

PointMass::PointMass(sf::Vector2f t_position, sf::Vector2f t_acceleration, bool t_isHook) :
	x{ t_position.x },
	y{ t_position.y },
	lastX{ t_position.x },
	lastY{ t_position.y },
	hookX{ t_position.x },
	hookY{ t_position.y },
	accX{ t_acceleration.x },
	accY{ t_acceleration.y },
	hook{ t_isHook }
{
}

void PointMass::update(std::vector<sf::RectangleShape> t_walls)
{
	// Inertia: objects in motion stay in motion.
	float velX = x - lastX + accX;
	float velY = y - lastY + accY;

	float nextX = x + velX;
	float nextY = y + velY;

	lastX = x;
	lastY = y;

	x = nextX;
	y = nextY;

	for (sf::RectangleShape const& wall : t_walls)
	{
		if (collision({ x, y }, wall))
		{
			float magnitude = sqrt(velX * velX + velY * velY);
			sf::Vector2f velUnit{ velX / magnitude , velY / magnitude };

			while (collision({ x, y }, wall))
			{
				x -= velUnit.x / 10.0f;
				y -= velUnit.y / 10.0f;
			}
		}
	}

	if (hook)
	{
		x = hookX;
		y = hookY;
	}

	renderPoint.setPosition(x, y);
}

bool collision(sf::Vector2f t_point, sf::RectangleShape const& t_wall)
{
	if (t_point.x > t_wall.getPosition().x&& t_point.x < t_wall.getPosition().x + t_wall.getGlobalBounds().width)
	{
		if (t_point.y > t_wall.getPosition().y&& t_point.y < t_wall.getPosition().y + t_wall.getGlobalBounds().height)
		{
			return true;
		}
	}

	return false;
}