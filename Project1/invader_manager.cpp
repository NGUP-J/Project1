#include "invader_manager.h"
#include <iostream>
#include "Game.h"
#include "resource_holder.h"


    namespace {
        const int MAX_INVADERS = 55;
    }

    InvaderManager::InvaderManager()
        : m_stepGap(seconds(1.0f))
        , m_invaderRenderer(12, 8, Invader::WIDTH, Invader::HEIGHT,
            ResourceHolder::get().textures.get("si/invaders"))
    {

        Invader::Type types[] = { Invader::Type::Squid, Invader::Type::Crab,
                                 Invader::Type::Crab, Invader::Type::Octopus,
                                 Invader::Type::Octopus };
        const int GAP = 10;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 11; x++) {
                float invaderX = x * Invader::WIDTH + (GAP * x * 3) + Invader::WIDTH;
                float invaderY = y * Invader::HEIGHT + (GAP * y) + Invader::HEIGHT * 4;
                m_invaders.emplace_back(Vector2f{ invaderX, invaderY }, types[y]);
            }
        }

        // load sounds
        for (int i = 0; i < 4; i++) 
        {
            m_stepSounds[i].setBuffer(ResourceHolder::get().soundBuffers.get(
                "si/fastinvader" + std::to_string(i + 1)));
            m_stepSounds[i].setVolume(10);
        }
        
        m_invaderKilledSound.setBuffer(ResourceHolder::get().soundBuffers.get("si/invaderkilled"));
        m_invaderKilledSound.setVolume(20);
    }

    void InvaderManager::tryStepInvaders()
    {

        if (m_stepTimer.getElapsedTime() > m_stepGap) {
            m_invaderRenderer.nextFrame();
            if (m_stepGap <= seconds(1.0) && m_stepGap >= seconds(0.05))
            {
                m_stepGap = m_stepGap - seconds(0.0005f);
            }
            bool moveDown = false;
            float step = m_isMovingLeft ? -10.0f : 10.0f;
            if (m_moveDown) {
                step *= -1;
            }
            m_stepSounds[m_ticks++ % 4].play();

            for (auto& invader : m_invaders) {
                if (!invader.isAlive())
                    continue;
                invader.move(step, 0.0f);
                if (m_moveDown == true) {
                    invader.move(0, Invader::HEIGHT / 2.0f);
                }
                else if (moveDown == false) {
                    moveDown = testInvaderPosition(invader);
                }
            }

            if (m_moveDown == true)
                m_isMovingLeft = !m_isMovingLeft;
            m_moveDown = moveDown;
            m_stepTimer.restart();
        }
    }

    void InvaderManager::drawInvaders(RenderTarget* target)
    {
        for (auto& invader : m_invaders) {
            if (!invader.isAlive())
                continue;
            m_invaderRenderer.renderEntity(target, (int)invader.getType(),
                invader.getPosition());
        }
    }

    CollisionResult
        InvaderManager::tryCollideWithProjectiles(std::vector<Bullet>& bullets)
    {
        CollisionResult result;
        std::vector<sf::Vector2f> collisionPoints;
        for (auto& Bullet : bullets) 
        {
            for (auto& invader : m_invaders) 
            {
                if (!invader.isAlive() || !Bullet.isActive())
                    continue;
                //this->player->getBullet(k).getGlobalBounds().intersects(this->ufo->getGlobalBounds())
                if (Bullet.getBox().intersects(invader.getBox())) {
                    m_aliveInvaders--;
                    invader.onCollide();
                    Bullet.onCollide();
                    m_invaderKilledSound.play();
                    if (m_aliveInvaders == 0)
                    {
                        m_hasAllInvadersBeenAdded = false;
                    }
                    result.second.emplace_back(invader.getPosition());
                    result.first += ((int)invader.getType() + 1) * 10;
                    updateStepDelay();
                }
            }
        }
        return result;
    }

    sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(Random<>& random)
    {
        if (m_aliveInvaders == 0)
            return { -1, -1 };
        while (true) {
            auto invaderColumn = random.getIntInRange(0, 10);
            for (int y = 4; y >= 0; y--) {
                int index = y * 11 + invaderColumn;
                auto& invader = m_invaders.at(index);
                if (invader.isAlive()) {
                    return {
                            invader.getPosition().x + Invader::WIDTH / 2,
                            invader.getPosition().y + Invader::HEIGHT + 5 };
                }
            }
        }
    }

    int InvaderManager::getAliveInvadersCount() const
    {
        return m_aliveInvaders;
    }

    void InvaderManager::initAddInvader()
    {
        static sf::Clock delay;
        if (delay.getElapsedTime().asSeconds() > 0.02) 
        {
            m_invaders.at(m_initY * 11 + m_initX).makeAlive();
            m_aliveInvaders++;
            m_initX++;
            if (m_initX == 11) {
                m_initX = 0;
                m_initY--;
            }
            delay.restart();
        }

        if (m_aliveInvaders == MAX_INVADERS) 
        {
            m_hasAllInvadersBeenAdded = true;
            m_initX = 0;
            m_initY = 4;
            updateStepDelay();
        }
    }

    bool InvaderManager::areInvadersAlive() const
    {
        return m_hasAllInvadersBeenAdded;
    }

    void InvaderManager::updateStepDelay()
    {
        m_stepGap = sf::seconds((float)m_aliveInvaders / 90.0f);
    }

    bool InvaderManager::testInvaderPosition(const Invader& invader) const
    {
        if (invader.getPosition().y > 800) {
            //this->player->gameover();
            //this->game->setGameIsOver();
        }
        return (invader.getPosition().x < 15 && m_isMovingLeft) || // Check invader left
            (invader.getPosition().x + Invader::WIDTH > 1000 - 15 &&
                !m_isMovingLeft); // Check invader right
    }

    Invader& InvaderManager::getInvader(unsigned index)
    {
        if (index < 0 || index > this->m_invaders.size())
            throw"OUT OF BOUNDS! InvaderManager:GETINVADER!";

        return this->m_invaders[index];
    }