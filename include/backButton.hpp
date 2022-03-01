#pragma once
#include<SFML/Graphics.hpp>


class BackButton
{
  private:
      sf::Sprite backBtnSprite;
      sf::Texture backBtnTexture;
  public:
      BackButton()
      {
        backBtnTexture.loadFromFile("./assets/image/backBtn.png");
        backBtnSprite.setTexture(backBtnTexture);
        backBtnSprite.setPosition(50,50);
        backBtnSprite.setOrigin(backBtnTexture.getSize().x/2.f,backBtnTexture.getSize().y/2.f);
        backBtnSprite.setScale(0.5,0.5);
      }

      bool checkIfClicked(int posX, int posY)
      {
          if (backBtnSprite.getGlobalBounds().contains(posX, posY))
          {
              return true;
          }
          else
              return false;
      }

      void draw(sf::RenderWindow &window)
      {
          window.draw(backBtnSprite);
      }
  
  
      
};
