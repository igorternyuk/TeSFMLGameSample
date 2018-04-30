#pragma once

#include "category.hpp"
#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
    Command();
    std::function<void(SceneNode&, sf::Time)> action;
    Category category;
};

/*
 * This is the small adapter function that takes a function on a class
 * derived from SceneNode and coverts in to a function on SceneNode class.
 * It creates a lambda expression, inside which we invoke the original
 * function on the derived class, passing a downcast argument to it
*/
template <class GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function originalFunction)
{
    return [=](SceneNode& node, sf::Time frameTime)
    {
        //Check if cast is save
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        //Downcast node and invoke original function
        originalFunction(static_cast<GameObject&>(node), frameTime);
    };
}

/*
template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return [=] (SceneNode& node, sf::Time dt)
    {
        // Check if cast is safe
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject&>(node), dt);
    };
}

*/
