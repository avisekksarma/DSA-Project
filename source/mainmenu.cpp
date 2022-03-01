#include "../include/mainmenu.hpp"

MainMenu::MainMenu(Context &c) : context(c), bfsDfsBtn(c), dijkstraBtn(c)
{
    init();
}
MainMenu::~MainMenu() {}
void MainMenu::run()
{
    while (context.window.isOpen())
    {
        sf::Event event;
        processEvents(event);
        renderWindow();
    }
}
void MainMenu::init()
{
    bfsDfsBtn.create("Traversal", context.getWinSize().x / 2.0f, context.getWinSize().y / 2.0f);
    dijkstraBtn.create("Dijkstra", context.getWinSize().x / 2.0f, context.getWinSize().y / 2.0f - 100);
    headingTexture.loadFromFile("./assets/image/title.png");
    headingSprite.setTexture(headingTexture);
    headingSprite.setPosition(context.getWinSize().x / 2.f, 100);
    headingSprite.setOrigin(headingSprite.getGlobalBounds().width / 2.f, headingSprite.getGlobalBounds().height / 2.f);
    headingSprite.setScale(0.75f, 0.75f);
}
void MainMenu::processEvents(sf::Event &event)
{
    while (context.window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            context.window.close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (bfsDfsBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    Screen::Traversal traversal(context);
                    traversal.run();
                }
                else if (dijkstraBtn.checkIfBtnClicked(event.mouseButton.x, event.mouseButton.y))
                {
                    Screen::DijkstraTraversal dijkstraTraversal(context);
                    dijkstraTraversal.run();
                }
            }
        }
    }
}
void MainMenu::renderWindow()
{
    context.window.clear(sf::Color{0x16191EFF});
    bfsDfsBtn.draw(context.window);
    context.window.draw(headingSprite);
    dijkstraBtn.draw(context.window);
    // graph.draw(context.window);
    context.window.display();
}
void MainMenu::update()
{
}
