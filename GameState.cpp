#include "GameState.h"

//Constructors / Destructors
GameState::GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	cout << "Initializing game state!" << "\n";
	initKeybinds();
	initFonts();
	initTextures();

	initPauseMenu();

	initPlayers();
}

GameState::~GameState()
{
	delete pmenu;
	delete player;
}


//Initializer functions
void GameState::initKeybinds()
{
	ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState:: initFonts()
{
	if (!gameFont.loadFromFile("Resources/Fonts/Montserrat-Regular.ttf"))
	{
		throw("ERROR:: MAINMENUSTATE COULD NOT LOAD FONT!");
	}
}

void GameState::initTextures()
{
	if (!textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	if (!textures["GAME_BACKGROUND"].loadFromFile("Resources/Images/Backgrounds/gameBackground.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
	gameBackground.setTexture(textures["GAME_BACKGROUND"]);
}

void GameState::initPauseMenu()
{
	pmenu = new PauseMenu(*window, gameFont);

	pmenu->addButton("EXIT_STATE", 800.f, "Quit");
}

void GameState::initPlayers()
{
	player = new Player(0, 0, textures["PLAYER_SHEET"]);

}


//Functions

void GameState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
	{
		if (!paused)
		{
			pauseState();
		}
		else
		{
			unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (Keyboard::isKeyPressed(Keyboard::Key(keybinds.at("MOVE_LEFT"))))
	{
		player->move(-1.f, 0.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
	{
		player->move(1.f, 0.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(keybinds.at("MOVE_UP"))))
	{
		player->move(0.f, -1.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(keybinds.at("MOVE_DOWN"))))
	{
		player->move(0.f, 1.f, dt);
	}
}

void GameState::updatePauseMenuButtons()
{
	if (pmenu->isButtonPressed("EXIT_STATE") && getKeytime())
	{
		cout << "Ending game state!" << "\n";
		endState();
	}
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateKeytime(dt);
	updateInput(dt);

	if (!paused) //Unpaused update
	{
		updatePlayerInput(dt);

		player->update(dt);
	}
	else //Paused update
	{
		pmenu->update(mousePosView);
		updatePauseMenuButtons();
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}
	target->draw(gameBackground);
	player->render(*target);

	if (paused) //paused menu render
	{
		pmenu->render(*target);
	}
}
