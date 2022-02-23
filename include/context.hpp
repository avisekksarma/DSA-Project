#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "load-assets.hpp"

class Context
{
    sf::Vector2f mWindowSize;
    Assets assets;

public:
    int gridLength = 1000;
    Context(const sf::Vector2f winSize)
    {
        mWindowSize = winSize;
    }
    const sf::Vector2f & getWinSize() const {
        return mWindowSize;
    }
    const Assets& getAssets() const {
        return assets;
    }
};