#include "Game.h"
#include "Cell.h"
#include "Figure.h"
#include <random>

Game::Game()
{
	Cell* border = new Cell(sf::Color(80, 80, 80));
	objects_.push_back(border);

	SpawnFigure();
}

Game::~Game()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			delete cells_[i][j];
			cells_[i][j] = nullptr;
		}
	}

	while (!objects_.empty())
	{
		objects_.pop_back();
	}

	delete figure_;
}

void Game::SpawnFigure()
{
	std::random_device rd;
	switch (rd() % 7)
	{
	case 0:
		figure_ = new Figure(figures::I);
		break;
	case 1:
		figure_ = new Figure(figures::J);
		break;
	case 2:
		figure_ = new Figure(figures::L);		
		break;
	case 3:
		figure_ = new Figure(figures::O);
		break;
	case 4:
		figure_ = new Figure(figures::S);
		break;
	case 5:
		figure_ = new Figure(figures::T);
		break;
	case 6:
		figure_ = new Figure(figures::Z);
		break;
	default:
		break;
	}

}

void Game::Input(sf::Keyboard::Key key)
{

}

void Game::Update()
{

}

void Game::Render(sf::RenderWindow& window)
{
	figure_->Render(window);

	for (int i = 1; i < 13; i++)  //horiz border
	{
		dynamic_cast<Cell*>(objects_[0])->setPosition(32 * i - 16, 16);
		window.draw(*objects_[0]);
		dynamic_cast<Cell*>(objects_[0])->setPosition(32 * i - 16, 688);
		window.draw(*objects_[0]);
	}
	for (int i = 2; i < 22; i++)  //vert border
	{
		dynamic_cast<Cell*>(objects_[0])->setPosition(16, 32 * i - 16);
		window.draw(*objects_[0]);
		dynamic_cast<Cell*>(objects_[0])->setPosition(368, 32 * i - 16);
		window.draw(*objects_[0]);
	}

	for (int i = 0; i < 10; i++)  //cells
	{
		for (int j = 0; j < 20; j++)
		{
			if (cells_[i][j] != nullptr)
				window.draw(*cells_[i][j]);
		}
	}

	for (int i = 1; i < objects_.size(); i++)  //other objects
	{
		window.draw(*objects_[i]);
	}

	window.display();
}
