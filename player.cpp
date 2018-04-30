#include "player.hpp"
#include "aircraft.hpp"
#include "commandqueue.hpp"
#include <iostream>

//Functor
struct AircraftAccelerator
{
    AircraftAccelerator(float vx, float vy):
        velIncrement(vx, vy)
    {}

    void operator()(Aircraft& aircraft, sf::Time frameTime) const
    {
        aircraft.accelerate(velIncrement);
    }

    sf::Vector2f velIncrement;
};

Player::Player()
{
    //Set initial key bindings
    mKeyBindings[sf::Keyboard::Left] = Action::MoveLeft;
    mKeyBindings[sf::Keyboard::A] = Action::MoveLeft;

    mKeyBindings[sf::Keyboard::Right] = Action::MoveRight;
    mKeyBindings[sf::Keyboard::D] = Action::MoveRight;

    mKeyBindings[sf::Keyboard::Up] = Action::MoveUp;
    mKeyBindings[sf::Keyboard::W] = Action::MoveUp;

    mKeyBindings[sf::Keyboard::Down] = Action::MoveDown;
    mKeyBindings[sf::Keyboard::S] = Action::MoveDown;

    initializeActions();

    for(auto &pair: mActionBindings)
    {
        pair.second.category = Category::PlayerAircraft;
    }
}

void Player::bindKey(sf::Keyboard::Key key, Player::Action action)
{
    // Remove all keys that already map to action
    for(auto it = mKeyBindings.begin(); it != mKeyBindings.end(); )
    {
        if(it->second == action)
        {
            mKeyBindings.erase(it++);
        }
        else
        {
            ++it;
        }
    }
    mKeyBindings[key] = action;
}

sf::Keyboard::Key Player::getBindedKey(Player::Action action) const
{
    for(auto pair: mKeyBindings)
    {
        if(pair.second == action)
        {
            return pair.first;
        }
    }
    return sf::Keyboard::Unknown;
}

void Player::processEvent(sf::Event event, CommandQueue &commands)
{
    if(event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBindings.find(event.key.code);
        if(found != mKeyBindings.end()
           && isRealtimeAction(found->second))
        {
            commands.push(mActionBindings[found->second]);
        }
    }

    if(event.type == sf::Event::KeyReleased
       && event.key.code == sf::Keyboard::P)
    {
       Command printCoords;
       printCoords.category = Category::PlayerAircraft;
       printCoords.action = [](SceneNode& node, sf::Time)
       {
           std::cout << "(" << node.getPosition().x << ", "
                     << node.getPosition().y << ")" << std::endl;
       };
       commands.push(printCoords);
    }
}

void Player::processRealTimeInput(CommandQueue &commands)
{
    // Traverse all assigned keys and check if they are pressed
    for(auto &pair: mKeyBindings)
    {
        if(sf::Keyboard::isKeyPressed(pair.first)
           && isRealtimeAction(pair.second))
        {
            commands.push(mActionBindings[pair.second]);
        }
    }
}

void Player::initializeActions()
{
    const float playerSpeed = 200.0f;
    mActionBindings[Action::MoveLeft].action =
            derivedAction<Aircraft>(AircraftAccelerator(-playerSpeed, 0.0f));
    mActionBindings[Action::MoveRight].action =
            derivedAction<Aircraft>(AircraftAccelerator(+playerSpeed, 0.0f));
    mActionBindings[Action::MoveUp].action =
            derivedAction<Aircraft>(AircraftAccelerator(0.0f, -playerSpeed));
    mActionBindings[Action::MoveDown].action =
            derivedAction<Aircraft>(AircraftAccelerator(0.0f, +playerSpeed));
}

bool Player::isRealtimeAction(Player::Action action)
{
    switch(action)
    {
        case Action::MoveLeft:
        case Action::MoveRight:
        case Action::MoveUp:
        case Action::MoveDown:
            return true;
        default:
            return false;
    }
}
