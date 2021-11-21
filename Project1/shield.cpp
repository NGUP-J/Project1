#include "shield.h"
#include "random.h"
#include <iostream>



Shield::Shield(float x, Texture *texture) : m_position(x,600)
{
    //this->texture.loadFromFile("resource/img/si/shield.png");
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale({ 0.2f ,  0.2f });
    this->sprite.setPosition(m_position);
    this->sprite.setColor(Color::Green);
}

void Shield::onCollide()
{
    s_live--;
    if (s_live == 5)
    {
        this->sprite.setColor(Color::Yellow);
    }
    if (s_live == 3)
    {
        this->sprite.setColor(Color(255, 128, 0));
    }    
    if (s_live == 1)
    {
        this->sprite.setColor(Color::Red);
    }
    if (s_live <= 0)
    {
        this->sprite.setPosition({ -100.f, -100.f });
    }
}

void Shield::update()
{

}

void Shield::draw(RenderTarget* target)
{
    target->draw(this->sprite);
}

const sf::Vector2f& Shield::getPosition() const
{
    return m_position;
}