#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum figures
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
};

class Cell;

class Figure
{
	bool speedUp_;
	std::vector<Cell*> cells_;
public:
	Figure(figures figure);
	~Figure();
	void Input(sf::Keyboard::Key key);
	void Update();
	void Render(sf::RenderWindow& window);
};

