#pragma once

#include "entity.hpp"
#include "resourceindentifiers.hpp"
#include <SFML/Graphics/Sprite.hpp>

class Aircraft: public Entity
{
public:
    enum class Type
    {
        Eagle,
        Raptor,
        Falcon
    };
    explicit Aircraft(Type type, const TextureManager& textures);

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    Type mType;
    sf::Sprite mSprite;
};
