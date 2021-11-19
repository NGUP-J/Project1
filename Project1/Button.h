#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace sf;

enum button_state{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonState;

	//bool pressed;
	//bool hover;

	RectangleShape shape;
	Font* font;
	Text text;
	std::string string;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

public:
	Button(float x, float y, float width, float height,
		Font* font, std::string text, 
		Color idleColor, Color hoverColor, Color activeColor);
	virtual ~Button();

	//Accessors
	const bool isPressed() const;

	// Functions
	void update(const Vector2f& mousePos);
	void render(RenderTarget* target);
};

