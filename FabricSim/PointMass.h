#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

const float POINT_RADIUS{ 2.0f };

class PointMass
{
public:
	PointMass(sf::Vector2f t_position, sf::Vector2f t_acceleration, bool t_isHook = false);

	sf::CircleShape renderPoint{ POINT_RADIUS };
	bool hook;
	float hookX, hookY;

	float x, y;
	float lastX, lastY;
	float accX, accY;

	void update(std::vector<sf::RectangleShape> t_walls);
};

