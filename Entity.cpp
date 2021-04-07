#include "Entity.h"


void Entity::initVariables()
{
	hitboxComponent = nullptr;
	movementComponent = nullptr;
	animationComponent = nullptr;
}

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete hitboxComponent;
	delete movementComponent;
	delete animationComponent;
}

//Component functions
void Entity::setTexture(Texture& texture)
{
	sprite.setTexture(texture);
	//REMOVE LATER - MAKES THE ENTITY BIGGER
	sprite.setScale(Vector2f(4.f, 4.f));
}

void Entity::createHitboxComponent(Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(Texture& texture_sheet)
{
	animationComponent = new AnimationComponent(sprite, texture_sheet);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}
void Entity::move( const float dir_x, const float dir_y, const float& dt)
{
	if (movementComponent)
	{
		movementComponent->move(dir_x, dir_y, dt); //Sets velocity
	}
}

void Entity::update(const float& dt)
{

}

void Entity::render(RenderTarget& target)
{
	target.draw(sprite);

	if (hitboxComponent)
	{
		hitboxComponent->render(target);
	}
}
