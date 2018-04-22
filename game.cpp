#include "game.hpp"

Game::Game():
    mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE_OF_MAIN_WINDOW),
    mPlayer()
{
    mWindow.setFramerateLimit(FPS);
    centralizeWindow();
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Green);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > mFrameTime)
        {
            timeSinceLastUpdate -= mFrameTime;
            processEvents();
            update(mFrameTime);
        }
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time frameTime)
{
    sf::Vector2f speed(0.0f, 0.0f);
    if(mIsMovingUp)
    {
        speed.y = -mPlayerSpeed;
    }
    if(mIsMovingDown)
    {
        speed.y = +mPlayerSpeed;
    }
    if(mIsMovingLeft)
    {
        speed.x = -mPlayerSpeed;
    }
    if(mIsMovingRight)
    {
        speed.x = +mPlayerSpeed;
    }
    mPlayer.move(speed * frameTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::centralizeWindow()
{
    const int screenWidth = sf::VideoMode::getDesktopMode().width;
    const int screenHeight = sf::VideoMode::getDesktopMode().height;
    mWindow.setPosition(sf::Vector2i((screenWidth - SCREEN_WIDTH) / 2,
                                     (screenHeight - SCREEN_HEIGHT) / 2));
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::A)
    {
        mIsMovingLeft = isPressed;
    }
    else if(key == sf::Keyboard::W)
    {
        mIsMovingUp = isPressed;
    }
    else if(key == sf::Keyboard::S)
    {
        mIsMovingDown = isPressed;
    }
    else if(key == sf::Keyboard::D)
    {
        mIsMovingRight = isPressed;
    }
}
