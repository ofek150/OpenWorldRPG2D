#include "Game.h"


//Static functions

//Initializer functions

void Game::initVariables()
{
	window = nullptr;
	fullscreen = false;
	dt = 0.f;
}

void Game::initWindow()
{
	ifstream ifs("Config/window.ini");
	videoModes = VideoMode::getFullscreenModes();


	string title = "None";
	VideoMode window_bounds = VideoMode::getDesktopMode();
	fullscreen = false;

	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;


	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	windowSettings.antialiasingLevel = antialiasing_level;
	if (fullscreen)
	{
		window = new RenderWindow(window_bounds, title, Style::Fullscreen, windowSettings);
	}
	else
	{
		window = new RenderWindow(window_bounds, title, Style::Titlebar | Style::Close, windowSettings);
	}
	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			supportedKeys[key] = key_value;
		}
	}
	ifs.close();

}

void Game::initStates()
{
	states.push(new MainMenuState(window, &supportedKeys, &states));
}
//Constructors/Destructors
Game::Game()
{
	initVariables();
	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
	delete window;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

//Accessors
const bool Game::getWindowisOpen() const
{
	return window->isOpen();
}


//Functions

//Core
void Game::runGame()
{
	while (getWindowisOpen())
	{
		//Update delta time
		updateDt();

		//Update
		update();

		//Render
		render();
	}
}

//Regular functions
void Game::endApplication()
{

	cout << "Ending Application!" << "\n";
}

//Update
void Game::updateDt()
{
	//Updates the dt variable with the time it takes to update and render one frame.
	dt = dtClock.restart().asSeconds();

	//system("cls");
	//cout << dt << "\n";
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::update()
{
	updateSFMLEvents();
	if (!states.empty())
	{
		states.top()->update(dt);

		if (states.top()->getQuit())
		{
			states.top()->endState();
			delete this->states.top();
			states.pop();
		}
	}
	//Aplication end
	else
	{
		endApplication();
		window->close();
	}
}

//Render
void Game::render()
{
	// Renders the game objects

	//Clear Old frame
	window->clear(Color::White);

	if (!states.empty())
	{
		states.top()->render();
	}

	window->display();
}