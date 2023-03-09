#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(682, 702), "Tetris");
	window.setFramerateLimit(60);

	Game game;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed))
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				game.Input(event.key.code);
				break;
			}
		}
		
		game.Update();

		game.Render(window);
	}

	return 0;
}
