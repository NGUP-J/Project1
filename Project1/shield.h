#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Bullet.h"
#include "Enemyshot.h"

class Shield {
        constexpr static int SECT_SIZE = 20;
private:
    Sprite sprite;
    Texture* texture;
    Vector2f m_position;

    int s_live = 5;
public:
    constexpr static int SIZE = SECT_SIZE * 4;
    Shield(float x, Texture* texture);
        
    void update();
    virtual void draw(RenderTarget* target);

    inline FloatRect getGlobalBounds()const { return sprite.getGlobalBounds(); }
    const Vector2f& getPosition() const;
    void onCollide();
};