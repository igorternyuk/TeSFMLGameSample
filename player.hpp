#pragma once

#include "command.hpp"
#include <SFML/Window/Event.hpp>
#include <map>

class CommandQueue;

class Player
{
public:
    enum class Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };
    explicit Player();
    void bindKey(sf::Keyboard::Key key, Action action);
    sf::Keyboard::Key getBindedKey(Action action) const;
    void processEvent(sf::Event event, CommandQueue& commands);
    void processRealTimeInput(CommandQueue& commands);

private:
    void initializeActions();
    static bool isRealtimeAction(Action action);

private:
    std::map<sf::Keyboard::Key, Action> mKeyBindings;
    std::map<Action, Command> mActionBindings;
};
