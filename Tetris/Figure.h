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

	void PlaceFigure(Cell* cells[10][20]);
	bool CanMove(Cell* cells[10][20]) const;
public:
	Figure(figures figure);
	~Figure();
	void Move(const float x, const float y);

	void Input(sf::Keyboard::Key key);
	bool Update(Cell* cells[10][20]);
	void Render(sf::RenderWindow& window);
};

