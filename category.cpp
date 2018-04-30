#include "category.hpp"

unsigned int operator&(Category first, Category second)
{
    unsigned int numFirst = static_cast<unsigned int>(first);
    unsigned int numSecond = static_cast<unsigned int>(second);
    return numFirst & numSecond;
}

unsigned int operator|(Category first, Category second)
{
    unsigned int numFirst = static_cast<unsigned int>(first);
    unsigned int numSecond = static_cast<unsigned int>(second);
    return numFirst | numSecond;
}

unsigned int operator^(Category first, Category second)
{
    unsigned int numFirst = static_cast<unsigned int>(first);
    unsigned int numSecond = static_cast<unsigned int>(second);
    return numFirst ^ numSecond;
}
