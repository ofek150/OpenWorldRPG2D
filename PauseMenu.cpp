#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font)
	: font(font)
{
	//Init background
	background.setSize(
		Vector2f(
			static_cast<float>(window.getSize().x),
			static_cast<float>(window.getSize().y)
		)
	);
	background.setFillColor(Color(20, 20, 20, 100));

	//Init container
	container.setSize(
		Vector2f(
			static_cast<float>(window.getSize().x / 4.f),
			static_cast<float>(window.getSize().y)- 100.f
		)
	);
	container.setFillColor(Color(20, 20, 20, 200));
	container.setPosition(
		static_cast<float>(window.getSize().x / 2.f - container.getSize().x / 2.f),
		30.f
	);

	//Init text
	menuText.setFont(font);
	menuText.setFillColor(Color(255, 255, 255, 200));
	menuText.setCharacterSize(60);
	menuText.setString("PAUSED");
	menuText.setPosition(
		container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f, 
		container.getPosition().y + 40.f
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, Button*>& PauseMenu::getButtons()
{
	return buttons;
}

const bool PauseMenu::isButtonPressed(const string key)
{
	return buttons[key]->isPressed();
}

void PauseMenu::addButton(const string key, float y, const string text)
{
	float width = 200.f;
	float height = 50.f;
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	buttons[key] = new Button(
		x, y, width, height, 
		&font, text, 40,
		Color(62, 216, 247, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
	cout << "Added button: " << key << "\n";
}

void PauseMenu::update(Vector2f& mousePos)
{
	for (auto i : buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : buttons)
	{
		i.second->render(target);
	}
	
	target.draw(menuText);
}
