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
	bool speedUp_, moved_, rotate_;
	int rotation_;
	figures figure_;
	direction dir_;
	std::vector<Cell*> cells_;

	void ReleaseButton();
	void PlaceFigure(Cell* cells[10][20]);
	bool CanMove(Cell* cells[10][20]) const;
	void MoveToFrame(); //when needed to move a piece to inside the board
	bool CanMoveSide(Cell* cells[10][20], direction dir) const;
	void MoveSide(Cell* cells[10][20]);
	bool MoveDown(Cell* cells[10][20]);
	void Rotate(Cell* cells[10][20]);
public:
	Figure(figures figure);
	~Figure();
	void Move(const float x, const float y);

	void Input(sf::Keyboard::Key key);
	bool Update(Cell* cells[10][20]);
	void Render(sf::RenderWindow& window);
};

