#pragma once

#include <iostream>
#include<ctime>
#include<cstdlib>
#include<sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:

	short unsigned buttonState;

	RectangleShape shape;
	Font* font;
	Text text;

	Color textIdleColor;
	Color textHoverColor;
	Color textActiveColor;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

public:
	Button(float x, float y, float width, float height, Font* font, string text, unsigned character_size,
		Color text_idle_color, Color text_hover_color, Color text_active_color,
		Color idle_color, Color hover_color, Color active_color);
	~Button();

	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const Vector2f& mousePos);
	void render(RenderTarget& target);
};

