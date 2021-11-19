#include "UFO.h"

UFO::UFO(Texture* texture, Random<>& rand) 
	: m_animation(16, 8), ufocheck(1), m_rng(rand), m_state(State::Waiting)
{
	this->texture = texture;
	this->sprite.setTexture(*this->texture);
	this->sprite.setTextureRect({ 0, 0, 16, 8 });
	this->sprite.setPosition({ 500.0f, 45.0f });
	this->sprite.setScale({ 4.5f, 4.5f });
	this->sprite.setColor(Color::Red);

	for (int i = 0; i < 3; i++) 
	{
		m_animation.addFrame(i, seconds(0.2f));
	}
	this->Buffer.loadFromFile("./resource/sfx/si/ufo_lowpitch.ogg");
	m_flyingSound.setBuffer(Buffer);
	m_flyingSound.setVolume(10);
}

UFO::State UFO::getState() const
{
	return m_state;
}

void UFO::Movement()
{
	if (sprite.getPosition().x <= 0)
	{
		ufocheck = true;
	}
	else if (sprite.getPosition().x + 72 >= 1000)
	{
		ufocheck = false;
	}

	if (ufocheck == false)
	{
		sprite.move(-5.0f, 0.0f);
	}
	else
	{
		sprite.move(5.0f, 0.0f);
	}
}

void UFO::Collision()
{
	m_state = State::Destroyed;
	//sprite.setPosition({ 100.0f, 70.0f });
}

void UFO::Update(const float &dt)
{
	
	switch (m_state)
	{
	case UFO::State::Waiting:
		if (m_rng.getIntInRange(1, 250) == 100) {
			std::cout << "fly!!" << "\n";
			m_state = State::Flying;
			m_vx = (float)m_rng.getIntInRange(-1, 1) * 200.0f;
			float xPos;
			if (m_vx >= 0) {
				xPos = -72;
			}
			else {
				xPos = 1000;
			}
			sprite.setPosition(xPos, 45.0f);
		}
		break;
	case UFO::State::Flying:
		sprite.move(m_vx * dt, 0);  // m_vx * dt
		if (getPosition().x <= -72 || getPosition().x >= 1000 + 72) 
		{
			m_state = State::Waiting;
		}
		if ((int)m_flyingSound.getStatus() != (int)Sound::Status::Playing ||
			m_flyingSound.getPlayingOffset() >= seconds(1.5)) {
			m_flyingSound.setPlayingOffset(seconds(0.2f));
			m_flyingSound.play();
		}
		//this->Movement();
		break;
	case UFO::State::Destroyed:
		m_state = State::Waiting;
		break;
	default:
		break;
	}
}

void UFO::Draw(RenderTarget* target)
{
	if (m_state == State::Flying)
	{
		sprite.setTextureRect(m_animation.getFrame());
		target->draw(this->sprite);
	}
}

const Vector2f& UFO::getPosition() const
{
	return sprite.getPosition();
}

