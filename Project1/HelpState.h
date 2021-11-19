#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "MainMenuState.h"

class HelpState : public State
{
private:
	RectangleShape background;
	Font font;
	Texture texture;

	std::map<std::string, Button*> buttons;

	// functions
	void initFonts();
	void initButtons();

public:
	HelpState(RenderWindow* window, std::stack<State*>* states);
	virtual ~HelpState();

	void endState();

	void updateEvent(Event input);
	void updateKeybinds(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButton(RenderTarget* target = NULL);
	void render(RenderTarget* target = NULL);
};

