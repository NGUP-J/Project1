#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"
#include "HighScoreState.h"
#include "HelpState.h"
#include "Textbox.h"

class MainMenuState : public State
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
	MainMenuState(RenderWindow* window, std::stack<State*>* states);
	virtual ~MainMenuState();

	// functions
	void updateEvent(Event input);
	void updateKeybinds(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButton(RenderTarget* target = NULL);
	void render(RenderTarget* target = NULL);
};

