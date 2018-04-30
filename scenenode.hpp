#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "category.hpp"
#include <vector>
#include <memory>

struct Command;

class SceneNode: public sf::Transformable, public sf::Drawable,
                 private sf::NonCopyable
{
public:
    using Ptr = std::unique_ptr<SceneNode>;
    explicit SceneNode();
    void attachChild(Ptr node);
    Ptr detachChild(const SceneNode& node);
    void update(sf::Time frameTime);
    void onCommand(const Command& command, sf::Time frameTime);
    sf::Vector2f getWorldPosition() const;
    sf::Transform getWorldTransform() const;
    virtual Category getCategory() const;
private:
    virtual void updateCurrent(sf::Time frameTime);
    void updateChildren(sf::Time frameTime);
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const final;
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;
    virtual void drawChildren(sf::RenderTarget& target,
                             sf::RenderStates states) const;
private:
    std::vector<Ptr> mChildren;
    SceneNode* mParent;
};
