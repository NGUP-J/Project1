#define _CRT_SECURE_NO_WARNINGS
#include "HighScoreState.h"

void HighScoreState::initFonts()
{
	if (!this->font.loadFromFile("resource/fonts/arcade.TTF"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void HighScoreState::initButtons()
{
	this->buttons["BACK_STATE"] = new Button(375, 650, 250, 70,
		&this->font, "BACK",
		Color(100, 100, 100, 200), Color(150, 150, 150, 255), Color(20, 20, 20, 200));
}

HighScoreState::HighScoreState(RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->initFonts();
	this->initButtons();

	this->texture.loadFromFile("resource/img/si/Background.png");

	this->background.setSize(Vector2f(window->getSize()));
	this->background.setTexture(&this->texture);

	this->background2.setSize({ 600 , 600 });
	this->background2.setPosition({ 200 , 50 });
	this->background2.setFillColor( Color(20, 20, 20, 255));

	text1.setFont(font);
	text1.setString("HIGH SCORE");
	text1.setPosition({ 350 , 80});
	text1.setCharacterSize(60);

	this->fp = fopen("./resource/HighScore.txt", "r");
	float num = 120.0f;
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &temp);
		name[i] = temp;
		fscanf(fp, "%d", &score[i]);
		this->userScore.push_back(make_pair(this->score[i], this->name[i]));
		textscore[i].setString(std::to_string(this->score[i]));
		textname[i].setString(this->name[i]);
		textcount[i].setString(std::to_string(i+1));

		num += 75.0f;
		textscore[i].setPosition({ 600.0f,  num});
		textname[i].setPosition({ 300.0f, num});
		textcount[i].setPosition({ 250.0f, num });

		textscore[i].setFont(font);
		textname[i].setFont(font);
		textcount[i].setFont(font);
		textscore[i].setCharacterSize(42);
		textname[i].setCharacterSize(42);
		textcount[i].setCharacterSize(42);
		

	}

}

HighScoreState::~HighScoreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HighScoreState::updateButtons()
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

void HighScoreState::endState()
{
	std::cout << "Ending MainMenuState! " << "\n";
}

void HighScoreState::updateEvent(Event input)
{
	
}

void HighScoreState::updateKeybinds(const float& dt)
{
}

void HighScoreState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeytime(dt);
	this->updateButtons();
}

void HighScoreState::renderButton(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void HighScoreState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	target->draw(this->background2);
	target->draw(text1);
	for (int i = 0; i < 5; i++)
	{
		target->draw(textname[i]);
		target->draw(textscore[i]);
		target->draw(textcount[i]);
	}

	this->renderButton(target);
}
