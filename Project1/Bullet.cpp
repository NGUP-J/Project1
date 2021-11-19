#include "Bullet.h"

Bullet::Bullet(Texture* texture, Vector2f position,
	Vector2f maxVelocity)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->maxVelocity = maxVelocity;

	this->sprite.setScale({ 1.5f, 1.5f });
    this->sprite.setTextureRect({ 0, 0, 4, 8 });
	this->sprite.setPosition(position);
	
}

Bullet::~Bullet()
{

}

void Bullet::Movement()
{
	this->sprite.move(this->maxVelocity.x, this->maxVelocity.y);
}

void Bullet::Update()
{
	this->Movement();
}

void Bullet::Draw(RenderTarget* target)
{
	target->draw(this->sprite);
}

const Vector2f& Bullet::getPosition() const
{
	return sprite.getPosition();
}

bool Bullet::isActive() const
{
	return m_isActive;
}

FloatRect Bullet::getBox() const
{
	return { getPosition().x, getPosition().y, 24.0f / 1.5f , 12.0f };
}

void Bullet::onCollide()
{
	m_isActive = false;
	sprite.setPosition( 0.0f , -1.0f);
}
