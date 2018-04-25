#pragma once

#include "scenenode.hpp"

class Entity: public SceneNode
{
public:
    sf::Vector2f getVelocity() const;
    void setVelocity(float vx, float vy);
    void setVelocity(const sf::Vector2f &velocity);

private:
    virtual void updateCurrent(sf::Time frameTime);

private:
    sf::Vector2f mVelocity;
};
