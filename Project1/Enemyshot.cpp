#include "Enemyshot.h"

Enemyshot::Enemyshot(Texture* texture, Vector2f position, Type type)
	:m_type(type)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);

	this->sprite.setScale({ 2.0f, 2.0f });
	if (m_type == Type::Lightning)
	{
		this->sprite.setTextureRect({ 0, 8, 4, 16 });
	}
	else if (m_type == Type::Knife)
	{
		this->sprite.setTextureRect({ 0, 16, 4, 24 });
	}
	this->sprite.setPosition(position);
}

Enemyshot::~Enemyshot()
{

}

void Enemyshot::Movement()
{
	this->sprite.move(0.0f, 7.5f);
}

void Enemyshot::update()
{
	this->Movement();
}

const Vector2f& Enemyshot::getPosition() const
{
	return sprite.getPosition();
}

void Enemyshot::Draw(RenderTarget& target)
{
	target.draw(this->sprite);
}

void Enemyshot::oncollision()
{
	this->sprite.setPosition(0.0f,900.0f);
}