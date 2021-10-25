#pragma once

#include "Player.h"

class Game
{
private:
	RenderWindow *window;

	Player *player;
	Texture playerTexture;
	Texture bulletTexture;

public:
	Game(RenderWindow* window);
	virtual ~Game();

	// Accessors
	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Function
	void Update();
	void Draw();

};