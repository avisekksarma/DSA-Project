#pragma once
#include <iostream>
#include "context.hpp"
#include "entities.hpp"
#include "bfs-dfs-Traversal.hpp"
#include "dijkstra-Traversal.hpp"

class MainMenu
{
    Context &context;
    Button bfsDfsBtn;
    Button dijkstraBtn;
    Button exitBtn;
    sf::Sprite headingSprite;
    sf::Texture headingTexture;

public:
    MainMenu(Context &c);
    ~MainMenu();
    void run();

private:
    void init();
    void processEvents(sf::Event &event);
    void renderWindow();
    void update();
};
