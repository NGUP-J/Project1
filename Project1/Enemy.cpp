#include "Enemy.h"

    Enemy::Enemy(const sf::Vector2f& initialLocation, Type type)
        : collidable(WIDTH, HEIGHT)
        , m_initialPosition(initialLocation)
        , m_location(initialLocation)
        , m_type(type)
    {
    }

    void Enemy::move(float x, float y)
    {
        m_location += {x, y};
    }

    const sf::Vector2f& Enemy::getPosition() const
    {
        return m_location;
    }

    bool Enemy::isAlive() const
    {
        return m_isAlive;
    }

    Enemy::Type Enemy::getType() const
    {
        return m_type;
    }

    void Enemy::onCollide([[maybe_unused]] collidable& other)
    {
        m_isAlive = false;
    }
