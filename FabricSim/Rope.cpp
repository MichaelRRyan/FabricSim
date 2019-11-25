#include "Rope.h"

Rope::Rope(int t_pointCount, sf::Vector2f t_position, sf::Vector2f t_acceleration) :
	m_lines{ sf::Lines }
{
	float indOffset = RESTING_DISTANCE;
	//float xOffset = (WINDOW_WIDTH / 2) - ((t_pointCount - 1) * indOffset) + t_position.x;
	//float yOffset = t_position.y;

	// Set up the first two points, the rest can be set in a loop
	PointMass* hookPoint = new PointMass(t_position, { 0.0f, 0.0f }, true);
	PointMass* secondPoint = new PointMass({ indOffset + t_position.x, t_position.y }, t_acceleration, false);
	Link newLink(hookPoint, secondPoint);

	m_links.push_back(newLink);

	// Loop and set up each point a link
	for (int i = 1; i < t_pointCount - 1; i++)
	{
		PointMass* newPoint = new PointMass({ (i + 1) * indOffset + t_position.x, t_position.y }, t_acceleration, false);
		Link newLink(m_links.back().getPtrPointB(), newPoint);

		m_links.push_back(newLink);
	}
}

void Rope::update(std::vector<sf::RectangleShape> t_walls)
{
	for (Link& link : m_links)
	{
		link.solve(t_walls);
	}

	float speed = 1.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_links.back().getPtrPointB()->x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_links.back().getPtrPointB()->x -= speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_links.back().getPtrPointB()->y -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_links.back().getPtrPointB()->y += speed;
	}
}

void Rope::draw(sf::RenderWindow& t_window)
{
	m_lines.clear();

	for (Link& link : m_links)
	{
		m_lines.append({ {link.getPtrPointA()->x + POINT_RADIUS, link.getPtrPointA()->y + POINT_RADIUS }, sf::Color::White });
		m_lines.append({ {link.getPtrPointB()->x + POINT_RADIUS, link.getPtrPointB()->y + POINT_RADIUS }, sf::Color::White });

		link.draw(t_window);
	}

	t_window.draw(m_lines);
}
