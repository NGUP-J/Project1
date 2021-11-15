#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include "collidable.h"
#include "Player.h"

    class Invader{
    public:
        enum class Type {
            Octopus,
            Crab,
            Squid,
        };

        Invader(const sf::Vector2f& initialLocation, Type type);

        void move(float x, float y);

        const sf::Vector2f& getPosition() const;
        bool isAlive() const;
        Type getType() const;

        sf::FloatRect getBox() const;

        void onCollide();

        void makeAlive()
        {
            m_isAlive = true;
            m_location = m_initialPosition;
        }

    private:
        const sf::Vector2f m_initialPosition;
        sf::Vector2f m_location;
        bool m_isAlive = false;
        Type m_type;
        sf::Sprite sprite;

    public:
        constexpr static float WIDTH = 48;
        constexpr static float HEIGHT = 32;
    };

