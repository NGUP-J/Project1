#pragma once

#include "Bullet.h"

class Player
{
private:
	Texture *texture;
	Sprite sprite;
	RectangleShape hitbox;

	Texture *bulletTexture;
	std::vector<Bullet> bullets;

	int controls[3];

	int hp;
	int hpMax;

	int damage;

	int score;

public:
	Player(Texture *texture, Texture *bulletTexture, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
	virtual ~Player();

	// Gets the coordinates of the gun
	sf::Vector2f getGunPosition() const;

	const sf::Vector2f& getPosition() const;

	void Movement();
	void Update();
	void Draw(RenderTarget& target);


};