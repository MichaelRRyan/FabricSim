#pragma once

#include "PointMass.h"
#include "Link.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Rope
{
public:
	Rope(int t_pointCount, sf::Vector2f t_position = { 0.0f, 0.0f }, sf::Vector2f t_acceleration = { 0.0f, 0.05f });
	void update(std::vector<sf::RectangleShape> t_walls);
	void draw(sf::RenderWindow& t_window);

private:
	std::vector<Link> m_links;
	sf::VertexArray m_lines;
};

