#pragma once

#include <iostream>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include <stack>
#include<map>

#include "Button.h";

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

class PauseMenu
{
private:
	Font& font;
	Text menuText;

	RectangleShape background;
	RectangleShape container;

	map<string, Button*> buttons;


public:
	PauseMenu(RenderWindow& window, Font& font);
	virtual ~PauseMenu();

	//Accessor
	map<string, Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const string key);
	void addButton(const string key, float y, const string text);
	void update(Vector2f& mousePos);
	void render(RenderTarget& target);
};

