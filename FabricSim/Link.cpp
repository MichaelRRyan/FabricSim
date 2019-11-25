#include "Link.h"

Link::Link(PointMass* firstPoint, PointMass* lastPoint)
{
	m_ptrPointA = firstPoint;
	m_ptrPointB = lastPoint;
}

void Link::solve(std::vector<sf::RectangleShape> t_walls)
{
	float diffX = m_ptrPointA->x - m_ptrPointB->x;
	float diffY = m_ptrPointA->y - m_ptrPointB->y;
	float d = sqrt(diffX * diffX + diffY * diffY);

	float difference = (restingDistance - d) / d;

	float translateX = diffX * 0.48f * difference;
	float translateY = diffY * 0.48f * difference;

	m_ptrPointA->x += translateX;
	m_ptrPointA->y += translateY;

	m_ptrPointB->x -= translateX;
	m_ptrPointB->y -= translateY;

	m_ptrPointA->update(t_walls);
	m_ptrPointB->update(t_walls);
}

void Link::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_ptrPointA->renderPoint);
	t_window.draw(m_ptrPointB->renderPoint);
}
