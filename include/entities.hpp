#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "context.hpp"

class Button
{
    sf::RectangleShape btn;
    sf::Text text;
    Context &context;
    std::string value;


public:
    bool isActive = false;
    Button(Context &c) : context(c) {}
    void create(std::string value, int xFactor, int yFactor)
    {
        this->value = value;
        text.setString(value);
        text.setFont(context.getAssets().font1);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(context.getWinSize().x - xFactor, context.getWinSize().y - yFactor);
        btn.setSize(sf::Vector2f(150, 80));
        btn.setPosition(context.getWinSize().x - xFactor, context.getWinSize().y - yFactor);
        btn.setOrigin(btn.getSize().x / 2.0f, btn.getSize().y / 2.0f);
        btn.setFillColor(sf::Color{0xB98D74FF});
        text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(btn);
        window.draw(text);
    }
    
    bool checkIfBtnClicked(int posX, int posY)
    {
        if (btn.getGlobalBounds().contains(posX, posY))
        {
            return true;
        }
        else
            return false;
    }
    void manageBtnState(std::string label = "Stop")
    {
        if (!isActive)
        {
            btn.setFillColor(sf::Color{0xB54756FF});
            text.setString(label);
            isActive = true;
        }
        else
        {
            btn.setFillColor(sf::Color{0xB98D74FF});
            text.setString(this->value);
            isActive = false;
        }
    }
};
