#include "world.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

World::World(sf::RenderWindow & window):
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mWorldBounds(0.0f,0.0f,mWorldView.getSize().x, 2000.0f),
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
    auto leaderPosition = mPlayerAircraft->getPosition();
    auto leaderVelocity = mPlayerAircraft->getVelocity();
    std::cout << "leaderVelocity = " << leaderVelocity.y << std::endl;

    if(leaderPosition.x <= mWorldBounds.left + 150.0f
       || leaderPosition.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
    {
        leaderVelocity.x = -leaderVelocity.x;
        mPlayerAircraft->setVelocity(leaderVelocity);
    }

    //Apply movements
    mSceneGraph.update(frameTime);
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
