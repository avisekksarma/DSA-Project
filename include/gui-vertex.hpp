#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "random.hpp"
#include "context.hpp"

namespace GUI
{
    class Vertex
    {
        sf::CircleShape circle;
        sf::Text text;
        Context &context;

    public:
        Vertex(Context &c) : context(c) {}
        void create(char value, const sf::Font &font, Context &c, sf::Vector2f pos, float radius = 30)
        {
            circle.setRadius(radius);
            circle.setFillColor(sf::Color::Green);
            text.setFont(font);
            text.setFillColor(sf::Color::Red);
            text.setString(value);
            text.setCharacterSize(30);
            circle.setPosition(pos.x, pos.y);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            text.setPosition(circle.getPosition().x+7, circle.getPosition().y);
            text.setOrigin(text.getGlobalBounds().width, text.getGlobalBounds().height);
            // find algorithm for putting this circle at a location
        }

        const sf::CircleShape &getCircle() const
        {
            return circle;
        }
        void draw(sf::RenderWindow &window)
        {
            window.draw(circle);
            window.draw(text);
        }
    };
}
