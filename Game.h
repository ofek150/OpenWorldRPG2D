#pragma once
#include "MainMenuState.h"

class Game
{
	private:
		//Variables
		RenderWindow* window;
		Event sfEvent;
		vector<VideoMode> videoModes; 
		ContextSettings windowSettings;
		bool fullscreen;

		Clock  dtClock;
		float dt;

		stack<State*> states;

		map<string, int> supportedKeys;


		//Initialization
		void initVariables();
		void initWindow();
		void initKeys();
		void initStates();

	public:

		//Constructors / Destructors
		Game();
		virtual ~Game();

		//Accessors
		const bool getWindowisOpen() const;


		//Functions

		//Regular
		void endApplication();

		//Update
		void updateDt();
		void updateSFMLEvents();

		void update();
		//Render
		void render();

		//Core
		void runGame();

};