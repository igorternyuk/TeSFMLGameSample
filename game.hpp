#pragma once

#include "world.hpp"
#include "player.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class Game: private sf::NonCopyable
{
public:
    explicit Game();
    void run();
private:
    const std::string TITLE_OF_MAIN_WINDOW { "Air combate" };
    enum
    {
        SCREEN_WIDTH = 640,
        SCREEN_HEIGHT = 480,
        FPS = 30
    };
    void processEvents();
    void update(sf::Time frameTime);
    void render();
    void updateStatistics(sf::Time frameTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed = true);
    void centralizeWindow();

private:
    const sf::Time mFrameTime {sf::seconds(1.0f /FPS)};
    sf::RenderWindow mWindow;
    World mWorld;
    Player mPlayer;
    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    size_t mStatisticsNumFrames;
};
