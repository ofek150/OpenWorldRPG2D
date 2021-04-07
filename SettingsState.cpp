#include "SettingsState.h"

//Constructors / Destructors
SettingsState::SettingsState(RenderWindow* _window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Initializer functions
void SettingsState::initKeybinds()
{
	ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		string key = "";
		string key2 = "";
		while (ifs >> key >> key2)
		{
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void SettingsState::initButtons()
{
	int window_width = window->getSize().x;
	int window_height = window->getSize().y;
	int centerX = window_width / 2.f - 125.f;
	int centerY = window_height / 2.f - 40.f;
	buttons["EXIT_STATE"] = new Button(centerX, centerY + 360.f, 250.f, 50.f,
		&gameFont, "Quit", 40,
		Color(62, 216, 247, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
}

void SettingsState::initVariables()
{

}

void SettingsState::initBackground()
{
	background.setSize(
		Vector2f
		(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);
	if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/Background.png"))
	{
		throw "ERROR::MAINMAINSTATE::FAILED_TO_LOAD_BACKGROUND_TEXUTRE";
	}
	background.setTexture(&backgroundTexture);

}

void SettingsState::initFonts()
{
	if (!gameFont.loadFromFile("Resources/Fonts/Montserrat-Regular.ttf"))
	{
		throw("ERROR:: MAINMENUSTATE COULD NOT LOAD FONT!");
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{

}

void SettingsState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}

	//Quit the game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}
}

void SettingsState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void SettingsState::renderButtons(RenderTarget& target)
{
	//gamestate_btn->render(target);
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render(RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}
	target->draw(background);

	renderButtons(*target);

	Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
	mouseText.setFont(gameFont);
	mouseText.setCharacterSize(12);

	//REMOVE LATER!
	stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}