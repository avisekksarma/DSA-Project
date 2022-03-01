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
  sf::CircleShape weightTextCircle;
  sf::Text weightText;

  Edge();
  Edge(Context &c, int id, int weight = 1);
};

class Vertex
{
  int id;
  GUI::Vertex guiVertex;

public:
  sf::Text shortestVal;
  static int count;
  std::list<Edge> edgeList;

public:
  Vertex(Context &c, const sf::Vector2f &pos);
  // ~Vertex()
  // {
  //     count--;
  // }
  //getters
  int getID();
  // setters
  void setID(int index);
  GUI::Vertex &getGUIVertex();
};

// this is undirected graph
class Graph
{
private:
  std::vector<Vertex> graph;
  Context &context;
  // to store two vertices to draw edge
  std::vector<int> vertexForEdge;
  std::vector<bool> isVisited;
  std::vector<int> dValue;    // always graph.size
  std::vector<int> dPrevious; // always graph.size
  std::vector<std::vector<int>> shortestPath;

public:
  std::vector<int> dUnvisited; // first graph.size then to 0 finally
  std::queue<int> queue;
  std::stack<int> stack;
  std::string visited_node_list;

private:
  bool isThisIDValid(int ID);
  bool doesThisEdgeExist(int end1ID, int end2ID);
  int getIndexFromID(int ID);

public:
  Graph(Context &c);
  // TODO: manage index and ID confusion here.
  // adds a edge if that edge does not exist yet otherwise does nothing.
  void addEdge(sf::Vector2f mousePos);
  void printGraph();

  std::vector<Vertex> &getGraph();

  void resetAnimation();
  void resetAnimation(bool isDijkstra);

  void addVertex(sf::Vector2f mousePos);
  void draw(sf::RenderWindow &window, bool drawWeight, bool isDijkstra, bool isAnimateBtnActive, bool isShortestPath);
  void drawLine(sf::Vector2f end1, sf::Vector2f end2, sf::RenderWindow &window, sf::Color col);
  void clearEdgeVector();
  void clear();

  int containsVertex(sf::Vector2f pos);
  void Dijkstra(bool isFirstNode, int startID = 0);
  int findMinID(int &index);
  bool containIntheRange(sf::Vector2f mousePos);
  void deleteVertex(sf::Vector2f mousePos);
  void BFS(sf::Text &visited_node_order, bool isFirstNode = false, int id = 0);
  void DFS(sf::Text &visited_node_order, bool isFirstNode = false, int id = 0);
  void draw(sf::RenderWindow &window, bool isAnimation);
  void setColorPath(int currID);
  int getNextVertexID(int nowVertexID);
};
