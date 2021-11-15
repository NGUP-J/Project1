#include "Game.h"

Game::Game(RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(60);

	// Init textures
	this->playerTexture.loadFromFile("resource/img/si/player.png");
	this->bulletTexture.loadFromFile("resource/img/si/projectile.png");
	this->ufoTexture.loadFromFile("resource/img/si/ufo.png");

	// Init sound
	
	//this->s_shoot.loadFromFile("resource/sfx/si/shoot.ogg");
	//this->m_playerShoot.setBuffer(s_shoot);

	// Init player
	player = new Player(&this->playerTexture, &this->bulletTexture);
	ufo = new UFO(&this->ufoTexture, m_rng);
	m_invaders = new InvaderManager();
}

Game::~Game()
{
	delete player;
}

void Game::CombatUpdate()
{
	// Window bounds

}

void Game::Update(const float &dt)
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


			for (size_t k = 0; k < this->player->getBulletsSize(); k++)
			{
				this->player->getBullets()[k].Update();


				// Invader collision
				auto result = m_invaders->tryCollideWithProjectiles(this->player->getBullets());
				//if (!this->player->getBullet(k).isActive()) {
				//	this->player->getBullets().erase(this->player->getBullets().begin() + k);
				//}

			// UFO collision
				if (this->player->getBullet(k).getGlobalBounds().intersects(this->ufo->getGlobalBounds()))
				{
					std::cout << "hit!!" << "\n";
					this->player->getBullets().erase(this->player->getBullets().begin() + k);
					ufo->Collision();
					break;
				}

				// Bullet update
				if (this->player->getBullets()[k].getPosition().y < 0)
				{
					this->player->getBullets().erase(this->player->getBullets().begin() + k);
					break;
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
			}
		}
	}
	else
	{
		m_invaders->initAddInvader();
	}

	if (this->player->isAlive() == false)
	{
		this->player->tryRevive();
	}

}

void Game::Draw()
{
	window->clear();
	ufo->Draw(*window);
	player->Draw(*window);
	m_invaders->drawInvaders(*window);
	for (size_t i = 0; i < this->Enemyshots.size(); i++)
	{
		this->Enemyshots[i].Draw(*window);
	}
	window->display();
}

