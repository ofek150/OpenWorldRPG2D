#pragma once

#include<iostream>
#include<string>
#include<map>
#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		Sprite& sprite;

		Texture& textureSheet;
		float animationTimer;
		float timer;
		bool done;
		int width;
		int height;
		IntRect startRect;
		IntRect currentRect;
		IntRect endRect;

		Animation(Sprite& sprite, Texture& texture_sheet, 
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), 
			animationTimer(animation_timer), timer(0.f), done(false), 
			width(width), height(height)
		{
			startRect = IntRect(start_frame_x * width, start_frame_y * height, width, height);
			currentRect = startRect;
			endRect = IntRect(frames_x * width, frames_y * height, width, height);
			
			sprite.setTexture(textureSheet, true);
			sprite.setTextureRect(startRect);
		}


		//Accessor
		const bool& isDone()
		{
			return done;
		}

		//Functions

		const bool& play(const float& dt)
		{
			//Update timer
			done = false;
			timer += 100.f * dt;
			if (timer >= animationTimer)
			{
				//Reset timer
				timer = 0.f;

				//Animate
				if (endRect != currentRect)
				{
					currentRect.left += width;
				}
				//Reset
				else
				{
					currentRect.left = startRect.left;
					done = true;
				}
				sprite.setTextureRect(currentRect);
			}

			return done;
		}

		bool play(const float& dt, float mod_percent)
		{
			//Update timer

			if (mod_percent < 0.5f)
			{
				mod_percent = 0.5f;
			}

			done = false;
			timer += mod_percent * 100.f * dt;

			if (timer >= animationTimer)
			{
				//Reset timer
				timer = 0.f;

				//Animate
				if (endRect != currentRect)
				{
					currentRect.left += width;
				}
				//Reset
				else
				{
					currentRect.left = startRect.left;
					done = true;

				}

				sprite.setTextureRect(currentRect);

			}
			return done;
		}

		void reset()
		{
			timer = animationTimer;
			currentRect = startRect;
		}
		
	};


	Sprite& sprite;
	Texture& textureSheet;
	map<string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(Sprite& sprite, Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Accessor
	const bool& isDone(string key);

	//Functions
	void addAnimation(const string key, 
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	const bool& play(string key, const float& dt, const bool priority = false);
	const bool& play(string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

