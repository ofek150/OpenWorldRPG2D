#include "MainMenuState.h"


//Constructors & Destructors
MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	cout << "Initializing main menu state!" << "\n";
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

//Initializer functions
void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{
	int window_width = window->getSize().x;
	int window_height = window->getSize().y;
	int x = window_width / 2.f - 125.f;
	buttons["GAME_STATE"] = new Button(
		x, 400.f, 250.f, 50.f
		, &gameFont, "New Game", 40,
		Color(62, 216, 247, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);

	buttons["SETTINGS"] = new Button(x, 500.f, 250.f, 50.f,
		&gameFont, "Settings", 40,
		Color(62, 216, 247, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);

	buttons["EDITOR_STATE"] = new Button(x, 600.f, 250.f, 50.f,
		&gameFont, "Editor", 40,
		Color(62, 216, 247, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);

	buttons["EXIT_STATE"] = new Button(x, 800.f, 250.f, 50.f, 
		&gameFont, "Quit", 40,
		Color(62, 216, 247, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
}

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
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

void MainMenuState::initFonts()
{
	if (!gameFont.loadFromFile("Resources/Fonts/Montserrat-Regular.ttf"))
	{
		throw("ERROR:: MAINMENUSTATE COULD NOT LOAD FONT!");
	}
}

//Functions
void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
	//New game
	if (buttons["GAME_STATE"]->isPressed())
	{
		states->push(new GameState(window, supportedKeys, states));
	}
	//Settings

	//Editor
	if (buttons["EDITOR_STATE"]->isPressed())
	{
		states->push(new EditorState(window, supportedKeys, states));
	}

	//Quit the game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}
}

void MainMenuState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void MainMenuState::renderButtons(RenderTarget& target)
{
	//gamestate_btn->render(target);
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
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