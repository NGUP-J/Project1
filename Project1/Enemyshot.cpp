#include "Enemyshot.h"

Enemyshot::Enemyshot(Texture* texture, Vector2f position, Type type)
	:m_type(type)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);

	this->sprite.setScale({ 3.0f, 3.0f });
	if (m_type == Type::Lightning)
	{
		this->sprite.setTextureRect({ 0, 8, 4, 8 });
		velocity = 5.0f;
	}
	else if (m_type == Type::Knife)
	{
		this->sprite.setTextureRect({ 0, 16, 4, 24 });
		velocity = 7.5f;
	}
	this->sprite.setPosition(position);
}

Enemyshot::~Enemyshot()
{

}

void Enemyshot::Movement()
{
	this->sprite.move(0.0f, velocity);
}

void Enemyshot::update()
{
	this->Movement();
	if (animationtime.getElapsedTime() > seconds(0.05))
	{
		animationtime.restart();
		if (m_type == Type::Lightning && famepoint == 2)
		{
			this->sprite.setTextureRect({ 4, 8, 8, 8 });
			famepoint = 1;
		}
		else if (m_type == Type::Knife && famepoint == 2)
		{
			this->sprite.setTextureRect({ 4, 16, 8, 24 });
			famepoint = 1;
		}
		else if (m_type == Type::Lightning && famepoint == 1)
		{
			this->sprite.setTextureRect({ 0, 8, 4, 8 });
			famepoint = 2;
		}
		else if (m_type == Type::Knife && famepoint == 1)
		{
			this->sprite.setTextureRect({ 0, 16, 4, 24 });
			famepoint = 2;
		}
	}
}

const Vector2f& Enemyshot::getPosition() const
{
	return sprite.getPosition();
}

void Enemyshot::Draw(RenderTarget* target)
{
	target->draw(this->sprite);
}

void Enemyshot::oncollision()
{
	this->sprite.setPosition(0.0f,900.0f);
}

FloatRect Enemyshot::getBox() const
{
	return { getPosition().x, getPosition().y, 24.0f / 1.5f , 12.0f };
}