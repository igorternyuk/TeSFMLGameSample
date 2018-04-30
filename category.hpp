#pragma once

//Command receiver category

enum class Category
{
    None = 0,
    Scene = 1,
    PlayerAircraft = 1 << 1,
    AlliedAircraft = 1 << 2,
    EnemyAircraft = 1 << 3
};

unsigned int operator&(Category first, Category second);
unsigned int operator|(Category first, Category second);
unsigned int operator^(Category first, Category second);
