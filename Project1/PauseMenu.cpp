#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow* window,Font& font)
	: font(font)
{
	//init background
	this->background.setSize(Vector2f(
		static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y)));
	this->background.setFillColor(Color(20, 20, 20, 100));

	//init container
	this->container.setSize({ 300 ,300 });
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(Vector2f(static_cast<float>(
		window->getSize().x) / 2.0f - this->container.getSize().x / 2.0f,
		100.0f));

	//init text
	this->MenuText.setFont(font);
	this->MenuText.setFillColor(Color(255, 255, 255, 200));
	this->MenuText.setCharacterSize(60);
	this->MenuText.setString("PAUSED");
	this->MenuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->MenuText.getGlobalBounds().width / 2.0f , 
		this->container.getPosition().y + 20);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.0f;
	float height = 50.0f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.0f - width / 2.0f;
	this->buttons[key] = new Button(x, y, width, height,
		&this->font, text,
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

void PauseMenu::update(const Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target->draw(this->MenuText);
}
