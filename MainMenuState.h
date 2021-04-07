#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Button.h"

class MainMenuState :
	public State
{
private:
	
	//Variables
	Texture backgroundTexture;
	RectangleShape background;
	Font gameFont;

	map<string, Button*>buttons;

	//Button* gamestate_btn;
	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(RenderWindow* _window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(RenderTarget& target);
	void render(RenderTarget* target = nullptr);
};

