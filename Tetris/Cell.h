#pragma once
#include <SFML/Graphics.hpp>

enum cellSize
{
	outline = 1,
	inner = 30,
	origin = 16
};

class Cell : public sf::Drawable
{
	sf::RectangleShape body_;
	bool placed_;
	sf::Vector2i pos_;
public:
	Cell(sf::Color color);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void setPosition(const float x, const float y);  //graphical position
	void setPos(const int x, const int y);  //data pos
	void Move(const float x, const float y);
	void MoveCell(const int x, const int y);
	friend class Figure;
};

