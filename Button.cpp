#include "Button.h"

Button::Button(float x, float y, float width, float height, Font* font, string text, unsigned character_size,
	Color text_idle_color, Color text_hover_color, Color text_active_color,
	Color idle_color, Color hover_color, Color active_color)
{
	buttonState = BTN_IDLE;

	shape.setPosition(x, y);
	shape.setSize(Vector2f(width, height));
	shape.setFillColor(idle_color);

	this->font = font;
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(Color::White);
	this->text.setOutlineColor(Color(0, 40, 48, 255));
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width  / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;
}

Button::~Button()
{

}

const bool Button::isPressed() const
{
	if (buttonState == BTN_ACTIVE)
	{
		cout << "Button pressed!"<< "\n";
		return true;
	}
	else
	{
		return false;
	}
}


//Functions
void Button::update(const Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	buttonState = BTN_IDLE;
	//Hover
	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonState = BTN_HOVER;
		//Pressed
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			buttonState = BTN_ACTIVE;
		}
	}
	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		break;
	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		break;
	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		break;
	default:
		shape.setFillColor(Color::Red);
		text.setFillColor(Color::Blue);
		break;
	}
}

void Button::render(RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}
