#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>

#include "Button.h"

using namespace sf;

class GameOverMenu
{
	RectangleShape background;
	RectangleShape container;

	Font font;
	Text MenuText;

	std::map<std::string, Button*> buttons;

public:
	GameOverMenu(RenderWindow* window, Font& font);
	virtual ~GameOverMenu();

	std::map<std::string, Button*>& getButtons();

	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const Vector2f& mousePos);
	void render(RenderTarget* target);
};

