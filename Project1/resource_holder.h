#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


#include "resource_manager.h"


    class ResourceHolder {
    public:
        static ResourceHolder& get();

        ResourceManager<sf::Font> fonts;
        ResourceManager<sf::Texture> textures;
        ResourceManager<sf::SoundBuffer> soundBuffers;

    private:
        ResourceHolder();
    };