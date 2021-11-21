#include "MainMenuState.h"

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("./resource/fonts/arcade.TTF"))
	{
		throw("ERROR::GAMESTATE::COULD NOT LOAD FONT");
	}

}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(375, 350, 250, 70,
		&this->font, "START GAME",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["HIGHSCORE_STATE"] = new Button(375, 450, 250, 70,
		&this->font, "HIGHSCORE",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["HELP_STATE"] = new Button(375, 550, 250, 70,
		&this->font, "HELP!",
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(375, 650, 250, 70,
		&this->font, "QUIT",
		Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

MainMenuState::MainMenuState(RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->initFonts();
	this->initButtons();

	this->texture.loadFromFile("resource/img/si/MainMenuBackground.png");

	this->background.setSize(Vector2f(window->getSize()));
	this->background.setTexture(&this->texture);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateEvent(Event input)
{

}

void MainMenuState::updateKeybinds(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	// uppdate all the button in the state and handles their functionlaity.
	
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//start game
	if (this->buttons["GAME_STATE"]->isPressed() && this->getKeytime())
	{
		this->states->push(new GameState(this->window, this->states));
	}

	//highscore
	if (this->buttons["HIGHSCORE_STATE"]->isPressed() && this->getKeytime())
	{
		this->states->push(new HighScoreState(this->window, this->states));
	}

	//Help!
	if (this->buttons["HELP_STATE"]->isPressed() && this->getKeytime())
	{
		this->states->push(new HelpState(this->window, this->states));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed() && this->getKeytime())
	{
		this->window->close();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeybinds(dt);
	this->updateKeytime(dt);
	this->updateButtons();
}

void MainMenuState::renderButton(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);

	this->renderButton(target);
}
