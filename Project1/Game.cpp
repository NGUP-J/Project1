#include "Game.h"
#include "resource_holder.h"



void Game::initwindow()
{
	this->window = new RenderWindow(VideoMode(1000, 800), "SPACE INVADER", Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(true);
	this->window->setKeyRepeatEnabled(true);
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->states));
}

Game::Game()
{
	this->initwindow();
	this->initStates();
}


Game::~Game()
{
	//delete player;
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending Application!" << "\n";
}

void Game::updateDt() 
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvent()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == Event::Closed)
		{
			this->window->close();
		}
		else if (this->sfEvent.type == Event::TextEntered)
		{
			this->states.top()->updateEvent(sfEvent);
		}
	}
}



void Game::update()
{
	this->updateSFMLEvent();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	// Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}

void Game::Run()
{
	// Game loop
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}