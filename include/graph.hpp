#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include <vector>
#include "gui-vertex.hpp"

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
    static int count;
    GUI::Vertex guiVertex;

public:
    std::list<Edge> edgeList;

public:
    Vertex(Context &c, const sf::Vector2f &pos) : guiVertex(c), edgeList(0)
    {
        this->id = count;
        std::cout<<id<<" "<<count<<std::endl;
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
    std::vector<Vertex> graph;
    int numOfVertices;
    Context &context;

private:
    bool isThisIndexValid(int index)
    {
        return index >= 0 and index < graph.size();
    }
    bool doesThisEdgeExist(int end1, int end2)
    {
        // make sure you call this function in valid end1, end2 values.
        auto i = graph[end1].edgeList.begin();
        for (; i != graph[end1].edgeList.end(); i++)
        {
            if (i->id == end2)
                return true;
        }
        return false;
    }

public:
    Graph(Context &c, int numOfVertices = 0) : context(c)
    {
        this->numOfVertices = numOfVertices;
        // graph.resize(numOfVertices);
        if (numOfVertices != 0)
        {
            for (int i = 0; i < numOfVertices; i++)
            {
                graph[i].setID(i);
            }
        }
    }
    bool isVertexAdjacent(int source, int checkVertex)
    {
        // index of say vertices A and B are given, i need to say if they are adjacent i.e. connected.
        if (isThisIndexValid(source) and isThisIndexValid(checkVertex))
        {
            auto it = graph[source].edgeList.begin();
            for (; it != graph[source].edgeList.end(); ++it)
            {
                if (it->id == checkVertex)
                    return true;
            }
            return false;
        }
    }
    // adds a edge if that edge does not exist yet otherwise does nothing.
    void addEdge(int end1, int end2, int weight = 1)
    {
        if (isThisIndexValid(end1) and isThisIndexValid(end2) and !doesThisEdgeExist(end1, end2))
        {
            graph[end1].edgeList.push_back(Edge(end2, weight));
            graph[end2].edgeList.push_back(Edge(end1, weight));
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
    void draw(sf::RenderWindow & window)
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            graph[i].getGUIVertex().draw(window);
        }
    }
};