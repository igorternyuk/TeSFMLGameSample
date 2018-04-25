#include "game.hpp"
#include <stdexcept>
#include <iostream>

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch(std::exception &ex)
    {
        std::cout << "Error " << ex.what() << " occured." << std::endl;
    }
    return 0;
}
