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

enum direction
{
	none,   //button not pressed
	down,
	left,
	right
};

class Cell;

class Figure
{
	bool speedUp_, moved_;
	figures figure_;
	direction dir_;
	std::vector<Cell*> cells_;

	void PlaceFigure(Cell* cells[10][20]);
	bool CanMove(Cell* cells[10][20]) const;
	bool CanMoveSide(direction dir) const;
	void Rotate();
public:
	Figure(figures figure);
	~Figure();
	void Move(const float x, const float y);
	bool Moved();

	void Input(sf::Keyboard::Key key);
	bool Update(Cell* cells[10][20], sf::Time elapsed);
	void Render(sf::RenderWindow& window);
};

