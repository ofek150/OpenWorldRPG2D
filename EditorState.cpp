#include "EditorState.h"

//Constructors & Destructors
EditorState::EditorState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	cout << "Initializing Editor state!" << "\n";
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

//Initializer functions
void EditorState::initKeybinds()
{
	ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initButtons()
{
	int window_width = window->getSize().x;
	int window_height = window->getSize().y;

}

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!gameFont.loadFromFile("Resources/Fonts/Montserrat-Regular.ttf"))
	{
		throw("ERROR::EDITORSTATE COULD NOT LOAD FONT!");
	}
}


void EditorState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(keybinds.at("CLOSE"))))
	{
		endState();
	}
}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void EditorState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	updateButtons();
}

void EditorState::renderButtons(RenderTarget& target)
{
	//gamestate_btn->render(target);
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	renderButtons(*target);

	//REMOVE LATER!
	Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
	mouseText.setFont(gameFont);
	mouseText.setFillColor(Color::Black);
	mouseText.setCharacterSize(12);

	stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
