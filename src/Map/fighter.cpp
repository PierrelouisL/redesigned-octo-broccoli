#include "fighter.h"


fighter::fighter(){
    atk_name[0] = "Soulevage en regle";
    atk_name[1] = "Pleure";
    atk_name[2] = "HOW DARE YOU";
    atk_name[3] = "Fuir";

    HP = 200;
    HP_base = HP;

    atk_dmg[0] = 50;
    atk_dmg[1] = 2;
    atk_dmg[2] = 100;
    atk_dmg[3] = -1;

   atk_desc[0] = sf::String("Le souleve avec une puissance phénomenale de 50PV");
   atk_desc[1] = sf::String("0"); // Deuxième ligne atq0
   atk_desc[2] = sf::String("Vous pleurez comme une victime ce qui fait perdre 2 HP a"); // <<<---- TAILLE MAX 
   atk_desc[3] = sf::String("l'adversaire par compassion..."); // Deuxième ligne atq1
   atk_desc[4] = sf::String("HOW DAARE YOU?!");
   atk_desc[5] = sf::String("2"); // Deuxième ligne atq2
   atk_desc[6] = sf::String("Vous fuiez comme un lâche");
   atk_desc[7] = sf::String("3"); // Deuxième ligne atq3

   alive = true;
}

/**
 * @brief perso = 0 for player, 0 for bot, 1 for Donald Trump
 * 
 * @param perso 
 */
fighter::fighter(int perso){
    switch(perso){
        case 0:
            atk_name[0] = "Soulevage en regle";
            atk_name[1] = "Pleure";
            atk_name[2] = "HOW DARE YOU";
            atk_name[3] = "Fuir";

            HP = 200;
            HP_base = HP;

            atk_dmg[0] = 50;
            atk_dmg[1] = 2;
            atk_dmg[2] = 100;
            atk_dmg[3] = -1;

            atk_desc[0] = sf::String("Le souleve avec une puissance phénomenale de 50PV");
            atk_desc[1] = sf::String("0"); // Deuxième ligne atq0
            atk_desc[2] = sf::String("Vous pleurez comme une victime ce qui fait perdre 2 HP a"); // <<<---- TAILLE MAX 
            atk_desc[3] = sf::String("l'adversaire par compassion..."); // Deuxième ligne atq1
            atk_desc[4] = sf::String("HOW DAARE YOU?!");
            atk_desc[5] = sf::String("2"); // Deuxième ligne atq2
            atk_desc[6] = sf::String("Vous fuiez comme un lâche");
            atk_desc[7] = sf::String("3"); // Deuxième ligne atq3

            alive = true;
            break;
        case 1:
            atk_name[0] = "Soulevage en regle";
            atk_name[1] = "Pleure";
            atk_name[2] = "HOW DARE YOU";
            atk_name[3] = "Fuir";

            HP = 200;
            HP_base = HP;

            atk_dmg[0] = 50;
            atk_dmg[1] = 2;
            atk_dmg[2] = 100;
            atk_dmg[3] = -1;

            atk_desc[0] = sf::String("Le souleve avec une puissance phénomenale de 50PV");
            atk_desc[1] = sf::String("0"); // Deuxième ligne atq0
            atk_desc[2] = sf::String("Vous pleurez comme une victime ce qui fait perdre 2 HP a"); // <<<---- TAILLE MAX 
            atk_desc[3] = sf::String("l'adversaire par compassion..."); // Deuxième ligne atq1
            atk_desc[4] = sf::String("HOW DAARE YOU?!");
            atk_desc[5] = sf::String("2"); // Deuxième ligne atq2
            atk_desc[6] = sf::String("Vous fuiez comme un lâche");
            atk_desc[7] = sf::String("3"); // Deuxième ligne atq3

            alive = true;
            break;

        case 2:
            atk_name[0] = "Soulevage en regle";
            atk_name[1] = "Pleure";
            atk_name[2] = "HOW DARE YOU";
            atk_name[3] = "Fuir";

            HP = 200;
            HP_base = HP;

            atk_dmg[0] = 50;
            atk_dmg[1] = 2;
            atk_dmg[2] = 100;
            atk_dmg[3] = -1;

            atk_desc[0] = sf::String("Le souleve avec une puissance phénomenale de 50PV");
            atk_desc[1] = sf::String("0"); // Deuxième ligne atq0
            atk_desc[2] = sf::String("Vous pleurez comme une victime ce qui fait perdre 2 HP a"); // <<<---- TAILLE MAX 
            atk_desc[3] = sf::String("l'adversaire par compassion..."); // Deuxième ligne atq1
            atk_desc[4] = sf::String("HOW DAARE YOU?!");
            atk_desc[5] = sf::String("2"); // Deuxième ligne atq2
            atk_desc[6] = sf::String("Vous fuiez comme un lâche");
            atk_desc[7] = sf::String("3"); // Deuxième ligne atq3

            alive = true;
            break;
    }
}

fighter::fighter(TileCharacter& character): fighter(){
    this->setOrigin(character.getOrigin());
    this->setPosition(character.getPosition());
    this->setScale(character.getScale());
    this->setRotation(character.getRotation());

    alive = true;
}

sf::String fighter::get_atk(int nb){
    return atk_name[nb];
}

sf::String fighter::get_Desc_Atq(int nb){
    return atk_desc[nb];
}

int fighter::get_dmg_atq(int nb){
    return this->atk_dmg[nb];
}

int fighter::get_PV(){
    return HP;
}

int fighter::get_pourcent_PV(){
    return 100-(int)(((float)(HP_base-HP)/(float)HP_base)*100);
}

void fighter::subit_atq(int dmg){
    HP -= dmg;
}

sf::String fighter::phrase_fin(int issue_du_match){
    if(issue_du_match == VICTOIRE)
        return "A mort la planete!";
    else   
        return "D'accord je vais faire attention avec la planete.";
}

void fighter::aff_fin(sf::RenderWindow* window, int issue_du_match){
    static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");
    sf::Text Msg_Fin;
    Msg_Fin.setPosition(sf::Vector2f(20.f, 510.f));
    Msg_Fin.setFont(NiceFont);
    Msg_Fin.setString(phrase_fin(issue_du_match));
    Msg_Fin.setCharacterSize(40);
    Msg_Fin.setFillColor(sf::Color(R, G, B, A));
    window->draw(Msg_Fin);
}

void fighter::aff_message(sf::RenderWindow* win, int nb_atq){
    static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");
    sf::Text Msg_Atq[2];
    Msg_Atq[0].setPosition(sf::Vector2f(20.f, 510.f));
    Msg_Atq[0].setFont(NiceFont);
    Msg_Atq[0].setString(this->get_Desc_Atq(2*(nb_atq)));
    Msg_Atq[0].setCharacterSize(40);
    Msg_Atq[0].setFillColor(sf::Color(R, G, B, A));
    Msg_Atq[1].setPosition(sf::Vector2f(20.f, 550.f));
    Msg_Atq[1].setFont(NiceFont);
    Msg_Atq[1].setString(this->get_Desc_Atq(2*(nb_atq)+1));
    Msg_Atq[1].setCharacterSize(40);
    Msg_Atq[1].setFillColor(sf::Color(R, G, B, A));
    win->draw(Msg_Atq[0]);
    win->draw(Msg_Atq[1]);
}
