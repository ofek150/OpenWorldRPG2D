#include "AnimationComponent.h"


//Constructors / Destructors
AnimationComponent::AnimationComponent(Sprite& sprite, Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	animations[key] = new Animation(
		sprite, textureSheet, animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height

	);
}

//Accessor
const bool& AnimationComponent::isDone(string key)
{
	return animations[key]->isDone();
}

//Functions 

const bool& AnimationComponent::play(string key, const float& dt, const bool priority)
{
	if (priority)
	{
		priorityAnimation = animations[key];
	}
	if (priorityAnimation) //If there is a priority animation
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == nullptr)
				{
					lastAnimation = animations[key];
				}
				else
				{
					lastAnimation->reset();
					lastAnimation = animations[key];
				}
			}

			//If the priority animation is done remove it
			if (animations[key]->play(dt))
			{
				priorityAnimation = nullptr;
			}
		}
	}
	else //Play animation if no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == nullptr)
			{
				lastAnimation = animations[key];
			}
			else
			{
				lastAnimation->reset();
				lastAnimation = animations[key];
			}
		}

		animations[key]->play(dt);
	}

	return animations[key]->isDone();
}

const bool& AnimationComponent::play(string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (priorityAnimation) //If there is a priority animation
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == nullptr)
				{
					lastAnimation = animations[key];
				}
				else
				{
					lastAnimation->reset();
					lastAnimation = animations[key];
				}
			}

			//If the priority animation is done remove it
			if (animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				priorityAnimation = nullptr;
			}
		}
	}
	else //Play animation if no other priority animation is set
	{
		if (priority)//If this is a priority animation, set it.
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == nullptr)
			{
				lastAnimation = animations[key];
			}
			else
			{
				lastAnimation->reset();
				lastAnimation = animations[key];
			}
		}
		animations[key]->play(dt, abs(modifier / modifier_max));
	}
	return animations[key]->isDone();
}