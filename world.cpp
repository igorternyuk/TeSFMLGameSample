#include "world.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

World::World(sf::RenderWindow & window):
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mWorldBounds(0.0f,0.0f,mWorldView.getSize().x, 10000.0f),
    mSpawnPosition(0.5f * mWorldView.getSize().x,
                   mWorldBounds.height - 0.5f * mWorldView.getSize().y),
    mScrollSpeed(-50.0f),
    mPlayerAircraft(nullptr)
{
    loadTextures();
    buildScene();
    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time frameTime)
{
    //Scroll the game world
    mWorldView.move(0.0f, mScrollSpeed * frameTime.asSeconds());
    mPlayerAircraft->setVelocity(0.0f, 0.0f);

    //Here all commands from the queue forwarrd to the screne graph root node
    while(!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), frameTime);
    }

    adaptPlayerVelocity();
    //Apply movements
    mSceneGraph.update(frameTime);
    keepPlayerPositionInsideTheScreenBounds();
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
    mTextureManager.load(TextureID::Desert, "resources/textures/Desert.png");
    mTextureManager.load(TextureID::Raptor, "resources/textures/Raptor.png");
    mTextureManager.load(TextureID::Eagle, "resources/textures/Eagle.png");
    mTextureManager.load(TextureID::Falcon, "resources/textures/Falcon.png");
}

void World::buildScene()
{
    //Initialize scene layers
    for(size_t i{0}; i < LayerCount; ++i)
    {
        auto currLayer = std::make_unique<SceneNode>();
        mSceneLayers[i] = currLayer.get(); //Here we do not transfer the ownership
        mSceneGraph.attachChild(std::move(currLayer));
    }

    sf::Texture& bgTexture = mTextureManager.get(TextureID::Desert);
    sf::IntRect& bgTextureRect(mWorldBounds);
    bgTexture.setRepeated(true); //We compose our background from tiles

    //Here we add the background sprite node
    auto bgSprite = std::make_unique<SpriteNode>(bgTexture, bgTextureRect);
    bgSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(bgSprite));

    //Now we add player's aircraft
    auto leader = std::make_unique<Aircraft>(Aircraft::Type::Eagle, mTextureManager);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.0f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(leader));

    // Add two escorting aircrafts, placed relatively to the main plane
    //Left escort
    auto leftEscort = std::make_unique<Aircraft>(Aircraft::Type::Falcon,
                                                 mTextureManager);
    leftEscort->setPosition(-80.0f, 50.0f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    //Right escort
    auto rightEscort = std::make_unique<Aircraft>(Aircraft::Type::Falcon,
                                                 mTextureManager);
    rightEscort->setPosition(+80.0f, 50.0f);
    mPlayerAircraft->attachChild(std::move(rightEscort));

}

void World::adaptPlayerVelocity()
{
    auto velocity = mPlayerAircraft->getVelocity();
    /*If player aircraft moves diagonally, we will reduce velocity
    (to have the same veloctity when the plane moves only in one direction*/
    if(velocity.x != 0.0f && velocity.y != 0)
    {
        auto coef = float(1.0f /  sqrt(2.0f));
        mPlayerAircraft->setVelocity(coef * velocity);
    }
    mPlayerAircraft->accelerate(0.0f, mScrollSpeed);
}

void World::keepPlayerPositionInsideTheScreenBounds()
{
    auto topLeftViewCorner = mWorldView.getCenter() - 0.5f * mWorldView.getSize();
    sf::FloatRect viewBounds(topLeftViewCorner, mWorldView.getSize());
    auto playerPosition = mPlayerAircraft->getPosition();
    const float borderDistance = 40.0f;
    playerPosition.x = std::max(playerPosition.x, viewBounds.left + borderDistance);
    playerPosition.x = std::min(playerPosition.x,
                                viewBounds.left + viewBounds.width - borderDistance);
    playerPosition.y = std::max(playerPosition.y, viewBounds.top + borderDistance);
    playerPosition.y = std::min(playerPosition.y,
                                viewBounds.top + viewBounds.height -borderDistance);
    mPlayerAircraft->setPosition(playerPosition);
    std::cout << "x = " << mPlayerAircraft->getPosition().x << " y = "
              << mPlayerAircraft->getPosition().y << std::endl;
}

CommandQueue &World::getCommandQueue()
{
    return mCommandQueue;
}
