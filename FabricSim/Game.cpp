/// @Author Michael Rainsford Ryan

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32u }, "Basic Game" },
	m_exitGame{ false }
{
	setupShapes();
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == nextEvent.type)
		{
			if (sf::Keyboard::Space == nextEvent.key.code)
			{
				setupShapes();
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	for (int i = 0; i < NO_OF_POINTS - 1; i++)
	{
		m_links[i].solve();
	}
}

void Game::render()
{
	m_window.clear();

	m_lines.clear();

	for (int i = 0; i < NO_OF_POINTS - 1; i++)
	{
		m_lines.append({ {m_links[i].pointA->x + POINT_RADIUS, m_links[i].pointA->y + POINT_RADIUS }, sf::Color::White });
		m_lines.append({ {m_links[i].pointB->x + POINT_RADIUS, m_links[i].pointB->y + POINT_RADIUS }, sf::Color::White });

		m_links[i].draw(m_window);
	}

	m_window.draw(m_lines);

	m_window.display();
}

void Game::setupShapes()
{
	float indOffset = RESTING_DISTANCE;
	float xOffset = (WINDOW_WIDTH / 2) - ((NO_OF_POINTS - 1) * indOffset) + POINT_RADIUS;
	float yOffset = 200.0f;

	for (int i = 0; i < NO_OF_POINTS - 1; i++)
	{
		m_points[i].accX = 0;
		m_points[i].accY = 0.05;
		m_points[i].x = i * indOffset + xOffset;
		m_points[i].lastX = i * indOffset + xOffset;
		m_points[i].y = yOffset;
		m_points[i].lastY = yOffset;

		m_links[i].pointA = &m_points[i];
		m_links[i].pointB = &m_points[i+1];
	}

	unsigned hookIndex = NO_OF_POINTS - 1;

	m_points[hookIndex].hook = true;
	m_points[hookIndex].accX = 0;
	m_points[hookIndex].accY = 0;
	m_points[hookIndex].x = hookIndex * indOffset + xOffset;
	m_points[hookIndex].lastX = hookIndex * indOffset + xOffset;
	m_points[hookIndex].y = yOffset;
	m_points[hookIndex].lastY = yOffset;
	m_points[hookIndex].hookX = m_points[hookIndex].x;
	m_points[hookIndex].hookY = m_points[hookIndex].y;
}