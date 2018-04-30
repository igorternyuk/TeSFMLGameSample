#include "entity.hpp"
#include <iostream>

sf::Vector2f Entity::getVelocity() const
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

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

void Entity::accelerate(const sf::Vector2f &velocity)
{
    mVelocity += velocity;
}

void Entity::updateCurrent(sf::Time frameTime)
{
    std::cout << "Moving entity vel.y = " << mVelocity.y << std::endl;
    move(mVelocity * frameTime.asSeconds());
}
