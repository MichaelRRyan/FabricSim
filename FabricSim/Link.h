#pragma once

#include "PointMass.h"

const float RESTING_DISTANCE{ 20.0f };

class Link
{
public:
	Link(PointMass *firstPoint, PointMass* lastPoint);

	void solve(std::vector<sf::RectangleShape> t_walls);
	void draw(sf::RenderWindow& t_window);

	inline PointMass* getPtrPointA() { return m_ptrPointA; }
	inline PointMass* getPtrPointB() { return m_ptrPointB; }

private:
	float restingDistance = RESTING_DISTANCE;

	PointMass * m_ptrPointA;
	PointMass * m_ptrPointB;
};

