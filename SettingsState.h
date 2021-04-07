#pragma once
#include "State.h"
#include "Button.h"

class SettingsState :
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
	//Constructors / Destructors
	SettingsState(RenderWindow* _window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~SettingsState();

//Accessors

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(RenderTarget& target);
	void render(RenderTarget* target = nullptr);
};

