#include "Figure.h"
#include "Cell.h"

static sf::Clock sideMoveClock, downMoveClock;

Figure::Figure(figures figure) :figure_(figure), dir_(none), rotation_(0)
{
	speedUp_ = moved_ = rotate_ = false;
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

		first->setPos(5, 0);
		second->setPos(5, 1);
		third->setPos(5, 2);
		four->setPos(5, 3);
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
		first->setPosition(207 + 32, 48);
		second->setPosition(207, 48);
		third->setPosition(207, 32 + 48);
		four->setPosition(207 - 32, 32 + 48);

		first->setPos(6, 0);
		second->setPos(5, 0);
		third->setPos(5, 1);
		four->setPos(4, 1);
		break;
	case T:
		first->setPosition(207 - 32, 48);
		second->setPosition(207, 48);
		third->setPosition(207 + 32, 48);
		four->setPosition(207, 48 + 32);

		first->setPos(4, 0);
		second->setPos(5, 0);
		third->setPos(6, 0);
		four->setPos(5, 1);
		break;
	case Z:
		first->setPosition(207 - 32, 48);
		second->setPosition(207, 48);
		third->setPosition(207, 32 + 48);
		four->setPosition(207 + 32, 32 + 48);

		first->setPos(4, 0);
		second->setPos(5, 0);
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
		cells_[i]->placed_ = true;
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

bool Figure::CanMoveSide(Cell* cells[10][20], direction dir) const
{
	if (dir == left)
		for (int i = 0; i < cells_.size(); i++)
		{
			if (cells_[i]->pos_.x == 0)
				return false;
			else if (cells[cells_[i]->pos_.x - 1][cells_[i]->pos_.y] != nullptr)
				return false;
		}
	else if (dir == right)
		for (int i = 0; i < cells_.size(); i++)
		{
			if (cells_[i]->pos_.x == 9)
				return false;
			else if (cells[cells_[i]->pos_.x + 1][cells_[i]->pos_.y] != nullptr)
				return false;
		}

	return true;
}

void Figure::MoveToFrame()
{
	bool left;

	while (true)
	{
		for (int i = 0; i < cells_.size(); i++)
		{
			if (cells_[i]->pos_.x < 0)
			{
				left = true;
				break;
			}
			if (cells_[i]->pos_.x > 9)
			{
				left = false;
				break;
			}

			if (i == cells_.size() - 1)
				return;
		}

		for (int i = 0; i < cells_.size(); i++)
		{
			if (left)
				cells_[i]->MoveCell(1, 0);
			else
				cells_[i]->MoveCell(-1, 0);
		}
	}
}

void Figure::Rotate(Cell* cells[10][20])
{
	int i;
	switch (figure_)
	{
	case I:
		if (rotation_ == 0)
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 1 && cells_[3]->pos_.y > 1)
				if (cells[cells_[3]->pos_.x - 2][cells_[3]->pos_.y - 2] != nullptr)
					break;

			cells_[0]->MoveCell(1, 1);
			cells_[2]->MoveCell(-1, -1);
			cells_[3]->MoveCell(-2, -2);
			rotation_ = 1;
		}
		else
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.x < 8 && cells_[3]->pos_.y < 18)
				if (cells[cells_[3]->pos_.x + 2][cells_[3]->pos_.y + 2] != nullptr)
					break;

			cells_[0]->MoveCell(-1, -1); 
			cells_[2]->MoveCell(1, 1);
			cells_[3]->MoveCell(2, 2);
			rotation_ = 0;
		}
		break;
	case J:
		if (rotation_ == 0)
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.y > 1)
				if (cells[cells_[3]->pos_.x][cells_[3]->pos_.y - 2] != nullptr)
					break;

			cells_[0]->MoveCell(1, 1);
			cells_[2]->MoveCell(-1, -1);
			cells_[3]->MoveCell(0, -2);
			rotation_ = 1;
		}
		else if (rotation_ == 1)
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.x < 8)
				if (cells[cells_[3]->pos_.x + 2][cells_[3]->pos_.y] != nullptr)
					break;

			cells_[0]->MoveCell(-1, 1);
			cells_[2]->MoveCell(1, -1);
			cells_[3]->MoveCell(2, 0);
			rotation_ = 2;
		}
		else if (rotation_ == 2)
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.y < 18)
				if (cells[cells_[3]->pos_.x][cells_[3]->pos_.y + 2] != nullptr)
					break;

			cells_[0]->MoveCell(-1, -1);
			cells_[2]->MoveCell(1, 1);
			cells_[3]->MoveCell(0, 2);
			rotation_ = 3;
		}
		else
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 1)
				if (cells[cells_[3]->pos_.x - 2][cells_[3]->pos_.y] != nullptr)
					break;

			cells_[0]->MoveCell(1, -1);
			cells_[2]->MoveCell(-1, 1);
			cells_[3]->MoveCell(-2, 0);
			rotation_ = 0;
		}
		break;
	case L:
		if (rotation_ == 0)
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 1)
				if (cells[cells_[3]->pos_.x - 2][cells_[3]->pos_.y] != nullptr)
					break;

			cells_[0]->MoveCell(1, 1);
			cells_[2]->MoveCell(-1, -1);
			cells_[3]->MoveCell(-2, 0);
			rotation_ = 1;
		}
		else if (rotation_ == 1)
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.y > 1)
				if (cells[cells_[3]->pos_.x][cells_[3]->pos_.y - 2] != nullptr)
					break;

			cells_[0]->MoveCell(-1, 1);
			cells_[2]->MoveCell(1, -1);
			cells_[3]->MoveCell(0, -2);
			rotation_ = 2;
		}
		else if (rotation_ == 2)
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.x < 8)
				if (cells[cells_[3]->pos_.x + 2][cells_[3]->pos_.y] != nullptr)
					break;

			cells_[0]->MoveCell(-1, -1);
			cells_[2]->MoveCell(1, 1);
			cells_[3]->MoveCell(2, 0);
			rotation_ = 3;
		}
		else
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.y < 18)
				if (cells[cells_[3]->pos_.x][cells_[3]->pos_.y + 2] != nullptr)
					break;

			cells_[0]->MoveCell(1, -1);
			cells_[2]->MoveCell(-1, 1);
			cells_[3]->MoveCell(0, 2);
			rotation_ = 0;
		}
		break;
	case O:  //none
		break;
	case S:
		if (rotation_ == 0)
		{

			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.y > 1)
				if (cells[cells_[3]->pos_.x][cells_[3]->pos_.y - 2] != nullptr)
					break;

			cells_[0]->MoveCell(-1, 1);
			cells_[2]->MoveCell(-1, -1);
			cells_[3]->MoveCell(0, -2);
			rotation_ = 1;
		}
		else
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.y < 18)
				if (cells[cells_[3]->pos_.x][cells_[3]->pos_.y + 2] != nullptr)
					break;

			cells_[0]->MoveCell(1, -1);
			cells_[2]->MoveCell(1, 1);
			cells_[3]->MoveCell(0, 2);
			rotation_ = 0;
		}
		break;
	case T:
		if (rotation_ == 0)
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 0 && cells_[3]->pos_.y > 0)
				if (cells[cells_[3]->pos_.x - 1][cells_[3]->pos_.y - 1] != nullptr)
					break;

			cells_[0]->MoveCell(1, -1);
			cells_[2]->MoveCell(-1, 1);
			cells_[3]->MoveCell(-1, -1);
			rotation_ = 1;
		}
		else if (rotation_ == 1)
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.x < 9 && cells_[3]->pos_.y > 0)
				if (cells[cells_[3]->pos_.x + 1][cells_[3]->pos_.y - 1] != nullptr)
					break;

			cells_[0]->MoveCell(1, 1);
			cells_[2]->MoveCell(-1, -1);
			cells_[3]->MoveCell(1, -1);
			rotation_ = 2;
		}
		else if (rotation_ == 2)
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.x < 9 && cells_[3]->pos_.y < 19)
				if (cells[cells_[3]->pos_.x + 1][cells_[3]->pos_.y + 1] != nullptr)
					break;

			cells_[0]->MoveCell(-1, 1);
			cells_[2]->MoveCell(1, -1);
			cells_[3]->MoveCell(1, 1);
			rotation_ = 3;
		}
		else
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 0 && cells_[3]->pos_.y < 19)
				if (cells[cells_[3]->pos_.x - 1][cells_[3]->pos_.y + 1] != nullptr)
					break;

			cells_[0]->MoveCell(-1, -1);
			cells_[2]->MoveCell(1, 1);
			cells_[3]->MoveCell(-1, 1);
			rotation_ = 0;
		}
		break;
	case Z:
		if (rotation_ == 0)
		{
			if (cells_[0]->pos_.x < 9 && cells_[0]->pos_.y > 0)
				if (cells[cells_[0]->pos_.x + 1][cells_[0]->pos_.y - 1] != nullptr)
					break;
			if (cells_[2]->pos_.x > 0 && cells_[2]->pos_.y > 0)
				if (cells[cells_[2]->pos_.x - 1][cells_[2]->pos_.y - 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 1)
				if (cells[cells_[3]->pos_.x - 2][cells_[3]->pos_.y] != nullptr)
					break;

			cells_[0]->MoveCell(1, -1);
			cells_[2]->MoveCell(-1, -1);
			cells_[3]->MoveCell(-2, 0);
			rotation_ = 1;
		}
		else
		{
			if (cells_[0]->pos_.x > 0 && cells_[0]->pos_.y < 19)
				if (cells[cells_[0]->pos_.x - 1][cells_[0]->pos_.y + 1] != nullptr)
					break;
			if (cells_[2]->pos_.x < 9 && cells_[2]->pos_.y < 19)
				if (cells[cells_[2]->pos_.x + 1][cells_[2]->pos_.y + 1] != nullptr)
					break;
			if (cells_[3]->pos_.x > 1)
				if (cells[cells_[3]->pos_.x + 2][cells_[3]->pos_.y] != nullptr)
					break;

			cells_[0]->MoveCell(-1, 1);
			cells_[2]->MoveCell(1, 1);
			cells_[3]->MoveCell(2, 0);
			rotation_ = 0;
		}
		break;
	default:
		break;
	}

	MoveToFrame();
	rotate_ = false;
}

void Figure::MoveSide(Cell* cells[10][20])
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dir_ = none;
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (dir_ == right)
				speedUp_ = false;
			dir_ = left;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (dir_ == left)
				speedUp_ = false;
			dir_ = right;
		}
	}	

	sf::Int32 time;
	if (speedUp_)
		time = 100;
	else
		time = 0;

	if (sideMoveClock.getElapsedTime().asMilliseconds() >= time)
	{
		if (dir_ == left)
		{
			if (CanMoveSide(cells, left))
				for (int i = 0; i < cells_.size(); i++)
				{
					cells_[i]->setPos(cells_[i]->pos_.x - 1, cells_[i]->pos_.y);
					cells_[i]->Move(-32, 0);
				}
		}
		else if (dir_ == right)
		{
			if (CanMoveSide(cells, right))
				for (int i = 0; i < cells_.size(); i++)
				{
					cells_[i]->setPos(cells_[i]->pos_.x + 1, cells_[i]->pos_.y);
					cells_[i]->Move(32, 0);
				}
		}

		if (!speedUp_)
			speedUp_ = true;

		sideMoveClock.restart();
	}
}

bool Figure::MoveDown(Cell* cells[10][20])
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		dir_ = down;
	}

	sf::Int32 time;
	if (speedUp_ && dir_ == down)
		time = 50;
	else
		time = 250;

	if (downMoveClock.getElapsedTime().asMilliseconds() >= time)  //down
	{
		if (!CanMove(cells))
		{
			PlaceFigure(cells);
			return false;
		}

		for (int i = 0; i < cells_.size(); i++)
		{
			cells_[i]->setPos(cells_[i]->pos_.x, cells_[i]->pos_.y + 1);
			cells_[i]->Move(0, 32);
		}

		if (!speedUp_)
			speedUp_ = true;

		downMoveClock.restart();
	}

	dir_ = none;
	ReleaseButton();

	return true;
}

void Figure::ReleaseButton()
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speedUp_ = false;
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
	else if (key == sf::Keyboard::Up)
		rotate_ = true;
}

bool Figure::Update(Cell* cells[10][20])
{	
	if (rotate_)
		Rotate(cells);
	MoveSide(cells);
	return MoveDown(cells);	
}

void Figure::Render(sf::RenderWindow& window)
{
	for (int i = 0; i < cells_.size(); i++)
	{
		window.draw(*cells_[i]);
	}
}
