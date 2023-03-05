#include "Cell.h"

Cell::Cell(sf::Color color)
{
	placed_ = false;

	body_.setSize(sf::Vector2f(inner, inner));
	body_.setOutlineThickness(outline);
	body_.setOrigin(origin, origin);
	body_.setFillColor(color);

	if (color.r > 20)
		color.r -= 20;
	if (color.g > 20)
		color.g -= 20;
	if (color.b > 20)
		color.b -= 20;
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
