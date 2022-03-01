#pragma once
#include <iostream>
#include "context.hpp"
#include "entities.hpp"
#include "bfs-dfs-Traversal.hpp"

class MainMenu
{
    Context &context;
    Button bfs_dfs;
    sf::Sprite headingSprite;
    sf::Texture headingTexture;

public:
    MainMenu(Context &c) : context(c), bfs_dfs(c)
    {
        init();
    }
    ~MainMenu() {}
    void run()
    {
        while (context.window.isOpen())
        {
            sf::Event event;
            processEvents(event);
            renderWindow();
        }
    }

private:
    void init()
    {
        bfs_dfs.create("Traversal", context.getWinSize().x / 2.0f, context.getWinSize().y / 2.0f);
        headingTexture.loadFromFile("./assets/image/title.png");
        headingSprite.setTexture(headingTexture);
        headingSprite.setPosition(context.getWinSize().x/2.f,100);
        headingSprite.setOrigin(headingSprite.getGlobalBounds().width/2.f,headingSprite.getGlobalBounds().height/2.f);
        headingSprite.setScale(0.75f,0.75f);
    }
    void processEvents(sf::Event &event)
    {
        while (context.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                context.window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (bfs_dfs.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                    {
                        Screen::Traversal traversal(context);
                        traversal.run();
                    }
                }
            }
        }
    }
    void renderWindow()
    {
        context.window.clear(sf::Color{0x16191EFF});
        bfs_dfs.draw(context.window);
        context.window.draw(headingSprite);
        // graph.draw(context.window);
        context.window.display();
    }
    void update()
    {
    }
};
