#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Assets{
    sf::Font font1;
    public:
    Assets(){
        if(!font1.loadFromFile("../assets/fonts/OpenSans-Italic.ttf")){
            std::cerr<<"Error: could not load font1"<<std::endl;
        }
    }
};