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
    bool drawNow = false;
    Button(std::string value, Context &c, int xFactor, int yFactor) : context(c)
    {
        this->value = value;
        text.setString(value);
        text.setFont(c.getAssets().font1);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Red);
        text.setPosition(context.getWinSize().x - xFactor, context.getWinSize().y - yFactor);
        btn.setSize(sf::Vector2f(150, 80));
        btn.setPosition(context.getWinSize().x - xFactor, context.getWinSize().y - yFactor);
        btn.setOrigin(btn.getSize().x / 2.0f, btn.getSize().y / 2.0f);
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
    void manageBtnState()
    {
        if (!drawNow)
        {
            btn.setFillColor(sf::Color::Cyan);
            text.setString("Stop");
            drawNow = true;
        }
        else
        {
            btn.setFillColor(sf::Color::White);
            text.setString(this->value);
            drawNow = false;
        }
    }
};
