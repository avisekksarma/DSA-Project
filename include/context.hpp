#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "load-assets.hpp"

class Context
{
    sf::Vector2f mWindowSize;
    Assets assets;
public:
    sf::RenderWindow window;
    Context(const sf::Vector2f winSize)
    {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        mWindowSize = winSize;
        window.create(sf::VideoMode(mWindowSize.x, mWindowSize.y), "Graph Algorithms", sf::Style::Default,settings);
    }
    const sf::Vector2f &getWinSize() const
    {
        return mWindowSize;
    }
    const Assets &getAssets() const
    {
        return assets;
    }
};
