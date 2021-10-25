#include "Player.h"

enum controls { LEFT = 0, RIGHT, SHOOT };

Player::Player(Texture *texture, Texture *bulletTexture, int LEFT, int RIGHT, int SHOOT)
	:hp(3), hpMax(3), damage(1), score(0)
{
	this->texture = texture;
	this->bulletTexture = bulletTexture;
	this->sprite.setTexture(*this->texture);

	this->sprite.setScale({ 4.0f, 4.0f });
	this->sprite.setPosition({ 500.f, 700.f });
	this->sprite.setTextureRect({ 0, 0, 11, 8 });

	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;
}

Player::~Player()
{

}

void Player::Movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
	{
		this->sprite.move(-10.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
	{
		this->sprite.move(10.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::SHOOT])))
	{
		std::cout << "SPACE" << "\n";
		this->bullets.push_back(Bullet(bulletTexture, this->getGunPosition()));
	}
}

void Player::Update()
{
	this->Movement();

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Update();
	}
}

void Player::Draw(RenderTarget& target)
{
	target.draw(this->sprite);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}
}

sf::Vector2f Player::getGunPosition() const
{
	return { sprite.getPosition().x + sprite.getGlobalBounds().width / 2,
			sprite.getPosition().y };
}

const sf::Vector2f& Player::getPosition() const
{
	return sprite.getPosition();
}