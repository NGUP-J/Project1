#include "Game.h"
Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);

	// Init textures
	this->playerTexture.loadFromFile("resource/img/si/player.png");
	this->bulletTexture.loadFromFile("resource/img/si/projectile.png");

	// Init player
	player = new Player(&this->playerTexture, &this->bulletTexture);
}

Game::~Game()
{
	delete player;
}

void Game::Update()
{
	player->Update();
}

void Game::Draw()
{
	window->clear();

	player->Draw(*window);

	window->display();
}