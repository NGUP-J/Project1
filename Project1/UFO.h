#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include "animation.h"
#include "random.h"

using namespace sf;

class UFO
{

public:
	enum class State { Waiting, Flying, Destroyed };

	State getState() const;
	

	UFO(Texture* texture, Random<>& rand);

	//bool isAlive() const;
	
	inline FloatRect getGlobalBounds()const { return this->sprite.getGlobalBounds(); }

	void Movement();
	void Collision();
	void Update(const float &dt);
	void Draw(RenderTarget& target);



    const Vector2f& getPosition() const;
private:
	Texture *texture;
	Sprite sprite;
	RectangleShape hitbox;
	
	Random<>& m_rng;
	Animation m_animation;

	SoundBuffer Buffer;
	Sound m_flyingSound;

	State m_state;
	float m_vx;

	bool ufocheck;
};

