#pragma once
#include <SFML/Graphics.hpp>

class Cell;
class Figure;

class Game
{
	std::vector<sf::Drawable*> objects_;
	Cell* cells_[10][20];
	Figure* figure_;

	void SpawnFigure();
public:
	Game();
	~Game();

	void Input(sf::Keyboard::Key key);
	void Update();
	void Render(sf::RenderWindow& window);
};

