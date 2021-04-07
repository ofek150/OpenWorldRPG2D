#include "State.h"

State::State(RenderWindow* _window, map<string, int>* supportedKeys, stack<State*>* states)
{
	window = _window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	quit = false;
	paused = false;
	keytime = 0.f;
	keytimeMax = 10.f;
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeytime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return true;
	}

	return false;
}

void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

void State::updateMousePositions()
{
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void State::updateKeytime(const float& dt)
{
	if (keytime < keytimeMax)
	{
		keytime += 40.f * dt;
	}
}

