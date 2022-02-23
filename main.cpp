#include <SFML/Graphics.hpp>
#include "include/context.hpp"
#include "include/vertex.hpp"

int main()
{
    Context context(sf::Vector2f(1000,1000));
    Vertex v1("0",context.getAssets().font1,context);
    sf::RenderWindow window(sf::VideoMode(context.getWinSize().x,context.getWinSize().y), "Graph Algorithms");
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(v1.getCircle());
        window.display();
    }

    return 0;
}