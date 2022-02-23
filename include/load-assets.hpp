#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>

class Assets{
    public:
    sf::Font font1;
    Assets(){
        // auto x = std::filesystem::current_path();
        // std::cout<<x.string()<<std::endl;
        if(!font1.loadFromFile("./assets/fonts/OpenSans-Italic.ttf")){
            std::cerr<<"Error: could not load font1"<<std::endl;
        }
    }
};