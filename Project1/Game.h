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
	
	/*Player* player;
	UFO *ufo;
	InvaderManager *m_invaders;
	RectangleShape m_explodeShape;
	Texture playerTexture;
	Texture bulletTexture;
	Texture ufoTexture;
	Texture shieldTexture;
	Texture explodeTexture;
	std::vector<Explosion> m_explosions;
	std::vector<Enemyshot> Enemyshots;
	std::vector<Shield> m_shields;
	std::vector<Bullet> Bullets;

	SoundBuffer s_shoot;
	Sound m_playerShoot;

	Random<> m_rng;

	sf::Clock m_invaderShotClock;*/

	//CollisionResult getCollisionResult(float dt);

	Event sfEvent;

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