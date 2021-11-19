#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Enemyshot
{
public:
	enum class Type { Rectangle, Lightning, Knife };

	Enemyshot(Texture* texture, Vector2f position, Type type);
	virtual ~Enemyshot();

	inline FloatRect getGlobalBounds()const { return sprite.getGlobalBounds(); }
	const Vector2f& getPosition() const;

	void Movement();
	void update();
	void Draw(RenderTarget* target);
	FloatRect getBox() const;

	void oncollision();
private:
	Texture* texture;
	Sprite sprite;

	bool m_isActive = true;
	Type m_type;

	float tmp = 0.75;
};