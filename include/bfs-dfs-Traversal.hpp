#pragma once
#include <iostream>
#include "context.hpp"
#include <SFML/Graphics.hpp>
#include "entities.hpp"
#include "graph.hpp"
#include <chrono>
#include <thread>

namespace Screen
{
    // screen for bfs and dfs visualization
    class Traversal
    {
    private:
        Context &context;
        Button addVertexBtn;
        Button addEdgeBtn;
        Button clearBtn;
        Button bfsBtn;
        Button dfsBtn;
        Graph graph;
        bool isBFSAnimation = false;
        bool isDFSAnimation = false;

    private:
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
                        }
                        else if (clearBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            graph.clear();
                            isBFSAnimation = false;
                            isDFSAnimation = false;
                        }
                        else if (bfsBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            graph.BFS(true);
                            isBFSAnimation = true;
                        }
                        else if (dfsBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            graph.DFS(true);
                            isDFSAnimation = true;
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
        }

    public:
        Traversal(Context &c) : context(c), addVertexBtn(c), addEdgeBtn(c), clearBtn(c), graph(c),
                                bfsBtn(c), dfsBtn(c)
        {
            addVertexBtn.create("Add Vertex", 100, 480);
            addEdgeBtn.create("Add Edge", 100, 380);
            clearBtn.create("Clear", 100, 280);
            bfsBtn.create("Animate BFS", 100, 180);
            dfsBtn.create("Animate DFS", 100, 80);
        }
        void run()
        {
            while (context.window.isOpen())
            {
                sf::Event event;
                processEvents(event);
                if (isBFSAnimation)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(700ms);
                    if (!graph.queue.empty())
                        graph.BFS(false);
                    else
                        isBFSAnimation = false;
                }
                else if (isDFSAnimation)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(700ms);
                    if (!graph.stack.empty())
                        graph.DFS(false);
                    else
                        isDFSAnimation = false;
                }
                renderWindow();
            }
        }
        void renderWindow()
        {
            context.window.clear();
            addVertexBtn.draw(context.window);
            addEdgeBtn.draw(context.window);
            clearBtn.draw(context.window);
            bfsBtn.draw(context.window);
            dfsBtn.draw(context.window);
            graph.draw(context.window);
            context.window.display();
        }
    };
}