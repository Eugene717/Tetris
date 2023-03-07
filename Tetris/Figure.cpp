#include "Figure.h"
#include "Cell.h"

Figure::Figure(figures figure)
{
	speedUp_ = moved_ = false;
	dir_ = none;
	figure_ = figure;

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
		first->setPosition(207, 48);
		second->setPosition(207, 32 * 2 + 16);
		third->setPosition(207, 32 * 3 + 16);
		four->setPosition(207, 32 * 4 + 16);

		first->setPos(5, 3);
		second->setPos(5, 2);
		third->setPos(5, 1);
		four->setPos(5, 0);
		break;
	case J:
		first->setPosition(207, 48);
		second->setPosition(207, 48 + 32);
		third->setPosition(207, 48 + 32 * 2);
		four->setPosition(207 - 32, 48 + 32 * 2);

		first->setPos(5, 0);
		second->setPos(5, 1);
		third->setPos(5, 2);
		four->setPos(4, 2);
		break;
	case L:
		first->setPosition(175, 48);
		second->setPosition(175, 48 + 32);
		third->setPosition(175, 48 + 32 * 2);
		four->setPosition(175 + 32, 48 + 32 * 2);

		first->setPos(4, 0);
		second->setPos(4, 1);
		third->setPos(4, 2);
		four->setPos(5, 2);
		break;
	case O:
		first->setPosition(175, 48);
		second->setPosition(175, 80);
		third->setPosition(207, 48);
		four->setPosition(207, 80);

		first->setPos(4, 0);
		second->setPos(4, 1);
		third->setPos(5, 0);
		four->setPos(5, 1);
		break;
	case S:
		first->setPosition(207, 48);
		second->setPosition(207 + 32, 48);
		third->setPosition(207, 32 + 48);
		four->setPosition(207 - 32, 32 + 48);

		first->setPos(5, 0);
		second->setPos(6, 0);
		third->setPos(5, 1);
		four->setPos(4, 1);
		break;
	case T:
		first->setPosition(207, 48);
		second->setPosition(207 - 32, 48);
		third->setPosition(207 + 32, 48);
		four->setPosition(207, 48 + 32);

		first->setPos(5, 0);
		second->setPos(4, 0);
		third->setPos(6, 0);
		four->setPos(5, 1);
		break;
	case Z:
		first->setPosition(207, 48);
		second->setPosition(207 - 32, 48);
		third->setPosition(207, 32 + 48);
		four->setPosition(207 + 32, 32 + 48);

		first->setPos(5, 0);
		second->setPos(4, 0);
		third->setPos(5, 1);
		four->setPos(6, 1);
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
	cells_.clear();
}

void Figure::Move(const float x, const float y)
{
	for (int i = 0; i < cells_.size(); i++)
	{
		cells_[i]->Move(x, y);
	}
}

void Figure::PlaceFigure(Cell* cells[10][20])
{
	for (int i = 0; i < cells_.size(); i++)
	{
		cells[cells_[i]->pos_.x][cells_[i]->pos_.y] = cells_[i];
	}
}

bool Figure::CanMove(Cell* cells[10][20]) const
{
	for (int i = 0; i < cells_.size(); i++)
	{
		if (cells_[i]->pos_.y + 1 > 19)
		{
			return false;
		}
		if (cells[cells_[i]->pos_.x][cells_[i]->pos_.y + 1] != nullptr)
		{
			return false;
		}
	}
	return true;
}

bool Figure::CanMoveSide(direction dir) const
{
	if (dir == left)
		for (int i = 0; i < cells_.size(); i++)
		{
			if (cells_[i]->pos_.x == 0)
				return false;
		}
	else if (dir == right)
		for (int i = 0; i < cells_.size(); i++)
		{
			if (cells_[i]->pos_.x == 9)
				return false;
		}

	return true;
}

bool Figure::Moved()
{
	if (moved_)
	{
		moved_ = false;
		return true;
	}
	else 
		return moved_;
}

void Figure::Rotate()
{
	switch (figure_)
	{
	case I:

		break;
	case J:

		break;
	case L:

		break;
	case O:

		break;
	case S:

		break;
	case T:

		break;
	case Z:

		break;
	default:
		break;
	}
}

void Figure::Input(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Down)
		dir_ = down;
	else if (key == sf::Keyboard::Left)
		dir_ = left;
	else if (key == sf::Keyboard::Right)
		dir_ = right;
	else if (key == sf::Keyboard::Up)  //rotate
		Rotate();
}

bool Figure::Update(Cell* cells[10][20], sf::Time elapsed)
{	
	sf::Int32 time;
	if (speedUp_)
		time = 50;
	else
		time = 250;

	if (elapsed.asMilliseconds() >= time)
	{
		speedUp_ = false;

		switch (dir_)
		{
		case none:
			speedUp_ = false;
			break;
		case down:
			speedUp_ = true;
			break;
		case left:
			speedUp_ = true;	
			if (CanMoveSide(left))
				for (int i = 0; i < cells_.size(); i++)
				{
					cells_[i]->setPos(cells_[i]->pos_.x - 1, cells_[i]->pos_.y);
					cells_[i]->Move(-32, 0);
				}
			break;
		case right:
			speedUp_ = true;
			if (CanMoveSide(right))
				for (int i = 0; i < cells_.size(); i++)
				{
					cells_[i]->setPos(cells_[i]->pos_.x + 1, cells_[i]->pos_.y);
					cells_[i]->Move(32, 0);
				}
			break;
		default:
			break;
		}

		if (!CanMove(cells))
		{
			PlaceFigure(cells);
			return false;
		}

		if (speedUp_ && dir_ == down)
			time = 50;
		else
			time = 250;
		if (elapsed.asMilliseconds() >= time)  //down
		{
			for (int i = 0; i < cells_.size(); i++)
			{
				cells_[i]->setPos(cells_[i]->pos_.x, cells_[i]->pos_.y + 1);
				cells_[i]->Move(0, 32);
			}
			moved_ = true;
		}

		dir_ = none;
	}

	return true;
}

void Figure::Render(sf::RenderWindow& window)
{
	for (int i = 0; i < cells_.size(); i++)
	{
		window.draw(*cells_[i]);
	}
}
