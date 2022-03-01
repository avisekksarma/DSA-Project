#include <SFML/Graphics.hpp>
#include "include/context.hpp"
#include "include/graph.hpp"
#include "include/entities.hpp"
#include "include/mainmenu.hpp"

int main()
{
    // Context context(sf::Vector2f(1000, 736));
    Context context(sf::Vector2f(1000,1000));
    // GUI::Vertex v1("0",context.getAssets().font1,context);
    // Graph graph(context);
    MainMenu menu(context);
    menu.run();
    return 0;
}
