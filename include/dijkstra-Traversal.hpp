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
    class DijkstraTraversal
    {
    private:
        Context &context;
        Button addVertexBtn;
        Button addEdgeBtn;
        Button clearBtn;
        Button animateBtn;
        Graph graph;
        enum class IsActive
        {
            None,
            addVertexBtn,
            addEdgeBtn,
            animateBtn
        };
        IsActive activeBtn = IsActive::None;
        bool isDijkstraAnimation = false;
        bool hasDijkstraStared = false;
        bool drawPath = false;

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
                            if (activeBtn == IsActive::None or activeBtn == IsActive::addVertexBtn)
                            {
                                addVertexBtn.manageBtnState();
                                if (addVertexBtn.isActive)
                                    activeBtn = IsActive::addVertexBtn;
                                else
                                    activeBtn = IsActive::None;
                            }
                        }
                        else if (addEdgeBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None or activeBtn == IsActive::addEdgeBtn)
                            {
                                addEdgeBtn.manageBtnState();
                                if (addEdgeBtn.isActive)
                                    activeBtn = IsActive::addEdgeBtn;
                                else
                                    activeBtn = IsActive::None;
                            }
                        }
                        else if (clearBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None)
                            {
                                graph.clear();
                                isDijkstraAnimation = false;
                                // isDFSAnimation = false;
                            }
                        }
                        else if (animateBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None or activeBtn == IsActive::animateBtn)
                            {
                                if (animateBtn.isActive)
                                {
                                    //TODO: implement below function later
                                    graph.resetAnimation(true);
                                    isDijkstraAnimation = false;
                                }
                                animateBtn.manageBtnState();
                                if (animateBtn.isActive)
                                {
                                    activeBtn = IsActive::animateBtn;
                                }
                                else
                                {
                                    drawPath = false;
                                    hasDijkstraStared = false;
                                    activeBtn = IsActive::None;
                                }

                                // isBFSAnimation = false;
                                // isDFSAnimation = false;
                            }
                        }
                        else if (addVertexBtn.isActive)
                        {
                            // draw vertex of the graph
                            graph.addVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                        else if (addEdgeBtn.isActive)
                        {
                            graph.addEdge(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                        else if (animateBtn.isActive)
                        {

                            int id;
                            id = graph.containsVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            if (!hasDijkstraStared)
                            {
                                if (id >= 0)
                                {
                                    graph.Dijkstra(true, id);
                                    isDijkstraAnimation = true;
                                    hasDijkstraStared = true;
                                }
                            }
                            else
                            {
                                // case for clicking after animation has finished ( for knowing path of a vertex )
                                drawPath = true;
                                graph.setColorPath(id);
                            }
                        }
                    }
                }
            }
        }

    public:
        DijkstraTraversal(Context &c) : context(c), addVertexBtn(c), addEdgeBtn(c), clearBtn(c), graph(c), animateBtn(c)
        {
            addVertexBtn.create("Add Vertex", 100, 480);
            addEdgeBtn.create("Add Edge", 100, 380);
            clearBtn.create("Clear", 100, 280);
            animateBtn.create("Animate", 100, 180);
        }
        void run()
        {
            while (context.window.isOpen())
            {
                sf::Event event;
                if (isDijkstraAnimation)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(700ms);

                    if (!graph.dUnvisited.empty())
                        graph.Dijkstra(false);
                    else
                        isDijkstraAnimation = false;
                }
                processEvents(event);
                renderWindow();
            }
        }
        void renderWindow()
        {
            context.window.clear(sf::Color{0x16191EFF});
            addVertexBtn.draw(context.window);
            addEdgeBtn.draw(context.window);
            clearBtn.draw(context.window);
            animateBtn.draw(context.window);
            if (drawPath)
            {
                graph.draw(context.window, true, true, animateBtn.isActive, true);
            }
            else
            {
                graph.draw(context.window, true, true, animateBtn.isActive, false);
            }
            context.window.display();
        }
    };
}