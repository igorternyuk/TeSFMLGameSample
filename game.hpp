#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Game
{
public:
    explicit Game();
    void run();
private:
    const std::string TITLE_OF_MAIN_WINDOW {"Air combate"};
    enum
    {
        SCREEN_WIDTH = 640,
        SCREEN_HEIGHT = 480,
        FPS = 60
    };
    void processEvents();
    void update(sf::Time frameTime);
    void render();
    void centralizeWindow();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed = true);

    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    const sf::Time mFrameTime {sf::seconds(1.0f /FPS)};
    float mPlayerSpeed {100.0f};
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;

};
