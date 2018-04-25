#pragma once

#include "resourceindentifiers.hpp"
#include "resourcemanager.hpp"
#include "scenenode.hpp"
#include "aircraft.hpp"
#include "spritenode.hpp"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

namespace sf
{
    class RenderWindow;
}

class World: private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time frameTime);
    void draw();

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer
    {
        Background,
        Air,
        LayerCount
    };

private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureManager mTextureManager;
    SceneNode mSceneGraph; //root
    std::array<SceneNode*, LayerCount> mSceneLayers;
    sf::IntRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Aircraft* mPlayerAircraft;
};
