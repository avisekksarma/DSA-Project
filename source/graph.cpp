#include "../include/graph.hpp"
#include <algorithm>
// #include "bfs-dfs-Traversal.hpp"

Edge::Edge() {}
Edge::Edge(Context &c, int id, int weight)
{
    this->id = id;
    this->weight = weight;
    weightText.setFont(c.getAssets().font1);
    weightText.setString(std::to_string(weight));
    weightText.setCharacterSize(30);
    weightText.setFillColor(sf::Color::Green);
    weightText.setLetterSpacing(1.2);
    // position will be set later when drawing line.
}

Vertex::Vertex(Context &c, const sf::Vector2f &pos) : guiVertex(c), edgeList(0)
{
    this->id = count;
    std::cout << id << " " << count << std::endl;
    std::cout << "Pos " << pos.x << " " << pos.y << std::endl;
    guiVertex.create(char(id + 65), c.getAssets().font1, c, pos);
    count++;

    // text part
    shortestVal.setFont(c.getAssets().font1);
    shortestVal.setFillColor(sf::Color::Yellow);
    shortestVal.setString("Inf");
    shortestVal.setCharacterSize(22);
    // 30 is radius of circleshape
    shortestVal.setPosition(pos.x, pos.y - 50);
    shortestVal.setOrigin(shortestVal.getGlobalBounds().width / 2.0f, shortestVal.getGlobalBounds().height / 2.0f);
}
// ~Vertex()
// {
//     count--;
// }
//getters
int Vertex::getID()
{
    return id;
}
// setters
void Vertex::setID(int index)
{
    id = index;
}
GUI::Vertex &Vertex::getGUIVertex()
{
    return guiVertex;
}

int Vertex::count = 0;
// ---------------Graph Class------------------

Graph::Graph(Context &c) : context(c)
{
}
bool Graph::isThisIDValid(int ID)
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

bool Graph::doesThisEdgeExist(int end1ID, int end2ID)
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

int Graph::getIndexFromID(int ID)
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

void Graph::addEdge(sf::Vector2f mousePos)
{
    //TODO: may be time efficiency in operations after storing index rather than id
    // is good.
    for (int i = 0; i < graph.size(); ++i)
    {
        sf::CircleShape &circle = graph[i].getGUIVertex().getCircle();
        if (circle.getGlobalBounds().contains(mousePos))
        {
            vertexForEdge.push_back(graph[i].getID());
            break;
        }
    }
    if (vertexForEdge.size() == 2)
    {
        sf::Vector2f posA = graph[getIndexFromID(vertexForEdge[0])].getGUIVertex().getCircle().getPosition();
        std::cout << "POSA = " << posA.x << ", " << posA.y << std::endl;
        sf::Vector2f posB = graph[getIndexFromID(vertexForEdge[1])].getGUIVertex().getCircle().getPosition();
        std::cout << "POSB = " << posB.x << ", " << posB.y << std::endl;
        int weight = sqrt(pow((posA.x - posB.x), 2) + pow((posA.y - posB.y), 2));
        weight = weight / 10;
        std::cout << "weight = " << weight << std::endl;
        if (vertexForEdge[0] != vertexForEdge[1])
        {
            if (!doesThisEdgeExist(vertexForEdge[0], vertexForEdge[1]))
            {
                graph[getIndexFromID(vertexForEdge[0])].edgeList.push_back(Edge(context, vertexForEdge[1], weight));
                graph[getIndexFromID(vertexForEdge[1])].edgeList.push_back(Edge(context, vertexForEdge[0], weight));
            }
        }
        vertexForEdge.clear();
    }
}

void Graph::printGraph()
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
std::vector<Vertex> &Graph::getGraph()
{
    return graph;
}

void Graph::resetAnimation()
{
    for (int i = 0; i < graph.size(); ++i)
    {
        graph[i].getGUIVertex().getCircle().setFillColor(sf::Color{0x14632EFF});
        isVisited[i] = false;
        visited_node_list.clear();
    }
    while (!queue.empty())
    {
        queue.pop();
    }
    while (!stack.empty())
    {
        stack.pop();
    }
}
void Graph::resetAnimation(bool isDijkstra)
{
    // for resetting dijkstra animation.
    for (int i = 0; i < graph.size(); ++i)
    {
        graph[i].getGUIVertex().getCircle().setFillColor(sf::Color{0x14632EFF});
        dValue[i] = 1000;
        graph[i].shortestVal.setString("Inf");
    }
    dPrevious.clear();
    dUnvisited.clear();
}

void Graph::addVertex(sf::Vector2f mousePos)
{
    if (!containIntheRange(mousePos))
    {
        graph.push_back(Vertex(context, mousePos));
    }
}

void Graph::draw(sf::RenderWindow &window, bool isAnimation)
{
    sf::Color col = sf::Color::White;
    auto x = graph;
    for (int i = 0; i < graph.size(); ++i)
    {
        auto it = graph[i].edgeList.begin();
        for (; it != graph[i].edgeList.end(); ++it)
        {

            if (isAnimation && isVisited[i] && isVisited[getIndexFromID(it->id)])
            {
                col = sf::Color::Red;
            }
            else
            {
                col = sf::Color::White;
            }
            drawLine(graph[i].getGUIVertex().getCircle().getPosition(), graph[getIndexFromID(it->id)].getGUIVertex().getCircle().getPosition(), window, col);
        }
    }
    for (int i = 0; i < graph.size(); ++i)
    {
        graph[i].getGUIVertex().draw(window);
    }
}

void Graph::draw(sf::RenderWindow &window, bool drawWeight, bool isDijkstra, bool isAnimateBtnActive, bool isShortestPath)
{
    for (int i = 0; i < graph.size(); ++i)
    {
        auto it = graph[i].edgeList.begin();
        for (; it != graph[i].edgeList.end(); ++it)
        {
            sf::Vector2f end1 = graph[i].getGUIVertex().getCircle().getPosition();
            sf::Vector2f end2 = graph[getIndexFromID(it->id)].getGUIVertex().getCircle().getPosition();
            if (!isShortestPath)
            {
                drawLine(end1, end2, window, sf::Color::White);
            }
            else
            {
                auto line = std::vector<int>({graph[i].getID(), it->id});
                auto x = std::find(shortestPath.begin(), shortestPath.end(), line);
                if (x != shortestPath.end())
                {
                    // this is one line in the path.
                    drawLine(end1, end2, window, sf::Color::Blue);
                }
                else
                {
                    drawLine(end1, end2, window, sf::Color::White);
                }
            }
            if (drawWeight)
            {
                it->weightText.setPosition((end1.x + end2.x) / 2.0f + 20, (end1.y + end2.y) / 2.0f);
                it->weightText.setOrigin(it->weightText.getGlobalBounds().width / 2.0f, it->weightText.getGlobalBounds().height / 2.0f);
                context.window.draw(it->weightText);
            }
        }
    }
    for (int i = 0; i < graph.size(); ++i)
    {
        graph[i].getGUIVertex().draw(window);
        if (isAnimateBtnActive)
        {
            window.draw(graph[i].shortestVal);
        }
    }
}

void Graph::drawLine(sf::Vector2f end1, sf::Vector2f end2, sf::RenderWindow &window, sf::Color col)
{
    float length = sqrt(pow((end1.x - end2.x), 2) + pow((end1.y - end2.y), 2));
    sf::RectangleShape line(sf::Vector2f(length, 2.0f));
    line.setPosition(end1);
    line.setFillColor(col);
    line.setOutlineColor(col);
    // for angle finding
    float angle = (atan(fabs(end2.y - end1.y) / fabs(end2.x - end1.x))) * 180 / 3.1415926;

    if ((end2.x - end1.x) <= 0)
    {
        if ((end2.y - end1.y) > 0)
        {
            angle = angle + (180 - 2 * angle);
        }
        else if ((end2.y - end1.y) < 0)
        {
            angle = angle + (180);
        }
        else
        {
            angle = -180;
        }
    }
    else
    {
        if ((end2.y - end1.y) < 0)
        {
            angle = -angle;
        }
    }
    line.setRotation(angle);
    auto rad = graph[0].getGUIVertex().getCircle().getRadius();

    /* sf::Vertex line[] = */
    /*     { */
    /*         sf::Vertex(sf::Vector2f(end1.x, end1.y)), */
    /*         sf::Vertex(sf::Vector2f(end2.x, end2.y))}; */
    /* window.draw(line, 2, sf::Lines); */
    window.draw(line);
}

void Graph::clearEdgeVector()
{
    // clears vertexForEdge
    vertexForEdge.clear();
}
void Graph::clear()
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

int Graph::containsVertex(sf::Vector2f pos)
{
    int id = -1;
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].getGUIVertex().getCircle().getGlobalBounds().contains(pos))
        {
            id = graph[i].getID();
            return id;
        }
    }
    return id;
}
void Graph::BFS(sf::Text &visited_node_order, bool isFirstNode, int id)
{
    std::cout << "BFS start" << std::endl;
    if (isFirstNode)
    {
        // first initialization
        queue.push(id);
        isVisited.resize(graph.size(), false);
        visited_node_list.push_back((char)(graph[getIndexFromID(id)].getID() + 65));
        visited_node_order.setString(visited_node_list);
        isVisited[getIndexFromID(id)] = true;
    }

    int x = queue.front();
    queue.pop();
    std::cout << x << std::endl;
    int currIndex = getIndexFromID(x);
    graph[currIndex].getGUIVertex().getCircle().setFillColor(sf::Color::Blue);
    if (!isVisited[currIndex])
    {
        visited_node_list.push_back((char)(graph[currIndex].getID() + 65));
        visited_node_order.setString(visited_node_list);
    }
    isVisited[currIndex] = true;
    std::cout << visited_node_list << std::endl;
    auto it = graph[currIndex].edgeList.begin();
    for (; it != graph[currIndex].edgeList.end(); ++it)
    {
        if (!isVisited[getIndexFromID(it->id)])
        {
            queue.push(it->id);
        }
    }
}

bool Graph::containIntheRange(sf::Vector2f mousePos)
{
    float dist, radi;

    for (int i = 0; i < graph.size(); i++)
    {
        sf::Vector2f center = graph[i].getGUIVertex().getCircle().getPosition();
        dist = sqrt(pow((mousePos.x - center.x), 2) + pow((mousePos.y - center.y), 2));
        radi = graph[i].getGUIVertex().getCircle().getRadius();
        if (dist < 2 * (radi + 2))
        {
            return true;
        }
    }
    return false;
}

void Graph::DFS(sf::Text &visited_node_order, bool isFirstNode, int id)
{
    std::cout << "DFS start" << std::endl;
    if (isFirstNode)
    {
        stack.push(id);
        isVisited.resize(graph.size(), false);
        isVisited[getIndexFromID(id)] = true;
        graph[getIndexFromID(id)].getGUIVertex().getCircle().setFillColor(sf::Color{0x00AAAAFF});
        visited_node_list.push_back((char)(graph[id].getID() + 65));
        visited_node_order.setString(visited_node_list);
        return;
    }
    bool isBreak = false;

    do
    {
        isBreak = false;
        int x = stack.top();

        int currIndex = getIndexFromID(x);
        auto it = graph[currIndex].edgeList.begin();
        for (; it != graph[currIndex].edgeList.end(); ++it)
        {
            if (!isVisited[getIndexFromID(it->id)])
            {
                if (!isVisited[it->id])
                {
                    visited_node_list.push_back((char)(graph[it->id].getID() + 65));
                    visited_node_order.setString(visited_node_list);
                }
                isVisited[getIndexFromID(it->id)] = true;
                stack.push(it->id);
                std::cout << it->id << std::endl;
                graph[getIndexFromID(it->id)].getGUIVertex().getCircle().setFillColor(sf::Color{0x00AAAAFF});
                isBreak = true;
                break;
            }
        }
        if (!isBreak)
        {
            stack.pop();
        }

    } while (!isBreak && !stack.empty());
    // if (graph.size() - 1 == getIndexFromID(it->id))
    // {
    // }
}

void Graph::deleteVertex(sf::Vector2f mousePos)
{
    int id = -1;
    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[i].getGUIVertex().getCircle().getGlobalBounds().contains(mousePos))
        {
            id = graph[i].getID();
            std::cout << " broken " << std::endl;
            std::cout << id << std::endl;
            break;
        }
    }

    for (int i = 0; i < graph.size(); i++)
    {
        auto it = graph[i].edgeList.begin();
        for (; it != graph[i].edgeList.end(); ++it)
        {
            if (it->id == id)
            {
                graph[i].edgeList.erase(it);
                break;
            }
        }
    }
    /* auto garg = remove(graph.begin(),graph.end(),graph[getIndexFromID(id)]); */
}

void printArray(const std::vector<int> &array)
{
    for (int i = 0; i < array.size(); ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
void Graph::Dijkstra(bool isFirstNode, int startID)
{
    std::cout << "dijkstra start" << std::endl;
    if (isFirstNode)
    {
        int index = getIndexFromID(startID);
        if (dValue.size() != graph.size())
        {
            // for very first animation where dvalue size is 0.
            dValue.resize(graph.size(), 1000);
        }
        dValue[index] = 0;
        dPrevious.resize(graph.size(), -1);
        dPrevious[index] = startID; // for starting node;
        for (int i = 0; i < graph.size(); ++i)
        {
            dUnvisited.push_back(graph[i].getID()); // pushing index not id
            // setting upper text in each vertices.
        }
        graph[index].shortestVal.setString("0");
    }

    int indexInUnvisited;
    auto minID = findMinID(indexInUnvisited);
    auto minIndex = getIndexFromID(minID);
    // set color in shortest path found node
    graph[minIndex].getGUIVertex().getCircle().setFillColor(sf::Color::Magenta);
    auto it = graph[minIndex].edgeList.begin();
    for (; it != graph[minIndex].edgeList.end(); ++it)
    {
        auto x = std::find(dUnvisited.begin(), dUnvisited.end(), it->id);
        if (x != dUnvisited.end())
        {
            // means this adjacent vertex/node is unvisited vertex
            auto i = getIndexFromID(it->id);
            if ((it->weight + dValue[minIndex]) < dValue[i])
            {
                dValue[i] = it->weight + dValue[minIndex];
                dPrevious[i] = minID;
                graph[i].shortestVal.setString(std::to_string(dValue[i]));
            }
        }
    }
    dUnvisited.erase(dUnvisited.begin() + indexInUnvisited);

    // std::cout << "dValue array" << std::endl;
    // printArray(dValue);
    // std::cout << "dValue end" << std::endl;
    // std::cout << "dPrevious array" << std::endl;
    // printArray(dPrevious);
    // std::cout << "dPrevious end" << std::endl;
}

int Graph::findMinID(int &index)
{
    int min;
    int minID;
    for (int i = 0; i < dUnvisited.size(); ++i)
    {
        if (i == 0)
        {
            min = dValue[getIndexFromID(dUnvisited[i])];
            minID = dUnvisited[i];
            index = i;
        }
        if (min > dValue[getIndexFromID(dUnvisited[i])])
        {
            min = dValue[getIndexFromID(dUnvisited[i])];
            minID = dUnvisited[i];
            index = i;
        }
    }
    return minID;
}

void Graph::setColorPath(int currID)
{
    // initially currID is clicked ID
    shortestPath.clear();
    while (true)
    {
        auto nextID = getNextVertexID(currID);
        if (nextID == currID)
        {
            break;
        }
        shortestPath.push_back({nextID, currID});
        shortestPath.push_back({currID, nextID});
        //TODO: check if this pushback works for {a,b} form
        currID = nextID;
    }
}
int Graph::getNextVertexID(int nowVertexID)
{
    auto nowIndex = getIndexFromID(nowVertexID);
    return dPrevious[nowIndex];
}