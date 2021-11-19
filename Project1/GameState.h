#pragma once

#include "Player.h"
#include "UFO.h"
#include "random.h"
#include "invader_manager.h"
#include "Bullet.h"
#include "Enemyshot.h"
#include "shield.h"
#include "explosion.h"
#include "State.h"
#include "PauseMenu.h"
#include "Textbox.h"
#include "GameOverMenu.h"
#include "ScoreBoard.h"

class GameState : public State
{
private:
	PauseMenu* pmenu;
	GameOverMenu* omenu;
	Textbox* textbox1;
	ScoreBoard scoreboard;

	Player* player;
	UFO* ufo;
	InvaderManager* m_invaders;
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

	Clock m_invaderShotClock;

	CollisionResult getCollisionResult(float dt);

	FILE* fp;
	char temp[255];
	unsigned int score[6];
	string name[6];
	vector<pair<int, string>> userScore;

	Font font;
	Text text;
	Text t_highscore;
	Text e_name;
	int m_score = 0;
	int m_currentScore;

	RectangleShape m_lifeshape;
	Text m_lifenum;
	bool m_isGameOver = false;

	void initfont();
	void initPauseMenu();
	void initGameOverMenu();
	void initText();
public:
	GameState(RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	// functions
	void setGameIsOver()
	{
		m_isGameOver = true;
	}


	void updateEvent(Event input);
	void updatePauseInput(const float& dt);
	void updateKeybinds(const float& dt);
	void updatePauseMenuButton();
	void updateGameOverButton();
	void update(const float& dt);
	void updatescore(int newScore);
	void updatescoredisplay();
	void lifedraw(RenderTarget* window, int lives);
	void render(RenderTarget* target = NULL);
	
	bool isGameOver() const;
};

