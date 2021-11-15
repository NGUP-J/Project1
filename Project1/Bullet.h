#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;


class Bullet
{
public:
	Bullet(Texture* texture, Vector2f position,
		Vector2f maxVelocity = Vector2f(0.0f, -10.0f));
	virtual ~Bullet();


	// Accessors
	inline FloatRect getGlobalBounds()const { return sprite.getGlobalBounds(); }
	const Vector2f& getPosition() const;

	// Functions
	void Movement();

	void onCollide();
	void Update();
	void Draw(RenderTarget &target);

	bool isActive() const;

	FloatRect getBox() const;

private:
	Texture* texture;
	Sprite sprite;

	Vector2f maxVelocity;

	bool m_isActive = true;
	

	//Type m_type;
};

