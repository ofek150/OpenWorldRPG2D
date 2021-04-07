#include "Player.h"


//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
}


//Constructors / Destructors
Player::Player(float x, float y, Texture& texture_sheet)
{
	initVariables();
	setPosition(x, y);
	//sprite.setScale(1f, 1.5f);

	createHitboxComponent(sprite, 10.f, 4.f, 44.f, 58.f);
	createMovementComponent(350.f, 25.f, 15.f);
	createAnimationComponent(texture_sheet);

	animationComponent->addAnimation("IDLE", 6.f, 0, 0, 8, 0, 64, 64);
	animationComponent->addAnimation("WALK_LEFT", 6.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 6.f, 8, 1, 11, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 6.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_DOWN", 6.f, 12, 1, 15, 1, 64, 64);
}

Player::~Player()
{

}

void Player::updateAttack(const float& dt)
{

}

void Player::updateAnimation(const float& dt)
{
	if (movementComponent->getState(IDLE))
	{
		animationComponent->play("IDLE", dt);
	}
	else if (movementComponent->getState(MOVING_LEFT))
	{
		animationComponent->play("WALK_LEFT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	}
	else if (movementComponent->getState(MOVING_RIGHT))
	{
		animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	}
	else if (movementComponent->getState(MOVING_UP))
	{
		animationComponent->play("WALK_UP", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	}
	else if (movementComponent->getState(MOVING_DOWN))
	{
		animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	movementComponent->update(dt);
	updateAnimation(dt);

	hitboxComponent->update();
}

