#pragma once

#include "Player.h"
#include "UFO.h"
#include "random.h"
#include "invader_manager.h"
#include "Bullet.h"
#include "Enemyshot.h"
#include "shield.h"
#include "explosion.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "HighScoreState.h"

class Game
{
private:
	RenderWindow *window;

	Clock dtClock;
	float dt;
	std::stack<State*> states;

	Event sfEvent;
	Image icon;

	void initwindow();
	void initStates();

public:
	Game(); //RenderWindow* window
	virtual ~Game();

	// Accessors

	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	//Regular
	void endApplication();

	// Function
	void updateDt();
	void updateSFMLEvent();
	//void Update(const float &dt);
	void update();
	//void Draw();
	void Run();
	void render();

	//bool PixelcollidesPair(const Shield& shield, const Bullet& bullet);
	
};