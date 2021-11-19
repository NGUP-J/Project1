#include "HelpState.h"

void HelpState::initFonts()
{
	if (!this->font.loadFromFile("resource/fonts/arcade.TTF"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void HelpState::initButtons()
{
	this->buttons["BACK_STATE"] = new Button(375, 650, 250, 70,
		&this->font, "BACK",
		Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

HelpState::HelpState(RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->initFonts();
	this->initButtons();

	this->texture.loadFromFile("./resource/img/si/Backgroundhelpstate.png");

	this->background.setSize(Vector2f(window->getSize()));
	this->background.setTexture(&this->texture);
}

HelpState::~HelpState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HelpState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["BACK_STATE"]->isPressed())
	{
		this->states->push(new MainMenuState(this->window, this->states));
	}
}

void HelpState::endState()
{
	std::cout << "Ending MainMenuState! " << "\n";
}

void HelpState::updateEvent(Event input)
{
}

void HelpState::updateKeybinds(const float& dt)
{
}

void HelpState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeytime(dt);
	this->updateButtons();
}

void HelpState::renderButton(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void HelpState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);

	this->renderButton(target);
}
