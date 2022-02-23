#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "random.hpp"
#include "context.hpp"

class Vertex
{
    sf::CircleShape circle;
    sf::Text text;
    sf::Vector2f pos;
    Context & context;

public:
    Vertex(std::string value, const sf::Font &font,Context & c,float radius = 20) : circle(radius)
    ,context(c){
        circle.setFillColor(sf::Color::Green);
        text.setFont(font);
        text.setString(value);
        text.setCharacterSize(15);
        circle.setOrigin(circle.getRadius() / 2.0f, circle.getRadius() / 2.0f);
        // find algorithm for putting this circle at a location

        // get base random alias which is auto seeded and has static API and internal state
        using Random = effolkronium::random_static;

        pos.x = Random::get(context.getWinSize().x1.f,-1.f);
    }
};
