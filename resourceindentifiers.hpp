#pragma once

// Forward declaration of SFML classes
namespace sf
{
    class Texture;
}

enum class TextureID
{
    Desert,
    Eagle,
    Raptor,
    Falcon
};

//Forward declaration of template class ResourceManager
template<class Resource, class Indentifier>
class ResourceManager;

using TextureManager = ResourceManager<sf::Texture, TextureID>;
