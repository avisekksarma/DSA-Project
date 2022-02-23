#include <SFML/Graphics.hpp>
#include "include/context.hpp"
#include "include/graph.hpp"
#include "include/entities.hpp"

int main()
{
    Context context(sf::Vector2f(1000, 1000));
    // GUI::Vertex v1("0",context.getAssets().font1,context);
    Button addVertexBtn("Add Vertex", context, 100, 280);
    Button addEdgeBtn("Add Edge", context, 100, 180);
    Button clearBtn("Clear", context, 100, 80);
    sf::RenderWindow window(sf::VideoMode(context.getWinSize().x, context.getWinSize().y), "Graph Algorithms");

    Graph graph(context);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (addVertexBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                    {
                        if (!addEdgeBtn.drawNow)
                        {
                            addVertexBtn.manageBtnState();
                        }
                    }
                    else if (addEdgeBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                    {
                        if (!addVertexBtn.drawNow)
                        {
                            addEdgeBtn.manageBtnState();
                            if (!addEdgeBtn.drawNow)
                            {
                                graph.clearEdgeVector();
                            }
                        }
                    }else if(clearBtn.checkIfBtnClicked(event.mouseButton.x,event.mouseButton.y)){
                        graph.clear();
                    }
                    else if (addVertexBtn.drawNow)
                    {
                        // draw vertex of the graph
                        graph.addVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (addEdgeBtn.drawNow)
                    {
                        // TODO: draw edge later.
                        graph.addEdge(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        window.clear();
        addVertexBtn.draw(window);
        addEdgeBtn.draw(window);
        clearBtn.draw(window);
        graph.draw(window);
        window.display();
    }

    return 0;
}