#pragma once
#include <iostream>
#include<ctime>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include <stack>
#include<map>
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

enum movement_states{IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class MovementComponent
{
private:
	Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;
	Vector2f velocity;
	//Initializers functions

public:
	MovementComponent(Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
	const Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;
	const bool getState(const short unsigned state) const;

	//Functions
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

