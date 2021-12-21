#include "combat.h"

#define DEBUG // A commenter pour enlever les commentaires

// Flags for key pressed
bool upFlag    = false;
bool downFlag  = false;
bool leftFlag  = false;
bool rightFlag = false;
bool returnFlag = false;

sf::Font NiceFont;



void aff_combat(sf::RenderWindow* window){
  static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
  static char last_pressed = UP, blinking_way = 1; 
  static int last_pos = 0;

  // On positionne les formes ici
  sf::RectangleShape Battle_outline(sf::Vector2f(1142.f, 199.f));
  Battle_outline.setFillColor(sf::Color(255,255,255,100));
  Battle_outline.setOutlineThickness(5.f);
  Battle_outline.setOutlineColor(sf::Color(sf::Color::Red));
  Battle_outline.setPosition(sf::Vector2f(5.f, 499.f));
  classetest test;
  sf::Text Atq[4];
  Atq[0].setPosition(sf::Vector2f(20.f, 510.f));
  Atq[1].setPosition(sf::Vector2f(600.f, 510.f));
  Atq[2].setPosition(sf::Vector2f(20.f, 610.f));
  Atq[3].setPosition(sf::Vector2f(600.f, 610.f));

  #ifdef DEBUG
  std::cout << "up = " << upFlag << "down = " << downFlag << "right" << rightFlag << "left=" << leftFlag << std::endl;
  #endif

  window->clear();
  aff_background(window);
  window->draw(Battle_outline);
  for(int i = 0; i < 4; i++){
    if(i != last_pos){
      Atq[i].setFont(NiceFont);
      Atq[i].setString(test.get_atq(i));
      Atq[i].setCharacterSize(40);
      Atq[i].setFillColor(sf::Color(R,G,B,255));
      window->draw(Atq[i]);
    }
  }

  if(upFlag){
    Atq[last_pos].setFillColor(sf::Color(R,G,B,255));
    switch(last_pos){
      case 0: break; // On était deja en haut donc on bouge pas 
      case 1: break; // On était deja en haut donc on bouge pas
      case 2: last_pos = 0; break; // On monte d'une case
      case 3: last_pos = 1; break; // On monte d'une case
    }
    last_pressed = UP;
  }else if(downFlag){
    Atq[last_pos].setFillColor(sf::Color(R,G,B,255));
    switch(last_pos){
      case 0: last_pos = 2; break;
      case 1: last_pos = 3; break;
      case 2: break;
      case 3: break;
    }
    last_pressed = DOWN;
  }else if(rightFlag){
    Atq[last_pos].setFillColor(sf::Color(R,G,B,255));
    switch (last_pos){
    case 0: last_pos = 1; break;
    case 1: break;
    case 2: last_pos = 3; break;
    case 3: break;
    }
    last_pressed = RIGHT;
  }else if(leftFlag){
    Atq[last_pos].setFillColor(sf::Color(R,G,B,255));
    switch(last_pos){
      case 0: break;
      case 1: last_pos = 0; break;
      case 2: break;
      case 3: last_pos = 2; break;
    }
    last_pressed = LEFT;
  }else if(returnFlag){
    
  }

   // On fait clignotter le texte!
  if(blinking_way){ // Blinking_way = 1 donc on baisse la valeur
    if(A >= 15){
      A -= 5;
    }else{
      blinking_way = 0;
    }
  }else{
    if(A <= 240){
      A += 5;
    }else{
      blinking_way = 1;
    }
  }
  #ifdef DEBUG
  std::cout<< " last_pos= " << (int)last_pos << " A= " << (int)A<<" last_pressed= " << (int)last_pressed<<std::endl;
  #endif
  Atq[last_pos].setFont(NiceFont);
  Atq[last_pos].setString(test.get_atq(last_pos));
  Atq[last_pos].setCharacterSize(40);
  Atq[last_pos].setFillColor(sf::Color(R,G,B,A));
  window->draw(Atq[last_pos]);
  window->display();
}



void handleEvents(sf::Event event){
  if (event.type == sf::Event::KeyPressed){
    switch (event.key.code){
        case sf::Keyboard::Up :     upFlag=true; break;
        case sf::Keyboard::Down:    downFlag=true; break;
        case sf::Keyboard::Left:    leftFlag=true; break;
        case sf::Keyboard::Right:   rightFlag=true; break;
        case sf::Keyboard::Return:  returnFlag=true; break;
        default : break;
    }
  }

  // Si on relache la touche
  if (event.type == sf::Event::KeyReleased){
    switch (event.key.code){
    // Process the up, down, left and right keys
    case sf::Keyboard::Up :     upFlag=false; break;
    case sf::Keyboard::Down:    downFlag=false; break;
    case sf::Keyboard::Left:    leftFlag=false; break;
    case sf::Keyboard::Right:   rightFlag=false; break;
    case sf::Keyboard::Return:  returnFlag=false; break;
    default : break;
    }
  }
}

int main(int argc, char* argv[]){
  sf::RenderWindow window(sf::VideoMode(1152,704),
    "Petage de gueule en regle des pollueurs");
  NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");

  aff_background(&window);

  while (window.isOpen())
  {
    // on gère les évènements
    sf::Event event;

    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
        window.close();
      }
      handleEvents(event);
    }
    //ScreenMutex.unlock();
    aff_combat(&window);
  }
  return 0;
}

