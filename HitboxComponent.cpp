#include "HitboxComponent.h"


//Constructors / Des
HitboxComponent::HitboxComponent(Sprite& sprite, 
	float offset_x, float offset_y, 
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	hitbox.setSize(Vector2f(width, height));
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineThickness(1.f);
	hitbox.setOutlineColor(Color::Green);
}

HitboxComponent::~HitboxComponent()
{

}

bool HitboxComponent::checkIntersect(const FloatRect& frect)
{
	return hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(RenderTarget& target)
{
	target.draw(hitbox);
}
