#pragma once
#include "State.h"
#include "PauseMenu.h"
class GameState:
	public State
{

private:
	PauseMenu* pmenu;

	Font gameFont;

	Player* player;
	Sprite gameBackground;


	//Initializer functions
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
public:
	GameState(RenderWindow* _window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~GameState();

	//Functions

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(RenderTarget* target = nullptr);
};

