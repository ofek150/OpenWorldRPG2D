#pragma once
#include "Player.h"

class State
{
private:
protected:
	stack<State*>* states;
	RenderWindow* window;
	map<string, int>* supportedKeys;
	map<string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	//Mouse positions
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	//Resources
	map<string, Texture> textures;

	//Initiallizer functions
	virtual void initKeybinds() = 0;

public:
	State(RenderWindow* _window, map<string,int>* supportedKeys, stack<State*>* states);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeytime();

	//Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
};