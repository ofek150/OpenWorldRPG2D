#pragma once
#include <iostream>
#include<ctime>
#include<cstdlib>
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

class HitboxComponent
{
private:
	Sprite& sprite;
	RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const FloatRect& frect);

	void update();
	void render(RenderTarget& target);
};

