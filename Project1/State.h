#ifndef STATE_H
#define STATE_H

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

using namespace sf;

class State
{
private:

protected:
	std::stack<State*> *states;
	RenderWindow* window;
	std::vector<Texture*> texture;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

public:
	State(RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	void pauseState();
	void unpauseState();
	void endState();

	virtual void updateMousePosition();
	virtual void updateEvent(Event input) = 0;
	virtual void updateKeytime(const float& dt);
	virtual void updateKeybinds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};

#endif // !STATE_H