#define _CRT_SECURE_NO_WARNINGS
#include "GameState.h"
#include "resource_holder.h"
#include "Player.h"
#include "UFO.h"
#include "random.h"
#include "invader_manager.h"
#include "Bullet.h"
#include "Enemyshot.h"
#include "shield.h"
#include "explosion.h"

void GameState::initfont()
{
	if (!this->font.loadFromFile("resource/fonts/arcade.TTF"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(this->window, this->font);

	this->pmenu->addButton("QUIT", 500.0f, "Quit");
}

void GameState::initGameOverMenu()
{
	this->omenu = new GameOverMenu(this->window, this->font);

	this->omenu->addButton("ENTER", 400.0f, "Enter");
}

void GameState::initText()
{
	e_name.setFont(font);
	e_name.setPosition({ 450, 250 });
	e_name.setCharacterSize(40);
	e_name.setString("Name");
}

GameState::GameState(RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->initfont();
	this->initText();
	this->initPauseMenu();
	this->initGameOverMenu();

	// Init textures
	this->playerTexture.loadFromFile("./resource/img/si/player.png");
	this->bulletTexture.loadFromFile("./resource/img/si/projectile.png");
	this->ufoTexture.loadFromFile("./resource/img/si/ufo.png");
	this->shieldTexture.loadFromFile("./resource/img/si/shield.png");
	this->explodeTexture.loadFromFile("./resource/img/si/explosion.png");

	// Init player
	player = new Player(&this->playerTexture, &this->bulletTexture);
	ufo = new UFO(&this->ufoTexture, m_rng);
	m_invaders = new InvaderManager();

	m_explodeShape.setSize({ 52, 28 });
	m_explodeShape.setTexture(&this->explodeTexture);

	// Init sound
	const int SECT_SIZE = (1000 / 4);
	for (int i = 0; i < 4; i++) {

		this->m_shields.emplace_back(float(i * SECT_SIZE + SECT_SIZE / 2 - Shield::SIZE / 2), &this->shieldTexture);
	}

	// Init font
	//this->font.loadFromFile("resource/fonts/arcade.TTF");
	text.setFont(font);
	text.setPosition({ 20, 10 });
	//text.setString(" score ");
	updatescoredisplay();

	// Init life counter
	m_lifeshape.setSize({ 22, 16 });
	m_lifeshape.setTexture(&this->playerTexture);
	m_lifeshape.setTextureRect({ 0, 0, 11, 8 });
	m_lifenum.setPosition(1000 - (44 * 5) + 80, 10);
	m_lifenum.setFont(font);

	textbox1 = new Textbox(30, sf::Color::White, true);
	textbox1->setFont(font);
	textbox1->setPosition({ 400, 300 });



	t_highscore.setFont(font);
	this->fp = fopen("./resource/HighScore.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(this->score[i], this->name[i]));
	}
	t_highscore.setString("HIGHT SCORE " + std::to_string(score[0]));
	t_highscore.setPosition({ 400, 10});
}

GameState::~GameState()
{
	delete this->pmenu;
	delete player;
}


void GameState::updateGameOverInput(const float& dt)
{
	if (m_isGameOver)
	{
		if (Keyboard::isKeyPressed(Keyboard::Enter) && this->getKeytime())
		{
			scoreboard.WriteFile(textbox1->getText(), m_score);
			this->endState();
		}
	}
}

void GameState::updateEvent(Event input)
{
	if (m_isGameOver)
	{
		textbox1->typedOn(input);
	}
}

void GameState::updatePauseInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape) && this->getKeytime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updateKeybinds(const float& dt)
{

}

void GameState::updatePauseMenuButton()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::updateGameOverButton()
{
	if (this->omenu->isButtonPressed("ENTER"))
	{
		scoreboard.WriteFile(textbox1->getText(), m_score);
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeybinds(dt);
	this->updateKeytime(dt);
	this->updatePauseInput(dt);
	this->updateGameOverInput(dt);
	if (!m_isGameOver)
	{
		if (!this->paused) //unpaused update
		{
			if (m_invaders->areInvadersAlive())
			{
				this->player->Update(dt); //this->window->getSize()
				//player->Update();
				if (this->player->isAlive())
				{
					ufo->Update(dt);
					m_invaders->tryStepInvaders();

					if (m_invaderShotClock.getElapsedTime().asSeconds() >= 0.1 &&
						m_rng.getIntInRange(0, 80) == 2) {
						auto point = m_invaders->getRandomLowestInvaderPoint(m_rng);
						if ((int)point.x == -1)
							return;
						auto type = static_cast<Enemyshot::Type>(m_rng.getIntInRange(1, 2));
						Enemyshots.emplace_back(&this->bulletTexture, point, type);
						m_invaderShotClock.restart();
					}
					auto collisionResult = getCollisionResult(dt);
					if (collisionResult.second.size() > 0) {
						m_score += collisionResult.first;
						for (auto& point : collisionResult.second) {
							m_explosions.emplace_back(point);
						}
					}

					for (auto itr = m_explosions.begin(); itr != m_explosions.end();) {
						if (itr->isLifeOver())
							itr = m_explosions.erase(itr);
						else
							itr++;
					}
				}
			}
			else
			{
				m_invaders->initAddInvader();
				Bullets.clear();
				Enemyshots.clear();
				m_explosions.clear();
			}

			if (this->player->isAlive() == false)
			{
				this->player->tryRevive();
			}

			updatescore(m_score);
			for (int i = 0; i < this->m_invaders->getInvaders().size() ; i++)
			{
				if (this->m_invaders->getInvader(i).getPosition().y > 800)
				{
					m_isGameOver = true;
				}
			}
		}
		else // paused update
		{
			this->pmenu->update(this->mousePosView);
			this->updatePauseMenuButton();
		}
		if (this->player->getLives() <= 0)
		{
			m_isGameOver = true;
		}
	}
	if (m_isGameOver)
	{
		this->omenu->update(this->mousePosView);
		this->updateGameOverButton();
		std::cout << "Gameover! " << "\n";
	}
}

CollisionResult GameState::getCollisionResult(float dt)
{
	// Invader collision
	auto result = m_invaders->tryCollideWithProjectiles(this->player->getBullets());

	for (size_t k = 0; k < this->player->getBulletsSize(); k++)
	{
		this->player->getBullets()[k].Update();

		// Shield collision
		for (size_t l = 0; l < this->m_shields.size(); l++)
		{
			//m_shields[l].update();
			if (this->player->getBullet(k).getGlobalBounds().intersects(this->m_shields[l].getGlobalBounds()))
			{
				std::cout << "sh!!" << "\n";
				this->m_shields[l].onCollide();
				this->player->getBullet(k).onCollide();
			}
		}

		// UFO collision
		if (this->player->getBullet(k).getGlobalBounds().intersects(this->ufo->getGlobalBounds()))
		{
			std::cout << "hit!!" << "\n";
			Vector2f tmp = this->ufo->getPosition();
			//this->player->getBullets().erase(this->player->getBullets().begin() + k);
			this->player->getBullet(k).onCollide();
			ufo->Collision();
			result.second.emplace_back(tmp);
			result.first += 200;
			std::cout << "200" << "\n";
		}

		// Bullet update
		if (this->player->getBullets()[k].getPosition().y < 0)
		{
			this->player->getBullets().erase(this->player->getBullets().begin() + k);
		}
	}


	// Bullet bullet
	for (size_t j = 0; j < this->Enemyshots.size(); j++)
	{
		this->Enemyshots[j].update();
		for (size_t k = 0; k < this->player->getBulletsSize(); k++)
		{
			if (this->player->getBullet(k).getGlobalBounds().intersects(this->Enemyshots[j].getGlobalBounds()))
			{
				this->player->getBullets().erase(this->player->getBullets().begin() + k);
				this->Enemyshots[j].oncollision();
				//result.second.emplace_back(this->player->getBullet(k).getPosition());
			}
		}

		// player collision
		if (this->Enemyshots[j].getGlobalBounds().intersects(this->player->getGlobalBounds()))
		{
			this->Enemyshots[j].oncollision();
			this->player->onCollide();
		}

		// EnemyBullet Update
		if (this->Enemyshots[j].getPosition().y < 0)
		{
			this->Enemyshots.erase(this->Enemyshots.begin() + j);
		}

		// Shield collision
		for (size_t l = 0; l < this->m_shields.size(); l++)
		{
			//m_shields[l].update();
			if (this->Enemyshots[j].getGlobalBounds().intersects(this->m_shields[l].getGlobalBounds()))
			{
				std::cout << "sheeee!!" << "\n";
				this->m_shields[l].onCollide();
				this->Enemyshots[j].oncollision();
			}
		}
	}
	return result;
}

void GameState::updatescore(int newScore)
{
	m_currentScore = newScore;
	updatescoredisplay();
}

void GameState::updatescoredisplay()
{
	text.setString("score " + std::to_string(m_currentScore));
}

void GameState::lifedraw(RenderTarget* window, int lives)
{
	float xOrigin = m_lifenum.getPosition().x + m_lifenum.getGlobalBounds().width + 10;
	float yOrigin = m_lifenum.getPosition().y + m_lifenum.getGlobalBounds().height / 2;

	m_lifenum.setString(std::to_string(lives));

	window->draw(m_lifenum);
	for (int i = 0; i < lives; i++) {
		m_lifeshape.setPosition(xOrigin + i * 44 / 2 + i * 10, yOrigin);
		window->draw(m_lifeshape);
	}
}

void GameState::render(RenderTarget* target)
{
	window->draw(text);
	window->draw(t_highscore);
	lifedraw(this->window, this->player->getLives());
	for (auto& exp : m_explosions)
	{
		m_explodeShape.setPosition(exp.getPosition());
		window->draw(m_explodeShape);
	}
	for (auto& shield : m_shields)
	{
		shield.draw(this->window);
	}
	ufo->Draw(this->window);
	player->Draw(this->window);
	m_invaders->drawInvaders(this->window);
	for (size_t i = 0; i < this->Enemyshots.size(); i++)
	{
		this->Enemyshots[i].Draw(this->window);
	}

	if (this->paused) // Pause menu render
	{
		this->pmenu->render(this->window);
	}

	if (m_isGameOver)
	{
		this->omenu->render(this->window);
		this->textbox1->drawTo(this->window);
		window->draw(e_name);
	}
}

bool GameState::isGameOver() const
{
	return this->player->getLives() == 0 || m_isGameOver;
}


