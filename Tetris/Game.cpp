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

bool Game::CheckGameEnd()
{
	return !nextFigure_->CanBePlaced(cells_);
}

void Game::InitGame()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			delete cells_[i][j];
			cells_[i][j] = nullptr;
		}
	}

	delete figure_;
	delete nextFigure_;

	gameStarted_ = gameEnded_ = false;
	figure_ = SpawnFigure();
	nextFigure_ = SpawnFigure();
	nextFigure_->Move(335, 0);
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
	bool filled = true;
	int scored = 0;

	for (int j = 19; j >= 0; j--)
	{
		for (int i = 0; i < 10; i++)
		{
			if (cells_[i][j] == nullptr)
			{
				filled = false;
				break;
			}
		}

		if (filled)
		{
			if (scored == 0)
				scored = 100;  //1 row
			else if (scored == 100)
				scored = 300;  //2 rows
			else if (scored == 300) 
				scored = 700;  //3 rows
			else
				scored = 1500; //tetris
			
			for (int k = j; k >= 0; k--)
			{
				for (int i = 0; i < 10; i++)
				{
					if (k != 0)
					{
						if (cells_[i][k] != nullptr)
							delete cells_[i][k];
						cells_[i][k] = cells_[i][k - 1];

						if (cells_[i][k - 1] != nullptr)
							cells_[i][k - 1]->MoveCell(0, 1);

						cells_[i][k - 1] = nullptr;
					}
					else
					{
						if (cells_[i][k] != nullptr)
						{
							delete cells_[i][k];
							cells_[i][k] = nullptr;
						}
					}
				}
			}

			j++;
		}

		filled = true;
	}

	score_ += scored;
	dynamic_cast<sf::Text*>(objects_[1])->setString("Score: " + std::to_string(score_));
}

void Game::Input(sf::Keyboard::Key key)
{
	if (!gameStarted_)
	{
		gameStarted_ = true;
	}
	else if (gameEnded_)
	{
		InitGame();
	}
	else
		figure_->Input(key);
}

void Game::Update()
{
	if (gameStarted_)
	{
		if (!figure_->Update(cells_))  //placed
		{
			DestroyFullLines(); //placed

			if (CheckGameEnd())
			{
				gameEnded_ = true;
				dynamic_cast<sf::Text*>(objects_[1])->setFillColor(sf::Color::Red);
				return;
			}

			StartPlaceElement();
		}
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
