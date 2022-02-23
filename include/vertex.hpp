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
    Context &context;
    struct Grid{
        int numOfVertexHeight;
        int numOfVertexWidth;
        Grid(){
            numOfVertexHeight= 10;
            numOfVertexWidth = 10;
        }
    };
    Grid grid;
    static std::vector<std::vector<sf::Vector2f>> possiblePos;

public:
    Vertex(std::string value, const sf::Font &font, Context &c, float radius = 20) : circle(radius), context(c)
    {
        circle.setFillColor(sf::Color::Green);
        text.setFont(font);
        text.setString(value);
        text.setCharacterSize(15);
        circle.setOrigin(circle.getRadius() / 2.0f, circle.getRadius() / 2.0f);
        // find algorithm for putting this circle at a location

        // get base random alias which is auto seeded and has static API and internal state
        // pos.x = Random::get(context.getWinSize().x1*1.f,-1.f);
        sf::Vector2f top(context.getWinSize().x/2.0f - context.gridLength/2.0,context.getWinSize().y/2.0f - context.gridLength/2.0f);
        for(int i  = 0;i<grid.numOfVertexHeight;i++){
            for(int j = 0;j<grid.numOfVertexWidth;j++){
                possiblePos[i].push_back(sf::Vector2f(top.x +  j*(context.gridLength/grid.numOfVertexWidth),top.y + i* (context.gridLength/grid.numOfVertexHeight)));
            }
        }
        // TODO: check grid values later


        using Random = effolkronium::random_static;
        auto x = Random::get(0,grid.numOfVertexWidth-1);
        auto y = Random::get(0,grid.numOfVertexHeight-1);
        std::cout<<x<<" "<<y<<std::endl;
        circle.setPosition(possiblePos[x][y].x , possiblePos[x][y].y); 
        // circle.setPosition(possiblePos[1][4].x , possiblePos[2][5].y); 
    }
    
    const sf::CircleShape & getCircle() const{
        return circle;
    }
};
std::vector<std::vector<sf::Vector2f>> Vertex::possiblePos{10,std::vector<sf::Vector2f>(0,sf::Vector2f(0,0))};