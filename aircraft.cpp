#include "aircraft.hpp"
#include "resourcemanager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

TextureID getTextureID(Aircraft::Type type)
{
    switch(type)
    {
        case Aircraft::Type::Eagle:
            return TextureID::Eagle;
        case Aircraft::Type::Raptor:
            return TextureID::Raptor;
        case Aircraft::Type::Falcon:
            return TextureID::Falcon;
    };
    return TextureID::Raptor;
}

Aircraft::Aircraft(Aircraft::Type type, const TextureManager &textures):
    mType(type), mSprite(textures.get(getTextureID(type)))
{
    auto spriteBoundingRect = mSprite.getLocalBounds();
    mSprite.setOrigin(0.5f * spriteBoundingRect.width,
                      0.5f * spriteBoundingRect.height);
}

void Aircraft::drawCurrent(sf::RenderTarget &target,
                           sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
