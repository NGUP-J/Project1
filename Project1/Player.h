#pragma once

#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "animation.h"


class Player
{
private:
	void restart();

	Texture *texture;
	Sprite m_sprite;
	RectangleShape hitbox;

	Texture *bulletTexture;
	std::vector<Bullet> bullets;

    Clock m_playerShotClock;


    sf::Vector2f m_velocity;

	SoundBuffer s_shoot;
	Sound m_playerShoot;
	
	SoundBuffer Buffer;
	Sound m_deathSound;
	Animation m_deathAnimation;
	int n = 0;
	Clock redelay;

	int controls[3];
	int hp;
	int hpMax;

	int damage;

	int score;
	
	Clock m_deathTimer;
    bool m_isAlive = true;
    int m_livesLeft = 3;
	Clock revive;
	
public:
	Player(Texture *texture, Texture *bulletTexture, int LEFT = 0, int RIGHT = 3, int SHOOT = 57);
	virtual ~Player();

	inline const int getBulletsSize()const { return this->bullets.size(); }

	inline FloatRect getGlobalBounds()const { return m_sprite.getGlobalBounds(); }

	Bullet& getBullet(unsigned index);

	// Accessors
	inline std::vector<Bullet>& getBullets() { return this->bullets; }

	// Gets the coordinates of the gun
	Vector2f getGunPosition() const;

	const Vector2f& getPosition() const;

	int getLives() const;
    bool isAlive() const;

	void Movement(const float& dt);
	void Update(const float &dt);  //Vector2u windowBounds

	void onCollide();
	void Draw(RenderTarget* target);

	void tryRevive();

};