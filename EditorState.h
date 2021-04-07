#pragma once
#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
private:

	//Variables
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
	EditorState(RenderWindow* _window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~EditorState();

	//Functions

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(RenderTarget& target);
	void render(RenderTarget* target = nullptr);
};

