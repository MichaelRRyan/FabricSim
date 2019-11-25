/// @Author Michael Rainsford Ryan

#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ WINDOW_WIDTH, WINDOW_HEIGHT, 32u }, "Basic Game" },
	m_exitGame{ false },
	m_rope{ NO_OF_POINTS, {WINDOW_WIDTH / 2.0f, 200.0f} }
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

	m_rope.update(m_walls);
}

void Game::render()
{
	m_window.clear();

	m_rope.draw(m_window);

	for (sf::RectangleShape const& wall : m_walls)
	{
		m_window.draw(wall);
	}

	m_window.display();
}

void Game::setupShapes()
{
	sf::RectangleShape newWall({50.0f, 50.0f});
	newWall.setPosition(400.0f, 400.0f);

	m_walls.push_back(newWall);
}