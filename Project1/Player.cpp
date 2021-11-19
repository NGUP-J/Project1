#include "Player.h"


enum controls { LEFT = 0, RIGHT, SHOOT };

Player::Player(Texture *texture, Texture *bulletTexture, int LEFT, int RIGHT, int SHOOT)
	:hp(3), hpMax(3), damage(1), score(0), m_deathAnimation(11, 8)
{
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->m_sprite.setTexture(*this->texture);

	this->m_sprite.setScale({ 4.0f, 4.0f });
	this->m_sprite.setPosition({ 500.f, 700.f });
	this->m_sprite.setTextureRect({ 0, 0, 11, 8 });

	for (int i = 0; i < 20; i++) 
	{
		m_deathAnimation.addFrame(((i % 2) + 1), seconds(0.1f));
	}

	this->s_shoot.loadFromFile("./resource/sfx/si/shoot.ogg");
	this->m_playerShoot.setBuffer(s_shoot);
	this->m_playerShoot.setVolume(10);

	this->Buffer.loadFromFile("./resource/sfx/si/explosion.ogg");
	this->m_deathSound.setBuffer(Buffer);
	this->m_deathSound.setVolume(10);

	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;
}

Player::~Player()
{

}

void Player::Movement(const float &dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
	{
		if (m_sprite.getPosition().x <= 1) 
		{
			m_sprite.setPosition(1.0f, 700.0f);
		}
		else
		{
			this->m_sprite.move(-500.f * dt, 0.f);
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
	{
		auto w = m_sprite.getGlobalBounds().width;
		if (m_sprite.getPosition().x + w >= 999) 
		{
			m_sprite.setPosition(1000 - 1.0f - w, 700);
		}
		else
		{
			this-> m_sprite.move(500.f * dt, 0.f);
		}
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])) && m_playerShotClock.getElapsedTime().asSeconds() > 0.5f)
	{
		std::cout << "SPACE" << "\n";
		this->bullets.push_back(Bullet(bulletTexture, this->getGunPosition()));
		m_playerShotClock.restart();
		m_playerShoot.play();
	}
}

void Player::restart()
{
	m_sprite.setTextureRect({ 0, 0, 11, 8 });
	m_isAlive = true;
	m_livesLeft--;
	m_sprite.setPosition({ 500, 700 });
}

void Player::Update(const float &dt)  //Vector2u windowBounds
{
	if (isAlive())
	{
		this->Movement(dt);
	}
	//for (size_t i = 0; i < this->bullets.size(); i++)
	//{
	//	this->bullets[i].Update();
	//}
}

void Player::Draw(RenderTarget* target)
{
	if (!m_isAlive) {
		m_sprite.setTextureRect(m_deathAnimation.getFrame());
	}
	if (m_livesLeft > 0) {
		//target.draw(m_sprite);
		target->draw(this->m_sprite);
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}

sf::Vector2f Player::getGunPosition() const
{
	return { m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
			m_sprite.getPosition().y };
}

const Vector2f& Player::getPosition() const
{
	return m_sprite.getPosition();
}

Bullet& Player::getBullet(unsigned index)
{
	if (index < 0 || index > this->bullets.size())
		throw"OUT OF BOUNDS! PLAYER::GETBULLET!";

	return this->bullets[index];
}

bool Player::isAlive() const
{
	return m_isAlive;
}

void Player::tryRevive()
{
	if (m_deathTimer.getElapsedTime().asSeconds() >= 1.5f) {
		restart();
	}
}

void Player::onCollide()
{
	m_isAlive = false;
	m_deathTimer.restart();
	m_deathSound.play();
}

int Player::getLives() const
{
	return m_livesLeft;
}