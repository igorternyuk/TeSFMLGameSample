#include "entity.hpp"

sf::Vector2f Entity::velocity() const
{
    return mVelocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

void Entity::setVelocity(const sf::Vector2f &velocity)
{
    mVelocity = velocity;
}

void Entity::updateCurrent(sf::Time frameTime)
{
    move(mVelocity * frameTime.asSeconds());
}
