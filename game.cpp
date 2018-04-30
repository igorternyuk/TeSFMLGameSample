#include "game.hpp"
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <iostream>

Game::Game():
    mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), TITLE_OF_MAIN_WINDOW,
            sf::Style::Close),
    mWorld(mWindow)
{
    mWindow.setFramerateLimit(FPS);
    centralizeWindow();
    mFont.loadFromFile("resources/fonts/Sansation.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.0f, 5.0f);
    mStatisticsText.setCharacterSize(14);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        auto elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while(timeSinceLastUpdate > mFrameTime)
        {
            timeSinceLastUpdate -= mFrameTime;
            processEvents();
            update(mFrameTime);
        }
        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    CommandQueue& commands = mWorld.getCommandQueue();

    while(mWindow.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                mPlayer.processEvent(event, commands);
                break;
        }
    }
    mPlayer.processRealTimeInput(commands);
}

void Game::update(sf::Time frameTime)
{
    mWorld.update(frameTime);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time frameTime)
{
    mStatisticsNumFrames += 1;
    mStatisticsUpdateTime += frameTime;
    if (mStatisticsUpdateTime >= sf::seconds(0.5f))
    {
        auto updateTime = mStatisticsUpdateTime.asMicroseconds() /
                mStatisticsNumFrames;
        mStatisticsText.setString(
            "Frames / Second = " + std::to_string(mStatisticsNumFrames) +
            "\nTime / Update = " + std::to_string(updateTime) + "us"
        );
        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Game::centralizeWindow()
{
    const int screenWidth = sf::VideoMode::getDesktopMode().width;
    const int screenHeight = sf::VideoMode::getDesktopMode().height;
    mWindow.setPosition(sf::Vector2i((screenWidth - SCREEN_WIDTH) / 2,
                                     (screenHeight - SCREEN_HEIGHT) / 2));
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{}


