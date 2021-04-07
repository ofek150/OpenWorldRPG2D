#include "MovementComponent.h"

MovementComponent::MovementComponent(Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), 
	acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{
}

//Accessors
const Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (velocity.x == 0.f && velocity.y == 0.f)
		{
			return true;
		}
		break;

	case MOVING:

		if (velocity.x != 0.f || velocity.y != 0.f)
		{
			return true;
		}

		break;

	case MOVING_LEFT:

		if (velocity.x < 0.f)
		{
			return true;
		}

		break;

	case MOVING_RIGHT:

		if (velocity.x > 0.f)
		{
			return true;
		}

		break;

	case MOVING_UP:

		if (velocity.y > 0.f)
		{
			return true;
		}

		break;

	case MOVING_DOWN:

		if (velocity.y < 0.f)
		{
			return true;
		}

		break;
	}
	return false;
}



//Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Accelerating the sprite until it reaches the max velocity*/
	velocity.x += acceleration * dir_x;
	velocity.y += acceleration * dir_y;

}
void MovementComponent::update(const float& dt)
{
	/*Decelerates the sprite and controls the maximum velocity.
	Moves the sprite.
	*/
	if (velocity.x > 0.f) //Check positive x
	{
		//Max velocity check x positive
		if (velocity.x > maxVelocity)
		{
			velocity.x = maxVelocity;
		}

		//Deceleration x positive
		velocity.x -= deceleration;
		if (velocity.x < 0.f)
		{
			velocity.x = 0.f;
		}
	}
	else if (velocity.x < 0.f) //Check negative x
	{
		//Max velocity check x negative
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity;
		}

		//Deceleration x negative
		velocity.x += deceleration;
		if (velocity.x > 0.f)
		{
			velocity.x = 0.f;
		}
	}

	if (velocity.y > 0.f) //Check positive y
	{
		//Max velocity check y positive
		if (velocity.y > maxVelocity)
		{
			velocity.y = maxVelocity;
		}

		//Deceleration y positive
		velocity.y -= deceleration;
		if (velocity.y < 0.f)
		{
			velocity.y = 0.f;
		}
	}
	else if (velocity.y < 0.f) //Check negative y
	{
		//Max velocity check y negative
		if (velocity.y < -maxVelocity)
		{
			velocity.y = -maxVelocity;
		}

		//Deceleration y negative
		velocity.y += deceleration;
		if (velocity.y > 0.f)
		{
			velocity.y = 0.f;
		}
	}
	//Final move
	sprite.move(velocity * dt); //Uses velocity
}
