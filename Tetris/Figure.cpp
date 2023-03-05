#include "Figure.h"
#include "Cell.h"

Figure::Figure(figures figure)
{
	speedUp_ = false;

	sf::Color color;

	switch (figure)
	{
	case I:
		color = sf::Color::Cyan;
		break;
	case J:
		color = sf::Color::Blue;
		break;
	case L:
		color = sf::Color(255, 165, 0);
		break;
	case O:
		color = sf::Color::Yellow;
		break;
	case S:
		color = sf::Color::Green;
		break;
	case T:
		color = sf::Color(130, 0, 130);
		break;
	case Z:
		color = sf::Color::Red;
		break;
	default:
		break;
	}

	Cell* first = new Cell(color);
	Cell* second = new Cell(color);
	Cell* third = new Cell(color);
	Cell* four = new Cell(color);

	switch (figure)
	{
	case I:
		first->setPosition(207, 32 * 4 + 16);
		second->setPosition(207, 32 * 3 + 16);
		third->setPosition(207, 32 * 2 + 16);
		four->setPosition(207, 48);
		break;
	case J:
		first->setPosition(207, 48);
		second->setPosition(207, 48 + 32);
		third->setPosition(207, 48 + 32 * 2);
		four->setPosition(207 - 32, 48 + 32 * 2);
		break;
	case L:
		first->setPosition(175, 48);
		second->setPosition(175, 48 + 32);
		third->setPosition(175, 48 + 32 * 2);
		four->setPosition(175 + 32, 48 + 32 * 2);
		break;
	case O:
		first->setPosition(175, 48);
		second->setPosition(175, 48 + 32);
		third->setPosition(207, 48);
		four->setPosition(207, 48 + 32);
		break;
	case S:
		first->setPosition(207, 48);
		second->setPosition(207 + 32, 48);
		third->setPosition(207, 32 + 48);
		four->setPosition(207 - 32, 32 + 48);
		break;
	case T:
		first->setPosition(207, 48);
		second->setPosition(207 - 32, 48);
		third->setPosition(207 + 32, 48);
		four->setPosition(207, 48 + 32);
		break;
	case Z:
		first->setPosition(207, 48);
		second->setPosition(207 - 32, 48);
		third->setPosition(207, 32 + 48);
		four->setPosition(207 + 32, 32 + 48);
		break;
	default:
		break;
	}

	cells_.push_back(first);
	cells_.push_back(second);
	cells_.push_back(third);
	cells_.push_back(four);
}

Figure::~Figure()
{
	while (!cells_.empty())
	{
		cells_.pop_back();
	}
}

void Figure::Input(sf::Keyboard::Key key)
{

}

void Figure::Update()
{

}

void Figure::Render(sf::RenderWindow& window)
{
	for (int i = 0; i < cells_.size(); i++)
	{
		window.draw(*cells_[i]);
	}
}
