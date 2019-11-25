

/// @Author Michael Rainsford Ryan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Rope.h"
#include "Globals.h"

const unsigned NO_OF_POINTS{ 20u };

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

	Rope m_rope;

	std::vector<sf::RectangleShape> m_walls;
};

#endif // !GAME

