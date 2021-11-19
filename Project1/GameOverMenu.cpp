#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(RenderWindow* window, Font& font)
	: font(font)
{
	//init background
	this->background.setSize(Vector2f(
		static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y)));
	this->background.setFillColor(Color(20, 20, 20, 100));

	//init container
	this->container.setSize(Vector2f(
		static_cast<float>(window->getSize().x) / 4.0f,
		static_cast<float>(window->getSize().y) - 60.0f));
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(Vector2f(static_cast<float>(
		window->getSize().x) / 2.0f - this->container.getSize().x / 2.0f,
		30.0f));

	//init text
	this->MenuText.setFont(font);
	this->MenuText.setFillColor(Color(255, 255, 255, 200));
	this->MenuText.setCharacterSize(50);
	this->MenuText.setString("Game Over");
	this->MenuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.0f - this->MenuText.getGlobalBounds().width / 2.0f,
		this->container.getPosition().y + 20);
}

GameOverMenu::~GameOverMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& GameOverMenu::getButtons()
{
	return this->buttons;
}

const bool GameOverMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameOverMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.0f;
	float height = 50.0f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.0f - width / 2.0f;
	this->buttons[key] = new Button(x, y, width, height,
		&this->font, text,
		Color(70, 70, 70, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

void GameOverMenu::update(const Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void GameOverMenu::render(RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target->draw(this->MenuText);
}

