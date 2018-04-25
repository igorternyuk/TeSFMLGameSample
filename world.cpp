#include "world.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

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

}

void World::draw()
{
    mWindow.setView(mWorldView);
}

/*
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
*/

void World::loadTextures()
{
    mTextures.load(TextureID::Desert, "resources/textures/Desert.png");
    mTextures.load(TextureID::Desert, "resources/textures/Raptor.png");
    mTextures.load(TextureID::Desert, "resources/textures/Eagle.png");
    mTextures.load(TextureID::Desert, "resources/textures/Falcon.png");
}

void World::buildScene()
{

}

/*

void World::update(sf::Time dt)
{
    // Scroll the world
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    // Move the player sidewards (plane scouts follow the main aircraft)
    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    // If player touches borders, flip its X velocity
    if (position.x <= mWorldBounds.left + 150.f
     || position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
    {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
    }

    // Apply movements
    mSceneGraph.update(dt);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{

}

void World::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::Desert);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Add player's aircraft
    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(leader));

    // Add two escorting aircrafts, placed relatively to the main plane
    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}
*/
