#include "Cell.h"

Cell::Cell(sf::Color color)
{
	placed_ = false;

	body_.setSize(sf::Vector2f(inner, inner));
	body_.setOutlineThickness(outline);
	body_.setOrigin(origin, origin);
	body_.setFillColor(color);

	if (color.r > 50)
		color.r -= 50;
	if (color.g > 50)
		color.g -= 50;
	if (color.b > 50)
		color.b -= 50;
	body_.setOutlineColor(color);
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body_, states);
}

void Cell::setPosition(const float x, const float y)
{
	body_.setPosition(x, y);
}

void Cell::setPos(const int x, const int y)
{
	pos_.x = x;
	pos_.y = y;
}

void Cell::Move(const float x, const float y)
{
	body_.move(x, y);
}

void Cell::MoveCell(const int x, const int y)
{
	pos_.x += x;
	pos_.y += y;
	body_.move(x * 32, y * 32);
}
