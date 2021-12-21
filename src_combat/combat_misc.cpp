#include "combat.h"


void aff_background(sf::RenderWindow* window){
  sf::Texture backgroundTexture;
  backgroundTexture.loadFromFile("images/bacgroundcombattemp.png");
  sf::Sprite background(backgroundTexture);
  //sf::Vector2u size = backgroundTexture.getSize();
  //background.setOrigin(size.x/2, size.y/2);
  window->draw(background);
}


void StartCombatMsgThread(sf::RenderWindow* window){
  sf::Thread thread(std::bind(&aff_combat,window));
  thread.launch();
}