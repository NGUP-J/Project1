#pragma once

#include "animation_renderer.h"
#include "invader.h"
#include "Bullet.h"
#include <SFML/Audio.hpp>
#include <vector>
#include "random.h"
#include "Player.h"
#include "collidable.h"

using namespace sf;

    using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;


    class InvaderManager {
    public:
        InvaderManager();

   
        void tryStepInvaders();


        void drawInvaders(RenderTarget* target);
 
        CollisionResult tryCollideWithProjectiles(std::vector<Bullet>& bullets);
        sf::Vector2f getRandomLowestInvaderPoint(Random<>& random);

        int getAliveInvadersCount() const;
        void initAddInvader();
        bool areInvadersAlive() const;

        inline std::vector<Invader>& getInvaders() { return this->m_invaders; }

        Invader& getInvader(unsigned index);

    private:
        void updateStepDelay();


        bool testInvaderPosition(const Invader& invader) const;

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;
        Player* player;


        AnimationRenderer m_invaderRenderer;
        unsigned m_aliveInvaders = 0;

        bool startsteptime = true;

        bool m_hasAllInvadersBeenAdded = false;

        bool m_isMovingLeft = false;
        bool m_moveDown = false;

        int m_initX = 0;
        int m_initY = 4;
        int m_ticks = 0;

        sf::Sound m_stepSounds[4];
        sf::Sound m_invaderKilledSound;
    };