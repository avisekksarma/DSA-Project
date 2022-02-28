#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <vector>
#include <cmath>
#include <stack>
#include "gui-vertex.hpp"
#include <queue>
#include <SFML/Graphics/Shape.hpp>
// #include "bfs-dfs-Traversal.hpp"

class Edge
{
public:
    int weight; // for weighted graph
    int id;
    Edge() {}
    Edge(int id, int weight = 1)
    {
        this->id = id;
        this->weight = weight;
    }
};

class Vertex
{
    int id;
    GUI::Vertex guiVertex;

public:
    static int count;
    std::list<Edge> edgeList;

public:
    Vertex(Context &c, const sf::Vector2f &pos) : guiVertex(c), edgeList(0)
    {
        this->id = count;
        std::cout << id << " " << count << std::endl;
        guiVertex.create(char(id + 65), c.getAssets().font1, c, pos);
        count++;
    }
    // ~Vertex()
    // {
    //     count--;
    // }
    //getters
    int getID() const
    {
        return id;
    }
    // setters
    void setID(int index)
    {
        id = index;
    }
    GUI::Vertex &getGUIVertex()
    {
        return guiVertex;
    }
};
int Vertex::count = 0;

// this is undirected graph
class Graph
{
private:
    std::vector<Vertex> graph;
    Context &context;
    // to store two vertices to draw edge
    std::vector<int> vertexForEdge;

    std::vector<bool> isVisited;

public:
    std::queue<int> queue;
    std::stack<int> stack;

private:
    bool isThisIDValid(int ID)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            if (graph[i].getID() == ID)
            {
                return true;
            }
        }
        return false;
    }
    bool doesThisEdgeExist(int end1ID, int end2ID)
    {
        // make sure you call this function in valid end1, end2 values.
        auto i = graph[getIndexFromID(end1ID)].edgeList.begin();
        for (; i != graph[getIndexFromID(end1ID)].edgeList.end(); i++)
        {
            if (i->id == end2ID)
                return true;
        }
        return false;
    }
    int getIndexFromID(int ID)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            if (graph[i].getID() == ID)
            {
                return i;
            }
        }
        return -1;
    }

public:
    Graph(Context &c) : context(c)
    {
    }
    // TODO: manage index and ID confusion here.
    // bool isVertexAdjacent(int source, int checkVertex)
    // {
    //     // index of say vertices A and B are given, i need to say if they are adjacent i.e. connected.
    //     if (isThisIDValid(source) and isThisIDValid(checkVertex))
    //     {
    //         auto it = graph[source].edgeList.begin();
    //         for (; it != graph[source].edgeList.end(); ++it)
    //         {
    //             if (it->id == checkVertex)
    //                 return true;
    //         }
    //         return false;
    //     }
    // }
    // adds a edge if that edge does not exist yet otherwise does nothing.
    void addEdge(sf::Vector2f mousePos)
    {
        int weight = 1;
        for (int i = 0; i < graph.size(); ++i)
        {
            if (graph[i].getGUIVertex().getCircle().getGlobalBounds().contains(mousePos))
            {
                vertexForEdge.push_back(graph[i].getID());
                break;
            }
        }
        if (vertexForEdge.size() == 2)
        {
            if (vertexForEdge[0] != vertexForEdge[1])
            {
                if (!doesThisEdgeExist(vertexForEdge[0], vertexForEdge[1]))
                {
                    graph[getIndexFromID(vertexForEdge[0])].edgeList.push_back(Edge(vertexForEdge[1], weight));
                    graph[getIndexFromID(vertexForEdge[1])].edgeList.push_back(Edge(vertexForEdge[0], weight));
                }
            }
            vertexForEdge.clear();
        }
    }
    void printGraph()
    {
        for (int i = 0; i < graph.size(); i++)
        {
            std::cout << graph[i].getID() << "-->";
            auto j = graph[i].edgeList.begin();
            for (; j != graph[i].edgeList.end(); j++)
            {
                std::cout << "(" << j->id << " [" << j->weight << "] )   ";
            }
            std::cout << std::endl;
        }
    }

    void addVertex(sf::Vector2f mousePos)
    {
        graph.push_back(Vertex(context, mousePos));
    }
    void draw(sf::RenderWindow &window)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            auto it = graph[i].edgeList.begin();
            for (; it != graph[i].edgeList.end(); ++it)
            {
                drawLine(graph[i].getGUIVertex().getCircle().getPosition(), graph[getIndexFromID(it->id)].getGUIVertex().getCircle().getPosition(), window);
            }
        }
        for (int i = 0; i < graph.size(); ++i)
        {
            graph[i].getGUIVertex().draw(window);
        }
    }
    void drawLine(sf::Vector2f end1, sf::Vector2f end2, sf::RenderWindow &window)
    {
        /* float length = sqrt(pow((end1.x - end2.x), 2) + pow((end1.y - end2.y), 2)); */
        /* sf::RectangleShape line(sf::Vector2f(length, 5.0f)); */
        /* line.setPosition(end1); */
        /* // for angle finding */
        /* float angle = (atan((end2.x - end1.x) / (end2.y - end1.y)))*180/3.14; */
        /* std::cout<<"Angle is:" <<angle<<std::endl; */
        /* line.setRotation(90+angle); */
        /* auto rad = graph[0].getGUIVertex().getCircle().getRadius(); */
        



        sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(end1.x, end1.y)),
                sf::Vertex(sf::Vector2f(end2.x, end2.y))};
        window.draw(line, 2, sf::Lines);
        // window.draw(line);
    }
    void clearEdgeVector()
    {
        // clears vertexForEdge
        vertexForEdge.clear();
    }
    void clear()
    {
        graph.clear();
        while (!queue.empty())
        {
            queue.pop();
        }
        while (!stack.empty())
        {
            stack.pop();
        }
        isVisited.clear();
        vertexForEdge.clear();
        Vertex::count = 0;
    }
    void BFS(bool isFirstNode = false)
    {
        std::cout << "BFS start" << std::endl;
        if (isFirstNode)
        {
            // first initialization
            queue.push(graph[0].getID());
            isVisited.resize(graph.size(), false);
            isVisited[0] = true;
        }

        int x = queue.front();
        queue.pop();
        std::cout << x << std::endl;
        int currIndex = getIndexFromID(x);
        graph[currIndex].getGUIVertex().getCircle().setFillColor(sf::Color::Blue);
        auto it = graph[currIndex].edgeList.begin();
        for (; it != graph[currIndex].edgeList.end(); ++it)
        {
            if (!isVisited[getIndexFromID(it->id)])
            {
                isVisited[getIndexFromID(it->id)] = true;
                queue.push(it->id);
            }
        }
    }

    void DFS(bool isFirstNode = false)
    {
        std::cout << "DFS start" << std::endl;
        if (isFirstNode)
        {
            stack.push(graph[0].getID());
            isVisited.resize(graph.size(), false);
            isVisited[0] = true;
            graph[0].getGUIVertex().getCircle().setFillColor(sf::Color::Cyan);
        }
        int x = stack.top();

        int currIndex = getIndexFromID(x);
        auto it = graph[currIndex].edgeList.begin();
        bool isBreak = false;
        for (; it != graph[currIndex].edgeList.end(); ++it)
        {
            if (!isVisited[getIndexFromID(it->id)])
            {
                isVisited[getIndexFromID(it->id)] = true;
                stack.push(it->id);
                std::cout << it->id << std::endl;
                graph[getIndexFromID(it->id)].getGUIVertex().getCircle().setFillColor(sf::Color::Cyan);
                isBreak = true;
                break;
            }
        }
        if (!isBreak)
        {
            stack.pop();
        }
        // if (graph.size() - 1 == getIndexFromID(it->id))
        // {
        // }
    }
};
