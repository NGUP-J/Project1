#pragma once

#include "Player.h"
#include "UFO.h"
#include "random.h"
#include "invader_manager.h"
#include "Bullet.h"
#include "Enemyshot.h"

class Game
{
private:
	RenderWindow *window;

	Player* player;
	UFO *ufo;
	InvaderManager *m_invaders;
	Texture playerTexture;
	Texture bulletTexture;
	Texture ufoTexture;
	std::vector<Enemyshot> Enemyshots;


	SoundBuffer s_shoot;
	Sound m_playerShoot;

	Random<> m_rng;

	sf::Clock m_invaderShotClock;

public:
	Game(RenderWindow* window);
	virtual ~Game();

	// Accessors

	inline RenderWindow& getWindow() { return *this->window; }

	// Setters

	// Function
	void CombatUpdate();
	void Update(const float &dt);
	void Draw();
	
};