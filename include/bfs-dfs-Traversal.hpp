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
        Button pauseBtn;
        Button deleteBtn;
        sf::Text visited_node_order;
        Graph graph;

        enum class IsActive
        {
            None,
            addVertexBtn,
            addEdgeBtn,
            bfsBtn,
            dfsBtn,
            pauseBtn,
            deleteBtn
        };
        IsActive activeBtn = IsActive::None;
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
                                {
                                    graph.clearEdgeVector();
                                    activeBtn = IsActive::None;
                                }
                            }
                        }
                        else if (deleteBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None or activeBtn == IsActive::deleteBtn)
                            {
                                deleteBtn.manageBtnState();
                                if (deleteBtn.isActive)
                                    activeBtn = IsActive::deleteBtn;
                                else
                                    activeBtn = IsActive::None;
                            }
                        }
                        else if (clearBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None)
                            {
                                graph.clear();
                                isBFSAnimation = false;
                                isDFSAnimation = false;
                            }
                        }
                        else if (bfsBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None or activeBtn == IsActive::bfsBtn)
                            {
                                if (bfsBtn.isActive)
                                {
                                    graph.resetAnimation();
                                    isBFSAnimation = false;
                                    visited_node_order.setString("");
                                }
                                bfsBtn.manageBtnState();
                                if (bfsBtn.isActive)
                                    activeBtn = IsActive::bfsBtn;
                                else
                                    activeBtn = IsActive::None;
                            }
                        }
                        else if (dfsBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            if (activeBtn == IsActive::None or activeBtn == IsActive::dfsBtn)
                            {
                                if (dfsBtn.isActive)
                                {
                                    graph.resetAnimation();
                                    isDFSAnimation = false;
                                    visited_node_order.setString("");
                                }
                                dfsBtn.manageBtnState();
                                if (dfsBtn.isActive)
                                    activeBtn = IsActive::dfsBtn;
                                else
                                    activeBtn = IsActive::None;
                            }
                        }
                        else if (pauseBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            pauseBtn.manageBtnState("Resume");
                            if (pauseBtn.isActive)
                            {
                                isDFSAnimation = false;
                                isBFSAnimation = false;
                            }
                            else
                            {
                                if (bfsBtn.isActive)
                                {
                                    isBFSAnimation = true;
                                }
                                else
                                {
                                    isDFSAnimation = true;
                                }
                            }
                        }
                        else if (addVertexBtn.isActive)
                        {
                            // draw vertex of the graph
                            graph.addVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                        else if (bfsBtn.isActive)
                        {
                            int id;
                            id = graph.containsVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            if (id >= 0)
                            {
                                graph.BFS(visited_node_order, true, id);
                                isBFSAnimation = true;
                            }
                        }
                        else if (dfsBtn.isActive)
                        {
                            int id;
                            id = graph.containsVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                            if (id >= 0)
                            {
                                graph.DFS(visited_node_order, true, id);
                                isDFSAnimation = true;
                            }
                        }
                        else if (addEdgeBtn.isActive)
                        {
                            // TODO: draw edge later.
                            graph.addEdge(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                        else if (deleteBtn.isActive)
                        {
                            graph.deleteVertex(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                    }
                }
            }
        }

    public:
        Traversal(Context &c) : context(c), deleteBtn(c), pauseBtn(c), addVertexBtn(c), addEdgeBtn(c), clearBtn(c), graph(c), bfsBtn(c), dfsBtn(c)
        {
            addVertexBtn.create("Add Vertex", 100, 480);
            addEdgeBtn.create("Add Edge", 100, 380);
            clearBtn.create("Clear", 100, 280);
            bfsBtn.create("Animate BFS", 100, 180);
            dfsBtn.create("Animate DFS", 100, 80);
            pauseBtn.create("Pause", 100, 580);
            deleteBtn.create("Delete", 100, 580);
            visited_node_order.setFont(context.getAssets().font1);
            visited_node_order.setFillColor(sf::Color::White);
            visited_node_order.setString("");
            visited_node_order.setPosition(100, context.getWinSize().y - 100);
        }
        void run()
        {
            while (context.window.isOpen())
            {
                sf::Event event;
                if (isBFSAnimation)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(700ms);
                    if (!graph.queue.empty())
                        graph.BFS(visited_node_order, false);
                    else
                        isBFSAnimation = false;
                }
                else if (isDFSAnimation)
                {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(700ms);
                    if (!graph.stack.empty())
                        graph.DFS(visited_node_order, false);
                    else
                        isDFSAnimation = false;
                }
                processEvents(event);
                renderWindow();
            }
        }
        void renderWindow()
        {
            context.window.clear(sf::Color{0x16191EFF});
            if (isBFSAnimation || isDFSAnimation || pauseBtn.isActive)
            {
                pauseBtn.draw(context.window);
            }
            addVertexBtn.draw(context.window);
            deleteBtn.draw(context.window);
            addEdgeBtn.draw(context.window);
            clearBtn.draw(context.window);
            bfsBtn.draw(context.window);
            dfsBtn.draw(context.window);
            context.window.draw(visited_node_order);
            if (isBFSAnimation || isDFSAnimation)
            {
                graph.draw(context.window, true);
            }
            else
            {
                graph.draw(context.window, false);
            }
            context.window.display();
        }
    };
}
