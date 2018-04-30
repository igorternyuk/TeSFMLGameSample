#include "scenenode.hpp"
#include "command.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>

SceneNode::SceneNode()
{}

void SceneNode::attachChild(SceneNode::Ptr node)
{
    node->mParent = this;
    mChildren.push_back(std::move(node));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
                              [&node](auto &ptr){ return ptr.get() == &node; });
    assert(found != mChildren.end());
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    //Here we transfer the ownership of result to the caller
    return result;
}

void SceneNode::update(sf::Time frameTime)
{
    updateCurrent(frameTime);
    updateChildren(frameTime);
}

void SceneNode::onCommand(const Command &command, sf::Time frameTime)
{
    if(command.category & getCategory())
    {
        command.action(*this, frameTime);
    }

    for(auto &child: mChildren)
    {
        child->onCommand(command, frameTime);
    }
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for(const SceneNode *node = this; node != nullptr; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    }
    return transform;
}

Category SceneNode::getCategory() const
{
    return Category::Scene;
}

void SceneNode::updateCurrent(sf::Time frameTime)
{}

void SceneNode::updateChildren(sf::Time frameTime)
{
    for(auto &child: mChildren)
    {
        child->update(frameTime);
    }
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &target,
                            sf::RenderStates states) const
{}

void SceneNode::drawChildren(sf::RenderTarget &target,
                             sf::RenderStates states) const
{
    for(auto &child: mChildren)
    {
        child->draw(target, states);
    }
}
