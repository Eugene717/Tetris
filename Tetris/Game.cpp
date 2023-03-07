#include "Game.h"
#include "Cell.h"
#include "Figure.h"
#include <random>

Game::Game()
{
	font_.loadFromFile("arial.ttf");

	Cell* border = new Cell(sf::Color(80, 80, 80));
	objects_.push_back(border);

	sf::Text* score = new sf::Text("Score: " + std::to_string(score_), font_, 30);
	score->setFillColor(sf::Color::White);
	score->setPosition(450, 500);
	objects_.push_back(score);

	gameStarted_ = gameEnded_= false;
	figure_ = SpawnFigure();
	nextFigure_ = SpawnFigure();
	nextFigure_->Move(335, 0);
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
	delete nextFigure_;
}

Figure* Game::SpawnFigure()
{
	std::random_device rd;
	switch (rd() % 7)
	{
	case 0:
		return new Figure(figures::I);
		break;
	case 1:
		return new Figure(figures::J);
		break;
	case 2:
		return new Figure(figures::L);
		break;
	case 3:
		return new Figure(figures::O);
		break;
	case 4:
		return new Figure(figures::S);
		break;
	case 5:
		return new Figure(figures::T);
		break;
	case 6:
		return new Figure(figures::Z);
		break;
	default:
		break;
	}
}

bool Game::CheckGameEnd() const
{
	if (cells_[5][0] != nullptr && cells_[5][1] != nullptr)
		return true;

	return false;
}

void Game::StartPlaceElement()
{
	delete figure_;
	figure_ = nextFigure_;
	nextFigure_ = SpawnFigure();

	figure_->Move(-335, 0);
	nextFigure_->Move(335, 0);
}

void Game::DestroyFullLines()
{

}

void Game::Input(sf::Keyboard::Key key)
{
	if (!gameStarted_)
	{
		clock.restart();
		gameStarted_ = true;
	}
	else if (gameEnded_)
	{
		gameStarted_ = false;
		gameEnded_ = false;
	}
	else
		figure_->Input(key);
}

void Game::Update()
{
	if (gameStarted_)
	{
		if (!figure_->Update(cells_, clock.getElapsedTime()))  //placed
		{
			if (CheckGameEnd())
			{
				gameEnded_ = true;
				dynamic_cast<sf::Text*>(objects_[1])->setFillColor(sf::Color::Red);
				return;
			}

			StartPlaceElement();

			DestroyFullLines(); //placed
		}

		if (figure_->Moved())
			clock.restart();
	}
}

void Game::Render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	figure_->Render(window);
	nextFigure_->Render(window);

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
